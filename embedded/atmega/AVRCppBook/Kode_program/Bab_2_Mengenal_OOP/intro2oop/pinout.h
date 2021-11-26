//Id:pinout.h,intro2cpp,1-8-2012,sidiknur@yahoo.com
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

class PinOut{
public:
    PinOut(port_id_t port_id, uint8_t bit)
        :the_port_id(port_id), the_bit(bit)
    {
        ddr(the_port_id) |= _BV(the_bit);
    }
    void On(){
        port(the_port_id) |= _BV(the_bit);
    }
    void Off(){
        port(the_port_id) &= ~_BV(the_bit);
    }
private:
    port_id_t the_port_id;
    uint8_t the_bit;
};

#endif // PINOUT_H_INCLUDED
