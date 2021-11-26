#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

typedef enum{
    BAUD_1200 = 1200,
    BAUD_4800 = 4800,
    BAUD_9600 = 9600,
    BAUD_19200 = 19200,
    BAUD_38400 = 38400,
    BAUD_57600 = 57600,
    BAUD_76800 = 76800,
    BAUD_115200= 115200
}uart_baud_t;

#define MYUBRR(BAUD) 	(F_CPU/16/BAUD-1)

template<uart_baud_t baud=BAUD_9600>
class Uart_8N1
{
public:
    Uart_8N1(){
        UBRRH = (uint8_t)(MYUBRR(baud)>>8);
        UBRRL = (uint8_t)MYUBRR(baud);
        UCSRB = (1<<RXEN)|(1<<TXEN);
        //Set frame format: 8data, 1stop bit
        UCSRC = (1<<URSEL)|(3<<UCSZ0);
    }

    void PutChar(char ch){
        while ( bit_is_clear(UCSRA,UDRE) ){}
        UDR = ch;
    }

    void PutStr(const char *str){
        while(*str){
            PutChar(*str);
            str++;
        }
    }

    char GetChar(void){
        while ( bit_is_clear(UCSRA,RXC) ){}
        return UDR;
    }

private:

};

#endif // UART_H_INCLUDED
