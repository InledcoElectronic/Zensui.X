#include "pin.h"

void PIN_Initialize()
{
    //TRISx
    TRISAbits.TRISA2 = 0;                   //PWM3
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;                   //DAT
    TRISCbits.TRISC1 = 0;                   //PWM4
    TRISCbits.TRISC3 = 0;                   //PWM2
    TRISCbits.TRISC5 = 0;                   //PWM1
    
    //ANSELx
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    
    //LATx
    LATAbits.LATA2   = 0;
    LATCbits.LATC1   = 0;
    LATCbits.LATC3   = 0;
    LATCbits.LATC5   = 0;
    
    //WPUx
    WPUBbits.WPUB7 = 1;
    WPUBbits.WPUB4 = 0;
    WPUBbits.WPUB6 = 0;
}
