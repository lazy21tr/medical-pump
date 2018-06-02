/*
 * File:   serialcomm.c
 * Author: msuzer
 * Created on 08 March 2014
 */

#include <stdarg.h>
#include <stdio.h>
#include "serialcomm.h"
#include "hal.h"

SerialPort COM1;

#define SIZE_OF_PC_MESSAGE          32
#define SIZE_OF_STEPPER_MESSAGE     5
#define SIZE_OF_RFID_MESSAGE        32
#define SIZE_OF_BALANCER_MESSAGE    5
#define SIZE_OF_PREAMBLE            5
#define SIZE_OF_ENDM                5

char preamble_string[] = "$00RF";
char eof_message_string[] = "<EOM>";

char uart1ReceiveBuffer[SIZE_OF_PC_MESSAGE];
char uart2ReceiveBuffer[SIZE_OF_STEPPER_MESSAGE];
char uart3ReceiveBuffer[SIZE_OF_RFID_MESSAGE + SIZE_OF_ENDM + 1];
char uart4ReceiveBuffer[SIZE_OF_BALANCER_MESSAGE];

char pcMessageString[SIZE_OF_PC_MESSAGE + 1];
char stepperMessageString[SIZE_OF_STEPPER_MESSAGE];
char balancerMessageString[SIZE_OF_BALANCER_MESSAGE];

char transmitBuffer[SIZE_OF_PC_MESSAGE + 1];

void uart_printf(char * format, ...);
void uart_println(char * message);

void UART_RX_Interrupt_Handler1(char rbyte);
void UART_RX_Interrupt_Handler2(char rbyte);
void UART_RX_Interrupt_Handler3(char rbyte);
void UART_RX_Interrupt_Handler4(char rbyte);

void init_serial_comm(void) {
    COM1.transmitBuffer = transmitBuffer;
    COM1.pc.messageReceived = FALSE;
    COM1.pc.messageBody = pcMessageString;
    COM1.pc.printf = uart_printf;
    COM1.pc.println = uart_println;
    COM1.stepper.messageReceived = FALSE;
    COM1.stepper.messageBody = stepperMessageString;
    COM1.stepper.sendMessage = sendMessageToStepper;
    COM1.rfid.devID = RFID1;
    COM1.rfid.sendMessage = sendMessageToRFID;
    COM1.balancer.devID = BALANCER1;
    COM1.balancer.messageReceived = FALSE;
    COM1.balancer.messageBody = balancerMessageString;
    COM1.balancer.sendMessage = sendMessageToBalancer;
}

void sendMessageToStepper(void) {
    int i;
    char * data = transmitBuffer;
    putsUART2((UINT *)preamble_string);
    for (i = 0; i < SIZE_OF_STEPPER_MESSAGE; ++i) {
        while(U2STAbits.UTXBF);
        putcUART2(*data++);
    }
    putsUART2((UINT *)eof_message_string);
}

void sendMessageToRFID(RFID_DEVICE dev, char * param) {
    demux_rfid_uart_pins(dev);
    putsUART3((UINT *)preamble_string);
    putsUART3((UINT *)param);
    putsUART3((UINT *)eof_message_string);
}

void sendMessageToBalancer(BALANCER_DEVICE dev) {
    int i;
    char * data = transmitBuffer;
    demux_balancer_uart_pins(dev);
    putsUART4((UINT *)preamble_string);
    for (i = 0; i < SIZE_OF_BALANCER_MESSAGE; ++i) {
        while(U4STAbits.UTXBF);
        putcUART4((UINT)*data++);
    }
    putsUART4((UINT *)eof_message_string);
}

void uart_println(char * message) {
    putsUART1((UINT *)preamble_string);
    putsUART1((UINT *)message);
    putsUART1((UINT *)eof_message_string);
}

void uart_printf(char * format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(transmitBuffer, format, args);
    va_end(args);
    putsUART1((UINT *)preamble_string);
    putsUART1((UINT *)transmitBuffer);
    putsUART1((UINT *)eof_message_string);
}

void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt(void) {
    char temp = ReadUART1();
    if (!(U1STAbits.FERR | U1STAbits.OERR))
        UART_RX_Interrupt_Handler1(temp);
    U1RX_Clear_Intr_Status_Bit;
}

void __attribute__ ((interrupt,no_auto_psv)) _U2RXInterrupt(void) {
    char temp = ReadUART2();
    if (!(U2STAbits.FERR | U2STAbits.OERR)){
        UART_RX_Interrupt_Handler2(temp);
    }
    U2RX_Clear_Intr_Status_Bit;
}

void __attribute__ ((interrupt,no_auto_psv)) _U3RXInterrupt(void) {
    unsigned char temp = ReadUART3();
    if (!(U3STAbits.FERR | U3STAbits.OERR))
        UART_RX_Interrupt_Handler3(temp);
    U3RX_Clear_Intr_Status_Bit;
}

void __attribute__ ((interrupt,no_auto_psv)) _U4RXInterrupt(void) {
    char temp = ReadUART4();
    if (!(U4STAbits.FERR | U4STAbits.OERR))
        UART_RX_Interrupt_Handler4(temp);
    U4RX_Clear_Intr_Status_Bit;
}

void UART_RX_Interrupt_Handler1(char rbyte) {
    static unsigned int i, index = 0;
    char *ptr1, *ptr2;

    if (index < SIZE_OF_PREAMBLE) {
        if (rbyte != preamble_string[index]) {
            index = 0;
            return;
        }
    } else if (index < (SIZE_OF_PC_MESSAGE + SIZE_OF_PREAMBLE)) {
        uart1ReceiveBuffer[index - SIZE_OF_PREAMBLE] = rbyte;
    } else {
        if (rbyte != eof_message_string[index - (SIZE_OF_PC_MESSAGE + SIZE_OF_PREAMBLE)]) {
            index = 0;
            return;
        }
    }

    if (++index == (SIZE_OF_PC_MESSAGE + SIZE_OF_PREAMBLE + SIZE_OF_ENDM)) {
        ptr1 = uart1ReceiveBuffer;
        ptr2 = pcMessageString;
        for (i = 0; i < SIZE_OF_PC_MESSAGE; ++i)
            *ptr2++ = *ptr1++;
        index = 0;
        *ptr2 = '\0';
        COM1.pc.messageReceived = TRUE;
    }
}

void UART_RX_Interrupt_Handler2(char rbyte) {
    static unsigned int i, index = 0;
    char *ptr1, *ptr2;

    if (index < SIZE_OF_PREAMBLE) {
        if (rbyte != preamble_string[index]) {
            index = 0;
            return;
        }
    } else if (index < (SIZE_OF_STEPPER_MESSAGE + SIZE_OF_PREAMBLE)) {
        uart2ReceiveBuffer[index - SIZE_OF_PREAMBLE] = rbyte;
    } else {
        if (rbyte != eof_message_string[index - (SIZE_OF_STEPPER_MESSAGE + SIZE_OF_PREAMBLE)]) {
            index = 0;
            return;
        }
    }

    if (++index == (SIZE_OF_STEPPER_MESSAGE + SIZE_OF_PREAMBLE + SIZE_OF_ENDM)) {
        ptr1 = uart2ReceiveBuffer;
        ptr2 = stepperMessageString;
        for (i = 0; i < SIZE_OF_STEPPER_MESSAGE; ++i)
            *ptr2++ = *ptr1++;
        index = 0;
        COM1.stepper.messageReceived = TRUE;
    }
}

void UART_RX_Interrupt_Handler3(char rbyte) {
    static int index = 0xFFFF;
    static int eomIndex = 0;
    int available_bytes;

    if (++index < SIZE_OF_PREAMBLE) {
        if (rbyte != preamble_string[index])
            index = 0xFFFF;
    } else if (index < (SIZE_OF_PREAMBLE + SIZE_OF_RFID_MESSAGE + SIZE_OF_ENDM)) {
        uart3ReceiveBuffer[index - SIZE_OF_PREAMBLE] = rbyte;
        if (rbyte == eof_message_string[eomIndex]) {
            if (++eomIndex == SIZE_OF_ENDM) {
                available_bytes = index - (SIZE_OF_PREAMBLE + SIZE_OF_ENDM);
                uart3ReceiveBuffer[available_bytes + 1] = '\0';
                COM1.pc.println(uart3ReceiveBuffer);
                index = 0xFFFF;
                eomIndex = 0;
            }
        } else {
            eomIndex = 0;
        }
    } else {
        COM1.pc.println("Buffer Over Flow!");
        index = 0xFFFF;
        eomIndex = 0;
    }
}

void UART_RX_Interrupt_Handler4(char rbyte) {
    static unsigned int i, index = 0;
    char *ptr1, *ptr2;

    if (index < SIZE_OF_PREAMBLE) {
        if (rbyte != preamble_string[index]) {
            index = 0;
            return;
        }
    } else if (index < (SIZE_OF_BALANCER_MESSAGE + SIZE_OF_PREAMBLE)) {
        uart4ReceiveBuffer[index - SIZE_OF_PREAMBLE] = rbyte;
    } else {
        if (rbyte != eof_message_string[index - (SIZE_OF_BALANCER_MESSAGE + SIZE_OF_PREAMBLE)]) {
            index = 0;
            return;
        }
    }

    if (++index == (SIZE_OF_BALANCER_MESSAGE + SIZE_OF_PREAMBLE + SIZE_OF_ENDM)) {
        ptr1 = uart4ReceiveBuffer;
        ptr2 = balancerMessageString;
        for (i = 0; i < SIZE_OF_BALANCER_MESSAGE; ++i)
            *ptr2++ = *ptr1++;
        index = 0;
        COM1.balancer.messageReceived = TRUE;
    }
}
