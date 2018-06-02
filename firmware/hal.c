#include "hal.h"
#include "serialcomm.h"
#include "devapi.h"

_CONFIG1(WDTPS_PS32768 & FWPSA_PR128 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & LPCFG_OFF & GWRP_ON & GCP_ON & JTAGEN_OFF)
_CONFIG2(POSCMD_HS & WDTCLK_SOSC & OSCIOFCN_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & ALTCMPI_CxINC_RX & WDTCMX_WDTCLK & IESO_OFF)
_CONFIG3(WPFP_WPFP127 & SOSCSEL_ON & WDTWIN_PS75_0 & PLLSS_PLL_PRI & BOREN_ON & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
_CONFIG4(DSWDTPS_DSWDTPSA & DSWDTOSC_SOSC & DSBOREN_ON & DSWDTEN_OFF & DSSWEN_OFF & PLLDIV_PLL4X & I2C1SEL_DISABLE & IOL1WAY_OFF)

extern DEVICE_STATE_VALUES dsv;
extern SerialPort COM1;

void OpenADConverter(void);
void OpenOC1inPWMMode(void);

void init_mcu_core(void) {
    PwrMgnt_ClkDiv_Sel(PERI_CLK_RATIO_SET_1 | PLL_ENABLE);

    ANSA = DISABLED;
    ANSB = DISABLED;
    ANSC = DISABLED;

    TRISA = INPUT_PORT;
    TRISB = INPUT_PORT;
    TRISC = INPUT_PORT;

    LATA = 0;
    LATB = 0;
    LATC = 0;

    PMCON1 = 0;

    PPSUnLock;
    iPPSOutput(OUT_PIN_PPS_RP19, OUT_FN_PPS_U1TX); //Assign U1TX to pin RP19 PCRS232TX
    iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP20); //Assign U1RX to pin RP20 PCRS232RX
    //iPPSOutput(OUT_PIN_PPS_RP6, OUT_FN_PPS_U2TX); //Assign U2TX to pin RP6 STEPRS2321TX
    iPPSOutput(OUT_PIN_PPS_RP9, OUT_FN_PPS_U2TX); //Assign U2TX to pin RP9 STEPRS2321TX
    iPPSInput(IN_FN_PPS_U2RX, IN_PIN_PPS_RP5); //Assign U2RX to pin RP5 STEPRS232RX
    iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_U3TX); //U3TX to pin RP7 RFID1RS232TX
    iPPSInput(IN_FN_PPS_U3RX, IN_PIN_PPS_RP8); //U3RX to pin RP8 RFID1RS232RX
    iPPSOutput(OUT_PIN_PPS_RP24, OUT_FN_PPS_U4TX); //U4TX to pin RP24 BAL1RS232TX
    iPPSInput(IN_FN_PPS_U4RX, IN_PIN_PPS_RP25); //U4RX to pin RP25 BAL1RS232RX
    iPPSOutput(OUT_PIN_PPS_RP21, OUT_FN_PPS_OC1); //Assign OC1 to pin RP21 PumpSpeedControl
    PPSLock;

    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
    PMD3 = 0xFFFF;
    PMD4 = 0xFFFF;
    PMD6 = 0xFFFF;
    PMD7 = 0xFFFF;

    PMD1bits.T2MD = 0;
    PMD1bits.ADC1MD = 0;
    PMD1bits.U1MD = 0;
    PMD1bits.U2MD = 0;
    PMD2bits.OC1MD = 0;
    PMD3bits.U3MD = 0;
    PMD4bits.U4MD = 0;

    ConfigureUnUsedPins();
    ConfigureLEDPin();
    ConfigurePumpMotorDCPin();
    ConfigurePumpMotorSCPin();
    ConfigurePCRS232TXPin();
    ConfigureSTEPRS232TXPin();
    ConfigureRFID1RS232TXPin();
    ConfigureRFID2RS232TXPin();
    ConfigureBAL1RS232TXPin();
    ConfigureBAL2RS232TXPin();
    ConfigureTrimPOTPin();
    ConfigureTempSensorPin();
    ConfigureExtSens1Pin();
    ConfigureExtSens2Pin();
    ConfigureExtSens3Pin();
    ConfigureExtSens4Pin();
    ConfigureExtSens5Pin();
}

void init_peripherals(void) {
    CloseUART1();
    CloseUART2();
    CloseUART3();
    CloseUART4();
    CloseTimer2();

    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIORITY);
    OpenTimer2(T2_ON | TIMER2_PRESCALER, TIMER2_PERIOD_VAL);

    ConfigIntUART1(UART_RX_INT_EN | U1_RX_INT_PRIORITY);
    OpenUART1(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);

    ConfigIntUART2(UART_RX_INT_EN | U2_RX_INT_PRIORITY);
    OpenUART2(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);

    ConfigIntUART3(UART_RX_INT_EN | U3_RX_INT_PRIORITY);
    OpenUART3(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);

    ConfigIntUART4(UART_RX_INT_EN | U4_RX_INT_PRIORITY);
    OpenUART4(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);

    OpenADConverter();
    OpenOC1inPWMMode();
}

//AN0 TrimPOT, AN1 TempSensor, AutoConvert
void OpenADConverter(void){
    AD1CON1 = ADC_MODULE_OFF | ADC_10BIT_MODE | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF;
    AD1CON2 = ADC_BUF_REG_ENABLE | ADC_SCAN_OFF | ADC_INTR_2_CONV | ADC_ALT_INPUT_ON;
    AD1CON3 = ADC_SAMPLE_TIME_17 | ADC_CONV_CLK_254Tcy;
    AD1CON4 = 0;
    AD1CON5 = 0;
    AD1CHS = ADC_CH0_POS_SAMPLEA_AN0 | ADC_CH0_POS_SAMPLEB_AN1;
    ANCFG = 0;
    AD1CHITL = 0;
    AD1CSSH= 0;
    AD1CSSL= 0;
    AD1CTMENL = 0;
    AD1CON1bits.ADON = 1;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.ASAM = 1;
}

void OpenOC1inPWMMode(void){
    OC1CON1 = 0;
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0x07; //select the peripheral clock as the clock input
    OC1R = 0; //DutyCycle
    OC1RS = PWM_PERIOD;
    OC1CON2bits.SYNCSEL = 0x1F; //select the synchronization source as itself
    OC1CON1bits.OCM = 6; //select and start the Edge Aligned PWM mode
}

void demux_rfid_uart_pins(RFID_DEVICE dev){
    if (dev == COM1.rfid.devID)
        return;

    if (dev == RFID1){
        U3MODEbits.UARTEN = 0;
        COM1.rfid.devID = RFID1;
        PPSUnLock;
        iPPSOutput(OUT_PIN_PPS_RP7, OUT_FN_PPS_U3TX); //U3TX to pin RP7 RFID1RS232TX
        iPPSInput(IN_FN_PPS_U3RX, IN_PIN_PPS_RP8); //U3RX to pin RP8 RFID1RS232RX
        PPSLock;
        ConfigIntUART3(UART_RX_INT_EN | U3_RX_INT_PRIORITY);
        OpenUART3(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);
    } else if (dev == RFID2){
        U3MODEbits.UARTEN = 0;
        COM1.rfid.devID = RFID2;
        PPSUnLock;
        iPPSOutput(OUT_PIN_PPS_RP23, OUT_FN_PPS_U3TX); //U3TX to pin RP23 RFID2RS232TX
        iPPSInput(IN_FN_PPS_U3RX, IN_PIN_PPS_RP22); //U3RX to pin RP22 RFID2RS232RX
        PPSLock;
        ConfigIntUART3(UART_RX_INT_EN | U3_RX_INT_PRIORITY);
        OpenUART3(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);
    }
}

void demux_balancer_uart_pins(BALANCER_DEVICE dev){
    if (dev == COM1.balancer.devID)
        return;

    if (dev == BALANCER1){
        U4MODEbits.UARTEN = 0;
        COM1.balancer.devID = BALANCER1;
        PPSUnLock;
        iPPSOutput(OUT_PIN_PPS_RP24, OUT_FN_PPS_U4TX); //U4TX to pin RP24 BAL1RS232TX
        iPPSInput(IN_FN_PPS_U4RX, IN_PIN_PPS_RP25); //U4RX to pin RP25 BAL1RS232RX
        PPSLock;
        ConfigIntUART4(UART_RX_INT_EN | U4_RX_INT_PRIORITY);
        OpenUART4(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);
    } else if (dev == BALANCER2){
        U4MODEbits.UARTEN = 0;
        COM1.balancer.devID = BALANCER2;
        PPSUnLock;
        iPPSOutput(OUT_PIN_PPS_RP10, OUT_FN_PPS_U4TX); //U4TX to pin RP10 BAL2RS232TX
        iPPSInput(IN_FN_PPS_U4RX, IN_PIN_PPS_RP11); //U4RX to pin RP11 BAL2RS232RX
        PPSLock;
        ConfigIntUART4(UART_RX_INT_EN | U4_RX_INT_PRIORITY);
        OpenUART4(UART_EN, UART_TX_ENABLE | UART_RX_ENABLE, BAUD_RATE_REG_VAL);
    }
}

void read_sensors(void) {
    static unsigned int kbCount0 = 0;
    static unsigned int kbCount1 = 0;
    static unsigned int kbCount2 = 0;
    static unsigned int kbCount3 = 0;
    static unsigned int kbCount4 = 0;

    if (ExtSens1Active()) {
        if (!dsv.ExtSensorValues.bits.b0)
            if (++kbCount0 > SWITCH_DEBOUNCE) {
                dsv.ExtSensorValues.bits.b0 = 1;
            }
    } else {
        kbCount0 = 0;
        dsv.ExtSensorValues.bits.b0 = 0;
    }

    if (ExtSens2Active()) {
        if (!dsv.ExtSensorValues.bits.b1)
            if (++kbCount1 > SWITCH_DEBOUNCE) {
                dsv.ExtSensorValues.bits.b1 = 1;
            }
    } else {
        kbCount1 = 0;
        dsv.ExtSensorValues.bits.b1 = 0;
    }

    if (ExtSens3Active()) {
        if (!dsv.ExtSensorValues.bits.b2)
            if (++kbCount2 > SWITCH_DEBOUNCE) {
                dsv.ExtSensorValues.bits.b2 = 1;
            }
    } else {
        kbCount2 = 0;
        dsv.ExtSensorValues.bits.b2 = 0;
    }

    if (ExtSens4Active()) {
        if (!dsv.ExtSensorValues.bits.b3)
            if (++kbCount3 > SWITCH_DEBOUNCE) {
                dsv.ExtSensorValues.bits.b3 = 1;
            }
    } else {
        kbCount3 = 0;
        dsv.ExtSensorValues.bits.b3 = 0;
    }

    if (ExtSens5Active()) {
        if (!dsv.ExtSensorValues.bits.b4)
            if (++kbCount4 > SWITCH_DEBOUNCE) {
                dsv.ExtSensorValues.bits.b4 = 1;
            }
    } else {
        kbCount4 = 0;
        dsv.ExtSensorValues.bits.b4 = 0;
    }
}

void blink_board_alive_indicator(void) {
    static unsigned int timeCtr = 0;

    if (++timeCtr == 1)
        SetLED(ON);
    else if (timeCtr == 10)
        SetLED(OFF);
    else if (timeCtr > 100)
        timeCtr = 0;
}
