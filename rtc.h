/* 
 * File:   rtc.h
 * Author: Administrator
 *
 * Created on September 20, 2017, 10:16 AM
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef union
{
    struct
    {
        unsigned   fSec :1;
        unsigned   fMin :1;
        unsigned   fRsv :6;
        
        unsigned char second;
        unsigned char minute;
        unsigned char hour;
    }datatime;
    unsigned char array[4];
}DateTime_t;

volatile DateTime_t gCurrentTime;

extern void UpdateRTC();
extern void RunRTC();

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

