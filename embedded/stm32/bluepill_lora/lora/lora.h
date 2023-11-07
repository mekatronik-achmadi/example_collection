#ifndef _LORA_H_
#define _LORA_H_

#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42

// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06

// PA config
#define PA_BOOST                 0x80

// IRQ masks
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40

#define MAX_PKT_LENGTH           255

#define LORA_DEFAULT_SS_PIN    PA4
#define LORA_DEFAULT_RESET_PIN PB0
#define LORA_DEFAULT_DIO0_PIN  PA1

#define PA_OUTPUT_RFO_PIN      0
#define PA_OUTPUT_PA_BOOST_PIN 1

#include "ch.h"
#include "hal.h"

int lora_Begin(long frequency);
int lora_End(void);

int lora_BeginPacket(int implicitHeader);
int lora_EndPacket(void);

int lora_ParsePacket(int size);
int lora_PacketRssi(void);
float lora_PacketSnr(void);

size_t lora_Write(uint8_t byte);
size_t lora_WriteBuffer(const uint8_t *buffer, size_t size);

int lora_Available(void);
int lora_Read(void);
int lora_Peek(void);
void lora_Flush(void);

void lora_OnReceive(void);

void lora_Receive(int size);
void lora_idle(void);
void lora_sleep(void);

void  lora_setTxPower(int level, int outputPin);
void lora_setFrequency(long frequency);
void lora_setSpreadingFactor(int sf);
void lora_setSignalBandwidth(long sbw);
void lora_setCodingRate4(int denominator);
void lora_setPreambleLength(long length);
void lora_setSyncWord(int sw);
void lora_enableCrc(void);
void lora_disableCrc(void);

void lora_setPins(int ss, int reset, int dio0);
void lora_setSPIFrequency(uint32_t frequency);

void lora_handleDio0Rise(void);

uint8_t lora_readRegister(uint8_t address);
void lora_writeRegister(uint8_t address, uint8_t value);
uint8_t lora_singleTransfer(uint8_t address, uint8_t value);

void lora_OnDio0Rise(void);

#endif
