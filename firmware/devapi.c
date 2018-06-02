#include "devapi.h"
#include "serialcomm.h"
#include "hal.h"
#include <stdlib.h>
#include <stdio.h>

extern unsigned long int tick;
extern SerialPort COM1;
DEVICE_STATE_VALUES dsv;
PI_CONTROLLER pic;
RegDat response, temp;

void init_pi_controller(void) {
    dsv.ExtSensorValues.Val = 0;
    pic.controllerON = FALSE;
    pic.disableTwoWay = FALSE;
    pic.kp = 32;
    pic.olderror = 0;
    pic.piLoop = pi_controller_loop;
}

void run_peristaltic_motor(long int speed) {
    if (speed <= 0) {
        SetPumpMotorDirection(CCW);
        speed = -speed;
    } else {
        SetPumpMotorDirection(CW);
    }
    //PWMDutyCycleReg = min(speed, PWM_PERIOD);
    PWMDutyCycleReg = min(speed, PWM_DUTY_CYCLE);
}

void commandStepperDriver(PeerDeviceCommand command, unsigned long int val) {
    temp.dword = val;
    COM1.transmitBuffer[0] = command;
    COM1.transmitBuffer[1] = temp.bytes.top;
    COM1.transmitBuffer[2] = temp.bytes.high;
    COM1.transmitBuffer[3] = temp.bytes.mid;
    COM1.transmitBuffer[4] = temp.bytes.low;
    COM1.stepper.sendMessage();
}

void run_stepper_motor(int speed, unsigned int steps) {
    temp.words.high = speed;
    temp.words.low = steps;
    dsv.StepMotorDirection = TRUE;
    if (speed < 0)
        dsv.StepMotorDirection = FALSE;
    commandStepperDriver(RUN_STEPPER, temp.dword);
}

void commandBalancerDriver(BALANCER_DEVICE dev, PeerDeviceCommand command, unsigned long int val) {
    temp.dword = val;
    COM1.transmitBuffer[0] = command;
    COM1.transmitBuffer[1] = temp.bytes.top;
    COM1.transmitBuffer[2] = temp.bytes.high;
    COM1.transmitBuffer[3] = temp.bytes.mid;
    COM1.transmitBuffer[4] = temp.bytes.low;
    COM1.balancer.sendMessage(dev);
}

void pi_controller_loop(int currentValue) {
    pic.olderror = pic.error;
    pic.error = pic.setValue - currentValue;
    pic.derror = pic.error - pic.olderror;
    pic.output = pic.error << 5;

    if (!pic.disableTwoWay) {
        if (pic.output < 0)
            pic.output = 0;
    }

    if (abs(pic.output) < 35)
        pic.output = 0;
    
    run_peristaltic_motor(pic.output);
    if (pic.output == 0) {
        pic.controllerON = FALSE;
        COM1.pc.printf("Filled: %d ", pic.setValue);
    }
}

void ParseStepperResponse(void) {
    PeerDeviceCommand id = COM1.stepper.messageBody[0];
    response.bytes.top = COM1.stepper.messageBody[1];
    response.bytes.high = COM1.stepper.messageBody[2];
    response.bytes.mid = COM1.stepper.messageBody[3];
    response.bytes.low = COM1.stepper.messageBody[4];
    switch (id) {
        case PRINT_ENCODER_COUNTER:
            dsv.StepEncoderValue = response.dword;
            COM1.pc.printf("ENC1: %06d", dsv.StepEncoderValue);
            break;
        case PRINT_EXT_SENSOR_STATE:
            dsv.ExtSensorValues.Val &= 0x1F;
            dsv.ExtSensorValues.Val |= response.words.low << 5;
            COM1.pc.printf("Sens: %03X", dsv.ExtSensorValues.Val & 0x3FF);
            break;
        case TASK_EXEC_COMPLETE:
            if (dsv.StepMotorDirection)
                COM1.pc.println("ENJFW");
            else
                COM1.pc.println("ENJBW");
            break;
        case BALANCER_OVERFLOW:
            //COM1.pc.println("Err!: UnderFlow");
            break;
        case BALANCER_OVERFLOW + 1:
            //COM1.pc.println("Err!: OverFlow");
            break;
        default:
            COM1.pc.println("Err!: Unknown Response");
            break;
    }
}

void ParseBalancerResponse(void) {
    PeerDeviceCommand id = COM1.balancer.messageBody[0];
    response.bytes.top = COM1.balancer.messageBody[1];
    response.bytes.high = COM1.balancer.messageBody[2];
    response.bytes.mid = COM1.balancer.messageBody[3];
    response.bytes.low = COM1.balancer.messageBody[4];
    switch (id) {
        case PRINT_WEIGHT_ONCE:
            if (COM1.balancer.devID == BALANCER1) {
                dsv.Balancer1Value = response.dword;
                if (pic.controllerON){
                    pic.piLoop((int)(dsv.Balancer1Value / 100));
                    if (!pic.controllerON) {
                        acquireBalancerValue(BALANCER1);
                    }
                }
                sprintf(COM1.transmitBuffer, "BAL1: %08ld ", dsv.Balancer1Value);
            } else {
                dsv.Balancer2Value = response.dword;
                if (pic.controllerON){
                    pic.piLoop((int)(dsv.Balancer2Value / 100));
                    if (!pic.controllerON) {
                        acquireBalancerValue(BALANCER2);
                    }
                }
                sprintf(COM1.transmitBuffer, "BAL2: %08ld ", dsv.Balancer2Value);
            }
            COM1.transmitBuffer[14] = COM1.transmitBuffer[13];
            COM1.transmitBuffer[13] = COM1.transmitBuffer[12];
            COM1.transmitBuffer[12] = '.';
            COM1.pc.println(COM1.transmitBuffer);
            break;
        case BALANCER_OVERFLOW:
            if (COM1.balancer.devID == BALANCER1)
                COM1.pc.println("BAL1: 8888.88");
            else
                COM1.pc.println("BAL2: 8888.88");
            break;
        case TASK_EXEC_COMPLETE:
            COM1.pc.println("Done!");
            break;
        case UNKNOWN_COMMAND:
            COM1.pc.println("Errr: Unknown Command");
            break;
        default:
            COM1.pc.println("Errr: Unknown Response");
            break;
    }
}

void CheckUpPeerDeviceResponse(void) {
    if (COM1.stepper.messageReceived) {
        ParseStepperResponse();
        COM1.stepper.messageReceived = FALSE;
    } else if (COM1.balancer.messageReceived) {
        ParseBalancerResponse();
        COM1.balancer.messageReceived = FALSE;
    }
}
