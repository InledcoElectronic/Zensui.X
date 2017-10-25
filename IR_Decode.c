#include "IR_Decode.h"
#include "i2c.h"

#define DAT             RB7
#define USER_CODE       0x0A
#define TURE            1
#define FALSE           0

#define STATE_IDLE      0
#define	STATE_START     1				//ÆðÊ¼Âë
#define	STATE_BYTE_0	2				

tagRunPara_t   gRunPara;;
tagRunState_t  gRunState;
IrReveiveDataStructure_t IR_ReveiveDataStructure;

static unsigned char CheckSum(unsigned char *pbuf,unsigned char len)
{
    unsigned char result = 0x00;
    unsigned char i;
    for(i = 0;i < len;i ++)
    {
        result += *(pbuf + i);
    }
    return result;
}
void Decode()
{
    static unsigned char state = STATE_IDLE;
    static unsigned char rcv = 0;
    static unsigned char index = 0;
    if(DAT)
    {
        TMR0 = 0;
    }
    else
    {
        gRunPara.HighCount = TMR0;                   //16us
        switch(state)
        {
            case STATE_IDLE:
                state = STATE_START;
                break;
            case STATE_START:
                if((gRunPara.HighCount >= 140) && (gRunPara.HighCount <= 175))
                {
                    gRunPara.HighCount = 0;     
                    state = STATE_BYTE_0;
                }
                else
                {
                    state = STATE_IDLE;
                }
                break;
            case STATE_BYTE_0:
                if((gRunPara.HighCount > 38) && (gRunPara.HighCount < 54))
                {
                    gRunPara.HighCount = 0;
                    gRunPara.nBit ++;    
                }
                else if((gRunPara.HighCount > 15) && (gRunPara.HighCount < 31))
                {
                    gRunPara.HighCount = 0;
                    rcv |= 1 << gRunPara.nBit;
                    gRunPara.nBit ++;
                }
                else
                {
                    state = STATE_IDLE;
                }
                if(gRunPara.nBit >= 8)
                {
                    gRunPara.nBit = 0;
                    IR_ReveiveDataStructure.array[index] = rcv;
                    rcv = 0;
                    index ++;
                    if(index >= 14)
                    {
                        rcv = 0;
                        index = 0;
                        if(IR_ReveiveDataStructure.UserCode == USER_CODE)
                        {
                            if(CheckSum((unsigned char*)IR_ReveiveDataStructure.array,sizeof(IR_ReveiveDataStructure.array) - 1) == IR_ReveiveDataStructure.array[13])
                            {
                                gRunState.fRecKey = 1;
                            }
                        }
                        state = STATE_IDLE;
                    }
                }
                break;
            default:
                break;
        }
    }
}