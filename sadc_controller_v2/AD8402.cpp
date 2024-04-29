#include "AD8402.h"

struct Resistor
{
  unsigned short channel1Res;
  unsigned short channel2Res;
  unsigned char pinCS;
  unsigned char pinCLK;
  unsigned char pinMOSI;
};

struct Resistor AD8402_R = {0};

void setPins(unsigned char pinCS, unsigned char pinCLK, unsigned char pinMOSI){
  AD8402_R.pinCS = pinCS;
  AD8402_R.pinCLK = pinCLK;
  AD8402_R.pinMOSI = pinMOSI;
}

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
