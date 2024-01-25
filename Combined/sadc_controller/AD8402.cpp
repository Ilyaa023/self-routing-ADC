#include "AD8402.h"

#ifndef TARGET_ARDUINO
    void digitalWrite (unsigned char pin; unsigned char state){
        pin = state;
    }
    unsigned char bitRead (unsigned char val, unsigned char num){
        return (val >> num) & 1
    }
#endif

struct Resistor AD8402_R = {0};

void setResistance (unsigned char value) {
    digitalWrite(AD8402_R.pinCS, LOW);
    digitalWrite(AD8402_R.pinMOSI, LOW);
    for (int i = 15; i >= 0; i--){
        digitalWrite(AD8402_R.pinMOSI, bitRead(value, i));
        digitalWrite(AD8402_R.pinCLK, LOW);
        delayMicroseconds(DELAY_RESISTANCE);
        digitalWrite(AD8402_R.pinCLK, HIGH); 
        delayMicroseconds(DELAY_RESISTANCE);     
    }
    digitalWrite(AD8402_R.pinCS, HIGH);
}

void setResistanceCh0 (unsigned char value) {
    AD8402_R.channel1Res = value;
    setResistance (AD8402_R.channel1Res);
}
void setResistanceCh1 (unsigned char value) {
    AD8402_R.channel2Res = value;
    AD8402_R.channel2Res |= (1 << 9);
    setResistance (AD8402_R.channel2Res);
}