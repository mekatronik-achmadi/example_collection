//id:kendali_onoffLCD.h,kendali_onoff
//4-8-2012,sidiknur@yahoo.com

#ifndef KENDALI_ONOFFLCD_H_INCLUDED
#define KENDALI_ONOFFLCD_H_INCLUDED

#include "adc.h"
#include "textlcd.h"
#include <string.h>
#include "kendali_onoff.h"

//termocontrol On-Off dengan:
//setpoint berupa potensio,
//sensor suhu   : LM35
//display       : TextLCD
template <uint8_t MIN, uint8_t MAX, port_id_t pOut, uint8_t bOut,
          port_id_t pRS, uint8_t bRS,
          port_id_t pEN, uint8_t bEN,
          port_id_t pD4, uint8_t bD4,
          port_id_t pD5, uint8_t bD5,
          port_id_t pD6, uint8_t bD6,
          port_id_t pD7, uint8_t bD7,
          uint8_t AdcChSetpoint, uint8_t AdcChActual>
class TermoControlOnOffLCD : KontrolerOnOff<MIN,MAX,pOut,bOut>,
                             TextLCD<pRS,bRS,pEN,bEN,pD4,bD4,pD5,bD5,pD6,bD6,pD7,bD7>,
                             Adc<ADC_REF_AVCC,MAX<=255?ADC_RES8:ADC_RES10,AdcChSetpoint>,
                             Adc<ADC_REF_2V56,ADC_RES8,AdcChActual>
{
public:
    TermoControlOnOffLCD(){
        Display::PutStr(" Termo Control  ");
        Display::GotoXY(2,1);
        Display::PutStr("Set=   ,Act=   C");

    }
    void Action(){
        uint8_t setpoint;
        uint8_t actual;
        int8_t flag;

        setpoint = Setpoint::Get()*MAX/((MAX<=255)?255:1023);
        actual = Actual::Get();

        flag = Controler::Update(setpoint,actual);

        //perbaruhi indikator
        if(flag>0){

        }
        else if(flag<0){

        }
        else{

        }
        //perbaruhi tampilan LCD
        char str[4];
        uint8_t len;
        utoa(setpoint,str,10);
        Display::GotoXY(2,5);
        len = 3-strlen(str);
        while(len--)
            Display::PutChar(' ');
        Display::PutStr(str);

        Display::GotoXY(2,13);
        utoa(actual,str,10);
        len = 3-strlen(str);
        while(len--)
            Display::PutChar(' ');
        Display::PutStr(str);
    }
    void Histerisis(uint8_t his){
        Controler::Change(his);
    }

private:
    typedef KontrolerOnOff<MIN,MAX,pOut,bOut> Controler;
    typedef TextLCD<pRS,bRS,pEN,bEN,pD4,bD4,pD5,bD5,pD6,bD6,pD7,bD7,16> Display;
    typedef Adc<ADC_REF_AVCC,MAX<=255?ADC_RES8:ADC_RES10,AdcChSetpoint> Setpoint;
    typedef Adc<ADC_REF_2V56,ADC_RES8,AdcChActual> Actual;
};

#endif // KENDALI_ONOFFLCD_H_INCLUDED
