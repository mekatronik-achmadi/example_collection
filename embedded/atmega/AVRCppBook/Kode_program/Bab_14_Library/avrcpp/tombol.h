//id:tombol.h,pinin,5-8-2012,sidiknur@yahoo.com
//Atmega8
#ifndef TOMBOL_H_INCLUDED
#define TOMBOL_H_INCLUDED
#include "pinin.h"

template<port_id_t p, uint8_t bit, active_t active>
struct Tombol : PinIn<p,bit,PULLUP>
{
    typedef PinIn<p,bit,PULLUP> tombol;
    static inline bool IsPressed(){
        if(active==ACTIVE_LOW)
            return tombol::IsClear();
        else
            return tombol::IsSet();
    }
};
#endif // TOMBOL_H_INCLUDED
