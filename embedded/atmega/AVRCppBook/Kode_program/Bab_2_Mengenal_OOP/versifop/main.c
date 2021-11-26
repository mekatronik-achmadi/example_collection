//Id:main.c,versifop,1-8-2012,sidiknur@yahoo.com
//ATmega8,8MHz-internal
#include <avr/io.h>
#include <util/delay.h>

#define ddr(p)  _SFR_IO8(_SFR_IO_ADDR(p)-1)
#define pin(p)  _SFR_IO8(_SFR_IO_ADDR(p)-2)

#define LED_MERAH_PORT  PORTB
#define LED_MERAH_BIT   1
#define LED_KUNING_PORT PORTC
#define LED_KUNING_BIT  2

#define LED_MERAH_init() ddr(LED_MERAH_PORT) |= \
                            _BV(LED_MERAH_BIT)
#define LED_MERAH_on()   LED_MERAH_PORT |= \
                            _BV(LED_MERAH_BIT)
#define LED_MERAH_off()  LED_MERAH_PORT &= \
                            ~_BV(LED_MERAH_BIT)

#define LED_KUNING_init() ddr(LED_KUNING_PORT) |= \
                            _BV(LED_KUNING_BIT)
#define LED_KUNING_on()   LED_KUNING_PORT |= \
                            _BV(LED_KUNING_BIT)
#define LED_KUNING_off()  LED_KUNING_PORT &= \
                            ~_BV(LED_KUNING_BIT)

int main(void)
{
    LED_MERAH_init();
    LED_KUNING_init();

    while(1){
        LED_MERAH_on();
        LED_KUNING_off();
        _delay_ms(500);

        LED_MERAH_off();
        LED_KUNING_on();
        _delay_ms(500);
    }
    return 0;
}
