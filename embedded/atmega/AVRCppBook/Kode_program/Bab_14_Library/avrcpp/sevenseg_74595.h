//id:sevenseg_74595.h,sevenseg_74595,
//1-8-2012,sidiknur@yahoo.com
#ifndef SEVENSEG_74595_H_INCLUDED
#define SEVENSEG_74595_H_INCLUDED

#include <stdlib.h>
#include "sevenseg.h"
#include "_74595.h"

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
            *p = sevenseg_pattern<COMMON_CATHODE>(*p-48);
            len++;
            p++;
        }
        //kirim pattern blank
        uint8_t j=DIGIT_NUM-len;
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
