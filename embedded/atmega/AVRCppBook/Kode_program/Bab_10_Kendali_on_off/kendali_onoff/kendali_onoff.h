//id:kendali_onoff.h,kendali_onoff
//4-8-2012,sidiknur@yahoo.com
#ifndef KENDALI_ONOFF_H_INCLUDED
#define KENDALI_ONOFF_H_INCLUDED

#include "pinout.h"

typedef enum{LOWER,EQUAL,OVER}state_t;

template<uint8_t MIN, uint8_t MAX, port_id_t p, uint8_t bit>
class KontrolerOnOff : PinOut<p,bit>
{
public:
    state_t Update(uint8_t setpoint, uint8_t actual)
    {
        uint8_t BA, BB;
        if((MAX-setpoint)>histerisis)
			BA = setpoint + histerisis;
		else
			BA = MAX;

		if(setpoint>histerisis)
			BB = setpoint - histerisis;
		else
			BB = MIN;

		if(actual>=BA){
		    Output::Clear();
            return OVER;
		}
		else if(actual <= BB){
		    Output::Set();
            return LOWER;
		}
		else
            return EQUAL;
    }
    void Change(uint8_t Histerisis){
        histerisis = Histerisis;
    }
private:
    uint8_t setpoint;
    uint8_t actual;
    uint8_t histerisis;
    typedef PinOut<p,bit> Output;
};
#endif // KENDALI_ONOFF_H_INCLUDED
