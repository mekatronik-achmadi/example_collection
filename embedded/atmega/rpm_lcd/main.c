// preprocessor untuk avr-gcc
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

// header untuk ALCD
#include "alcd.h"

// definisi maksimum tick untuk reset periode
#define tick_all 13107000

// variabel rpm, tick, dan jumlah gigi
volatile unsigned int rpm,tick,N_gigi;

// variabel untuk LCD
char text[16];

// fungsi utama dan inisiasi
int main(void){
	//=== pengaturan register Timer 1 ===//

	// nilai clock Fsc/1 atau 8Mhz
	TCCR1B|=(0<<CS12)|(0<<CS11)|(1<<CS10);

	// matikan Input Capture Noise Canceller
	TCCR1B&=~(1<<ICNC1);

	// input capture pada Rising Edge
	TCCR1B|=1<<ICES1;

	// aktifkan Interrupt Timer Overflow
	TIMSK|=1<<TOIE1;

	// aktifkan Interrupt Input Capture
	TIMSK|=1<<TICIE1;

	// reset semua variabel
	TCNT1=0; // variabel Input Capture
	rpm=0; // variabel RPM

	// jumlah gigi 1
	N_gigi = 1;

	// jalankan semua interrupt
	sei();

	// Bersihkan LCD
	LCD_Init();

	while(1){
		// tampilkan RPM ke LCD
		sprintf(text,"rpm= %5i",rpm);
		LCD_String(0,0,text);
	}

	return 0;
}

// Interrupt Input Capture untuk baca frekuensi
ISR(TIMER1_CAPT_vect){

	tick=ICR1;
	TCNT1=0;

	if(tick>0){
		rpm=tick_all/tick;
	}

	if(N_gigi>0){
		rpm = rpm/N_gigi;
	}
}

// Interrupt Timer Overflow untuk reset bila frekuensi 0
ISR(TIMER1_OVF_vect){
      rpm=0;
}
