#ifndef C_H
#define C_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

void delay_ms(unsigned int time){
	unsigned int i;
	
	for(i=0;i<time;i++){
		_delay_ms(1);
	};
}

void delay_us(unsigned int time){
	unsigned int i;
	
	for(i=0;i<time;i++){
		_delay_us(1);
	};
}

#define adds(x,y)	x+y
#define subs(x,y)	x-y
#define muls(x,y)	x*y
#define divs(x,y)	x/y
#define mods(x,y)	x%c
#define incre(x)	x++
#define decre(x)	x--

#define assign_equal(x,y)	x=y
#define	assign_adds(x,y)	x+=y
#define assign_subs(x,y)	x-=y
#define	assign_muls(x,y)	x*=y
#define assign_divs(x,y)	x/=y
#define assign_mods(x,y)	x%=y
#define assign_left(x,y)	x<<=y
#define	assign_right(x,y)	x>>=y

#define is_equal(x,y)		x==y		
#define is_not_equal(x,y)	x!=y
#define is_more(x,y)		x>y
#define is_less(x,y)		x<y
#define is_more_equal(x,y)	x>=y
#define is_less_equal(x,y)	x<=y

#define bit_and			&
#define bit_or			|
#define bit_xor			^
#define bit_not			~
#define bit_to_left		<<
#define bit_to_right	>>

#define logic_and		&&
#define	logic_or		||
#define	logic_not		!

#define sfr_Set(x,y)	x|=1<<y
#define sfr_Clear(x,y)	x&=~(1<<y)
#define sfr_IsHigh		(x&(1<<y))

// this is one line comment
/* this is multi-line comment */

/*
#include <systemheader.h>
#include "userheader.h"

#define var_const	1500
#define calc(x,y)	x*y

#if mcu==0
y=x*x;
#else
y=0;
#endif

#ifdef max
#define min 10
range=max-min;
#endif

uint16_t var_global;
volatile uint16_t var_interrupt

void calc_function(uint16_t var_parameter);

int main(void){
	uint16_ var_local;
	
	while(1){
		calc_function(var_local);
	};
}

void calc_function(uint16_t var_parameter){
	var_global=var_const*var_local;
}

IRQ_function(IRQ_vector){
	var_interrupt=var_interrupt+var_const;
}
*/

/*
uint8_t multiply(uint8_t x, uint8_t y){return x*y;}
uint8_t divide(void){uint8_t x,y=10;x=y/2;return x;}
void add(uint8_t x){x=x+1;}
void sub(void){uint8_t x;x=x-1;}
*/

/*
if(logic1){statement1;}
else if(logic2){statement2;}
else{statement3;}

switch(x){
	case a:statement1;break;
	case b:statement2;break;
	default:statement3;break;
}

if(logic){continue;}else{statement;}
*/

/*
while(logic){statement;};

for(i=0;i<a;i++){statement;};

do{statement}while(logic);
*/

/*
printf("anytext %c | %i | %u | %x | %l | %p | %f | %d | %s",v_char,v_int,v_uint16_t,v_hexa,v_long,v_pointer,v_float,v_double,v_string);
scanf("%c ^ %i ^ %u ^ %x ^ %l ^ %p ^ %f ^ %d ^ %s",&v_char^&v_int^&v_uint16_t^&v_hexa^&v_long^&v_pointer^&v_float^&v_double^v_string);

enum knownsymbol={'\r','\n','\\','\"','\'','\0'};

%<frontcoma>.<backcoma><specifier>

#ifdef float $(PRINTF_LIB_FLOAT)&&$(SCANF_LIB_FLOAT)
*/

#endif