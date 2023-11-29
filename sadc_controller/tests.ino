
//TESTS
void idTest(){
  for (byte i = 0; i < ARRAY_LENGTH; i++){
    if (oinArray[i] < 192 || oinArray[i] > 254){
      Serial.print("Wrong ID ");
      Serial.print(oinArray[i]);
      Serial.print(" with index ");
      Serial.print(i);
      while(1){
        digitalWrite(13, LOW);
        delay(500); 
        digitalWrite(13, HIGH);
        delay(500);                
      }     
    }  
  }
}

void testResetOINS(){
  Serial.println("Test Reset OINs: ");
  resetOINs();
  Serial.println();
  
  for (byte i = 0; i < ARRAY_LENGTH; i++){
    Serial.print("\ttesting ");
    Serial.print(oinArray[i]);
    Serial.print(" with index ");
    Serial.print(i);
    Serial.print("... ");
    switch(i){
      case 0: {
        if (command[i] != OIN_HIGH){
          Serial.print("Error: expected ");
          Serial.print(OIN_HIGH, BIN);
          Serial.print(" but ");
          Serial.print(command[i], BIN); 
          Serial.print(" found");         
        }
        else{
          Serial.println("OK");
        }  
      }
      case ARRAY_LENGTH - 1:{
        if (command[i] != OIN_LOW){
          Serial.print("Error: expected ");
          Serial.print(OIN_LOW, BIN);
          Serial.print(" but ");
          Serial.print(command[i], BIN); 
          Serial.print(" found"); 
        }
        else{
          Serial.println("OK");
        }  
      }
      default:{
        if (command[i] != OIN_MIDDLE){
          Serial.print("Error: expected ");
          Serial.print(OIN_MIDDLE, BIN);
          Serial.print(" but ");
          Serial.print(command[i], BIN); 
          Serial.print(" found"); 
        }
        else{
          Serial.println("OK");
        }  
      }
    }     
  }
}