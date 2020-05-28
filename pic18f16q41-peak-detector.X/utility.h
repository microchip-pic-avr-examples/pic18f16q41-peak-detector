#ifndef UTILITY_H
#define	UTILITY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

    /**
     * <b><FONT COLOR=BLUE>void</FONT> sendString(<FONT COLOR=BLUE>const char*</FONT> str, <FONT COLOR=BLUE>uint8_t</FONT> sendEOL)</B>
     * @param str (const char*) - Null terminated string to send
     * @param sendEOL (uint8_t) - Set to 1 to send a new line sequence (/n/r)
     */
    void sendString(const char* str, uint8_t sendEOL);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> sendStringSafe(<FONT COLOR=BLUE>const char*</FONT> str, <FONT COLOR=BLUE>uint8_t</FONT> size)</B>
     * @param str (const char*) - String (or char) to send. Does NOT need to be null terminated
     * @param size (uint8_t) - Length of the string to send.
     */
    void sendStringSafe(const char* str, uint8_t size);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> printRegisterLine(<FONT COLOR=BLUE>const char*</FONT> str, <FONT COLOR=BLUE>uint8_t</FONT> rg)</B>
     * @param str (const char*) - Null-terminated String to send before the value.
     * @param rg (uint8_t) - Converts the value to an equiv. ASCII string and transmits it after str.
     */
    void printRegisterLine(const char* str, uint8_t rg);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> printRegisterLineLarge(<FONT COLOR=BLUE>const char*</FONT> str, <FONT COLOR=BLUE>uint16_t</FONT> rg)</B>
     * @param str (const char*) - Null-terminated String to send before the value. 
     * @param rg (uint16_t) - Converts the value to an equiv. ASCII string and transmits it after str.
     */
    void printRegisterLineLarge(const char* str, uint16_t rg);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> sendLargeHexValue(<FONT COLOR=BLUE>uint16_t</FONT> rg)</B>
     * @param value (uint16_t) - Hex value to transmit
     * 
     * Converts a hex value to an equiv. ASCII string and sends it.
     */
    void sendLargeHexValue(uint16_t value);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> sendHexValue(<FONT COLOR=BLUE>uint8_t</FONT> rg)</B>
     * @param value (uint8_t) - Hex value to transmit
     * 
     * Converts a hex value to an equiv. ASCII string and sends it.
     */
    void sendHexValue(uint8_t value);
        
/**
 * <B>END_OF_LINE</B>
 * 
 * Sends /n/r to the UART.
 */
#define END_OF_LINE do { sendStringSafe("\n\r", 2); } while(0)
    
#ifdef	__cplusplus
}
#endif

#endif	/* CALIBRATION_H */

