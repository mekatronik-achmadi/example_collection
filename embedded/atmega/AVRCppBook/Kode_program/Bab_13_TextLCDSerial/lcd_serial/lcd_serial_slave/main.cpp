//id:main.cpp,lcd_serial_slave
//13-8-2012,sidiknur@yahoo.com
//Atmega8,11059200Hz-internal

#include <avr/io.h>
#include "../lcd_serial_slave.h"

int main(void)
{
    TextLCDSerialSlave<PD,2,PD,3,
                PD,4,PD,5,PD,6,PD,7,16> lcd;

    while(1){
        lcd.Update();
    }

    return 0;
}
