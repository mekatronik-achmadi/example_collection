//id:main.cpp,tes_adc,2-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal
#include <avr/io.h>
#include <stdlib.h>

#include "adc.h"
#include "textlcd.h"

int main(void)
{
    uint16_t data;
    char str[10];

    Adc<ADC_REF_AVCC,ADC_RES10,0> Potensio;
    Adc<ADC_REF_2V56,ADC_RES8,1> SensorSuhu;
    TextLCD<PB,0,PB,1,PB,3,PD,3,PD,4,PD,5,16> Display;

    while(1){
        data = Potensio.Get();
        Display.GotoXY(1,1);
        Display.PutStr("Pot=");
        utoa(data,str,10);
        Display.PutStr(str);
        Display.PutStr("    ");

        data = SensorSuhu.Get();
        Display.GotoXY(2,1);
        Display.PutStr("LM35=");
        utoa(data,str,10);
        Display.PutStr(str);
        Display.PutStr("    ");
    }

    return 0;
}
