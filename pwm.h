/* 
 * File:   pwm.h
 * Author: Administrator
 *
 * Created on September 19, 2017, 11:27 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic.h>
    
#define MAX_BRIGHTNESS          1000
#define MIN_BRIGHTNESS          0
    
extern void PWM1_Initialize();
extern void PWM1_Enable();
extern void PWM1_Disable();
extern void PWM2_Initialize();
extern void PWM2_Enable();
extern void PWM2_Disable();
extern void PWM3_Initialize();
extern void PWM3_Enable();
extern void PWM3_Disable();
extern void PWM4_Initialize();
extern void PWM4_Enable();
extern void PWM4_Disable();
extern void PWM1_LoadDutyValue(unsigned int dutyValue);
extern void PWM2_LoadDutyValue(unsigned int dutyValue);
extern void PWM3_LoadDutyValue(unsigned int dutyValue);
extern void PWM4_LoadDutyValue(unsigned int dutyValue);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

