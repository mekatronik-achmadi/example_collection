#include <mega16.h>

void main(void){
PORTC=0x20;
DDRC=0x40;
ACSR=0x80;
SFIOR=0x00;

while (1){
    if(PINC.5==1) PORTC.6=0;
    else PORTC.6=1;
    }
}
