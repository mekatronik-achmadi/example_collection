#include <Arduino.h>
#include <I2S.h>

#define BLINK_LED 16

void setup(){
    Serial.begin(115200);
    pinMode(BLINK_LED,OUTPUT);

    if(!I2S.begin(I2S_PHILIPS_MODE,16000,16)){
        Serial.println("I2S Failed");
        while(1);
    }
}

void loop(){
    digitalWrite(BLINK_LED, HIGH);
    delay(100);
    digitalWrite(BLINK_LED, LOW);
    delay(100);

    int sample = I2S.read();
    Serial.println(sample);
}
