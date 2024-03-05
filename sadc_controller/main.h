// #include "Arduino.h"

// #define COM_COMPORATOR  0b00000100  // use the '|'
// #define COM_OIN_MINUS1  0b11111001  // use the '&'
// #define COM_OIN_MINUS2  0b00000010  // use the '|'
// #define COM_OIN_MINUS   0b11111011  // use the '&'
// #define COM_OIN_PLUS1   0b11100111  // use the '&'
// #define COM_OIN_PLUS2   0b00001000  // use the '|'
// #define COM_OIN_PLUS    0b11101111  // use the '&'
// #define COM_BALANCE     0b00010000  // use the '|'
// #define COM_GROUND      0b11111110  // use the '&'
// #define COM_POWER       0b00000001  // use the '|'

// #define PIN_COMPORATOR  6
// #define PIN_MEASURE     A0

// #define PIN_MOSI        12
// #define PIN_CLK         13
// #define PIN_CS          11

// #define PIN_BUTTON      3

// #define OIN_MIDDLE      0 & COM_OIN_PLUS1 & COM_OIN_MINUS1 & COM_GROUND  //OIN + 1, OIN - 1, Ground
// #define OIN_HIGH        (COM_COMPORATOR | COM_POWER ) & COM_OIN_PLUS1  //OIN + 1, Comporator, Power, (OIN-2)
// //#define OIN_LOW         (COM_BALANCE | COM_OIN_PLUS2 | COM_COMPORATOR | COM_OIN_MINUS2) & COM_GROUND
// #define OIN_LOW         (COM_BALANCE | COM_OIN_PLUS2) & COM_OIN_MINUS1 & COM_GROUND  //Balance, OIN - 1, Ground, (OIN+2)

// #define UART_SPEED      115200
// #define delayTime       1
// #define delayMeasure    1000

// #define ARRAY_LENGTH    2

// byte command[ARRAY_LENGTH];
// byte oinArray[ARRAY_LENGTH] = {195, 197};  //From high to low

// byte count = 0;

// String measured = "00000000";
