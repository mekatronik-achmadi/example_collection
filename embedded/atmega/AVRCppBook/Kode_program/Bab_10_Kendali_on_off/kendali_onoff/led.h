//id:led.h,pinout_lanjut,1-8-2012,sidiknur@yahoo.com

#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include "pinout.h"

template<port_id_t p, uint8_t bit, active_t active>
struct LED : PinOut<p,bit>{
    typedef PinOut<p,bit> this_pin;
    static inline void On(){
        if(active==ACTIVE_HIGH)
            this_pin::Set();
        else
            this_pin::Clear();
    }
    static inline void Off(){
        if(active==ACTIVE_HIGH)
            this_pin::Clear();
        else
            this_pin::Set();
    }
};

template<port_id_t p, uint8_t bit, active_t active>
struct Relay : LED<p,bit,active>{};

#endif // LED_H_INCLUDED
