//Runtime test
void measure(){
  resetOINs();

  for(int i = 0; i < ARRAY_LENGTH; i++){
    //while (digitalRead(12) != LOW);    
    bool isNotLastOin = i < ARRAY_LENGTH - 1;  
    delay(delayMeasure);
      
    if (digitalRead(PIN_COMPORATOR) == LOW)
       command[i] &= COM_GROUND;
      // command[i] |= COM_POWER;
    Serial.write(oinArray[i]);
    Serial.write(command[i]);
    //delay(delayMeasure);
    
    if (isNotLastOin) {
      command[i + 1] |= COM_POWER;
      // command[i] &= COM_GROUND;
      Serial.write(oinArray[i + 1]);
      Serial.write(command[i + 1]);
    }
  }
  delay(delayMeasure);

  setMeasured();
}

//Without tests
void setMeasured(){
  for (int i = 0; i < ARRAY_LENGTH; i++){
    if (bitRead(command[i], 0))
      measured[i] = '1';
    else
      measured[i] = '0';
  }
}

void sendReport(){
  Serial.write(255);
  byte analog = analogRead(PIN_MEASURE)>>2; 
       
  for (int i = 7; i >= 0; i--)
    Serial.print(bitRead(count, i));
    
  // Serial.print(' ');    
  Serial.print(measured); 
  // Serial.print(' ');    
                
  for (int i = 7; i >= 0; i--)   
    Serial.print(bitRead(analog, i));
      
  Serial.println();
}
//With tests
void resetOINs(){
  command[0] = OIN_HIGH;
  command[ARRAY_LENGTH - 1] = OIN_LOW;
  for(int i = 1; i < ARRAY_LENGTH - 1; i++)
    command[i] = 0;//OIN_MIDDLE;      
  for(int i = 0; i < ARRAY_LENGTH; i++){
    Serial.write(oinArray[i]);
    Serial.write(command[i]);
  }
  measured = "00000000";
}