#include "pwm.h"

void PWM1_Initialize()
{
    PWM1CONbits.PWM1EN = 1;
    PWM1CONbits.PWM1OE = 1;
    PWM1CONbits.PWM1POL = 0;
    
    PWM1DCH = 0x00;
    PWM1DCL = 0x00;
}
void PWM1_Enable()
{
    PWM1CONbits.PWM1EN = 1;    
}
void PWM1_Disable()
{
    PWM1CONbits.PWM1EN = 0;
}
void PWM1_LoadDutyValue(unsigned int dutyValue)
{
    PWM1DCL = (dutyValue & 0x03)<<6;
    PWM1DCH = dutyValue >> 2;
}
void PWM2_Initialize()
{
    PWM2CONbits.PWM2EN = 1;
    PWM2CONbits.PWM2OE = 1;
    PWM2CONbits.PWM2POL = 0;
    
    PWM2DCH = 0x00;
    PWM2DCL = 0x00;
}
void PWM2_Enable()
{
    PWM2CONbits.PWM2EN = 1;    
}
void PWM2_Disable()
{
    PWM2CONbits.PWM2EN = 0;
}
void PWM2_LoadDutyValue(unsigned int dutyValue)
{
    PWM2DCL = (dutyValue & 0x03) << 6;
    PWM2DCH = dutyValue >> 2;
}
void PWM3_Initialize()
{
    PWM3CONbits.PWM3EN = 1;
    PWM3CONbits.PWM3OE = 1;
    PWM3CONbits.PWM3POL = 0;
    
    PWM3DCH = 0x00;
    PWM3DCL = 0x00;
}
void PWM3_Enable()
{
    PWM3CONbits.PWM3EN = 1;    
}
void PWM3_Disable()
{
    PWM3CONbits.PWM3EN = 0;
}
void PWM3_LoadDutyValue(unsigned int dutyValue)
{
    PWM3DCL = (dutyValue & 0x03) << 6;
    PWM3DCH = dutyValue >> 2;
}
void PWM4_Initialize()
{
    PWM4CONbits.PWM4EN = 1;
    PWM4CONbits.PWM4OE = 1;
    PWM4CONbits.PWM4POL = 0;
    
    PWM4DCH = 0x00;
    PWM4DCL = 0x00;
}
void PWM4_Enable()
{
    PWM4CONbits.PWM4EN = 1;    
}
void PWM4_Disable()
{
    PWM4CONbits.PWM4EN = 0;
}
void PWM4_LoadDutyValue(unsigned int dutyValue)
{
    PWM4DCL = (dutyValue & 0x03) << 6;
    PWM4DCH = dutyValue >> 2;
}