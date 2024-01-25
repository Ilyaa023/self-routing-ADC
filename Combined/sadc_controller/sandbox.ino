// void resetOINsone(){
//   command[0] = OIN_HIGH;
//   command[ARRAY_LENGTH - 1] = OIN_LOW;
//   for(int i = 1; i < ARRAY_LENGTH - 1; i++)
//     command[i] = OIN_MIDDLE;    
//   command[0] |= 1;
  
//   command[1] |= 1;
  
//   command[2] |= 1;
//   for(int i = 0; i < ARRAY_LENGTH; i++){
//     Serial.write(oinArray[i]);
//     Serial.write(command[i]);
//   }
//   measured = "00000000";
// }


// void setResistanceDS1801(byte value1, byte value2){
//   digitalWrite(PIN_CS, HIGH);
//   for (int i = 7; i >= 0; i--){
//     digitalWrite(PIN_MOSI, bitRead(value1, i));
//     digitalWrite(PIN_CLK, HIGH);
//     delayMicroseconds(delayTime);
//     digitalWrite(PIN_CLK, LOW); 
//     delayMicroseconds(delayTime);     
//   }
//   for (int i = 7; i >= 0; i--){
//     digitalWrite(PIN_MOSI, bitRead(value2, i));
//     digitalWrite(PIN_CLK, HIGH);
//     delayMicroseconds(delayTime);
//     digitalWrite(PIN_CLK, LOW); 
//     delayMicroseconds(delayTime);     
//   }
//   digitalWrite(PIN_CS, LOW);
// }
