/* 
 * File:   command.h
 * Author: Administrator
 *
 * Created on September 20, 2017, 9:55 AM
 */

#ifndef COMMAND_H
#define	COMMAND_H

#ifdef	__cplusplus
extern "C" {
#endif
   
#include <pic.h>
    
#define INTERRUPT_GlobalInterruptEnable()       (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()      (INTCONbits.GIE = 0)
#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE = 0)
    
extern void SYSTEM_Initialize();   

#ifdef	__cplusplus
}
#endif

#endif	/* COMMAND_H */

