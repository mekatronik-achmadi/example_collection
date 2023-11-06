#include <SPI.h>
#include <LoRa_STM32.h>

#define NSS   PA4
#define RST   PB0
#define DI0   PA1
#define BAND  433E6

int counter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(NSS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Started");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Packet: ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
