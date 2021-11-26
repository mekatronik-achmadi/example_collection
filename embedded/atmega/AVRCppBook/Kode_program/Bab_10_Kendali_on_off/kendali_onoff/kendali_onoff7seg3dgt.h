//id:kendali_onoff7seg3dgt.h,kendali_onoff
//4-8-2012,sidiknur@yahoo.com

#ifndef KENDALI_ONOFF7SEG3DGT_H_INCLUDED
#define KENDALI_ONOFF7SEG3DGT_H_INCLUDED

//termocontrol On-Off dengan:
//setpoint berupa potensio,
//sensor suhu   : LM35
//indikator     : LED_RED (over), LED_GREEN (fit), LED_YELLOW (lower)
//display       : 3 digit seven segment untuk menampilkan setpoint (ketika sebuah
//                tombol sedang ditekan) atau aktual (ketika tombol tidak ditekan)
#include "adc.h"
#include "led.h"
#include "sevenseg_74595.h"
#include "tombol.h"
#include "kendali_onoff.h"

template <uint8_t MIN, uint8_t MAX, port_id_t pOut, uint8_t bOut,
          port_id_t pLED_RED, uint8_t bLED_RED,
          port_id_t pLED_GREEN, uint8_t bLED_GREEN,
          port_id_t pLED_YELLOW, uint8_t bLED_YELLOW,
          port_id_t pSER, uint8_t bSER,
          port_id_t pSCK, uint8_t bSCK,
          port_id_t pRCK, uint8_t bRCK,
          port_id_t pBTN, uint8_t bBTN,
          uint8_t AdcChSetpoint, uint8_t AdcChActual>
class TermoControlOnOff7seg : KontrolerOnOff<MIN,MAX,pOut,bOut>,
                          LED<pLED_RED,bLED_RED,ACTIVE_HIGH>,
                          LED<pLED_GREEN,bLED_GREEN,ACTIVE_HIGH>,
                          LED<pLED_YELLOW,bLED_YELLOW,ACTIVE_HIGH>,
                          SevenSeg_74595<pSER,bSER,pSCK,bSCK,pRCK,bRCK,3>,
                          Tombol<pBTN,bBTN,ACTIVE_LOW>,
                          Adc<ADC_REF_AVCC,MAX<=255?ADC_RES8:ADC_RES10,AdcChSetpoint>,
                          Adc<ADC_REF_2V56,ADC_RES8,AdcChActual>
{
public:
    void Action(){
        uint8_t setpoint;
        uint8_t actual;
        state_t flag;

        setpoint = Setpoint::Get()*MAX/((MAX<=255)?255:1023);
        actual = Actual::Get();

        flag = Controler::Update(setpoint,actual);

        //perbaruhi tampilan LED
        if(flag==OVER){
            LED_RED::On();
            LED_GREEN::Off();
            LED_YELLOW::Off();
        }
        else if(flag==LOWER){
            LED_RED::Off();
            LED_GREEN::Off();
            LED_YELLOW::On();
        }
        else{
            LED_RED::Off();
            LED_GREEN::On();
            LED_YELLOW::Off();
        }
        //perbaruhi tampilan seven segment
        if(BTN::IsPressed())
            SevenSeg::Put(setpoint);
        else
            SevenSeg::Put(actual);
    }
    void Histerisis(uint8_t his){
        Controler::Change(his);
    }

private:
    typedef KontrolerOnOff<MIN,MAX,pOut,bOut> Controler;
    typedef LED<pLED_RED,bLED_RED,ACTIVE_HIGH> LED_RED;
    typedef LED<pLED_GREEN,bLED_GREEN,ACTIVE_HIGH> LED_GREEN;
    typedef LED<pLED_YELLOW,bLED_YELLOW,ACTIVE_HIGH> LED_YELLOW;
    typedef SevenSeg_74595<pSER,bSER,pSCK,bSCK,pRCK,bRCK,3> SevenSeg;
    typedef Tombol<pBTN,bBTN,ACTIVE_LOW> BTN;
    typedef Adc<ADC_REF_AVCC,MAX<=255?ADC_RES8:ADC_RES10,AdcChSetpoint> Setpoint;
    typedef Adc<ADC_REF_2V56,ADC_RES8,AdcChActual> Actual;
};


#endif // KENDALI_ONOFF7SEG3DGT_H_INCLUDED
