#include "i2c.h"
#include "pwm.h"

#define ERROR_COUNT             10
#define EEPROM_ADDR             0xA0                //24C02µØÖ·

#define _XTAL_FREQ 16000000

void I2C_Initialize()
{
    SSP1STATbits.SMP = 0;
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.CKP = 0;
    SSP1CON1bits.SSPM = 0x08;
    SSP1CON3bits.SDAHT = 0;
    SSP1ADD = 39;
}

static void CheckSSPIF()
{
	while(!SSP1IF);
	SSP1IF	= 0;
}

void I2C_WriteByte(unsigned char suba,unsigned char byte)
{
    unsigned char n = 0;
    
    SSP1CON2bits.SEN = 1;
    CheckSSPIF();
    
    SSP1BUF = EEPROM_ADDR;
    CheckSSPIF();   
    while(SSP1CON2bits.ACKSTAT)
    {
        n ++;
        if(n > ERROR_COUNT)
        {
            return ;
        }
        __delay_ms(1);
        SSP1CON2bits.SEN = 1;
        CheckSSPIF();
        SSP1BUF = EEPROM_ADDR;
        CheckSSPIF();  
    } 
    
    SSP1BUF = suba;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return ;
    }
    
    SSP1BUF = byte;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return ;
    }
    
    SSP1CON2bits.PEN = 1;
    CheckSSPIF();
}
void I2C_WriteBuffer(unsigned char suba,unsigned char *pbuf,unsigned char len)
{
    unsigned char i = 0;
    unsigned char n = 0;
    
    SSP1CON2bits.SEN = 1;
    CheckSSPIF();
    
    SSP1BUF = EEPROM_ADDR;
    CheckSSPIF();
    while(SSP1CON2bits.ACKSTAT)
    {
        n ++;
        if(n > ERROR_COUNT)
        {
            return ;
        }
        __delay_ms(1);
        SSP1CON2bits.SEN = 1;
        CheckSSPIF();
        SSP1BUF = EEPROM_ADDR;
        CheckSSPIF();  
    } 
    
    SSP1BUF = suba;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return ;    
    }
    
    for(i = 0;i < len;i ++)
    {
        SSP1BUF = *(pbuf + i);
        CheckSSPIF();
        if(SSP1CON2bits.ACKSTAT)
        {
            return ;
        }
    }
    
    SSP1CON2bits.PEN = 1;
    CheckSSPIF();
}
unsigned char I2C_ReadByte(unsigned char suba)
{
    unsigned char n = 0;
    unsigned char dat;
    
    SSP1CON2bits.SEN = 1;
    CheckSSPIF();
    
    SSP1BUF = EEPROM_ADDR;
    CheckSSPIF();   
    while(SSP1CON2bits.ACKSTAT)
    {
        n ++;
        if(n > ERROR_COUNT)
        {
            return 0;
        }
        __delay_ms(1);
        SSP1CON2bits.SEN = 1;
        CheckSSPIF();
        SSP1BUF = EEPROM_ADDR;
        CheckSSPIF();  
    } 

    SSP1BUF = suba;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return 0;
    }
    
    SSP1CON2bits.RSEN = 1;
    CheckSSPIF();
    SSP1BUF = EEPROM_ADDR + 1;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return 0;
    }
    
    SSP1CON2bits.RCEN = 1;
    CheckSSPIF();
    dat = SSP1BUF;
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    CheckSSPIF();
    
    SSP1CON2bits.PEN = 1;
    CheckSSPIF();
    
    return dat;
}
void I2C_ReadBuffer(unsigned char suba,unsigned char *pbuf,unsigned char len)
{
    unsigned char i = 0;
    unsigned char n = 0;
    
    SSP1CON2bits.SEN = 1;
    CheckSSPIF();
         
    SSP1BUF = EEPROM_ADDR;
    CheckSSPIF();
    while(SSP1CON2bits.ACKSTAT)
    {
        n ++;
        if(n > ERROR_COUNT)
        {
            return ;
        }
        __delay_ms(1);
        SSP1CON2bits.SEN = 1;
        CheckSSPIF();
        SSP1BUF = EEPROM_ADDR;
        CheckSSPIF();
    }
    
    SSP1BUF = suba;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return ;
    }
    
    SSP1CON2bits.RSEN = 1;
    CheckSSPIF();
    SSP1BUF = EEPROM_ADDR + 1;
    CheckSSPIF();
    if(SSP1CON2bits.ACKSTAT)
    {
        return ;
    }
    
    for(i = 0;i < len - 1;i ++)
    {
        SSP1CON2bits.RCEN = 1;
        CheckSSPIF();
        *(pbuf + i) = SSP1BUF;
        SSP1CON2bits.ACKDT = 0;
        SSP1CON2bits.ACKEN = 1;
        CheckSSPIF();
    }
    SSP1CON2bits.RCEN = 1;   
    CheckSSPIF();
    *(pbuf + len - 1) = SSP1BUF;
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    CheckSSPIF();
    
    SSP1CON2bits.PEN = 1;
    CheckSSPIF();
}
