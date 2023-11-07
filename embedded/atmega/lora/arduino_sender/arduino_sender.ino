#include <SPI.h>
#include <LoRa.h>

int count = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  while (!Serial);  
  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Initiated");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);

  LoRa.beginPacket();
  LoRa.print(count);
  LoRa.endPacket();

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  Serial.print("LoRa Data Send: ");
  Serial.println(count);

  count++;
}
