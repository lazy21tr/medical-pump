/*
 * File:   main.c
 * Author: msuzer
 *
 * Created on 08 March 2014, 00:18
 */

#include "serialcomm.h"
#include "ui.h"
#include "hal.h"
#include <stdlib.h>

extern SerialPort COM1;
extern DEVICE_STATE_VALUES dsv;
unsigned long int tick = 0;

void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt(void) {
    static unsigned int count = 0;

    if (++count == 5 * CPU_USER_TASK_FREQ) {
        ++tick;
        count = 0;
    }

    read_sensors();
    blink_board_alive_indicator();

    if (ADC_Module_Int_Flag){
        dsv.trimPOTValue = min(ReadADC10(0), PWM_PERIOD);
        dsv.tempSensorValue = ReadADC10(1);
        ADC_Module_Int_Flag = 0;
    }

    T2_Clear_Intr_Status_Bit;
}

int main(void) {
    static int OldSensorValues = 0;
    
    init_mcu_core();
    init_peripherals();
    init_serial_comm();
    init_pi_controller();

    COM1.pc.println("Live!");
    DELAY_MS(200);
    acquireStepSensors();
    while (TRUE) {
        DELAY_MS(100);
        if (OldSensorValues != dsv.ExtSensorValues.Val) {
            COM1.pc.printf("Sens: %03X", dsv.ExtSensorValues.Val & 0x3FF);
            OldSensorValues = dsv.ExtSensorValues.Val;
        }
//        if (dsv.trimPOTValue != PWMDutyCycleReg){
//            PWMDutyCycleReg = dsv.trimPOTValue;
//        }
        CheckUpUserInstruction();
        CheckUpPeerDeviceResponse();
    }

    return 0;
}
