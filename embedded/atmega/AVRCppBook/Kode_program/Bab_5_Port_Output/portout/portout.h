//id:portout.h,portout,1-8-2012,sidiknur@yahoo.com
//Atmega8
#ifndef PORTOUT_H_INCLUDED
#define PORTOUT_H_INCLUDED

#include "pinout.h"


template<port_id_t p>
static inline void PortPut(uint8_t data){
    port(p) = data;
}

template<port_id_t p>
static inline void PortPutHighNible(uint8_t data){
    port(p) &= 0x0f;
    port(p) |= data<<4;
}

template<port_id_t p>
static inline void PortPutLowNible(uint8_t data){
    port(p) &= 0xf0;
    port(p) |= data & 0x0f;
}

template <port_id_t p>
struct PortOut{
    PortOut(){
        ddr(p) = 0xff;
    }
    static inline void Put(uint8_t data){
        PortPut<p>(data);
    }
    static inline void PutHighNible(uint8_t data){
        PortPutHighNible<p>(data);
    }
    static inline void PutLowNible(uint8_t data){
        PortPutLowNible<p>(data);
    }
};

#endif // PORTOUT_H_INCLUDED
