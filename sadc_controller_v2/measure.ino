#include "sadc_controller.h"

extern OIN oins[10];
extern OIN allOins[10];
extern byte firstOin;
extern byte lastOin;

byte firstIndex = 0;
byte lastIndex = 0;

void measure(){
  resetOINs();

  for (int i = firstIndex; i <= lastIndex; i++){
    oins[i].commands[0] |= 255 & COM_POWER_MASK;
    Serial.write(OIN_REQUEST);
    Serial.write(oins[i].ID);
    Serial.write(oins[i].commands[0]);
    delay(DELAY_MEASURE);

    if (digitalRead(PIN_COMPORATOR) == HIGH){
      oins[i].commands[0] &= ~COM_POWER_MASK;
      Serial.write(OIN_REQUEST);
      Serial.write(oins[i].ID);
      Serial.write(oins[i].commands[0]);
    }
  }
}

void resetOINs(){
  byte num = 0;
  bool active = false;
  for (int i = 0; i < numOfAllOins; i++){
    if (firstOin == oins[i].ID){
      active = true;
      firstIndex = i;
      num++;
      oins[i].commands[0] = OIN_HIGH;
    } else if (lastOin != oins[i].ID){
      if (active){
        oins[i].commands[0] = OIN_MIDDLE;
        num++;
      }
      else
        oins[i].commands[0] = OIN_DISABLE;
    } else {
      active = false;
      lastIndex = i;
      num++;
      oins[i].commands[0] = OIN_LOW;
    }
    Serial.write(OIN_REQUEST);
    Serial.write(oins[i].ID);
    Serial.write(oins[i].commands[0]);
  }
  delay(DELAY_MEASURE);
  // for(int i = 0; i < numOfOins; i++){
  //   oins[i].is_working = workable[i]; 
  //   if (oins[i].is_working){
  //     bool isNotLastOin = num < numOfActiveOins - 1;  
  //     if (digitalRead(PIN_COMPORATOR) == HIGH)
  //       oins[i].commands[0] &= ~COM_POWER_MASK;
  //     Serial.write(OIN_REQUEST);
  //     Serial.write(oins[i].ID);
  //     Serial.write(oins[i].commands[0]);
  //     num++;
  //   } else
  //     oins[i].command[0] = OIN_DISABLE; 
  // }
}

void setMeasured(){
  for (int i = 0; i < numOfActiveOins; i++){
    if (bitRead(oins[i].commands[0], 0))
      measured[i] = '1';
    else
      measured[i] = '0';
  }
}

void sendReport(){
  Serial.write(255);
  byte analog = analogRead(PIN_MEASURE); 
       
  for (int i = 7; i >= 0; i--)
    Serial.print(bitRead(count, i));
    
  Serial.print(' ');    
  Serial.print(measured); 
  Serial.print(' ');    
                
  for (int i = 7; i >= 0; i--)   
    Serial.print(bitRead(analog, i));
      
  Serial.println();
}


//Runtime test
// void poop(){
//   resetOINs();

//   for(int i = 0; i < numOfOins; i++){
//     //while (digitalRead(12) != LOW);    
//     bool isNotLastOin = i < numOfOins - 1;  
//     delay(DELAY_MEASURE);
      
//     if (digitalRead(PIN_COMPORATOR) == HIGH)
//       oins[i].commands[0] &= ~COM_POWER_MASK;
//       // command[i] |= COM_POWER;
//     Serial.write(OIN_REQUEST);
//     Serial.write(oins[i].ID);
//     Serial.write(oins[i].commands[0]);
//     //delay(delayMeasure);
    
//     if (isNotLastOin) {
//       oins[i + 1].commands[0] |= COM_POWER_MASK;
//       // command[i] &= COM_GROUND;
//       Serial.write(OIN_REQUEST);
//       Serial.write(oins[i + 1].ID);
//       Serial.write(oins[i + 1].commands[0]);
//     }
//   }
//   delay(DELAY_MEASURE);

//   setMeasured();
// }


// //With tests
// void resetOINs(){
//   for(int i = 1; i < numOfAllOins; i++)
//     allOins[i].commands[0] = OIN_DISABLE;//OIN_MIDDLE;      
//   for(int i = 0; i < numOfAllOins; i++){
//     Serial.write(OIN_REQUEST);
//     Serial.write(allOins[i].ID);
//     Serial.write(allOins[i].commands[0]);
//   }
//   oins[0].commands[0] = OIN_HIGH;
//   oins[numOfOins - 1].commands[0] = OIN_LOW;
//   for(int i = 1; i < numOfOins - 1; i++)
//     oins[i].commands[0] = OIN_MIDDLE;//OIN_MIDDLE;      
//   for(int i = 0; i < numOfOins; i++){
//     Serial.write(OIN_REQUEST);
//     Serial.write(oins[i].ID);
//     Serial.write(oins[i].commands[0]);
//   }
//   measured = "00000000";
// }