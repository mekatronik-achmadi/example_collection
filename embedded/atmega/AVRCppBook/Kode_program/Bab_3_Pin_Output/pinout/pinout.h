//Id:pinout.h,pinout,1-8-2012,sidiknur@yahoo.com
//ATmega8
#ifndef PINOUT_H_INCLUDED
#define PINOUT_H_INCLUDED

typedef enum{
    PB,
    PC,
    PD
}port_id_t;

#define port(p) (p==PB?PORTB:(p==PC?PORTC:PORTD))
#define ddr(p)  _SFR_IO8(_SFR_IO_ADDR(port(p))-1)
#define pin(p)  _SFR_IO8(_SFR_IO_ADDR(port(p))-2)

template<port_id_t p>
static inline void PortSetBit(uint8_t bit){
    port(p) |= _BV(bit);
}

template<port_id_t p>
static inline void PortClearBit(uint8_t bit){
    port(p) &= ~_BV(bit);
}

template<port_id_t p, uint8_t bit>
class PinOut{
public:
    PinOut(){
        ddr(p) |= _BV(bit);
    }
    static inline void On(){ PortSetBit<p>(bit); }
    static inline void Off(){ PortClearBit<p>(bit);}
};

#endif // PINOUT_H_INCLUDED
