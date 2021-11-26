#ifndef SEVENSEG_74595_H_INCLUDED
#define SEVENSEG_74595_H_INCLUDED

#include <stdlib.h>
#include "pinout.h"
#include "sevenseg.h"

template <port_id_t pSER, uint8_t bSER,
          port_id_t pSCK, uint8_t bSCK,
          port_id_t pRCK, uint8_t bRCK>
class _74595 : PinOut<pSER,bSER>, PinOut<pSCK,bSCK>, PinOut<pRCK,bRCK>
{
public:
    static inline void SendByte(uint8_t data){
        for(register uint8_t i=0x80; i>0; i>>=1){
            if(data & i)
                SER::Set();
            else
                SER::Clear();
            shift_clock();
        }
    }

    static inline void Put(uint8_t *buf, uint8_t len){
        while(len--){
            SendByte(*buf);
            buf++;
        }
        restore_clock();
    }
private:
    typedef PinOut<pSER,bSER> SER;
    typedef PinOut<pSCK,bSCK> SCK;
    typedef PinOut<pRCK,bRCK> RCK;
    static inline void shift_clock(){
        SCK::Set();
        SCK::Clear();
    }
    static inline void restore_clock(){
        RCK::Set();
        RCK::Clear();
    }
};

template <port_id_t pSER, uint8_t bSER,
          port_id_t pSCK, uint8_t bSCK,
          port_id_t pRCK, uint8_t bRCK,
          uint8_t DIGIT_NUM>
struct SevenSeg_74595 : _74595<pSER,bSER,pSCK,bSCK,pRCK,bRCK>
{
    static inline void Put(uint16_t data){
        char str[DIGIT_NUM+1];
        char *p = str;
        uint8_t len = 0;
        utoa(data,str,10);

        while(*p){
            *p = sevenseg_pattern(*p-48);
            len++;
            p++;
        }
        //kirim pattern blank
        uint8_t j=len-3;
        while(j--){
            Drv::SendByte(0);
        }
        //kirim pattern data
        Drv::Put((uint8_t*)str,len);
    }
private:
    typedef _74595<pSER,bSER,pSCK,bSCK,pRCK,bRCK> Drv;
};

#endif // SEVENSEG_74595_H_INCLUDED
