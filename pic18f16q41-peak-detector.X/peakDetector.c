#include "peakDetector.h"
#include "utility.h"

#include "./mcc_generated_files/mcc.h"

#include <stdint.h>
#include <xc.h>

static volatile PEAK_STATES peakReady = PK_WAITING;

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

void setState(PEAK_STATES state)
{
    peakReady = state;
}

PEAK_STATES getState(void)
{
    return peakReady;
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
        sendString("[WARNING] Peak exceeds ADC measurement range", 1);
    }
    
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

void negativeEdgeAction(void)
{
    CM1CON1bits.INTN = 0;
    CM1CON1bits.INTP = 1;

    WindowOpen_LED_LAT = 0;         // Turn off an LED
    ADCC_StopConversion();          // Abort the conversion
    setState(PK_DONE);              // Indicate that the peak can be printed now
}

void positiveEdgeAction(void)
{
    CM1CON1bits.INTP = 0;
    CM1CON1bits.INTN = 1;

    WindowOpen_LED_LAT = 1;          // Turn on an LED
    setState(PK_OPEN);               // Indicate the window is open
    ADSTPT = 0x00;                   // Clear the max
    ADCC_StartConversion(0x8D);
}