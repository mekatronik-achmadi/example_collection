#include "ta_uart.h"

char var_str[CHAR_LONG];
extern uint16_t adc0;

static int uart_putchar(char ch,FILE *stream)
{
    if(ch=='\n'){uart_putchar('\r',stream);}
    while ((UCSR0A & (1 << UDRE0)) == 0) {};
    UDR0=ch;
    return 0;
}

static int uart_getchar(FILE *stream)
{
    (void) stream;
    char temp;

    while ((UCSR0A & (1 << RXC0)) == 0) {};
    temp=UDR0;
//    uart_putchar(temp,stream);
    return(temp);
}

static FILE uart_stdout=FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);
static FILE uart_stdin=FDEV_SETUP_STREAM(NULL,uart_getchar,_FDEV_SETUP_READ);

void ta_uart_Init(void){
    UBRR0H=(((F_CPU / (BAUDRATE * 16UL))) - 1)>>8;
    UBRR0L=(((F_CPU / (BAUDRATE * 16UL))) - 1);

    UCSR0B |= 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0;

    UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);

    stdin=&uart_stdin;
    stdout=&uart_stdout;
}

ISR(USART0_RX_vect){

    //pastikan nerima End Of Line (EOL) sebagai LF,
    //bukan CR atau CRLF
    scanf("%s",var_str);

    if(strcmp(var_str,"test")==0){
        printf("serial OK \n");
    }
	else if(strcmp(var_str,"testmmc")==0){
		ta_mmc_WriteTest();
        printf("mmc written \n");
    }
    else if(strcmp(var_str,"adc")==0){
        printf("%4i \n",adc0);
    }
    else{
        printf("%s? \n",var_str);
    }


    return;
}
