#include "sadc_controller.h"

void setup() {
  
  AD8402_R.pinCS = PIN_CS;
  AD8402_R.pinCLK = PIN_CLK;
  AD8402_R.pinMOSI = PIN_MOSI;
  
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
  delay(500);
  resetOINs();
}

void loop() {
  setResistanceCh1(count); 
  delay(delayMeasure);
  measure(); 
  if (digitalRead(PIN_BUTTON) == LOW){
    delay(100); 
    if (digitalRead(PIN_BUTTON) == LOW)
      count = 255;
  }    
  count++;      
  sendReport();  
  // if(count < 255)      
  //   count++;
  // else 
  //   count = 0;
}