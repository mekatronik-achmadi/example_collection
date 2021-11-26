#ifndef UART_SOFT_H_INCLUDED
#define UART_SOFT_H_INCLUDED

#include <util/delay.h>
#include "pinout.h"
#include "pinin.h"

#define UART_SOFT_CHAR_DELAY    1  //milisecond

#define BIT_TIME_CONST(baud)           (1000000UL/baud)
#define uart_soft_bit_delay(baud)       _delay_us(BIT_TIME_CONST(baud))
#define uart_soft_half_bit_delay(baud)  _delay_us(BIT_TIME_CONST(baud)/2)

typedef enum{
    BAUD_1200 = 1200,
    BAUD_4800 = 4800,
    BAUD_9600 = 9600,
    BAUD_19200 = 19200,
    BAUD_38400 = 38400,
    BAUD_57600 = 57600,
    BAUD_76800 = 76800,
    BAUD_115200= 115200
}uart_baud_t;

template<port_id_t pTxD, uint8_t bTxD,
         port_id_t pRxD, uint8_t bRxD,
         uart_baud_t baud>
class UartSoft_8N1 : PinOut<pTxD,bTxD>, PinIn<pRxD,bRxD,PULLUP>
{
public:
    UartSoft_8N1(){
        TxD::Set();
    }
    void PutChar(char data){
        uart_soft_tx_low();     //send start
        for(register uint8_t i=0x01; i>0; i<<=1){ //send LSB first
            if(data & i)
                uart_soft_tx_high();
            else
                uart_soft_tx_low();
        }
        uart_soft_tx_high();    //send stop
        //_delay_ms(UART_SOFT_CHAR_DELAY);
    }

    void PutStr(const char *str){
        while(*str){
            PutChar(*str);
            str++;
        }
    }
    bool GetChar(char *data){
        uint8_t temp = 0;
        bool sts = false;

        while(RxD::IsSet());

        uart_soft_bit_delay(baud);
        for(register uint8_t i=0x01; i>0; i<<=1){
            uart_soft_half_bit_delay(baud);
            if(RxD::IsSet())
                temp |= 0x80;
            if(i<0x80)
                temp >>= 1;
            uart_soft_half_bit_delay(baud);
        }
        *data = temp;
        uart_soft_half_bit_delay(baud);
        if(RxD::IsSet()) //check stop bit
            sts = true;
        uart_soft_half_bit_delay(baud);
        return sts;
    }

    uint8_t GetBuf(uint8_t *buf, uint8_t len){

        uint8_t data;

        while(len--){
            if(GetChar(&data)){
                *buf = data;
                buf++;
            }
            else
                return false;
        }
        return true;
    }

private:
    typedef PinOut<pTxD,bTxD> TxD;
    typedef PinOut<pRxD,bRxD> RxD;

    static inline void uart_soft_tx_low(void){
        TxD::Clear();
        uart_soft_bit_delay(baud);
    }

    static inline void uart_soft_tx_high(void){
        TxD::Set();
        uart_soft_bit_delay(baud);
    }
};


#endif // UART_SOFT_H_INCLUDED
