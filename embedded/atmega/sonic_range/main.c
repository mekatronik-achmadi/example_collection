/*
Project:	pak_den
Board:		uno
MCU:		16MHzatmega328
FRENQUENCY:	16000000

Created using QtCreator
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////

// beberapa pre-define

#define trig_pin    3 //PD3
#define echo_pin    2 //PD2 - INT0
#define led_pin     5 //PB5

#define DELAY_MS    100
#define baud_rate   9600

////////////////////////////////////////////////////////////

// Implementasi fungsi tunda
void delay_ms(unsigned int time){
    unsigned int i;

    for(i=0;i<time;i++){
        _delay_ms(1);
    };
    return;
}

void delay_us(unsigned int time){
    unsigned int i;

    for(i=0;i<time;i++){
        _delay_us(1);
    };
    return;
}

////////////////////////////////////////////////////////////

// Implementasi standar I/O data ASCII
static int uart_putchar(char ch,FILE*stream)
{
    if(ch=='\n'){uart_putchar('\r',stream);}
    while ((UCSR0A & (1 << UDRE0)) == 0) {};
    UDR0=ch;
    return 0;
}

static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);

////////////////////////////////////////////////////////////

// inisialisasi variable global
volatile unsigned int tick, cacah;

////////////////////////////////////////////////////////////

// referensi fungsi-fungsi global

static void tim0_active(unsigned char stt){
    // timer clock senilai 1/8 dari clock utama
    if(stt==1){
        TCCR0B|=(1<<CS00);
    }
    else if(stt==0){
        TCCR0B&=~(1<<CS00);
    }
}

static void sensor_ukur(void){
    tick = 0;
    cacah = 0;

    // kirim sinyal trigger
    PORTD |= (1<< trig_pin);
    delay_us(10);
    PORTD &= ~(1<< trig_pin);
    delay_ms(100);

    // aktifkan Timer 0 untuk pencacahan
    tim0_active(1);
}

////////////////////////////////////////////////////////////

int main()
{

    // pengaturan LED
    // Arduino : pin Digital 5
    // ATMega  : port B5

    // diatur sebagai output
    DDRB |= 1<< led_pin;

    // nilainya low (led mati)
    PORTB &= ~(1<< led_pin);
////////////////////////////////////////////////////////////
    // inisialisasi fitur komunikasi serial UART (Universal Asychronous Rx Tx)

    // aktifasi register serial (1 bit)
    UCSR0B|=1<<TXEN0;

    // pengaturan baudrate atau kecepatan (16 bit)
    UBRR0H=(((F_CPU / (baud_rate * 16UL))) - 1)>>8;
    UBRR0L=(((F_CPU / (baud_rate * 16UL))) - 1);

    // pengaturan mode 8n1 (8 bit)
    UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);

    // retarget fungsi printf()
    stdout=&uart_stdout;
////////////////////////////////////////////////////////////
    // aktifasi pin untuk Trigger HC-SR04
    // Arduino pin : Digital 3
    // ATmega pin : port D3

    // diatur sebagai output
    DDRD |= 1<< trig_pin;

    // nilai awal Low
    PORTD &= ~(1<< trig_pin);

////////////////////////////////////////////////////////////
    // aktifasi pin untuk Echo HC-SR04
    // Arduino pin : Digital 2
    // ATMega pin : pin D2
    // Interrupt : INT0

    // diatur sebagai input
    DDRD &= ~(1<< echo_pin);

    // nilai di pull-up
    PORTD |= 1<< echo_pin;

    // Interrtupt pada Falling-Edge
    EICRA |= 1<<ISC01;

    // Aktifasi interrupt INT0
    EIMSK |= 1 << INT0;

////////////////////////////////////////////////////////////
    // inisialisasi Timer 0 untuk pencacah

    // aktifasi Timer Overflow interrupt
    TIMSK0 |=1<<TOIE0;

    // deaktifasi awal
    tim0_active(0);

////////////////////////////////////////////////////////////

    // aktifkan semua interrupt
    sei();

////////////////////////////////////////////////////////////

    while (1)
    {

        // mulai ukur nilai
        sensor_ukur();
        delay_ms(100);

        // kirim nilai register lewat serial
        printf("%i\n\r",cacah);

        // tunda untuk pengukuran selanjutnya
        delay_ms(500);
    }

}

////////////////////////////////////////////////////////////

// fungsi-fungsi interrupt handler

// interrupt untuk IC Timer Overflow
ISR(TIMER0_OVF_vect){
    tick++;
}

// interrupt untuk INT 0
ISR(INT0_vect){
    tim0_active(0);

    if((tick<=0) || (tick>250)){
        cacah = 0;
    }
    else{
        cacah = tick;
    }
}
