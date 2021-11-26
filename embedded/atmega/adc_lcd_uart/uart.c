#include "uart.h"

extern uint16_t adc0;
char var_str[16];

static int uart_putchar(char ch,FILE*stream)
{
    if(ch=='\n'){uart_putchar('\r',stream);}
    while ((UCSR3A & (1 << UDRE3)) == 0) {};
    UDR3=ch;
    return 0;
}

static int uart_getchar(FILE*stream)
{
    (void) stream;
    char temp;

    while ((UCSR3A & (1 << RXC3)) == 0) {};
    temp=UDR3;
    return(temp);
}

static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);
static FILE uart_stdin=FDEV_SETUP_STREAM(NULL,uart_getchar,_FDEV_SETUP_READ);

void delay_ms(unsigned int time){
    unsigned int i;

    for(i=0;i<time;i++){
    _delay_ms(1);
    };
    return;
}

void UART_Init(void){
    UBRR3H=(((F_CPU / (BAUDRATE * 16UL))) - 1)>>8;
    UBRR3L=(((F_CPU / (BAUDRATE * 16UL))) - 1);

    UCSR3B |= 1<<RXEN3 | 1<<TXEN3 | 1<<RXCIE3;

    UCSR3C|=(1<<UCSZ31)|(1<<UCSZ30);

    stdin=&uart_stdin;
    stdout=&uart_stdout;

    sei();
}

ISR(USART3_RX_vect){

    scanf("%s",var_str);
    if(strcmp(var_str,"adc")==0){
        printf("adc0=%4i\n\r",adc0);
    }
    else{
        printf("%s?\n\r",var_str);
    }

    return;
}
