#include "uart.h"

FILE uart_out = {0} ;
FILE uart_in = {0} ;

static int uart_putchar(char ch,FILE*stream)
{
    if(ch=='\n'){uart_putchar('\r',stream);}
    while ((UCSRA & (1 << UDRE)) == 0) {};
    UDR=ch;
    return 0;
}

static int uart_getchar(FILE*stream)
{
    (void) stream;
    char temp;

    while ((UCSRA & (1 << RXC)) == 0) {};
    temp=UDR;
    return(temp);
}

static void uart_baud(void){
    UBRRH=(((F_CPU / (BAUDRATE * 16UL))) - 1)>>8;
    UBRRL=(((F_CPU / (BAUDRATE * 16UL))) - 1);
}

static void uart_retarget(void){
	fdev_setup_stream (&uart_out, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream (&uart_in, NULL, uart_getchar, _FDEV_SETUP_READ);
    stdout = &uart_out;
    stdin = &uart_in;
}

void uart_init(void){

	DDRD |= 1<<1;

    UCSRB |= 1<<RXEN | 1<<TXEN;
    UCSRC |= 1<<UCSZ1| 1<<UCSZ0;

    uart_baud();
    uart_retarget();

#if USE_RECV_INT
    UCSRB |= 1<<RXCIE;
    sei();
#endif // USE_RECV_INT

}
