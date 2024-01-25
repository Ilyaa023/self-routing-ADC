#include "Arduino.h"
#include "oin_global_interface.h"
#include "AD8402.h"
#include "target_info.h"

#define delayMeasure    1000

#define ARRAY_LENGTH    2

extern struct Resistor AD8402_R;

byte command[ARRAY_LENGTH];
byte oinArray[ARRAY_LENGTH] = {195, 197};  //From high to low

byte count = 0;

String measured = "00000000";
