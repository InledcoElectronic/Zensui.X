#include "interruptOnChange.h"

void InterruptOnChange_Initialize()
{
    IOCBNbits.IOCBN7 = 1;
    IOCBPbits.IOCBP7 = 1;
    IOCAF = 0;
    IOCBF = 0;
    
    INTCONbits.IOCIE = 1;
}
