/* 
 * File:   IR_Decode.h
 * Author: Administrator
 *
 * Created on September 20, 2017, 10:10 AM
 */

#ifndef IR_DECODE_H
#define	IR_DECODE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic.h>
    
typedef union
{
    struct
    {
        unsigned        UserCode        :4;
        unsigned        fReserved       :1;    
        unsigned        fWhiteOnOff     :1;  
        unsigned        fBlueOnOff      :1; 
        unsigned        fModeAuto       :1; 
        
        unsigned char   TimeHour;
        unsigned char   TimeMinute;  
        
        unsigned char   RiseTimeHour;
        unsigned char   RiseTimeMinute;
        unsigned char   RiseBrightPercen[2];
        
        unsigned char   SunsetTimeHour;
        unsigned char   SunsetTimeMinute;
        unsigned char   SunsetBrightPercen[2];
        
        unsigned char   ManualBrightPercen[2];
        unsigned char   XORCheck;
    };
    unsigned char array[14];
}IrReveiveDataStructure_t;

typedef struct
{
    unsigned   fRecKey        :1;
    unsigned   fReserved      :7;   
}tagRunState_t;

typedef struct
{  
    unsigned char   HighCount;
    unsigned char   LowCount;
    unsigned char   nBit;
}tagRunPara_t;

extern tagRunPara_t   gRunPara;;
extern tagRunState_t  gRunState;
extern IrReveiveDataStructure_t IR_ReveiveDataStructure;

extern void ResetState();
extern void Decode();

#ifdef	__cplusplus
}
#endif

#endif	/* IR_DECODE_H */

