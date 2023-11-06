#ifndef _LORA_H_
#define _LORA_H_

#define LORA_DEFAULT_SS_PIN    PA4
#define LORA_DEFAULT_RESET_PIN PB0
#define LORA_DEFAULT_DIO0_PIN  PA1

#define PA_OUTPUT_RFO_PIN      0
#define PA_OUTPUT_PA_BOOST_PIN 1

int lora_Begin(long frequency);
int lora_End();

int lora_BeginPacket(int implicitHeader);
int lora_EndPacket();

int lora_ParsePacket(int size);
int lora_PacketRssi();
float lora_PacketSnr();

#endif
