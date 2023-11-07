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
    // received a packet
    Serial.print("Received packet size ");
    Serial.print(packetSize);
    Serial.print(" data ");
    // read packet
    while (LoRa.available())
    for(int i=0;i<packetSize;i++){
      data[i]= LoRa.read();
      Serial.print(' ');
      Serial.print(data[i]);
      inString += (char) data[i];
    }

    Serial.print("' as ");
    Serial.print(inString);
    // print RSSI of packet
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());

    inString = "";
  }
}
