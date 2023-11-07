#include <SPI.h>
#include <LoRa.h>

#define NSS   PA4
#define RST   PA2
#define DI0   PA3

#define TX_P    17
#define BAND    433E6
#define ENCRYPT 0x78

int counter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setTxPower(TX_P);
  LoRa.setSyncWord(ENCRYPT);
  LoRa.setPins(NSS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Started");
  digitalWrite(LED_BUILTIN, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
