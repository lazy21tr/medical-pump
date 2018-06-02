/* 
 * File:   hal.h
 * Author: msuzer
 *
 * Created on 08 Mart 2014 Cumartesi, 00:20
 */

#ifndef HAL_H
#define	HAL_H

#define USE_AND_OR
#define FIRMWARE_VERSION        100
#define FOSC                    32000000L
#define FCY                     FOSC/2		//instruction frequency

#include "core_pins.h"
#include "devapi.h"

#include "PPS.h"
#include "ports.h"
#include "PwrMgnt.h"
#include "uart.h"

#include <adc.h>
#include <timer.h>
#include <xc.h>
#include <libpic30.h>

#define CPU_USER_TASK_FREQ      50 //Hz
#define BAUD_RATE_REG_VAL       51 //19230
#define TIMER2_PRESCALER        T2_PS_1_256
#define TIMER2_PERIOD_VAL       (FCY/CPU_USER_TASK_FREQ/256) //0.02sn
#define PWM_PERIOD              832 //19230 Hz
#define DELAY_MS                __delay_ms
#define DELAY_US                __delay_us
#define SWITCH_DEBOUNCE         3

#define SoftReset()             {asm ("RESET");}         //Reset in software

#define T2_INT_PRIORITY         T2_INT_PRIOR_1
#define U1_RX_INT_PRIORITY      UART_RX_INT_PR2
#define U2_RX_INT_PRIORITY      UART_RX_INT_PR2
#define U3_RX_INT_PRIORITY      UART_RX_INT_PR2
#define U4_RX_INT_PRIORITY      UART_RX_INT_PR2
#define ADC_Module_Int_Flag     IFS0bits.AD1IF
#define PWMDutyCycleReg         OC1R

    void init_mcu_core(void);
    void init_peripherals(void);
    void demux_rfid_uart_pins(RFID_DEVICE dev);
    void demux_balancer_uart_pins(BALANCER_DEVICE dev);
    void blink_board_alive_indicator(void);
    void read_sensors(void);

#endif	/* HAL_H */
