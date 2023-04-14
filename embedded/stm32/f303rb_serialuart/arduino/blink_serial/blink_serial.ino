String strUart;
HardwareSerial Serial1(PA10, PA9);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  Serial1.begin(115200);
  Serial1.print("hello arduino\r\n");
}

// the loop function runs over and over again forever
void loop() {
  while(Serial1.available()){
    strUart = Serial1.readString();
    Serial1.println(strUart);
  }
  
  pinMode(PA_1, OUTPUT);
  digitalWrite(PA_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(PA_1, LOW);    // turn the LED off by making the voltage LOW
  delay(50);                       // wait for a second
}
