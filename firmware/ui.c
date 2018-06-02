#include "ui.h"
#include "hal.h"
#include "serialcomm.h"
#include "devapi.h"
#include <stdio.h>

extern SerialPort COM1;
extern DEVICE_STATE_VALUES dsv;
extern PI_CONTROLLER pic;

int initRFIDDevice;
int motorSpeed;
unsigned int tempInCelcius, steps;
unsigned long int offsetVal, gainVal;

static void ParseAndApplyCommand(UserCommand command, char * param) {
    switch (command) {
        case PRINT_TEMPERATURE:
            tempInCelcius = dsv.tempSensorValue;
            tempInCelcius *= 41;
            tempInCelcius >>= 7;
            tempInCelcius -= 50;
            COM1.pc.printf("Temp: %02dC", tempInCelcius);
            break;
        case PRINT_SENSOR_STATE:
            acquireStepSensors();
            COM1.pc.printf("Sens: %03X", dsv.ExtSensorValues.Val & 0x3FF);
            break;
        case PRINT_BALANCER1:
            acquireBalancerValue(BALANCER1);
            break;
        case PRINT_BALANCER2:
            acquireBalancerValue(BALANCER2);
            break;
        case PRINT_ENCODER:
            acquireStepEncoder();
            break;
        case PRINT_RFID1:
            COM1.rfid.sendMessage(RFID1, param);
            break;
        case PRINT_RFID2:
            COM1.rfid.sendMessage(RFID2, param);
            break;
        case PRINT_FIRMWARE_VERSION:
            COM1.pc.printf("FVer: %d", FIRMWARE_VERSION);
            break;
        case RUN_PERISTALTIC_MOTOR:
            sscanf(&param[1], "%d", &motorSpeed);
            run_peristaltic_motor(motorSpeed);
            break;
        case RUN_STEPPER_MOTOR:
            if (sscanf(param, "%d%d", &motorSpeed, &steps) == 2)
                run_stepper_motor(motorSpeed, steps);
            else
                COM1.pc.println("Err!: Incorrect Params!");
            break;
        case FILLUP_LARGE_BAG:
            if (param[0] == 'U') {
                pic.disableTwoWay = TRUE;
            } else {
                pic.disableTwoWay = FALSE;
            }
           
            sscanf(&param[1], "%d", &pic.setValue);
            pic.controllerON = TRUE;
            acquireBalancerValueCont(BALANCER1);
            break;
        case FILLUP_SMALL_BAG:
            if (param[0] == 'U') {
                pic.disableTwoWay = TRUE;
            } else {
                pic.disableTwoWay = FALSE;
            }
            sscanf(&param[1], "%d", &pic.setValue);
            pic.controllerON = TRUE;
            acquireBalancerValueCont(BALANCER2);
            break;
        case RESET_STEP_ENCODER:
            resetStepEncoder();
            acquireStepEncoder();
            break;
        case RESET_TARE_BALANCER1:
            resetTareBalancer(BALANCER1);
            break;
        case RESET_TARE_BALANCER2:
            resetTareBalancer(BALANCER2);
            break;
        case CALIBRATE_BALANCER1:
            prepareBalancerCalibration(BALANCER1);
            break;
        case CALIBRATE_BALANCER2:
            prepareBalancerCalibration(BALANCER2);
            break;
        case SET_OFFSET_BALANCER1:
            if (sscanf(param, "%ld", &offsetVal) == 1){
                setOffsetBalancer(BALANCER1, offsetVal);
            }
            break;
        case SET_OFFSET_BALANCER2:
            if (sscanf(param, "%ld", &offsetVal) == 1){
                setOffsetBalancer(BALANCER2, offsetVal);
            }
            break;
        case SET_GAIN_BALANCER1:
            if (sscanf(param, "%ld", &gainVal) == 1){
                setGainBalancer(BALANCER1, gainVal);
            }
            break;
        case SET_GAIN_BALANCER2:
            if (sscanf(param, "%ld", &gainVal) == 1){
                setGainBalancer(BALANCER2, gainVal);
            }
            break;
        case RESET_BALANCER1:
            resetBalancer(BALANCER1);
            COM1.pc.println("Done!");
            break;
        case RESET_BALANCER2:
            resetBalancer(BALANCER2);
            COM1.pc.println("Done!");
            break;
        default:
            COM1.pc.println("Err!: Unknown Command!");
            break;
    }
}

void CheckUpUserInstruction(void) {
    if (COM1.pc.messageReceived) {
        ParseAndApplyCommand(COM1.pc.messageBody[0], &(COM1.pc.messageBody[1]));
        COM1.pc.messageReceived = FALSE;
    }
}
