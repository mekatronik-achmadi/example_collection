//id:main.cpp,sevenseg_direct,1-8-2012,sidiknur@yahoo.com
#ifndef SEVENSEG_DIRECT_H_INCLUDED
#define SEVENSEG_DIRECT_H_INCLUDED

#include "sevenseg.h"
#include "portout.h"

template<port_id_t p1, port_id_t p0>
class SevenSeg_Direct_2dgt : PortOut<p1>, PortOut<p0>
{
public:
    static inline void Put(uint8_t data){
        if(data>99)
            data = 99;
        uint8_t puluhan = data / 10;
        uint8_t satuan = data % 10;
        uint8_t pattern;

        pattern = sevenseg_pattern<COMMON_CATHODE>(puluhan);
        Dgt1::Put(pattern);
        pattern = sevenseg_pattern<COMMON_CATHODE>(satuan);
        Dgt0::Put(pattern);
    }
private:
    typedef PortOut<p1> Dgt1;
    typedef PortOut<p0> Dgt0;
};

#endif // SEVENSEG_DIRECT_H_INCLUDED
