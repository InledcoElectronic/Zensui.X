#include "rtc.h"
#include "IR_Decode.h"

volatile DateTime_t gCurrentTime;

void UpdateRTC()
{
    gCurrentTime.datatime.hour = IR_ReveiveDataStructure.TimeHour;
    gCurrentTime.datatime.minute = IR_ReveiveDataStructure.TimeMinute;
}
void RunRTC()
{
    gCurrentTime.datatime.second ++;
    if(gCurrentTime.datatime.second > 29)
    {
        gCurrentTime.datatime.second = 0;
        gCurrentTime.datatime.minute ++;
        if(gCurrentTime.datatime.minute > 59)
        {
            gCurrentTime.datatime.minute = 0;
            gCurrentTime.datatime.hour ++;
            if(gCurrentTime.datatime.hour > 23)
            {
                gCurrentTime.datatime.hour = 0;
            }
        }
    }
}
