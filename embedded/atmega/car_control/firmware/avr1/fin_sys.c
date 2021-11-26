#include "fin_inc.h" 

unsigned int v_adc,v_set=512;
int dv;
volatile char word_respon;

void SYS_Setup(void){
  DDRB|=1<<0|1<<1;
  PORTB|=1<<0|1<<1;
}

void calc(void){
  
  dv=v_adc-v_set;
  
  if(dv<-5||dv>5){
    
    if(v_adc>v_set){
      word_respon='R';
    }
    
    else if(v_adc<v_set){
      word_respon='L';
    }
    
    else{
      word_respon='R';
    }
    
  }
  
  else{
    word_respon='S';
  }
  
}

void respon(void){
  if(word_respon=='R'){
    kanan();
  }
  else if(word_respon=='L'){
    kiri();
  }
  else if(word_respon=='S'){
    stop();
  }
}

void kanan(void){
  PORTB|=1<<0;
  PORTB&=~(1<<1);
}

void kiri(void){
  PORTB|=1<<1;
  PORTB&=~(1<<0);
}

void stop(void){
  PORTB|=1<<0|1<<1;
}

