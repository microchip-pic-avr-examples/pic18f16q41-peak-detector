#include "peakDetector.h"
#include "utility.h"

#include "./mcc_generated_files/mcc.h"

#include <stdint.h>
#include <xc.h>

static volatile PEAK_STATES peakState = PK_WAITING;
static volatile PEAK_STATES nextPeakState = PK_WAITING;

// Returns the remainder, and subtracts from the numerator during the division.
uint16_t inline fastDivide(uint16_t* numer, uint16_t divisor)
{
    uint16_t count = 0;
    while (*numer >= divisor)
    {
        *numer -= divisor;
        count++;
    }
    return count;
}

PEAK_STATES getState(void)
{
    return peakState;
}

void setNextState(PEAK_STATES state)
{
    nextPeakState = state;
}

void applyNextState(void)
{
    peakState = nextPeakState;
}

// Sends the peak value the ADCC stored
void sendPeakValue(void)
{
    // With a 4.096V reference, every bit is 1mV
    // This is the value in mV
    
    uint16_t adc_peak = ADSTPT;
    char digit;
    
    // Warning for clipping signals
    if (adc_peak >= 0xFFF)
    {
        sendString("[WARNING] Peak signal exceeds ADC range", 1);
    }
    
    //Right Shift by 1 to compensate a gain of 2
    adc_peak = adc_peak >> 1;
    
    sendString("Peak Input: ", 0);
    
    if (adc_peak >= 1000)
    {
        // 1000's place
        digit = '0' + fastDivide(&adc_peak, 1000);
        sendStringSafe(&digit, 1);
        sendStringSafe(".", 1);
        
        // 100's place
        digit = '0' + fastDivide(&adc_peak, 100);
        sendStringSafe(&digit, 1);

        // 10's place
        digit = '0' + fastDivide(&adc_peak, 10);
        sendStringSafe(&digit, 1);
        
        // 1's place
        digit = '0' + adc_peak;
        sendStringSafe(&digit, 1);
        sendString("V", 1);
    }
    else
    {
        // mV range
        if (adc_peak >= 100)
        {
            // 100's place
            digit = '0' + fastDivide(&adc_peak, 100);
            sendStringSafe(&digit, 1);
            
            // 10's place
            digit = '0' + fastDivide(&adc_peak, 10);
            sendStringSafe(&digit, 1);
        }
        else if (adc_peak >= 10)
        {
            // 10's place
            digit = '0' + fastDivide(&adc_peak, 10);
            sendStringSafe(&digit, 1);
        }
        
        // 1's place
        digit = '0' + adc_peak;
        sendStringSafe(&digit, 1);
        sendString("mV", 1);
        
    }
}

void enableNegativeEdge(void)
{
    CM1CON1bits.INTP = 0;
    CM1CON1bits.INTN = 1;
}

void enablePositiveEdge(void)
{
    CM1CON1bits.INTN = 0;
    CM1CON1bits.INTP = 1;
}

void disableEdges(void)
{
    CM1CON1bits.INTP = 0;
    CM1CON1bits.INTN = 0;
    PIR1bits.C1IF = 0;
}

void updateADCCPeak(uint16_t value)
{
    ADCON0bits.ADGO = 0;
    
    // Set new max
    ADCC_DefineSetPoint(value);
    
    ADCON0bits.ADGO = 1;
}

void peakDetectorStateMachine(void)
{
    PEAK_STATES state = getState();
    switch(state)
    {
        case PK_WAITING:
            // Not in peak window
            // If the comparator missed the edge
            if (C1OUT)
            {
                disableEdges();
                setNextState(PK_OPEN);
            }
            break;
        case PK_OPEN:
            // Sampling Window is now open
            // Move the next state to running
            setNextState(PK_RUNNING);

            WindowOpen_LED_SetHigh();

            // Print the message
            sendString("Peak Window Open", 1); 

            //Enable falling edge interrupts
            enableNegativeEdge();
            break;
        case PK_RUNNING:
            // Peak Window is running
            // If the comparator missed the edge
            if (!C1OUT)
            {
                disableEdges();
                setNextState(PK_DONE);
            }
            break;
        case PK_DONE:
            // Sampling Window has closed
            // Set the next state to WAIT
            setNextState(PK_WAITING);

            WindowOpen_LED_SetLow();

            // Transmit the peak value found
            sendPeakValue();
            updateADCCPeak(0x00);

            // Print the message
            sendString("Peak Window Closed", 1);
            END_OF_LINE;

            enablePositiveEdge();
            break;
    }
    applyNextState();
}