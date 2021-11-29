/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_web.c
 * @brief   Web server routine code.
 *
 * @addtogroup Communication
 * @{
 */

#include "din_web.h"

extern adcsample_t adc0,adc00,adc01;
extern float v_adc;
extern float ax,ay,az,mag;

float s_ax,s_ay,s_az;
float s_v_adc,s_mag;
float m_ax,m_ay,m_az;
float m_v_adc,m_mag;

u_int8_t fuz_res;
u_int8_t fall_stt=0;

static THD_WORKING_AREA(waData, 256);
static THD_FUNCTION(thdData, arg) {

    (void)arg;

    uint8_t i=0;

    s_ax = 0;
    s_ay = 0;
    s_az = 0;
    s_v_adc = 0;
    s_mag = 0;

    chRegSetThreadName("Data Process");
    while (true) {
        d_mpu_i2cReadData(0x3B, 14);

        adc01 = adc0;
        v_adc = ADC_SCALE * abs(adc01-adc00);
        adc00 = adc01;

        s_ax = s_ax + ax;
        s_ay = s_ay + ay;
        s_az = s_az + az;
        s_v_adc = s_v_adc + v_adc;
        s_mag = s_mag + mag;

        i++;

        if(i==100){
            m_ax = s_ax/100;
            m_ay = s_ay/100;
            m_az = s_az/100;
            m_v_adc = s_v_adc/100;
            m_mag = s_mag/100;

            fuz_res = d_fuzzy(m_mag,m_v_adc);
            if(fuz_res==1){
                fall_stt = 1;
            }
//            chprintf((BaseSequentialStream *)&SD1,"%5.2f:%5.2f:%5.2f:%5.2f:%5.2f:%1i\r\n",m_v_adc,m_ax,m_ay,m_az,m_mag,fuz_res);

            i = 0;
            s_ax = 0;
            s_ay = 0;
            s_az = 0;
            s_v_adc = 0;
            s_mag = 0;
        }

        chThdSleepMilliseconds(1);
    }
}

/**
 * @brief   Shell handler variable.
 */
static thread_t *shelltp = NULL;

#if SERVER_NOTIF
/**
 * @brief   Server request notification to SD1.
 */
static void request_notif(u_int8_t chan){
    chprintf((BaseSequentialStream *)&SD1,"%i:%5.2f:%5.2f:%5.2f:%5.2f:%5.2f:%1i:%1i\r\n",chan,m_v_adc,m_ax,m_ay,m_az,m_mag,fuz_res,fall_stt);
}
#endif

/**
 * @brief   Text sending function.
 */
static void text_http(void){
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)&SD2,"%5.2f:%5.2f:%5.2f:%5.2f:%5.2f:%1i:%1i\r\n",m_v_adc,m_ax,m_ay,m_az,m_mag,fuz_res,fall_stt);
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)&SD2,"\r\n");
    chThdSleepMilliseconds(100);
}

/**
 * @brief   Channel 0 handler function.
 */
static void cmd_send0(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  (void)argc;
  (void)chp;

#if SERVER_NOTIF
    request_notif(0);
#endif
  chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=0,34\r\n");
  text_http();
  chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=0\r\n");
}

/**
 * @brief   Channel 1 handler function.
 */
static void cmd_send1(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(1);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=1,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=1\r\n");
}

/**
 * @brief   Channel 2 handler function.
 */
static void cmd_send2(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(2);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=2,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=2\r\n");
}

/**
 * @brief   Channel 3 handler function.
 */
static void cmd_send3(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(3);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=3,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=3\r\n");
}

/**
 * @brief   Channel 4 handler function.
 */
static void cmd_send4(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(4);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=4,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=4\r\n");
}

/**
 * @brief   Channel 5 handler function.
 */
static void cmd_send5(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(5);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=5,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=5\r\n");
}

/**
 * @brief   Channel 6 handler function.
 */
static void cmd_send6(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(6);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=6,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=6\r\n");
}

/**
 * @brief   Channel 7 handler function.
 */
static void cmd_send7(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    (void)argc;
    (void)chp;

#if SERVER_NOTIF
    request_notif(7);
#endif
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSEND=7,34\r\n");
    text_http();
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPCLOSE=7\r\n");
}

/**
 * @brief   Shell commands enumeration.
 */
static const ShellCommand commands[] = {
    {"0,CONNECT", cmd_send0},
    {"1,CONNECT", cmd_send1},
    {"2,CONNECT", cmd_send2},
    {"3,CONNECT", cmd_send3},
    {"4,CONNECT", cmd_send4},
    {"5,CONNECT", cmd_send5},
    {"6,CONNECT", cmd_send6},
    {"7,CONNECT", cmd_send7},
    {NULL, NULL}
};

/**
 * @brief   Shell configuration variable.
 */
static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD2,
    commands
};

/**
 * @brief   Web server start function.
 */
void d_web_start(void){
    palSetPadMode(GPIOA,2,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
    palSetPadMode(GPIOA,3,PAL_MODE_INPUT); //RX
    sdStart(&SD2,NULL);

    chThdSleepMilliseconds(100);
    d_web_setup();

    shellInit();
}

/**
 * @brief   Web server shell function.
 */
void d_web_term(void){
    if (!shelltp)
      shelltp = shellCreate(&shell_cfg, SHELL_WA_SIZE, NORMALPRIO);
    else if (chThdTerminatedX(shelltp)) {
      chThdRelease(shelltp);
      shelltp = NULL;
    }
}

/**
 * @brief   Web server setup function.
 */
void d_web_setup(void){
    chprintf((BaseSequentialStream *)&SD2,"AT+RST\r\n");
    chThdSleepMilliseconds(1000);
    chprintf((BaseSequentialStream *)&SD2,"ATE0\r\n");
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)&SD2,"AT+CWMODE=2\r\n");
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPMUX=1\r\n");
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)&SD2,"AT+CIPSERVER=1,80\r\n");
    chThdSleepMilliseconds(100);
}

void d_web_data(void){
    chThdCreateStatic(waData, sizeof(waData), NORMALPRIO, thdData, NULL);
}
/** @} */
