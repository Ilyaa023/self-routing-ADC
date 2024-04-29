#include "sadc_controller.h"

class OIN {
  public:
  byte ID;
  byte commands[2];
  bool is_working;
};

byte numOfAllOins = 8;
byte numOfActiveOins = 4;
byte allIDs[8] = {200, 199, 198, 197, 196, 195, 194, 193};
//bool workable[8] = {false, false, false, false, true, true, true, true};
byte highOin = 196;
byte lowOin = 193;
OIN oins[10];

byte count;
String measured;

byte measureMode = 1;
byte resistanceMode = 1;

// byte i = 3;

void setup() {
  pinMode(PIN_COMPORATOR, INPUT);
  pinMode(PIN_MEASURE, INPUT); 
  pinMode(PIN_BUTTON, INPUT_PULLUP); 
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);

  digitalWrite(PIN_CS, HIGH);
  digitalWrite(PIN_MOSI, HIGH);
  digitalWrite(PIN_CLK, HIGH);

  // analogReference(EXTERNAL);  

  Serial.begin(UART_SPEED);
  Serial.setTimeout(10);
  delay(500);

  if(digitalRead(PIN_BUTTON) == LOW){
    // implement id call by rquest id (0-255) and waiting response on PIN_MEASURE that connected to target oin
  } else{
    for (byte i = 0; i < numOfAllOins; i++){
      oins[i].ID = allIDs[i];
      // oins[i].is_working = workable[i]; 
      // oins[i].command[0] = OIN_DISABLE; 
    }
  }
  resetOINs();
}

void loop() {
    GetMessage();

  if (measureMode){
    setResistanceAD8402(1, count); 
    //setResistanceAD8402(1, count >> 8); 
    delay(DELAY_MEASURE);
    measure(); 
    if (digitalRead(PIN_BUTTON) == LOW){
      delay(100); 
      if (digitalRead(PIN_BUTTON) == LOW)
        count = 255;
    }    
    if (resistanceMode) count++;
    if (count == 255)
      count = 0;
    sendReport();  
  }
}
