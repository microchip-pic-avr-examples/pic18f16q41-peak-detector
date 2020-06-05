/* 
 * File:   peakDetector.h
 * Author: C62081
 *
 * Created on May 7, 2020, 11:43 AM
 */

#ifndef PEAKDETECTOR_H
#define	PEAKDETECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    /**
     *  Peak detecting state machine states
     */
    typedef enum {PK_WAITING = 0, PK_OPEN, PK_RUNNING, PK_DONE} PEAK_STATES;
        
    /**
     * <b><FONT COLOR=BLUE>void</FONT> setNextState(<FONT COLOR=BLUE>PEAK_STATES</FONT> state)</B>
     * @param state (PEAK_STATES) - new state machine state
     * 
     *  This function sets the next state of the peak detecting state machine.
     */
    void setNextState(PEAK_STATES state);
    
    /**
     * <b><FONT COLOR=BLUE>PEAK_STATES</FONT> getState(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function gets the state of the peak detecting state machine. 
     */
    PEAK_STATES getState(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> applyNextState(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function applies the stored next state to the current state.
     */
    void applyNextState(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> sendPeakValue(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function transmits the peak value (stored in ADSTPT) to the UART.
     *  Data sent is in floating point (3 decimals) format, however does not use floats.
     * 
     *  Works only with the 4.096V FVR.
     */
    void sendPeakValue(void);

    /**
     * <b><FONT COLOR=BLUE>void</FONT> enableNegativeEdge(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function enables negative edge interrupts for the comparator.
     */
    void enableNegativeEdge(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> enablePositiveEdge(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function enables positive edge interrupts for the comparator.
     */
    void enablePositiveEdge(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> disableEdges(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function disables edge interrupts for the comparator.
     */
    void disableEdges(void);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> updateADCCPeak(<FONT COLOR=BLUE>uint16_t</FONT> value)</B>
     * 
     *  This function disables the ADCC, updates the setpoint register to value, then restarts the ADCC.
     */
    void updateADCCPeak(uint16_t value);
    
    /**
     * <b><FONT COLOR=BLUE>void</FONT> peakDetectorStateMachine(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function runs the peak detection state machine.
     */
    void peakDetectorStateMachine(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PEAKDETECTOR_H */

