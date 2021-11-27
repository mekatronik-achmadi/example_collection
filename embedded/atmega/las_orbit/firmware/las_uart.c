#include "avr_header.h"

#define baud 9600

static int uart_putchar(char ch,FILE*stream)
{
    if(ch=='\n'){uart_putchar('\r',stream);}
    while ((UCSR0A & (1 << UDRE0)) == 0) {};
    UDR0=ch;
    return 0;
}

static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);

void UART_Setup(void){
    UCSR0B|=1<<TXEN0;
    UBRR0H=(((F_CPU / (baud * 16UL))) - 1)>>8;UBRR0L=(((F_CPU / (baud * 16UL))) - 1);
    UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);
    stdout=&uart_stdout;
}
