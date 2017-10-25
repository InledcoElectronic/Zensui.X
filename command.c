#include "command.h"
#include "osccon.h"
#include "pin.h"
#include "pwm.h"
#include "tmr.h"
#include "i2c.h"
#include "rtc.h"
#include "interruptOnChange.h"
#include "IR_Decode.h"

void SYSTEM_Initialize()
{
    OSCCON_Initialize();
    PIN_Initialize();
    PWM1_Initialize();
    PWM2_Initialize();
    PWM3_Initialize();
    PWM4_Initialize();
    TMR0_Initialize();
    TMR1_Initialize();    
    TMR2_Initialize();
    I2C_Initialize();
    InterruptOnChange_Initialize();
}
void interrupt INTERRUPT_interruptManager ()
{
    if(IOCBFbits.IOCBF7)
    {
        IOCBFbits.IOCBF7 = 0;
        Decode();
    }
    else if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        gCurrentTime.datatime.fSec = 1;
        RunRTC();
    }
}
