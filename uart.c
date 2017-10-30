#include "uart.h"
#include <pic.h>

void USART_Initialize()
{
    TXSTAbits.CSRC   = 0;
    TXSTAbits.TX9    = 0;    
    TXSTAbits.TXEN   = 1;                   //ʹ�ܴ��ڷ���
    TXSTAbits.SYNC   = 0;                   //�첽
    TXSTAbits.SENDB  = 0;
    TXSTAbits.BRGH   = 1;                   //����
    
    RCSTAbits.SPEN   = 1;                   //ʹ�ܽ���
    RCSTAbits.RX9    = 0;                   //8λ
    RCSTAbits.SREN   = 0;
    RCSTAbits.CREN   = 1;                   //ʹ�ܽ�����
    
    BAUDCONbits.SCKP    = 0;
    BAUDCONbits.BRG16   = 1;                //16λ�����ʷ�����
    BAUDCONbits.WUE     = 0;
    BAUDCONbits.ABDEN   = 0;
    
    SPBRGH  = 0x01;
    SPBRGL  = 0xA0;  
    PIE1bits.RCIE    = 1;
    PIR1bits.RCIF    = 0;
}
void USART_WriteByte(unsigned char byte)
{
    while(!TXSTAbits.TRMT);
    TXREG = byte;
}
void USART_WriteNum(unsigned int num)
{
    USART_WriteByte('0' + num/10000);
    USART_WriteByte('0' + num/1000%10);
    USART_WriteByte('0' + num/100%10);
    USART_WriteByte('0' + num/10%10);
    USART_WriteByte('0' + num%10);
}
void USART_WriteString(const unsigned char *pstr)
{
    while(*pstr != '\0')
    {
        USART_WriteByte(*pstr ++);
    }
}


