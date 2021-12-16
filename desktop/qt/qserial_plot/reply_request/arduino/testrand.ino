/*
Project:	testrand
Board:		mega
MCU:		atmega2560	
FRENQUENCY:	16000000

Created using Qt Creator
*/

#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile uint8_t var1,var2,var3;

//****************************************************

int uart_getchar(FILE*stream);
int uart_putchar(char ch,FILE*stream);
void UART_init(uint16_t uart_baud);

char inString[16];
FILE uart_out = {0} ;
FILE uart_in = {0} ;

//******************************
//* SETUP AND LOOP SECTION
//* Always leave setup() and loop() functions at the end of file
void setup() {                
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
    pinMode(13, OUTPUT);
    UART_init(38400);
}

void loop() {
	digitalWrite(13, HIGH);   // set the LED on
    delay(500);              // wait for a second

    var1 = rand()%256;
    var2 = rand()%256;
    var3 = rand()%256;

    digitalWrite(13, LOW);    // set the LED off
    delay(500);              // wait for a second
}

//********************************************

ISR(USART0_RX_vect){

    scanf("%s",inString);

    if(strcmp(inString,"data")==0){
      printf("%3i,%3i,%3i",var1,var2,var3);
    }

    return;
}

int uart_putchar(char ch,FILE*stream)
{
    if(ch == '\n'){uart_putchar('\r',stream);}
    while ((UCSR0A & _BV(UDRE0)) == 0) {};
    UDR0 = ch;
    return 0;
}

int uart_getchar(FILE*stream)
{
    char temp;
    while ((UCSR0A & _BV( RXC0)) == 0) {};
    temp = UDR0;
    //uart_putchar(temp,stream);
    return(temp);
}

void UART_init(uint16_t uart_baud){

    UCSR0B|=1<<RXEN0;
    UCSR0B|=1<<TXEN0;
    UCSR0B|=1<<RXCIE0;

    UBRR0H=(((F_CPU / (uart_baud * 16UL))) - 1)>>8;
    UBRR0L=(((F_CPU / (uart_baud * 16UL))) - 1);

    UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);

    fdev_setup_stream (&uart_out, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream (&uart_in, NULL, uart_getchar, _FDEV_SETUP_READ);
    stdout=&uart_out;
    stdin=&uart_in;

    sei();
}
//********************************************
