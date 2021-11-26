#ifndef UART_SOFT_H_INCLUDED
#define UART_SOFT_H_INCLUDED

#include <util/delay.h>
#include "pinout.h"
#include "pinin.h"

#define bit_delay(BAUD)         _delay_us(1000000UL/BAUD)
#define half_bit_delay(BAUD)    _delay_us(1000000UL/BAUD/2)

typedef enum{
    BAUD_1200   = 1200,
    BAUD_2400   = 2400,
    BAUD_4800   = 4800,
    BAUD_9600   = 9600,
    BAUD_19200  = 19200
}uart_soft_baud_t;

template<port_id_t pTXD, uint8_t bTXD,
         port_id_t pRXD, uint8_t bRXD,
         uart_soft_baud_t BAUD>
class UartSoft_8N1 : PinOut<pTXD,bTXD>, PinIn<pRXD,bRXD,PULLUP>
{
public:
    UartSoft_8N1(){
        TXD::Set();
    }
    static inline void PutChar(char data){
        uart_soft_tx_low();     //send start
        for(register uint8_t i=0x01; i>0; i<<=1){//send LSB first
            if(data & i)
                uart_soft_tx_high();
            else
                uart_soft_tx_low();
        }
        uart_soft_tx_high();    //send stop
        //_delay_ms(UART_SOFT_CHAR_DELAY);
    }

    static inline void PutStr(const char *str){
        while(*str){
            PutChar(*str);
            str++;
        }
    }

    static inline char GetChar(void){
        uint8_t temp = 0;

        while(RXD::IsSet());

        bit_delay(BAUD);
        for(register uint8_t i=0x01; i>0; i<<=1){
            half_bit_delay(BAUD);
            if(RXD::IsSet())
                temp |= 0x80;
            if(i<0x80)
                temp >>= 1;
            half_bit_delay(BAUD);
        }
        bit_delay(BAUD);
        return temp;
    }
private:
    typedef PinOut<pTXD,bTXD> TXD;
    typedef PinIn<pRXD,bRXD,PULLUP> RXD;

    //send low to TXD then delay one bit
    static inline void uart_soft_tx_low(void){
        TXD::Clear();
        bit_delay(BAUD);
    }

    //send high to TXD then delay one bit
    static inline void uart_soft_tx_high(void){
        TXD::Set();
        bit_delay(BAUD);
    }
};

#endif // UART_SOFT_H_INCLUDED
