#include "fin_inc.h"

void EXTI_Setup(void){
  DDRD&=~(1<<2|1<<3);
  PORTD|=1<<2|1<<3;
  MCUCR|=(0<<ISC01)|(0<<ISC00);
  MCUCR|=(0<<ISC11)|(0<<ISC10);
  GICR|=1<<INT0;
  GICR|=1<<INT1;
}

