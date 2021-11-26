//id:portin.h,portin,sidiknur@yahoo.com
//22-8-2012

#ifndef PORTIN_H_INCLUDED
#define PORTIN_H_INCLUDED

#include "pinin.h"

template<port_id_t p, pullup_t pullup>
struct PortIn{
    PortIn(){
        ddr(p) = 0x00;
        if(pullup==PULLUP)
            port(p) = 0xff;
    }
    static inline uint8_t Get(){
        return pin(p);
    }
};

#endif // PORTIN_H_INCLUDED
