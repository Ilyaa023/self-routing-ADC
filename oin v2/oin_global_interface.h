/*
+-------------------------------------------------------------------------------------------------------------------+
¦ Communications:                                                                                                   ¦
¦-------------------------------------------------------------------------------------------------------------------¦
¦   Communication is a process that implements transfer data from main board to OIN and back to main board          ¦
¦   Every OIN member the last called ID and if its matching with OIN's ID then all commands will be received        ¦
¦   Otherwise OIN will receive only request by ID command (0b10000000)                                              ¦
¦                                                                                                                   ¦
¦-------------------------------------------------------------------------------------------------------------------¦
¦ Process map:                                                                                                      ¦
¦-------------------------------------------------------------------------------------------------------------------¦
¦   1. 0bxxxxxxxx                                                                                                   ¦
¦        0 is for 1 byte to transmit/receive                                                                        ¦
¦        01xxxxxx is for change key states                                                                          ¦
¦          ¦¦¦¦¦+-- state of power/ground key. Set to pull on power and reset to push on ground                     ¦
¦          ¦¦¦¦¦      0 is for ground                                                                               ¦
¦          ¦¦¦¦¦      1 is for power                                                                                ¦
¦          ¦¦¦¦¦                                                                                                    ¦
¦          ¦¦¦++--- state of keys to higher OIN                                                                     ¦
¦          ¦¦¦        00 is for disconnect                                                                          ¦
¦          ¦¦¦        01 is for connect to minus 1 line                                                             ¦
¦          ¦¦¦        10 is for connect to minus 2 line                                                             ¦
¦          ¦¦¦        11 is for connect to comparator                                                               ¦
¦          ¦¦¦                                                                                                      ¦
¦          ¦++----- state of keys to lower OIN or balance                                                           ¦
¦          ¦          00 is for disconnect                                                                          ¦
¦          ¦          01 is for connect to plus 1 line                                                              ¦
¦          ¦          10 is for connect to plus 2 line                                                              ¦
¦          ¦          11 is for connect to balance                                                                  ¦
¦          ¦                                                                                                        ¦
¦          +------- reserved                                                                                        ¦
¦                                                                                                                   ¦
¦        0 is for 1 byte to transmit/receive                                                                        ¦
¦        0000000x is for turn on/off the OIN                                                                        ¦
¦        0000001x is for change operability                                                                         ¦
¦        00000100 is for reset target ID  ?                                                                         ¦
¦                                                                                                                   ¦
¦-------------------------------------------------------------------------------------------------------------------¦
¦   1. 0bxxxxxxxx - first byte                                                                                      ¦
¦        1 is for 2 bytes to transmit/receive                                                                       ¦
¦                                                                                                                   ¦
¦        10000000 is for request by ID                                                                              ¦
¦        10000001 is for change ID                                                                                  ¦
¦        10000010 is for ping by ID                                                                                 ¦
¦                                                                                                                   ¦
¦        all another commands are reserved and ready to implement new functionality                                 ¦
¦   2. 0bxxxxxxxx - second byte                                                                                     ¦
¦                                                                                                                   ¦
¦        current version is just about to send ID (1 - 255) as data in second byte                                  ¦
¦                                                                                                                   ¦
¦        latest version would use that architecture to implement transmitting more data                             ¦
¦                                                                                                                   ¦
+-------------------------------------------------------------------------------------------------------------------+
*/

#define COM_BALANCE_MASK     b00011000
#define COM_OIN_PLUS1_MASK   b00001000
#define COM_OIN_PLUS2_MASK   b00010000
#define COM_COMPORATOR_MASK  b00000110
#define COM_OIN_MINUS1_MASK  b00000010
#define COM_OIN_MINUS2_MASK  b00000100
#define COM_POWER_MASK       b00000001

#define OIN_DISABLE     b01000000

#define OIN_HIGH        OIN_DISABLE | (255 & COM_OIN_PLUS1_MASK) | (255 & COM_COMPORATOR_MASK) | (255 & COM_POWER_MASK)  //OIN + 1, Comporator, Power
#define OIN_MIDDLE      OIN_DISABLE | (255 & COM_OIN_PLUS1_MASK) | (255 & COM_OIN_MINUS1_MASK) | (0 & COM_POWER_MASK)  //OIN + 1, OIN - 1, Ground
#define OIN_LOW         OIN_DISABLE | (255 & COM_BALANCE_MASK) | ( 255 & COM_OIN_MINUS1_MASK) | (0 & COM_POWER_MASK)  //Balance, OIN - 1, Ground

#define OIN_REQUEST     b10000000
#define OIN_CHANGE      b10000001
#define OIN_PING        b10000010

#define OIN_RESET_ID    b00000100
#define OIN_TURN_OFF    b00000000
#define OIN_TURN_ON     b00000001

#define UART_SPEED      115200