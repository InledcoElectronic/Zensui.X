/*
 * File:   mian.c
 * Author: Administrator
 *
 * Created on September 19, 2017, 11:05 AM
 */


#include "command.h"
#include "IR_Decode.h"
#include "i2c.h"
#include "led.h"
#include "rtc.h"
#include "pwm.h"
#include "tmr.h"

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

void main(void) 
{
    SYSTEM_Initialize();
    LedParaInit();
    
    TMR1_StartTimer();    
    TMR2_StartTimer();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    while(1)
    {
        CLRWDT();
        if(gRunState.fRecKey)
        {
            gRunState.fRecKey = 0; 
            LedUpdate();
            UpdateRTC();
        }
        if(PIR1bits.TMR2IF)
        {
            PIR1bits.TMR2IF = 0;
            manualMode();
        }
        if(gCurrentTime.datatime.fSec)
        {
            gCurrentTime.datatime.fSec = 0;
            AutoMode();
        }
    }
}
