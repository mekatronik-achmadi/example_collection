//id:adc.h,tes_adc,sidiknur@yahoo.com
//2-8-2012,Atmega8
#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

typedef enum{
    ADC_REF_AREF=0,
    ADC_REF_AVCC=1,
    ADC_REF_2V56=3
}adc_ref_t;

typedef enum{
    ADC_RES8,
    ADC_RES10
}adc_res_t;

#define ADC_PS_2	1
#define ADC_PS_4	2
#define ADC_PS_8	3
#define ADC_PS_16	4
#define ADC_PS_32	5
#define ADC_PS_64	6
#define ADC_PS_128	7

//choose ADC_PS automatically
#define ADC_PS  (F_CPU/2<200000?1:\
                (F_CPU/4<200000?2:\
                (F_CPU/8<200000?3:\
                (F_CPU/16<200000?4:\
                (F_CPU/32<200000?5:\
                (F_CPU/64<200000?6:\
                7))))))

template<adc_ref_t ref, adc_res_t res, uint8_t ch>
class Adc{
public:
    Adc(){
        ADMUX = admux = ((res==ADC_RES8)?_BV(ADLAR):0) | (ref<<REFS0) | ch;
        ADCSRA = adcsra = _BV(ADEN) | _BV(ADSC) | ADC_PS;
    }
    uint16_t Get(){
        ADCSRA |= _BV(ADIF);//clear complete flag
        ADMUX = admux;      //config adc
        ADCSRA = adcsra;    //choose prescaler, enable ADC and start
        while( !(ADCSRA & _BV(ADIF)) ){} //wai until complete
        return res==ADC_RES8? ADCH : ADCW;
    }

private:
    uint8_t admux;
    uint8_t adcsra;
};

#endif // ADC_H_INCLUDED
