/*
Project:	testrand
Board:		mega
MCU:		atmega2560	
FRENQUENCY:	16000000

Created using Qt Creator
*/

#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

uint8_t var1,var2,var3;
char txtdata[16];

//******************************
//* SETUP AND LOOP SECTION
//* Always leave setup() and loop() functions at the end of file
void setup() {                
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
    pinMode(13, OUTPUT);
    Serial.begin(38400);
}

void loop() {
	digitalWrite(13, HIGH);   // set the LED on
    delay(500);              // wait for a second

    var1 = random(256);
    var2 = random(256);
    var3 = random(256);

    sprintf(txtdata,"%3i,%3i,%3i\n\r",var1,var2,var3);
    Serial.print(txtdata);

	digitalWrite(13, LOW);    // set the LED off
    delay(500);              // wait for a second
}

