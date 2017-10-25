/* 
 * File:   led.h
 * Author: Administrator
 *
 * Created on September 21, 2017, 11:09 AM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CHANNEL_COUNT 2
    
typedef struct{
    unsigned fAuto : 1;
    unsigned fWhiteOn : 1;
    unsigned fBlueOn : 1;
    unsigned rsv: 5;
    
    unsigned char bright[CHANNEL_COUNT];
    
    unsigned char sunriseHour;
    unsigned char sunriseMin;
    unsigned char dayBright[CHANNEL_COUNT];
    
    unsigned char sunsetHour;
    unsigned char sunsetMin;
    unsigned char nightBright[CHANNEL_COUNT];
}LedPara_t;
    
typedef struct
{
    unsigned int nCurrentTime;
    unsigned int sunrisetime;
    unsigned int sunsettime;
    
    unsigned int nTargetLum[CHANNEL_COUNT];
    unsigned int nCurrentLum[CHANNEL_COUNT];
}LedRunPara_t;

extern LedPara_t gLedPara;
extern LedRunPara_t gLedRunPara;

extern void LedUpdatePara() ;
extern void SaveLedPara();
extern void LedUpdate();
extern void manualMode();
extern void AutoMode();
extern void LedParaInit();

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

