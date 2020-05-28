#include "utility.h"
#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include <stdint.h>

const char hexLookup[]  = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void sendString(const char* str, uint8_t sendEOL)
{
    int index = 0;
    while (str[index] != '\0')
    {   
        UART1_Write(str[index]);
        
        index++;
    }
    
    if (sendEOL == 0)
    {
        return;
    }
    
    END_OF_LINE;
}

void sendStringSafe(const char* str, uint8_t size)
{
    uint8_t index = 0;
    while (index < size)
    {
        UART1_Write(str[index]);
        
        index++;
    }
}

void printRegisterLine(const char* str, uint8_t rg)
{
    sendString(str, 0);
    sendHexValue(rg);
    END_OF_LINE;
}

void printRegisterLineLarge(const char* str, uint16_t rg)
{
    sendString(str, 0);
    sendLargeHexValue(rg);
    END_OF_LINE;
}

void sendHexValue(uint8_t value)
{    
    char tx[2];
    
    tx[0] = hexLookup[value >> 4];
    tx[1] = hexLookup[(value & 0x0F)];
    
    sendStringSafe(&tx[0], 2);
}

void sendLargeHexValue(uint16_t value)
{
    char tx[4];
    
    tx[0] = hexLookup[(value >> 12)];
    tx[1] = hexLookup[((value >> 8) & 0x0F)];
    tx[2] = hexLookup[((value >> 4) & 0x0F)];
    tx[3] = hexLookup[(value & 0x0F)];
    
    sendStringSafe(&tx[0], 4);
}