#ifndef _LORA_H_
#define _LORA_H_

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
