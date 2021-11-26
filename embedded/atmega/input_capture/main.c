#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "alcd.h"

#define save(alamat,data)   eeprom_write_byte((uint8_t*)alamat,data) //makro save eeprom
#define load(alamat)        eeprom_read_byte((uint8_t*)alamat) //makro load eeprom

#define RPM_ROMADDR			0x00     //alamat eeprom vI
#define N_GIGI				1        //jumlah gigi

// variabel untuk ukur periode
volatile uint32_t period32;
volatile uint8_t step, ovf, rst;
volatile uint8_t period;
volatile uint8_t n_gigi = N_GIGI;

// variabel untuk serial terminal receiver
uint16_t inInt;
char inString[32];

// variabel status saving eeprom
uint8_t savestt,addr;

// variabel untuh baca ADC
uint8_t vADC;

// variabel teks untuk LCD
char txtLCD[17];

// fungsi tunda 1 detik
void satu_detik(void){
	_delay_ms(250);_delay_ms(250);
	_delay_ms(250);_delay_ms(250);
}

// inisiasi PWM
void pwm_init(void){
	DDRB |= 1<<3;

	TCCR2|=(0<<CS22) |(1<<CS21)|(0<<CS20);
	TCCR2|=(0<<WGM21)|(1<<WGM20);
	TCCR2|=(1<<COM21)|(0<<COM20);
}

// inisiasi input capture
void icp_init(void){

	DDRD  &= ~(1<<6);
	PORTD |= (1<<6);

	TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10);
	TCCR1B &= ~(1<<ICES1);
	TIMSK  |= 1<<TOIE1;
	TIMSK  |= 1<<TICIE1;;
}

// inisiasi external interrupt
void exti_init(void){

	PORTD |= 1<<3;

	MCUCR|=(1<<ISC11)|(0<<ISC10);
	GICR|=1<<INT1;
}

// fungsi baca ADC
uint8_t adc_read(uint8_t pin){
	ADMUX=pin;
	ADMUX|=1<<ADLAR;

	ADMUX|=1<<REFS0;

	ADCSRA|=1<<ADEN;

	_delay_us(10);

	ADCSRA|=1<<ADSC;
	while (!(ADCSRA & 1<<ADIF));
	ADCSRA|=1<<ADIF;

	return ADCH;
}

int main (void){
	// inisiasi PWM
    pwm_init();
    OCR2 = 128;

    // inisiasi Input Capture
    icp_init();
    TCNT1= 0;

    // inisiasi UART
    uart_init();

	// inisiasi External Interrupt
    exti_init();

    // inisiasi AlphaLCD;
    alcd_init();
    alcd_clear();

    while (1){
        vADC = adc_read(0); // baca ADC
        OCR2 = vADC;        // set PWM dari ADC

        period = (uint8_t) period32; //scaling 32bit ke 8bit (?)

        sprintf(txtLCD,"TA mumet"); // tampilkan ADC ke ALCD
        alcd_printf(0,0,txtLCD);

        sprintf(txtLCD, "ADC:%3i T:%6i",vADC,period); // tampilkan period dan ADC ke ALCD
        alcd_printf(0,1,txtLCD);

        printf("ADC:%3i T:%6i",vADC,period); // kirim period dan ADC ke Serial

		// rutin simpan nilai dalam 512 detik
        if(savestt==1){
        	satu_detik();

        	if(addr<512){
				save(RPM_ROMADDR+addr,period);
				addr++;
        	}
        	else{
        		savestt=0;
        		addr=0;
        	}
        }
        else{
        	_delay_ms(255);
        }
    }
}

//================= Seluruh rutin Interrupt ======================//

// memulai saving eeprom dalam 512 data
ISR(INT1_vect){
	addr=0;
    savestt = 1;
}

// baca periode dalam ICR1
ISR(TIMER1_CAPT_vect){

	if(step==0){
		TCNT1 = 0;
		ICR1 = 0;
		step = 1;
		rst = 0;
	}
	else if(step==1){
		period32 = ICR1 + (ovf*65535);
		step = 0;
		ovf = 0;
		TCNT1=0;
		ICR1=0;
	}
}

// menambah 65535 ke ICR1 saat overflow
// mereset nilai period
ISR(TIMER1_OVF_vect){
	if(step==1)ovf++;

	rst++;
	if(rst>=2){
		period = 0;
		step = 0;
		ovf = 0;
		rst = 0;
	}
}


// contoh interrupt serial receiver
ISR(USART_RXC_vect){
    scanf("%s",inString);

	if(strcmp(inString,"test")==0){
		printf("serial OK\r");
	}
	else{
		inInt = atoi(inString);
		if(inInt>0){
			printf("%2i \r",inInt);
		}
		else{
			printf("%s ?\r",inString);
		}
	}
    return;
}
