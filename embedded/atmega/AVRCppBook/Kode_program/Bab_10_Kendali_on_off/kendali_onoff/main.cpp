//id:main.cpp,kendali_onoff
//4-8-2012,sidiknur@yahoo.com
#include <avr/io.h>
#include <util/delay.h>
#include "kendali_onoff7seg3dgt.h"
#include "kendali_onoffLCD.h"

int main(void)
{
#if 1
    TermoControlOnOff7seg<0,150,PD,0,//MIN,MAX,pOut,bOut
                 PD,1,PD,2,PD,3, //LEDs
                 PB,0,PB,1,PB,2, //74595
                 PB,3,           //BTN
                 0,1> TermCon;   //Pot,LM35
#else
    TermoControlOnOffLCD<0,150,PD,0,//MIN,MAX,pOut,bOut
                 PB,3,PB,0,PB,1,PD,7,PD,4,PD,3, //LCD
                 0,1> TermCon;	//Pot,LM35

#endif

    TermCon.Histerisis(2);
    while(1){
        TermCon.Action();
        _delay_ms(100);
    }
    return 0;
}
