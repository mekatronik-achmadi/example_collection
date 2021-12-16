#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "usbcfg.h"
#include "test.h"
#include <string.h>


/*===========================================================================*/
/* Pinout STM32.                                                             */
/*===========================================================================*/
/*
1. Ultrasonic samping		indikator			Pinout		
	trigger					GPIOE_LED7_GREEN	PE11
	echo					GPIOE_LED9_BLUE		PC6 	CHANNEL
	
2. Ultrasonic kiri			indikator			Pinout
	trigger					GPIOE_LED8_ORANGE	PE14
	echo					GPIOE_LED3_RED		PD12    CHANNEL

3. Ultrasonic depan			indikator			Pinout
	trigger					GPIOE_LED6_GREEN	PE15
	echo					GPIOE_LED5_ORANGE	PB6     CHANNEL
	
4. Motor DC					Indikator			Pinout
   PWM A					GPIOE_LED4_BLUE     PA15    CHANNEL
   
5. Servo					Indikator			Pinout
   Pulsa					GPIOE_LED10_RED		PE13    CHANNEL
   */


//deklarasi variable data global
//ultrasonic
int data_ul_depan=0, jarak_ul_depan;
int data_ul_samping, jarak_ul_samping;
int data_ul_kiri, jarak_ul_kiri;
int input_period;
int input_period1;
int input_period2;
int error_samping;
int ul_flag=0;
//motor
int pulsa_servo=1200;
int duty_cycle=70;//nilai awal pwm
int period_motorDC=120;//nilai periode motor dc (1/frequency)
int data_pwm =70;//nilai pwm 50% * period
///

// Serial over USB Driver structure.
SerialUSBDriver SDU1;
BaseSequentialStream* chp =(BaseSequentialStream*) &SDU1;
#define usb_lld_connect_bus(usbp)
#define usb_lld_disconnect_bus(usbp)
//

//Shell comand  (perintah lewat serial terminal)
void send_ul(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  chprintf((BaseSequentialStream *)&SDU1, "data ul samping=%d\r\njarak ul samping=%dcm\r\n", data_ul_samping, jarak_ul_samping);//print data ul terakhir ->jika pc6 disambung pa15=mengukur pse width pwm
  chprintf((BaseSequentialStream *)&SDU1, "error_samping=%d\r\n", error_samping);
  chprintf((BaseSequentialStream *)&SDU1, "Ultrasonic depan=%d\r\n", data_ul_depan);
  chprintf((BaseSequentialStream *)&SDU1, "pulsa servo=%d\r\n", pulsa_servo);
  chprintf((BaseSequentialStream *)&SDU1, "duty cycle motorDC=%d\r\n", duty_cycle);
}
void send_pwm_period(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  chprintf((BaseSequentialStream *)&SDU1, "period=%d\r\n", input_period);
}
void send_ubah_pwm(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  if (argc != 2) {
    chprintf(chp, "pwm -pulsewidth- -period-\r\n");
    return;
  }
  duty_cycle = atoi(argv[0]);
  period_motorDC = atoi(argv[1]);
  chprintf((BaseSequentialStream *)&SDU1, "duty_cycle=%d\r\n", duty_cycle);
  chprintf((BaseSequentialStream *)&SDU1, "period motorDC=%d\r\n", period_motorDC);
  //pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, data_pwm));
  pwmChangePeriod(&PWMD2, period_motorDC);//1 detik
}
void send_ubah_servo(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  if (argc != 1) {
    chprintf(chp, "servo nilai\r\n");
    return;
  }
  pulsa_servo = atoi(argv[0]);
}

void send_ubah_jarak0_samping(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  if (argc != 1) {
    chprintf(chp, "jarak0_samping nilai\r\n");
    return;
  }
  jarak_ul_samping = atoi(argv[0]);
}
void send_ubah_jarak0_depan(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argc;
  (void)argv;
  if (argc != 1) {
    chprintf(chp, "jarak0_depan nilai\r\n");
    return;
  }
  jarak_ul_depan = atoi(argv[0]);
}
#define SHELL_WA_SIZE   THD_WA_SIZE(2048)
static const ShellCommand commands[] = {
  {"ul", send_ul},//ketik ul+enter pada serial terminal(bray terminal)
  {"pp", send_pwm_period},
  {"pwm", send_ubah_pwm},
  {"servo", send_ubah_servo},
  {"jarak0_depan", send_ubah_jarak0_depan},
  {"jarak0_samping" , send_ubah_jarak0_samping},
  {NULL, NULL}
};
static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};
////


/////Driver PWM untuk motor DC
static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  palClearPad(GPIOE, GPIOE_LED4_BLUE);///pin pengontrol pwm motor DC
}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  palSetPad(GPIOE, GPIOE_LED4_BLUE);
}

static PWMConfig pwmcfg = {
  100000,                                    /* 10kHz PWM clock frequency.   */
  1000,                                    /* Initial PWM period 1S.       */
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
  },
  0,
};

////INPUT CAPTURE (menghitung pulsa masuk PC6) dari echo ultrasonic
icucnt_t last_width, last_period; 
static void icuwidthcb(ICUDriver *icup) {

  palTogglePad(GPIOE, GPIOE_LED9_BLUE);//indikator input dr ultrasonic
  last_width = icuGetWidth(icup);//menghitung panjang pulsa
  data_ul_samping = last_width;//1 data = 1/10.000 detik
 
  };
  

static void icuperiodcb(ICUDriver *icup) {

  //palClearPad(GPIOE, GPIOE_LED9_BLUE);
  last_period = icuGetPeriod(icup);
  input_period=last_period;
  };

static ICUConfig icucfg = {
  ICU_INPUT_ACTIVE_HIGH,
  40000,                                    /* 10kHz ICU clock frequency.  (1hitungan = 1/10.000 detik)*/
  icuwidthcb,
  icuperiodcb,
  NULL,
  ICU_CHANNEL_1,
};

//menghitung echo ultrasonic depan
icucnt_t last_width1, last_period1; 
static void icuwidth1cb(ICUDriver *icup) {

  palTogglePad(GPIOE, GPIOE_LED3_RED);//indikator input dr ultrasonic
  last_width1 = icuGetWidth(icup);//menghitung panjang pulsa
  data_ul_depan = last_width1;//1 data = 1/10.000 detik
  };
  

static void icuperiod1cb(ICUDriver *icup) {

  //palClearPad(GPIOE, GPIOE_LED3_RED);
  last_period1 = icuGetPeriod(icup);
  input_period1=last_period1;
  };

static ICUConfig icucfg1 = {
  ICU_INPUT_ACTIVE_HIGH,
  40000,                                    /* 40kHz ICU clock frequency.  (1hitungan = 1/40.000 detik)*/
  icuwidth1cb,
  icuperiod1cb,
  NULL,
  ICU_CHANNEL_1,
};


icucnt_t last_width2, last_period2; 
static void icuwidth2cb(ICUDriver *icup) {

  palTogglePad(GPIOE, GPIOE_LED5_ORANGE);//indikator input dr ultrasonic
  last_width2 = icuGetWidth(icup);//menghitung panjang pulsa
  data_ul_kiri = last_width2;//1 data = 1/10.000 detik
  };
  

static void icuperiod2cb(ICUDriver *icup) {

  //palClearPad(GPIOE, GPIOE_LED5_ORANGE);
  last_period2 = icuGetPeriod(icup);
  input_period2=last_period2;
  };

static ICUConfig icucfg2 = {
  ICU_INPUT_ACTIVE_HIGH,
  40000,                                    /* 40kHz ICU clock frequency.  (1hitungan = 1/40.000 detik)*/
  icuwidth2cb,
  icuperiod2cb,
  NULL,
  ICU_CHANNEL_1,
};




///THREAD TRIGGER ULTRASONIC
static WORKING_AREA(waThread_trigger_ul, 128);
static msg_t Thread_trigger_ul(void *arg) {
  chThdSleepMilliseconds(500);
  (void)arg;
  chRegSetThreadName("ul");
  while (TRUE)
  {
    palSetPad(GPIOE, GPIOE_LED7_GREEN);//pin pengontrol trigger ultrasonic kanan
	palSetPad(GPIOE, GPIOE_LED8_ORANGE);//pin pengontrol trigger ultrasonic
	palSetPad(GPIOE, GPIOE_LED6_GREEN);
    chThdSleepMicroseconds(10);//pulsa trigger 10us
	palClearPad(GPIOE, GPIOE_LED7_GREEN);
    palClearPad(GPIOE, GPIOE_LED8_ORANGE);
    palClearPad(GPIOE, GPIOE_LED6_GREEN);
    chThdSleepMilliseconds(100);//jeda antar pulsa 100 ms
  }
  return 0;
};

///THREAD SERVO % pwm
static WORKING_AREA(waThread_servo, 128);
static msg_t Thread_servo(void *arg) {
  chThdSleepMilliseconds(500);
  (void)arg;
  chRegSetThreadName("servo");

  while (TRUE)
  {
	//pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, data_pwm));//ubah kecepatan motor
	pwmEnableChannel(&PWMD2, 0, data_pwm);//ubah nilai pwm motor dc

    palSetPad(GPIOE, GPIOE_LED10_RED);//pin pengontrol servo
    //chThdSleepMicroseconds(pulsa_servo);//pulsa yang diberikan ke servo
    halPolledDelay(pulsa_servo*72);
    palClearPad(GPIOE, GPIOE_LED10_RED);
    //chSysLockFromIsr();
      //gptStartOneShotI(&GPTD1, 1000);   /* 0.1 second pulse.*/
      //chSysUnlockFromIsr();
    chThdSleepMilliseconds(20);//jeda antar pulsa
  }
  return 0;
}
///THREAD KALKULASI
static WORKING_AREA(waThread_calc, 1024);
static msg_t Thread_calc(void *arg) {
  chThdSleepMilliseconds(500);
  (void)arg;
  chRegSetThreadName("calc");
  int nilai_0servo=1200;//posisi lurus servo
  int error=0;
  int error_samping=0;
  int error_depan;
  int error_kiri=0;
  int jarak_0samping=120;//minimal jarak samping->misal 30cm
  int jarak_0depan=200;//minimal jarak samping->misal 30cm
  int jarak_0kiri=300;//minimal jarak samping->misal 30cm
  int kp=4, ki=1, kd=1;//nilai PID
  int error_P, error_I, error_D;
  int error_prev;
  int error_depan_P;
  while (TRUE)
  {
    data_pwm = (period_motorDC/100)*(duty_cycle);//data pwm motor dc


	jarak_ul_depan = data_ul_depan;//cek datasheet formula us jd jarak cm
	jarak_ul_samping = data_ul_samping;//cek datasheet formula us jd jarak cm
	jarak_ul_kiri = data_ul_kiri;//cek datasheet formula us jd jarak cm
	error_samping = jarak_0samping - jarak_ul_samping;
	//error_kiri = jarak_0kiri - jarak_ul_kiri;
	error_P = (error_samping)* kp;
	//error_D= (error_samping-error_prev)*kd;
	//error_prev=error_samping;
	//ki_error_samping =...?
	//kd_error_samping=..?
	//errorPID = error_P + error_I + error_D
	//pulsa_servo = nilai_0servo - errorPID;//-->jika menggunakan PID
	pulsa_servo = nilai_0servo - error_P;//nilai belok servo --misal hanya menggunakan P
	//if(data_ul_depan<400) pulsa_servo=1200;
	if(pulsa_servo<1000) pulsa_servo=1000;
	

	///PWM
	/*error_depan = jarak_0depan - jarak_ul_depan;
		if(jarak_ul_depan<0){
			error_depan=0;
		}
		error_depan_P = error_depan/5;
		duty_cycle = 100-error_depan_P;
		
		if(duty_cycle<0)  duty_cycle=0;*/
		
    chThdSleepMilliseconds(100);//jarak antar perhitungan
  }
  return 0;
}

//////
//Main program
int main(void) {
  Thread *shelltp = NULL;//deklarasi thread shell comand

  //inisialisasi HAL dan OS
  halInit();
  chSysInit();

  //inisialisasi usb
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);
  //aktifkan usb
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(200);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);
  //inisialisasi shell comand
  shellInit();
  ///

  	//aktifkan ICU ( dlm file mcuconf.h -> ICU driver system settings pilih  TRUE kecuali timer 2 untuk PWM)
    // 	  	  	   ( dlm file halconf.h -> #define HAL_USE_ICU   -jadikan- TRUE)
	
	//mengkatifkan ICU TIM3 CHANNEL 1
  	  icuStart(&ICUD3, &icucfg);
      palSetPadMode(GPIOC, 6, PAL_MODE_ALTERNATE(2));
	  icuEnable(&ICUD3);
	  
	//mengkatifkan ICU TIM4 CHANNEL 1
	  icuStart(&ICUD4, &icucfg1);
      palSetPadMode(GPIOD, 12, PAL_MODE_ALTERNATE(2));
	  icuEnable(&ICUD4);
      
	//mengkatifkan ICU TIM8 CHANNEL 1
	  icuStart(&ICUD8, &icucfg2);
      palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(2));
	  icuEnable(&ICUD8);
      
	  
    ////aktifkan PWM ( dlm file mcuconf.h -> #define STM32_PWM_USE_TIM2 -jadikan-  TRUE)
    // 	  	  	  	 ( dlm file halconf.h -> #define HAL_USE_PWM  -jadikan- TRUE)
  	
	pwmStart(&PWMD2, &pwmcfg);
    palSetPadMode(GPIOA, 15, PAL_MODE_ALTERNATE(1));
    chThdSleepMilliseconds(100);
    pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, data_pwm));
    pwmChangePeriod(&PWMD2, period_motorDC);//1 detik
    ///~pwm
    //start thread calc dan servo
	chThdCreateStatic(waThread_trigger_ul, sizeof(waThread_trigger_ul), NORMALPRIO+10, Thread_trigger_ul, NULL);
    chThdCreateStatic(waThread_calc, sizeof(waThread_calc), NORMALPRIO+7, Thread_calc, NULL);
    chThdCreateStatic(waThread_servo, sizeof(waThread_servo), NORMALPRIO+5, Thread_servo, NULL);
   
    
//looping thread Main
  while (TRUE)
  {
	//khusus USB Comand
    if (!shelltp && (SDU1.config->usbp->state == USB_ACTIVE))
    	{
    		shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);//mengaktifkan shell comand
    	}
    else if (chThdTerminated(shelltp))
    	{
			chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
			shelltp = NULL;           /* Triggers spawning of a new shell.        */
        }
    ///~usb

    chThdSleepMilliseconds(1000);//delay looping main thread
      ///
  }
  return 0;
}

