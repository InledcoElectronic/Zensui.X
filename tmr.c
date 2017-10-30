#include "tmr.h"

void TMR0_Initialize()
{
    OPTION_REG = 0x06;                      //ps  1:128
}
void TMR1_Initialize()
{
    T1CONbits.TMR1CS  = 0x02; 
    T1CONbits.T1CKPS  = 0x00;               //KPS  0    
    T1CONbits.T1OSCEN = 1;   
    T1CONbits.nT1SYNC = 0;    
    T1CONbits.TMR1ON  = 0;
    T1GCONbits.TMR1GE = 0;
    
    PIR1bits.TMR1IF   = 0;
    PIE1bits.TMR1IE   = 1;
}
void TMR2_Initialize()
{
    T2CONbits.T2OUTPS = 0x00;           //OUTPS   0
    T2CONbits.T2CKPS  = 0x03;           //KPS     64
    T2CONbits.TMR2ON  = 0;
    TMR2 = 0;
    PR2 = 249;
}
void TMR1_StartTimer()
{
    T1CONbits.TMR1ON = 1;
}
void TMR1_StopTimer()
{
    T1CONbits.TMR1ON = 0;    
}
void TMR2_StartTimer()
{
    T2CONbits.TMR2ON = 1;
}
void TMR2_StopTimer()
{
    T2CONbits.TMR2ON = 0;
}