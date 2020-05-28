/* 
 * File:   init.h
 * Author: C62081
 *
 * Created on April 30, 2020, 3:02 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

    void initADCC(void);
    void initDAC(void);
    void initCMP(void);
    void initOPA(void);

    void setTriggerLevel(uint8_t level);

#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

