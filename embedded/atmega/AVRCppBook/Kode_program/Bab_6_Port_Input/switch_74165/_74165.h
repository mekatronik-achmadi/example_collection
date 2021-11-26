//id:_75165.h,switch_74165,sidiknur@yahoo.com
//22-8-2012
//Atmega8, 8MHz-internal

#ifndef _74165_H_INCLUDED
#define _74165_H_INCLUDED

#include "pinin.h"

template<uint8_t chip_num,
        port_id_t pCLK, uint8_t bCLK,
		port_id_t pLD, uint8_t bLD,
		port_id_t pOUT, uint8_t bOUT>
class _74165 :  PinOut<pCLK,bCLK>,
                PinOut<pLD,bLD>,
                PinIn<pOUT,bOUT,PULLUP>
{
public:
    _74165(){
        LD::Set();
        CLK::Set();
    }

    void Get(uint8_t *data){
        uint8_t i=0;
        load();
        while(i++<chip_num){
            *data++=get8();
            clock();
        }
    }
private:
    typedef PinOut<pCLK,bCLK> CLK;
    typedef PinOut<pLD,bLD> LD;
    typedef PinIn<pOUT,bOUT,PULLUP> OUT;

    //clock is rising edge
    static inline void clock(void){
        CLK::Clear();
        CLK::Set();
    }

    //load occurs when PL=low
    static inline void load(void){
        LD::Clear();
        LD::Set();
    }

    static inline uint8_t get8(void){
        uint8_t data = 0;
        for(register uint8_t i=1; i<8; i++){
            if(OUT::IsSet())
                data |= 0x01;
            data <<= 1;
            clock();
        }
        if(OUT::IsSet())
            data |= 0x01;
        return data;
    }

};

#endif // _74165_H_INCLUDED
