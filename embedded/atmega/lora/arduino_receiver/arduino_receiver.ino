#include <SPI.h>
#include <LoRa.h>

String inString = "";
int val = 0;

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
  int packetSize = LoRa.parsePacket();

  digitalWrite(LED_BUILTIN, LOW);
  
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString.toInt();
          
    }
    inString = "";     
    LoRa.packetRssi();
    Serial.println(val);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
