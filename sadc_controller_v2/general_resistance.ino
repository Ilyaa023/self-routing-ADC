
void setResistanceAD8402(byte channel, byte value){   //channel 0 or 1
  int data = 0 | (channel) | (value << 2);
  // for (int i = 9; i >= 0; i--)   
  //   Serial.print(bitRead(data, i));
  digitalWrite(PIN_CS, LOW);
  digitalWrite(PIN_MOSI, LOW);
  for (int i = 9; i >= 0; i--){
    digitalWrite(PIN_CLK, LOW);
    delayMicroseconds(DELAY_TIME);
    digitalWrite(PIN_CLK, HIGH); 
    delayMicroseconds(DELAY_TIME);     
  }
  digitalWrite(PIN_CS, HIGH);
}

// for (int i = 10; i >= 0; i--){
  //   digitalWrite(PIN_CLK, LOW);
  //   delayMicroseconds(DELAY_TIME);
  //   digitalWrite(PIN_CLK, HIGH); 
  //   delayMicroseconds(DELAY_TIME);     
  // }
  // for (int i = 1; i >= 0; i--){
  //   digitalWrite(PIN_MOSI, bitRead(channel, i));
  //   digitalWrite(PIN_CLK, LOW);
  //   delayMicroseconds(DELAY_TIME);
  //   digitalWrite(PIN_CLK, HIGH);  
  //   delayMicroseconds(DELAY_TIME);   
  // }
  // for (int i = 7; i >= 0; i--){
  //   digitalWrite(PIN_MOSI, bitRead(value, i));
  //   digitalWrite(PIN_CLK, LOW);
  //   delayMicroseconds(DELAY_TIME);
  //   digitalWrite(PIN_CLK, HIGH); 
  //   delayMicroseconds(DELAY_TIME);     
  // }