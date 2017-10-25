/* 
 * File:   tmr.h
 * Author: Administrator
 *
 * Created on September 19, 2017, 11:33 AM
 */

#ifndef TMR_H
#define	TMR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic.h>
    
extern void TMR0_Initialize();
extern void TMR1_Initialize();
extern void TMR2_Initialize();
extern void TMR1_StartTimer();
extern void TMR1_StopTimer();
extern void TMR2_StartTimer();
extern void TMR2_StopTimer();

#ifdef	__cplusplus
}
#endif

#endif	/* TMR_H */

