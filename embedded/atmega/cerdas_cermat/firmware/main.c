#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define MEJA_A 0
#define MEJA_B 1
#define MEJA_C 2

#define MEJA_NETRAL 4

#define DIGIT_RATUS 0
#define DIGIT_PULUH 1
#define DIGIT_SATU  2

/**
 * @brief Variable status berisi Meja yg berusaha jawab
 */
volatile uint8_t meja_jawab = MEJA_NETRAL;

/**
 * @brief Variable status meja yg jawab salah
 */
volatile uint8_t meja_salah = MEJA_NETRAL;

/**
 * @brief Variable storage nilai meja A
 */
volatile uint16_t nilai_meja_a = 0;

/**
 * @brief Variable storage nilai meja B
 */
volatile uint16_t nilai_meja_b = 0;

/**
 * @brief Variable storage nilai meja C
 */
volatile uint16_t nilai_meja_c = 0;

/**
 * @brief Waktu tunda microsecond
 * @param uint16 Waktu tunda
 */
void tunda_us(unsigned int time){
    unsigned int i;
    for(i=0;i<time;i++){ _delay_us(1); };
    return;
}

/**
 * @brief Waktu tunda millisecond
 * @param uint16 Waktu tunda
 */
void tunda_ms(unsigned int time){
    unsigned int i;
    for(i=0;i<time;i++){ _delay_ms(1); };
    return;
}

/**
 * @brief BCD to 7-Segment inisiasi
 */
static void bcd_display_init(void){
    DDRC|=(1<<0)|(1<<1)|(1<<2)|(1<<3);
    DDRE|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
    DDRB|=(1<<0)|(1<<1)|(1<<2);

    PORTE|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
    PORTB|=(1<<0)|(1<<1)|(1<<2);
}

/**
 * @brief Toggle 4511 Latch status
 * @param uint8 Table Group (0...2)
 * @param uint8 Position (0...2)
 */
static void bcd_toggle_latch(uint8_t table, uint8_t pos){
    uint8_t disp;

    disp = table*3+pos;
    switch(disp){
        case 0: PORTE^=(1<<0);break;
        case 1: PORTE^=(1<<1);break;
        case 2: PORTE^=(1<<2);break;
        case 3: PORTE^=(1<<3);break;
        case 4: PORTE^=(1<<4);break;
        case 5: PORTE^=(1<<5);break;
        case 6: PORTB^=(1<<0);break;
        case 7: PORTB^=(1<<1);break;
        case 8: PORTB^=(1<<2);break;
    }
}

/**
 * @brief Set Value to Display Segment
 * @param uint8 Table Group (0...2)
 * @param uint8 Position (0...2)
 * @param uint8 Value (0...9)
 */
static void bcd_display_set(uint8_t table, uint8_t pos,uint8_t val){
    bcd_toggle_latch(table,pos);

    if(val<10)PORTC = 0b00000000 | val;

    bcd_toggle_latch(table,pos);
}

/**
 * @brief Set value using table group and value integer
 * @param uint8 Table Group (0...2)
 * @param uint8 Value (0...999)
 */
static void bcd_display_int(uint8_t table, uint16_t nilai){
    uint8_t ratus, puluh, satu;

    if(nilai<999){
        satu = nilai % 10;
        puluh = ((nilai % 100)-satu)/10;
        ratus = (nilai - (puluh*10) - satu)/100;

        bcd_display_set(table,DIGIT_RATUS,ratus);
        bcd_display_set(table,DIGIT_PULUH,puluh);
        bcd_display_set(table,DIGIT_SATU,satu);
    }
}

/**
 * @brief External Interrupt Inisiasi
 */
static void ext_interrupt_init(void){
    // PD0 Falling Edge Interrupt
    DDRD &= ~(1<<0); PORTD |= 1<<0;
    EICRA |= (0<<ISC00) | ((1<<ISC01));
    EIMSK |= (1<<INT0); EIFR |= (1<<INT0);

    // PD1 Falling Edge Interrupt
    DDRD &= ~(1<<1); PORTD |= 1<<1;
    EICRA |= (0<<ISC10) | ((1<<ISC11));
    EIMSK |= (1<<INT1); EIFR |= (1<<INT1);

    // PD2 Falling Edge Interrupt
    DDRD &= ~(1<<2); PORTD |= 1<<2;
    EICRA |= (0<<ISC20) | ((1<<ISC21));
    EIMSK |= (1<<INT2); EIFR |= (1<<INT2);

    // PD3 Falling Edge Interrupt
    DDRD &= ~(1<<3); PORTD |= 1<<3;
    EICRA |= (0<<ISC30) | ((1<<ISC31));
    EIMSK |= (1<<INT3); EIFR |= (1<<INT3);

    // PE6 Falling Edge Interrupt
    DDRE &= ~(1<<6); PORTE |= 1<<6;
    EICRB |= (0<<ISC60) | ((1<<ISC61));
    EIMSK |= (1<<INT6); EIFR |= (1<<INT6);

    // PE7 Falling Edge Interrupt
    DDRE &= ~(1<<7); PORTE |= 1<<7;
    EICRB |= (0<<ISC70) | ((1<<ISC71));
    EIMSK |= (1<<INT7); EIFR |= (1<<INT7);
}

/**
 * @brief Inisiasi LED Peserta
 */
static void led_peserta_init(void) {
    DDRA |= (1<<MEJA_A)|(1<<MEJA_B)|(1<<MEJA_C);

    PORTA &= ~(1<<MEJA_A);
    PORTA &= ~(1<<MEJA_B);
    PORTA &= ~(1<<MEJA_C);
}

/**
 * @brief Default Interrupt state for next
 */
static void juri_next_state(void){
    EIMSK |= (1<<INT0);
    EIMSK |= (1<<INT1);
    EIMSK |= (1<<INT2);

    PORTA &= ~(1<<MEJA_A);
    PORTA &= ~(1<<MEJA_B);
    PORTA &= ~(1<<MEJA_C);
}

/**
 * @brief Main function
 */
int main(void){

    ext_interrupt_init();
    bcd_display_init();
    led_peserta_init();

    // set all Interrupt active
    sei();
    
    while(1){
        bcd_display_int(MEJA_A,nilai_meja_a);
        bcd_display_int(MEJA_B,nilai_meja_b);
        bcd_display_int(MEJA_C,nilai_meja_c);
        tunda_ms(500);
	}
}

/**
 * Interrupt tombol Meja A
 */
ISR(INT0_vect){

    if(meja_salah!=MEJA_A){
        meja_jawab = MEJA_A;
        PORTA |= (1<<MEJA_A);

        EIMSK &= ~(1<<INT1);
        EIMSK &= ~(1<<INT2);
    }

    return;
}

/**
 * Interrupt tombol Meja B
 */
ISR(INT1_vect){

    if(meja_salah!=MEJA_B){
        meja_jawab = MEJA_B;
        PORTA |= (1<<MEJA_B);

        EIMSK &= ~(1<<INT0);
        EIMSK &= ~(1<<INT2);
    }

    return;
}

/**
 * Interrupt tombol Meja C
 */
ISR(INT2_vect){

    if(meja_salah!=MEJA_C){
        meja_jawab = MEJA_C;
        PORTA |= (1<<MEJA_C);

        EIMSK &= ~(1<<INT0);
        EIMSK &= ~(1<<INT1);
    }

    return;
}

/**
 * Interrupt tombol Juri Next
 */
ISR(INT3_vect){

    meja_jawab = MEJA_NETRAL;
    meja_salah = MEJA_NETRAL;

    juri_next_state();

    return;
}

/**
 * Interrupt tombol Lock Salah
 */
ISR(INT6_vect){

    if(meja_salah==MEJA_NETRAL){
        meja_salah = meja_jawab;
        juri_next_state();
    }

    return;
}

/**
 * Interrupt tombol Juri Nilai
 */
ISR(INT7_vect){

    switch(meja_jawab){
        case MEJA_A: if(meja_salah!=MEJA_A)nilai_meja_a += 5; break;
        case MEJA_B: if(meja_salah!=MEJA_B)nilai_meja_b += 5; break;
        case MEJA_C: if(meja_salah!=MEJA_C)nilai_meja_c += 5; break;
    }

    meja_jawab = MEJA_NETRAL;
    meja_salah = MEJA_NETRAL;

    juri_next_state();

    return;
}
