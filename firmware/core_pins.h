#ifndef CORE_PINS_H
#define	CORE_PINS_H

#define INPUT_PIN                       1
#define OUTPUT_PIN                      0
#define OUTPUT_HIGH                     1
#define OUTPUT_LOW                      0
#define INPUT_PORT                      0xFFFF
#define OUTPUT_PORT                     0x0000
#define DISABLED                        0
#define ON                          	OUTPUT_HIGH
#define OFF                         	OUTPUT_LOW
#define CW                          	OUTPUT_HIGH
#define CCW                         	OUTPUT_LOW

#define LEDPin                          LATBbits.LATB2
#define TrimPOTPin                      PORTAbits.RA0  //AN0
#define TempSensorPin                   PORTAbits.RA1  //AN1
#define PumpMotorDirectionControlPin	LATAbits.LATA9
#define PumpMotorSpeedControlPin        LATCbits.LATC5 //RP21

#define ExtSens1Pin                     PORTBbits.RB15 //CN11
#define ExtSens2Pin                     PORTBbits.RB14 //CN12
#define ExtSens3Pin                     PORTAbits.RA7  //CN33
#define ExtSens4Pin                     PORTAbits.RA10 //CN36
#define ExtSens5Pin                     PORTBbits.RB13 //CN13

//UART1
#define PCRS232TXPin                LATCbits.LATC3 //RP19
#define PCRS232RXPin                LATCbits.LATC4 //RP20

//UART2
#define STEPRS232TXPin              LATBbits.LATB6 //RP6
#define STEPRS232RXPin              LATBbits.LATB5 //RP5

//UART3
#define RFID1RS232TXPin             LATBbits.LATB7 //RP7
#define RFID1RS232RXPin             LATBbits.LATB8 //RP8
#define RFID2RS232TXPin             LATCbits.LATC7  //RP23
#define RFID2RS232RXPin             LATCbits.LATC6  //RP22

//UART4
#define BAL1RS232TXPin              LATCbits.LATC8  //RP24
#define BAL1RS232RXPin              LATCbits.LATC9  //RP25
#define BAL2RS232TXPin              LATBbits.LATB10 //RP10
#define BAL2RS232RXPin              LATBbits.LATB11 //RP11

#define ConfigureLEDPin()           TRISBbits.TRISB2 = OUTPUT_PIN
#define ConfigurePumpMotorDCPin()	TRISAbits.TRISA9 = OUTPUT_PIN
#define ConfigurePumpMotorSCPin()	TRISCbits.TRISC5 = OUTPUT_PIN

#define ConfigurePCRS232TXPin()		TRISCbits.TRISC3 = OUTPUT_PIN
//#define ConfigureSTEPRS232TXPin()	TRISBbits.TRISB6 = OUTPUT_PIN
#define ConfigureSTEPRS232TXPin()	TRISBbits.TRISB9 = OUTPUT_PIN
#define ConfigureRFID1RS232TXPin()	TRISBbits.TRISB7 = OUTPUT_PIN
#define ConfigureRFID2RS232TXPin()	TRISCbits.TRISC7 = OUTPUT_PIN
#define ConfigureBAL1RS232TXPin()	TRISCbits.TRISC8 = OUTPUT_PIN
#define ConfigureBAL2RS232TXPin()	TRISBbits.TRISB10 = OUTPUT_PIN

#define ConfigureTrimPOTPin()		ANSAbits.ANSA0 = 1 //AN0
#define ConfigureTempSensorPin()	ANSAbits.ANSA1 = 1 //AN1

#define ConfigureExtSens1Pin()		EnablePullUpCN11
#define ConfigureExtSens2Pin()		EnablePullUpCN12
#define ConfigureExtSens3Pin()		EnablePullUpCN33
#define ConfigureExtSens4Pin()		EnablePullUpCN36
#define ConfigureExtSens5Pin()		EnablePullUpCN13

// Unused pins, configure as outputs and drive low
// RA8/CN34, RB9/CN21, RB12/CN14, RB0/CN4, RB1/CN5, RB3/CN7, RC0/CN8, RC1/CN9, RC2/CN10
#define ConfigureUnUsedPins()           {TRISAbits.TRISA8 = OUTPUT_PIN; \
                                         TRISBbits.TRISB0 = OUTPUT_PIN; \
                                         TRISBbits.TRISB1 = OUTPUT_PIN; \
                                         TRISBbits.TRISB3 = OUTPUT_PIN; \
                                         TRISBbits.TRISB6 = OUTPUT_PIN; \
                                         TRISBbits.TRISB12 = OUTPUT_PIN; \
                                         TRISCbits.TRISC0 = OUTPUT_PIN; \
                                         TRISCbits.TRISC1 = OUTPUT_PIN; \
                                         TRISCbits.TRISC2 = OUTPUT_PIN; }

#define ReadLED()			LEDPin
#define SetLED(x)			LEDPin = x
#define ToggleLED()			SetLED(!ReadLED())

#define SetPumpMotorDirection(Dir)      PumpMotorDirectionControlPin = Dir

#define ExtSens1Active()                !ExtSens1Pin
#define ExtSens2Active()                !ExtSens2Pin
#define ExtSens3Active()                !ExtSens3Pin
#define ExtSens4Active()                !ExtSens4Pin
#define ExtSens5Active()                !ExtSens5Pin

#endif
