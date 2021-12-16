#include "ta_uart.h"

void Uart_Init(void){
    palSetPadMode(GPIOA,10,PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA,9,PAL_MODE_ALTERNATE(7));
    sdStart(&SD1,NULL);
}

void Sms_Text(void){
    Uart_Init();

    chprintf((BaseSequentialStream *)&SD1,"\n");
    chprintf((BaseSequentialStream *)&SD1,"AT+CMGF=1\n");
    chThdSleepMilliseconds(500);
}

void Sms_Test(void){
    chprintf((BaseSequentialStream *)&SD1,"\n");
    chprintf((BaseSequentialStream *)&SD1,"AT+CMGS=\"");
    chprintf((BaseSequentialStream *)&SD1,"+6282232159203");
    chprintf((BaseSequentialStream *)&SD1,"\"\n");
    chThdSleepMilliseconds(500);

    chprintf((BaseSequentialStream *)&SD1,"Test");
    chThdSleepMilliseconds(500);

    chSequentialStreamPut((BaseSequentialStream *)&SD1,0x1A);
    chSequentialStreamPut((BaseSequentialStream *)&SD1,0x0D);
    chSequentialStreamPut((BaseSequentialStream *)&SD1,0x0A);
}
