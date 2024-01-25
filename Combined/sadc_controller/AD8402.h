#include "target_info.h"
#ifdef TARGET_ARDUINO
  #include "Arduino.h"  
  #define DELAY_RESISTANCE 1
#elif defined TARGET_STM
  #define DELAY_RESISTANCE 1
  #define delayMicroseconds(unsigned long t) { delay(16 * t) }
  #define LOW 0
  #define HIGH 1
#endif

typedef struct Resistor {
  unsigned short channel1Res;
  unsigned short channel2Res;
  unsigned char pinCS;
  unsigned char pinCLK;
  unsigned char pinMOSI;
};

void setResistanceCh0 (unsigned char value);
void setResistanceCh1 (unsigned char value);