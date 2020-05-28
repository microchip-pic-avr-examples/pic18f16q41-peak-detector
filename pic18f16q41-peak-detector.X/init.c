#include "init.h"
#include <xc.h>
#include <stdint.h>

void initADCC(void)
{
    ADCON0 = 0x00;
    ADCON0bits.CONT = 1;        //Continuous Conversion
    ADCON0bits.CS = 1;          //Using ADCRC Oscillator
    ADCON0bits.FM = 1;          //Right Justified
    
    ADCON1 = 0x00;
    ADCON2 = 0x00;              //Basic Mode
    ADCON3 = 0x00;
    ADCON3bits.CALC = 0b001;    //ADRES - ADSTPT = ADERR
    ADCON3bits.TMD = 0b110;     //Interrupt if bigger than ADUTH
    
    ADSTAT = 0x00;
    ADCLK = 0x00;
    
    ADREF = 0x00;
    ADREFbits.NREF = 0;         //Vss
    ADREFbits.PREF = 0b11;      //FVR 
    
    ADPCH = 0b010010;           //RC2 (OPA Out)
    
    ADPRE = 0x00;               //Pre-charge time
    ADACQ = 6;                  //10uS
    ADCAP = 0x00;               //No extra capacitance
    
    ADRPT = 0;                  //No Repeats
    ADCNT = 0;                  //No counts
    
    ADSTPT = 0;
    ADUTH = 0;
    
    ADACT = 0;                  //No trigger
    
    ADCP = 0x00;
    ADCPbits.CPON = 1;          //Charge pump
    
    //While the charge pump is not ready
    while (!ADCPbits.ADCPRDY);
    
    //Threshold interrupt enable
    PIR2bits.ADTIF = 0;
    PIE2bits.ADTIE = 1;
    
    //Turn on the ADCC
    ADCON0bits.ON = 1;
}

void initDAC(void)
{
    FVRCON = 0x00;
    FVRCONbits.CDAFVR = 0b01;   //1.024V for DACs
    FVRCONbits.ADFVR = 0b11;
    
    FVRCONbits.EN = 1;
    
    //Wait for the FVR to be stable
    while (!FVRCONbits.RDY) { ; }
    
    DAC2CON = 0x20;
    DAC2CONbits.PSS = 0b10;     //FVR
    
    DAC2DATL = 0;
    
    DAC2CONbits.EN = 1;
}

void initCMP(void)
{
    CM1CON0 = 0x00;
    CM1CON0bits.HYS = 1;        //Enable Hysteresis
    CM1CON0bits.POL = 1;        //Invert Polarity
    
    CM1CON1 = 0x00;
    CM1CON1bits.INTN = 0;       //Negative starts cleared
    CM1CON1bits.INTP = 1;       //Positive starts enabled
    
    //RC2 (C1IN2-)
    CM1NCH = 0x02;
    TRISC2 = 1;
    ANSELC2 = 1;
    
    //DAC2 OUT
    CM1PCH = 0x05;
    
    TRISB6 = 0;
    RB6PPS = 0x19;                 //C1OUT (Comparator Output
    
    //Setup Interrupts
    PIR1bits.C1IF = 0;
    PIE1bits.C1IE = 1;
    
    CM1CON0bits.C1EN = 1;
}

void initOPA(void)
{
    OPA1CON0 = 0x00;
    OPA1CON0bits.UG = 1;
    
    OPA1CON1 = 0x00;
    
    OPA1CON2 = 0x00;
    OPA1CON2bits.NCH = 0b000;   //No connection
    OPA1CON2bits.PCH = 0b010;   //Pin Input
    
    OPA1CON3 = 0x00;
    OPA1CON3bits.FMS = 0b10;    //OPAxOUT Feedback
    OPA1CON3bits.PSS = 0b00;    //Select In0+
    
    OPA1HWC =  0x00;
    OPA1ORS =  0x00;
    
    //Enable the Module
    OPA1CON0bits.EN = 1;
}

void setTriggerLevel(uint8_t level)
{
    DAC2DATL = level;
}