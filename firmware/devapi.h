/* 
 * File:   devapi.h
 * Author: msuzer
 *
 * Created on 31 12 2014, 10:47
 */

#ifndef DEVAPI_H
#define	DEVAPI_H

#include <GenericTypeDefs.h>

    typedef enum {
        RFID1,
        RFID2
    } RFID_DEVICE;

    typedef enum {
        BALANCER1,
        BALANCER2
    } BALANCER_DEVICE;

    typedef enum {
        PRINT_WEIGHT_ONCE = 'A',
        PRINT_WEIGHT_CONT,
        PRINT_ENCODER_COUNTER,
        PRINT_EXT_SENSOR_STATE,
        RESET_ENCODER_REG,
        RESET_TARE,
        RESET_BALANCER,
        PREPARE_FOR_CALIBRATION,
        SET_OFFSET_REG,
        SET_GAIN_REG,
        RUN_STEPPER,
        TASK_EXEC_COMPLETE,
        BALANCER_OVERFLOW,
        UNKNOWN_COMMAND
    } PeerDeviceCommand;

    typedef union {
        signed long int dword;
        struct {
            int low;
            int high;
        } words;
        struct {
            unsigned char low;
            unsigned char mid;
            unsigned char high;
            unsigned char top;
        } bytes;
    } RegDat;

    typedef struct {
        BOOL StepMotorDirection;
        UINT16_VAL ExtSensorValues;
        long int Balancer1Value;
        long int Balancer2Value;
        int StepEncoderValue;
        unsigned int trimPOTValue;
        unsigned int tempSensorValue;
    } DEVICE_STATE_VALUES;

    typedef struct {
        BOOL controllerON;
        BOOL disableTwoWay;
        int kp;
        int setValue;
        int error;
        int olderror;
        int derror;
        int output;
        void (*piLoop)(int);
    } PI_CONTROLLER;

    void init_pi_controller(void);
    void pi_controller_loop(int);
    void CheckUpPeerDeviceResponse(void);
    void run_peristaltic_motor(long int speed);
    void run_stepper_motor(int speed, unsigned int steps);
    void commandStepperDriver(PeerDeviceCommand command, unsigned long int val);
    void commandBalancerDriver(BALANCER_DEVICE dev, PeerDeviceCommand command, unsigned long int val);

    #define acquireBalancerValue(dev)   commandBalancerDriver(dev, PRINT_WEIGHT_ONCE, 0)
    #define acquireBalancerValueCont(dev)   commandBalancerDriver(dev, PRINT_WEIGHT_CONT, 0)
    #define resetBalancer(dev)          commandBalancerDriver(dev, RESET_BALANCER, 0)
    #define resetTareBalancer(dev)      commandBalancerDriver(dev, RESET_TARE, 0)
    #define prepareBalancerCalibration(dev) commandBalancerDriver(dev, PREPARE_FOR_CALIBRATION, 0)
    #define setOffsetBalancer(dev, val) commandBalancerDriver(dev, SET_OFFSET_REG, val)
    #define setGainBalancer(dev, val)   commandBalancerDriver(dev, SET_GAIN_REG, val)
    #define resetStepEncoder()          commandStepperDriver(RESET_ENCODER_REG, 0)
    #define acquireStepEncoder()        commandStepperDriver(PRINT_ENCODER_COUNTER, 0)
    #define acquireStepSensors()        commandStepperDriver(PRINT_EXT_SENSOR_STATE, 0)

#endif	/* DEVAPI_H */
