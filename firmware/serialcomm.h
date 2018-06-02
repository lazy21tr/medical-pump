/* 
 * File:   serialcomm.h
 * Author: msuzer
 *
 * Created on 09 March 2014, 22:06
 */

#ifndef SERIAL_COMM_H
#define	SERIAL_COMM_H

#include <GenericTypeDefs.h>
#include "devapi.h"

    typedef struct {
        BOOL messageReceived;
        char * messageBody;
        void (*printf)(char *, ...);
        void (*println)(char *);
    } pcPort;

    typedef struct {
        BOOL messageReceived;
        char * messageBody;
        void (*sendMessage)(void);
    } stepperPort;

    typedef struct {
        char devID;
        void (*sendMessage)(RFID_DEVICE, char *);
    } rfidPort;

    typedef struct {
        char devID;
        BOOL messageReceived;
        char * messageBody;
        void (*sendMessage)(BALANCER_DEVICE);
    } balancerPort;

    typedef struct {
        pcPort pc;
        stepperPort stepper;
        rfidPort rfid;
        balancerPort balancer;
        char * transmitBuffer;
    } SerialPort;

    void init_serial_comm(void);
    void sendMessageToStepper(void);
    void sendMessageToRFID(RFID_DEVICE dev, char*);
    void sendMessageToBalancer(BALANCER_DEVICE dev);

#endif	/* SERIAL_COMM_H */
