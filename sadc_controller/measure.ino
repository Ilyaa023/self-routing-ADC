#include "sadc_controller.h"

extern OIN oins[10];

//Runtime test
void poop(){
  resetOINs();

  for(int i = 0; i < numOfOins; i++){
    //while (digitalRead(12) != LOW);    
    bool isNotLastOin = i < numOfOins - 1;  
    delay(DELAY_MEASURE);
      
    if (digitalRead(PIN_COMPORATOR) == LOW)
      oins[i].commands[0] &= ~COM_POWER_MASK;
      // command[i] |= COM_POWER;
    Serial.write(OIN_REQUEST);
    Serial.write(oins[i].ID);
    Serial.write(oins[i].commands[0]);
    //delay(delayMeasure);
    
    if (isNotLastOin) {
      oins[i + 1].commands[0] |= COM_POWER_MASK;
      // command[i] &= COM_GROUND;
      Serial.write(OIN_REQUEST);
      Serial.write(oins[i + 1].ID);
      Serial.write(oins[i + 1].commands[0]);
    }
  }
  delay(DELAY_MEASURE);

  setMeasured();
}

//Without tests
void setMeasured(){
  for (int i = 0; i < numOfOins; i++){
    if (bitRead(oins[i].commands[0], 0))
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
  oins[0].commands[0] = OIN_HIGH;
  oins[numOfOins - 1].commands[0] = OIN_LOW;
  for(int i = 1; i < numOfOins - 1; i++)
    oins[i].commands[0] = OIN_MIDDLE;//OIN_MIDDLE;      
  for(int i = 0; i < numOfOins; i++){
    Serial.write(OIN_REQUEST);
    Serial.write(oins[i].ID);
    Serial.write(oins[i].commands[0]);
  }
  measured = "00000000";
}