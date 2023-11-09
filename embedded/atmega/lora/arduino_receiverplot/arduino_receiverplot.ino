#include <SPI.h>
#include <LoRa.h>

String inString = "";
byte data[50];

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  while (!Serial);  
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Initiated");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available())
    for(int i=0;i<packetSize;i++){
      data[i]= LoRa.read();
      inString += (char) data[i];
    }
    Serial.print(inString);
    inString = "";
  }
}
