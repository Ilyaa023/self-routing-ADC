
#include "Arduino.h"
#include "oin_global_interface.h"
#include "AD8402.h"

#define DELAY_MEASURE   2
#define DELAY_TIME      1

#define PIN_COMPORATOR  6
#define PIN_MEASURE     A0

#define PIN_MOSI        12
#define PIN_CLK         13
#define PIN_CS          11

#define PIN_BUTTON      3

#define OIN_CALLING       "oin"
#define ARDUINO_CALLING   "ard"

// extern struct OIN oins[10];
// extern byte numOfOins;

void resetOINs();
void GetMessage();
