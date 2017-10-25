/* 
 * File:   i2c.h
 * Author: Administrator
 *
 * Created on September 19, 2017, 1:48 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic.h>
    
#define EEPROM_SUBA_ADDR        0x20
#define PAGE_COUNT              8
    
extern void I2C_Initialize();
extern void I2C_WriteByte(unsigned char suba,unsigned char byte);
extern void I2C_WriteBuffer(unsigned char suba,unsigned char *pbuf,unsigned char len);
extern unsigned char I2C_ReadByte(unsigned char suba);
extern void I2C_ReadBuffer(unsigned char suba,unsigned char *pbuf,unsigned char len);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

