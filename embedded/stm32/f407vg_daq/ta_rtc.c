#include "ta_rtc.h"

struct ds1307_t calendar;

static uint8_t rxbuf[DS1307_RX_DEPTH];
static uint8_t txbuf[DS1307_TX_DEPTH];

static i2cflags_t errors = 0;

uint8_t bcd2Dec ( uint8_t val )
{
    uint8_t res = ((val/16*10) + (val % 16));
    return res;
}

uint8_t dec2Bcd ( uint8_t val )
{
    uint8_t res = ((val/10*16) + (val%10));
    return res;
}


void setDs1307Date ( msg_t *status, systime_t *tmo, struct ds1307_t dsData )
{
    txbuf[0] = DS1307_SECONDS_REG;
    txbuf[1] = dec2Bcd( dsData.seconds );
    txbuf[2] = dec2Bcd( dsData.minutes );
    txbuf[3] = dec2Bcd( dsData.hours );
    txbuf[4] = dec2Bcd( dsData.day );
    txbuf[5] = dec2Bcd( dsData.date );
    txbuf[6] = dec2Bcd( dsData.month );
    txbuf[7] = dec2Bcd( dsData.year - 2000);

    i2cAcquireBus ( &I2CD1 );
    *status = i2cMasterTransmitTimeout ( &I2CD1, DS1307_ADDRESS, txbuf, DS1307_TX_DEPTH, rxbuf, 0, *tmo );
    i2cReleaseBus ( &I2CD1 );
}

struct ds1307_t getDs1307Date ( msg_t *status, systime_t *tmo )
{
    struct ds1307_t dsData;

    txbuf[0] = DS1307_SECONDS_REG;
    i2cAcquireBus( &I2CD1 );
    *status = i2cMasterTransmitTimeout ( &I2CD1, DS1307_ADDRESS, txbuf, 1,rxbuf, 7, *tmo );
    i2cReleaseBus ( &I2CD1 );

    if ( *status != MSG_OK )
    {
        errors = i2cGetErrors ( &I2CD1 );
    }
    else
    {
        dsData.seconds  = bcd2Dec ( rxbuf[0] & 0x7F );
        dsData.minutes  = bcd2Dec ( rxbuf[1] );
        dsData.hours    = bcd2Dec ( rxbuf[2] & 0x3F );
        dsData.day      = bcd2Dec ( rxbuf[3] );
        dsData.date     = bcd2Dec ( rxbuf[4] );
        dsData.month    = bcd2Dec ( rxbuf[5] );
        dsData.year     = bcd2Dec ( rxbuf[6] ) + 2000;
    }
    return dsData;
}

static THD_WORKING_AREA(waRTC, 128);
static THD_FUNCTION(ThdRTC, arg)  {

  (void)arg;

  msg_t status = MSG_OK;
  systime_t timeOut = MS2ST ( 4 );
  chRegSetThreadName("RTC Request");

  while (TRUE) {
    calendar = getDs1307Date ( &status, &timeOut );
    palSetPad(GPIOD, 14);       /* Red.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, 14);     /* Red.  */
    chThdSleepMilliseconds(500);
  }
}

void Ds1307_Init ( void )
{
    I2c_Init();
    chThdSleepMilliseconds(500);

    palSetPadMode(GPIOD,14,PAL_MODE_OUTPUT_PUSHPULL);
    chThdCreateStatic(waRTC, sizeof(waRTC), NORMALPRIO, ThdRTC, NULL);
}
