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

    /**
     *  Peak detecting state machine states
     */
    typedef enum {PK_WAITING = 0, PK_OPEN, PK_RUNNING, PK_DONE} PEAK_STATES;
        
    /**
     * <b><FONT COLOR=BLUE>void</FONT> setState(<FONT COLOR=BLUE>PEAK_STATES</FONT> state)</B>
     * @param state (PEAK_STATES) - new state machine state
     * 
     *  This function sets the state of the peak detecting state machine.
     */
    void setState(PEAK_STATES state);
    
    /**
     * <b><FONT COLOR=BLUE>PEAK_STATES</FONT> getState(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function gets the state of the peak detecting state machine. 
     */
    PEAK_STATES getState(void);

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
     * <b><FONT COLOR=BLUE>void</FONT> negativeEdgeAction(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function is called by the ISR when the signal falls below the threshold.
     *  Inside, this function sets up the positive edge events and disables the ADCC.
     */
    void negativeEdgeAction(void);

    /**
     * <b><FONT COLOR=BLUE>void</FONT> positiveEdgeAction(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     *  This function is called by the ISR (or main) when a signal rises above the threshold.
     *  Inside, this function sets up the negative edge events and enables the ADCC.
     */
    void positiveEdgeAction(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PEAKDETECTOR_H */

