#include <SPI.h>
#include <LoRa.h>

#define NSS   PA4
#define RST   PA2
#define DI0   PA3

#define TX_P    17
#define BAND    433E6
#define ENCRYPT 0x78

String inString = "";
int val = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

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
