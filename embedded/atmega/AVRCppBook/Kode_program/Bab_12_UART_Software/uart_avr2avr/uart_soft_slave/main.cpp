//id:main.cpp,uart_slave,uart_avr2avr
//12-8-2012,sidiknur@yahoo.com
//Atmega8,11059200Hz eksternal
#include <avr/io.h>

#include "../adc.h"
#include "../uart_soft.h"

#define CMD_READ_SUHU   'A'
#define CMD_READ_POT    'P'

int main(void)
{
    char cmd;
    uint16_t data;

    Adc<ADC_REF_AVCC,ADC_RES10,0> Potensio;
    Adc<ADC_REF_2V56,ADC_RES8,1> SensorSuhu;

    UartSoft_8N1<PD,6,PD,7,BAUD_9600> serial;

    while(1){
        cmd = serial.GetChar();

        if(cmd==CMD_READ_POT){
            data = Potensio.Get();
            serial.PutChar(data>>8);
            serial.PutChar(data & 0xff);
        }
        else
        if(cmd==CMD_READ_SUHU){
            data = SensorSuhu.Get();
            serial.PutChar(data);
        }

    }
    return 0;
}
