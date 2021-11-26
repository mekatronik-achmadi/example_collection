//id:sevenseg_7448.h,sevenseg_7448,1-8-2012,sidiknur@yahoo.com
#ifndef SEVENSEG_7448_H_INCLUDED
#define SEVENSEG_7448_H_INCLUDED

#include "portout.h"

typedef enum{
    NIBLE_HIGH,
    NIBLE_LOW
}nible_t;

template <port_id_t p, nible_t nible>
struct NibleOut{
    NibleOut(){
        ddr(p) |= ((nible==NIBLE_HIGH)? 0xf0 : 0x0f);
    }
    static inline void Put(uint8_t data){
        if(nible==NIBLE_HIGH)
            PortPutHighNible<p>(data);
        else
            PortPutLowNible<p>(data);
    }
};

template<port_id_t p2, nible_t n2, port_id_t p1, nible_t n1, port_id_t p0, nible_t n0>
class SevenSeg7448_3dgt : NibleOut<p2,n2>, NibleOut<p1,n1>, NibleOut<p0,n0>
{
public:
    void Put(uint16_t data){
        if(data>999)
            data = 999;

        uint8_t ratusan = data / 100;
        uint8_t puluhan = (data-100*ratusan) / 10;
        uint8_t satuan = (data-100*ratusan) % 10;

        Dgt2::Put(ratusan);
        Dgt1::Put(puluhan);
        Dgt0::Put(satuan);
    }
private:
    typedef NibleOut<p2,n2> Dgt2;
    typedef NibleOut<p1,n1> Dgt1;
    typedef NibleOut<p0,n0> Dgt0;
};


#endif // SEVENSEG_7448_H_INCLUDED
