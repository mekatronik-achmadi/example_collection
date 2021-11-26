//id:led.h,pinout_lanjut,1-8-2012,sidiknur@yahoo.com

#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include "pinout.h"

template<port_id_t p, uint8_t bit, active_t active>
struct LED : PinOut<p,bit>{
    static inline void On(){
        if(active==ACTIVE_HIGH)
            PinOut<p,bit>::Set();
        else
            PinOut<p,bit>::Clear();
    }
    static inline void Off(){
        if(active==ACTIVE_HIGH)
            PinOut<p,bit>::Clear();
        else
            PinOut<p,bit>::Set();
    }
};


#endif // LED_H_INCLUDED
