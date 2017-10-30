/* 
 * File:   uart.h
 * Author: Admin
 *
 * Created on 2017年10月27日, 上午9:39
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define UART_DEBUG
    
extern void USART_Initialize();
extern void USART_WriteByte(unsigned char byte);
extern void USART_WriteNum(unsigned int num);
extern void USART_WriteString(const unsigned char *pstr);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

