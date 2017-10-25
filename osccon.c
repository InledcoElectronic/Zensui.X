#include "osccon.h"

void OSCCON_Initialize()
{
    OSCCONbits.IRCF = 0x0F;
    OSCCONbits.SCS  = 0x00;
    while(!OSCSTATbits.HFIOFS);
}
