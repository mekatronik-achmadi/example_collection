//id:pinin.h,pinin,1-8-2012,sidiknur@yahoo.com

#ifndef PININ_H_INCLUDED
#define PININ_H_INCLUDED
#include "pinout.h"

typedef enum{
    NO_PULLUP,
    PULLUP
}pullup_t;

template<port_id_t p>
static inline bool PinIsSet(uint8_t bit){
    return ((pin(p) & _BV(bit))==_BV(bit));
}

template<port_id_t p>
static inline bool PinIsClear(uint8_t bit){
    return ( (pin(p) & _BV(bit))==0 );
}

template<port_id_t p, uint8_t bit, pullup_t pullup>
struct PinIn{
    PinIn(){
        ddr(p) &= ~_BV(bit);
        if(pullup==PULLUP)
            port(p) |= _BV(bit);
    }
    static inline bool IsSet(){
        return PinIsSet<p>(bit);
    }
    static inline bool IsClear(){
        return PinIsClear<p>(bit);
    }
};
#endif // PININ_H_INCLUDED
