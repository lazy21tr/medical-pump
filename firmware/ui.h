/* 
 * File:   ui.h
 * Author: msuzer
 *
 * Created on 09.04.2014, 22:06
 */

#ifndef USER_INTERFACE_H
#define	USER_INTERFACE_H

    typedef enum {
        PRINT_TEMPERATURE = 'A',
        PRINT_SENSOR_STATE,
        PRINT_BALANCER1,
        PRINT_BALANCER2,
        PRINT_ENCODER,
        PRINT_RFID1,
        PRINT_RFID2,
        PRINT_FIRMWARE_VERSION,
        RUN_PERISTALTIC_MOTOR,
        RUN_STEPPER_MOTOR,
        FILLUP_LARGE_BAG,
        FILLUP_SMALL_BAG,
        RESET_STEP_ENCODER,
        RESET_TARE_BALANCER1,
        RESET_TARE_BALANCER2,
        CALIBRATE_BALANCER1,
        CALIBRATE_BALANCER2,
        SET_OFFSET_BALANCER1,
        SET_OFFSET_BALANCER2,
        SET_GAIN_BALANCER1,
        SET_GAIN_BALANCER2,
        RESET_BALANCER1,
        RESET_BALANCER2
    } UserCommand;

    void CheckUpUserInstruction(void);

#endif	/* USER_INTERFACE_H */
