#ifndef _74595_H_INCLUDED
#define _74595_H_INCLUDED

#include "pinout.h"

template <port_id_t pSER, uint8_t bSER,
          port_id_t pSCK, uint8_t bSCK,
          port_id_t pRCK, uint8_t bRCK>
class _74595 :  PinOut<pSER,bSER>,
                PinOut<pSCK,bSCK>,
                PinOut<pRCK,bRCK>
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
#endif // _74595_H_INCLUDED
