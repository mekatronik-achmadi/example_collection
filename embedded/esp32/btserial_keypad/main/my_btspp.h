#ifndef _MY_BTSPP_H_
#define _MY_BTSPP_H_

#define SPP_TAG             "ESP32_SPP"
#define SPP_SERVER_NAME     "ESP32_SPPSRV"
#define EXAMPLE_DEVICE_NAME "ESP32_SERIAL"
#define SPP_SHOW_DATA       0
#define SPP_SHOW_SPEED      1
#define SPP_SHOW_MODE SPP_SHOW_DATA    /*Choose show mode: show data or speed*/

#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
 #define SPP_DATA_HEX 0
 #define SPP_DATA_CHR 1
 #define SPP_DATA_MODE SPP_DATA_CHR
#endif

void btsppInit(void);

#endif