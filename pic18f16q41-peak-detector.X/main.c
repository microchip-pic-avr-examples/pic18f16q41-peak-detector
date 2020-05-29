/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC18F16Q41
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "utility.h"
#include "peakDetector.h"
#include <xc.h>

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    DAC2_SetOutput(0x7F);       //50% Level
    
    // DAC is not usually initalized before CMP, clear edge flags
    PIR1bits.C1IF = 0;
    
    INTERRUPT_GlobalInterruptEnable(); 
    
    // If not above threshold, then startup normally
    if (!CMP1_GetOutputStatus())
        setState(PK_WAITING);
    else
    {
        // Threshold is exceeded, run trigger that was skipped
        setState(PK_OPEN);
        positiveEdgeAction();
    }    
    
    while (1)
    {
        if (getState() == PK_OPEN)
        {
            // Print the message
            sendString("Peak Window Open", 1);
            
            /*
             * This is a rare edge case fix.
             * 
             * A signal could rise above the level of a trigger
             * and then fall below the trigger point before the machine
             * finishes transmitting the message above, causing an improper
             * state change.
             */
            
            if (getState() != PK_DONE)
                 setState(PK_RUNNING);
        }
        if (getState() == PK_DONE)
        {
            // Transmit the peak value found
            sendPeakValue();
            
            // Print the message
            sendString("Peak Window Closed", 1);
            END_OF_LINE;
            
            // Return the state machine to WAIT
            setState(PK_WAITING);
        }
    }
}
/**
 End of File
*/