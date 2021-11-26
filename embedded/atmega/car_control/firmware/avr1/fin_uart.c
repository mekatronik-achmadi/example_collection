#include "fin_inc.h"

static int uart_putchar(char ch,FILE*stream)
{
	if(ch=='\n'){uart_putchar('\r',stream);}
	while ((UCSRA & (1 << UDRE)) == 0) {};
	UDR=ch;
	return 0;
}

static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);

void UART_Setup(void){
  stdout=&uart_stdout;
  UCSRB|=1<<RXEN|1<<TXEN;
  UBRRH=(((F_CPU / (9600 * 16UL))) - 1)>>8;UBRRL=(((F_CPU / (9600 * 16UL))) - 1);
  UCSRC|=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
}
