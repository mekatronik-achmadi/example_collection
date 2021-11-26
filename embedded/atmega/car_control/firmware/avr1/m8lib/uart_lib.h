#ifndef UART_H
#define UART_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//input pin is RXD as serial data input
//output pin is TXD	as serial data output

//==============================================================================

static int uart_putchar(char ch,FILE*stream)
{
	if(ch=='\n'){uart_putchar('\r',stream);}
	while ((UCSRA & (1 << UDRE)) == 0) {};
	UDR=ch;
	return 0;
}

static int uart_getchar(FILE*stream)
{
	char temp;
	while ((UCSRA & (1 << RXC)) == 0) {};
	temp=UDR;
	uart_putchar(temp,stream);
	return(temp);
}
static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);
static FILE uart_stdin=FDEV_SETUP_STREAM(NULL,uart_getchar,_FDEV_SETUP_READ);

#define UART_In		stdin=&uart_stdin
#define UART_Out	stdout=&uart_stdout

//==============================================================================

#define RX UCSRB|=1<<RXEN
#define TX UCSRB|=1<<TXEN

#define RX_IT UCSRB|=1<<RXCIE
#define TX_IT UCSRB|=1<<TXCIE

#define UART_Baudrate(x) 	UBRRH=(((F_CPU / (x * 16UL))) - 1)>>8;UBRRL=(((F_CPU / (x * 16UL))) - 1)
#define UART_Mode_8n1 UCSRC|=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)

#define TX_IRQ		ISR(USART_TXC_vect)
#define RX_IRQ 		ISR(USART_RXC_vect)
#define TX8535_IRQ	ISR(USART_TX_vect)

#define IRQ_Start sei()

#endif