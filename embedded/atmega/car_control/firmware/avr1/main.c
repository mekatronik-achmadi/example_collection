#include "fin_inc.h"

extern unsigned int v_adc,v_set;
extern int dv;
extern volatile char word_respon;

ISR(INT0_vect){
//   if(v_set<1000){
//     v_set=v_set+10;
//   }
  kanan();
}

ISR(INT1_vect){
//   if(v_set>20){
//     v_set=v_set-10;
//   }
  kiri();
}

void tunda(void){
  int i;
  for(i=0;i<1000;i++){
    _delay_ms(1);
  }
}

void uji(void){
  stop();
  tunda();
  
  kanan();
  tunda();
  tunda();
  
  stop();
  tunda();
  
  kiri();
  tunda();
  tunda();
}

int main(void){
  
  SYS_Setup();
  UART_Setup();
  ADC_Setup();
  EXTI_Setup();
  
  sei();
  
  while(1){
    
//     uji();
    
//     v_adc=read_adc(0);
//     calc();
    
//     if(!(PIND&1<<2)){
//       word_respon='L';
//     }else{_delay_ms(255);}
//     
//     if(!(PIND&1<<3)){
//       word_respon='R';
//     }else{_delay_ms(255);}
//     
//     printf("adc= %4i set= %4i dv= %4i res= %c \n",v_adc,v_set,dv,word_respon);
//     
//     respon();
//     tunda();
//     
//     word_respon='S';
//     respon();
//     _delay_ms(255);
    
    stop();
    
  }
  
}
