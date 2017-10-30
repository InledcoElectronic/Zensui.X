#include "IR_Decode.h"
#include "pwm.h"
#include "led.h"
#include "rtc.h"
#include "i2c.h"
#include "command.h"

#define MULTIPLE            10

#define STEP                1

#define MAX_PERCENTAGE      100
#define _XTAL_FREQ          16000000

LedPara_t gLedPara;
LedRunPara_t gLedRunPara;

static void UpdatePWM() 
{
    PWM1_LoadDutyValue(gLedRunPara.nCurrentLum[0]);
    PWM2_LoadDutyValue(gLedRunPara.nCurrentLum[1]);
    //    PWM3_LoadDutyValue(gLedPara.nCurrentLum[2]);
    //    PWM4_LoadDutyValue(gLedPara.nCurrentLum[3]);
}
void SaveLedPara()
{
    unsigned char len = sizeof( gLedPara );
    unsigned char offset = 0;
    unsigned char cnt;
    unsigned char *pbuf = (unsigned char *) &gLedPara;
    INTERRUPT_GlobalInterruptDisable();
    while ( len > 0 )
    {
        cnt = len >= PAGE_COUNT ? PAGE_COUNT : len;
        I2C_WriteBuffer( EEPROM_SUBA_ADDR + offset , pbuf + offset, cnt);
        offset += cnt;
        len -= cnt;
    }
    INTERRUPT_GlobalInterruptEnable();
}
void LedUpdate()
{
    unsigned char i;
    
    gLedPara.fAuto = IR_ReveiveDataStructure.fModeAuto;
    gLedPara.fWhiteOn = IR_ReveiveDataStructure.fWhiteOnOff;
    gLedPara.fBlueOn = IR_ReveiveDataStructure.fBlueOnOff;
    gLedPara.sunriseHour = IR_ReveiveDataStructure.RiseTimeHour;
    gLedPara.sunriseMin = IR_ReveiveDataStructure.RiseTimeMinute;
    gLedPara.sunsetHour = IR_ReveiveDataStructure.SunsetTimeHour;
    gLedPara.sunsetMin = IR_ReveiveDataStructure.SunsetTimeMinute;
    
    for(i = 0;i < CHANNEL_COUNT;i++)
    {
        gLedPara.bright[i] = IR_ReveiveDataStructure.ManualBrightPercen[i];
        gLedPara.dayBright[i] = IR_ReveiveDataStructure.RiseBrightPercen[i];
        gLedPara.nightBright[i] = IR_ReveiveDataStructure.SunsetBrightPercen[i];
    }
    SaveLedPara();
}
void LedUpdatePara() 
{
    unsigned char i;

    for (i = 0; i < CHANNEL_COUNT; i++) 
    {
        if (gLedRunPara.nCurrentLum[i] + STEP < gLedRunPara.nTargetLum[i])
        {
            gLedRunPara.nCurrentLum[i] += STEP;
        } 
        else if (gLedRunPara.nCurrentLum[i] > gLedRunPara.nTargetLum[i] + STEP) 
        {
            gLedRunPara.nCurrentLum[i] -= STEP;
        } 
        else 
        {
            gLedRunPara.nCurrentLum[i] = gLedRunPara.nTargetLum[i];
        }
    }
    UpdatePWM();
}
void manualMode() 
{
    if(gLedPara.fAuto)
    {
        if (gLedPara.fWhiteOn) 
        {
            PWM1_Enable();
            gLedRunPara.nTargetLum[0] = (unsigned int)gLedPara.bright[0] * MULTIPLE;
        } 
        else 
        {
            PWM1_Disable();
            gLedRunPara.nTargetLum[0] = MIN_BRIGHTNESS;
        }
        if (gLedPara.fBlueOn) 
        {
            PWM2_Enable();
            gLedRunPara.nTargetLum[1] = (unsigned int)gLedPara.bright[1] * MULTIPLE;
        } 
        else 
        {
            PWM2_Disable();
            gLedRunPara.nTargetLum[1] = MIN_BRIGHTNESS;
        } 
        LedUpdatePara();
    }
}
void TimeChangeSec()
{
    gLedRunPara.nCurrentTime = (gCurrentTime.datatime.hour * 60 + gCurrentTime.datatime.minute) * 30 + gCurrentTime.datatime.second;
    gLedRunPara.sunrisetime = (gLedPara.sunriseHour * 60 + gLedPara.sunriseMin) * 30;
    gLedRunPara.sunsettime = (gLedPara.sunsetHour * 60 + gLedPara.sunsetMin) * 30;
}
void AutoMode()
{
    unsigned char i;
    unsigned char *pstartBright;
    unsigned char *pendBright;
    long signed int dTime;
    static unsigned char flag = 1;
    
    if(!gLedPara.fAuto)
    {  
        PWM1_Enable();
        PWM2_Enable();
        TimeChangeSec();

        if(gLedRunPara.sunrisetime == gLedRunPara.sunsettime)
        {
            for(i = 0;i < CHANNEL_COUNT;i++)
            {
                gLedRunPara.nCurrentLum[i] = (unsigned int)gLedPara.nightBright[i] * MULTIPLE;
            }
        }
        if(((gLedRunPara.sunrisetime < gLedRunPara.sunsettime) && (gLedRunPara.sunrisetime <= gLedRunPara.nCurrentTime) && (gLedRunPara.nCurrentTime < gLedRunPara.sunsettime)) 
                || ((gLedRunPara.sunrisetime > gLedRunPara.sunsettime) && ((gLedRunPara.nCurrentTime >= gLedRunPara.sunrisetime) || (gLedRunPara.nCurrentTime < gLedRunPara.sunsettime))))
        {
            dTime = gLedRunPara.nCurrentTime - gLedRunPara.sunrisetime;
            pstartBright = (unsigned char*)gLedPara.nightBright;
            pendBright = (unsigned char*)gLedPara.dayBright;   
        }
        else
        {
            dTime = gLedRunPara.nCurrentTime - gLedRunPara.sunsettime;
            if(dTime < 0)
            {
                dTime += 43200;
            }
            pstartBright = (unsigned char*)gLedPara.dayBright;
            pendBright = (unsigned char*)gLedPara.nightBright;
        }
        for(i = 0;i < CHANNEL_COUNT;i++)
        {
            if(pstartBright[i] <= pendBright[i])
            {
                if(dTime < (unsigned int)(pendBright[i] - pstartBright[i]) * MULTIPLE)
                {
                    gLedRunPara.nCurrentLum[i] = ((unsigned int)pstartBright[i] * MULTIPLE) + dTime;
                }
                else
                {
                    gLedRunPara.nCurrentLum[i] = (unsigned int)pendBright[i] * MULTIPLE;
                }
            }
            else
            {
                if(dTime < (unsigned int)(pstartBright[i] - pendBright[i]) * MULTIPLE)
                {
                    gLedRunPara.nCurrentLum[i] = ((unsigned int)pstartBright[i] * MULTIPLE) - dTime;
                }
                else
                {
                    gLedRunPara.nCurrentLum[i] = (unsigned int)pendBright[i] * MULTIPLE;
                }
            }
        }
        UpdatePWM();
    }
}
void LedParaInit()
{
    unsigned char i;

    I2C_ReadBuffer(EEPROM_SUBA_ADDR, (unsigned char *) &gLedPara, sizeof (gLedPara));

    for (i = 0; i < CHANNEL_COUNT; i++)
    {
        if (gLedPara.bright[i] > MAX_PERCENTAGE) 
        {
            gLedPara.bright[i] = MAX_PERCENTAGE;
        }
        if (gLedPara.dayBright[i] > MAX_PERCENTAGE) 
        {
            gLedPara.dayBright[i] = MAX_PERCENTAGE;
        }
        if (gLedPara.nightBright[i] > MAX_PERCENTAGE) 
        {
            gLedPara.nightBright[i] = MAX_PERCENTAGE;
        }
    }
    if(gLedPara.sunriseHour > 23)
    {
       gLedPara.sunriseHour = 0; 
    }
    if(gLedPara.sunriseMin > 59)
    {
        gLedPara.sunriseMin = 0;
    }
    if(gLedPara.sunsetHour > 23)
    {
        gLedPara.sunsetHour = 0;
    }
    if(gLedPara.sunsetMin > 59)
    {
        gLedPara.sunsetMin = 0;
    }
}
