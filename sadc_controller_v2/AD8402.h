#include "Arduino.h"

#define DELAY_RESISTANCE 1

void setPins(unsigned char pinCS, unsigned char pinCLK, unsigned char pinMOSI);
void setResistanceCh0 (unsigned char value);
void setResistanceCh1 (unsigned char value);