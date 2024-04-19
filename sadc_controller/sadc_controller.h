/*
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║ Commands:                                                                                                         ║
╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
║   Send these commands to Arduino via UART                                                                         ║
║   Case doesn't matter                                                                                             ║
╠═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
║ OIN commands:                                                                                                     ║
╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
║   1. Ping by ID                                                                                                   ║
║     oin123p                                                                                                       ║
║     ││││││└─ Keyword that means "ping"                                                                            ║
║     ││││││                                                                                                        ║
║     │││└└└── ID of called OIN. 1-3 digits                                                                         ║
║     │││                                                                                                           ║
║     └└└───── Keyword that means workng with OIN                                                                   ║
║                                                                                                                   ║
║   2. On/off                                                                                                       ║
║     oin123xxx                                                                                                     ║
║     ││││││└└└ Write "on" to turn on the OIN and "off" to turn off the OIN                                         ║
║     ││││││                                                                                                        ║
║     │││└└└─── ID of called OIN. 1-3 digits                                                                        ║
║     │││                                                                                                           ║
║     └└└────── Keyword that means workng with OIN                                                                  ║
║                                                                                                                   ║
║   3. Change ID                                                                                                    ║
║     oin123c456                                                                                                    ║
║     │││││││└└└ New ID                                                                                             ║
║     │││││││                                                                                                       ║
║     ││││││└─── Keyword that means "change"                                                                        ║
║     ││││││                                                                                                        ║
║     │││└└└──── ID of called OIN. 1-3 digits                                                                       ║
║     │││                                                                                                           ║
║     └└└─────── Keyword that means workng with OIN                                                                 ║
║                                                                                                                   ║
║   4. Reset ID                                                                                                     ║
║     oin123r                                                                                                       ║
║     ││││││└─── Keyword that means "reset"                                                                         ║
║     ││││││                                                                                                        ║
║     │││└└└──── ID of called OIN. 1-3 digits                                                                       ║
║     │││                                                                                                           ║
║     └└└─────── Keyword that means workng with OIN                                                                 ║
║                                                                                                                   ║
║   5. Change keys states                                                                                           ║
║     oin123s123                                                                                                    ║
║     │││││││││└─── state of keys to lower OIN or balance                                                           ║
║     │││││││││       0 to disconnect                                                                               ║
║     │││││││││       1 to connect to plus 1 line                                                                   ║
║     │││││││││       2 to connect to plus 2 line                                                                   ║
║     │││││││││       3 to connect to balamce                                                                       ║
║     │││││││││                                                                                                     ║
║     ││││││││└──── state of keys to higher OIN                                                                     ║
║     ││││││││        0 to connect to ground                                                                        ║
║     ││││││││        1 to connect to power                                                                         ║
║     ││││││││                                                                                                      ║
║     │││││││└───── state of keys to higher OIN                                                                     ║
║     │││││││         0 to disconnect                                                                               ║
║     │││││││         1 to connect to minus 1 line                                                                  ║
║     │││││││         2 to connect to minus 2 line                                                                  ║
║     │││││││         3 to connect to comparator                                                                    ║
║     │││││││                                                                                                       ║
║     ││││││└────── Keyword that means "set"                                                                        ║
║     ││││││                                                                                                        ║
║     │││└└└─────── ID of called OIN. 1-3 digits                                                                    ║
║     │││                                                                                                           ║
║     └└└────────── Keyword that means workng with OIN                                                              ║
║                                                                                                                   ║
║   TODO: IMPLEMENT RESISTANCE MANAGEMENT                                                                           ║
║                                                                                                                   ║
╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
║ Arduino commands:                                                                                                 ║
╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
║   1. Start/stop measuring                                                                                         ║
║     ardsm0                                                                                                        ║
║     │││││└─ State of masuring.                                                                                    ║
║     │││││     0 to stop                                                                                           ║
║     │││││     1 to start                                                                                          ║
║     │││││                                                                                                         ║
║     │││└└── Keyword that means "state of measuring"                                                               ║
║     │││                                                                                                           ║
║     └└└──── Keyword that means workng with Arduino                                                                ║
║                                                                                                                   ║
║   2. Start/stop changing resistance                                                                               ║
║     ardsr0                                                                                                        ║
║     │││││└─ State of masuring.                                                                                    ║
║     │││││     0 to stop                                                                                           ║
║     │││││     1 to start                                                                                          ║
║     │││││                                                                                                         ║
║     │││└└── Keyword that means "state of resistance"                                                              ║
║     │││                                                                                                           ║
║     └└└──── Keyword that means workng with Arduino                                                                ║
║                                                                                                                   ║
║   3. Change resistance                                                                                            ║
║     ardr123                                                                                                       ║
║     ││││└└└─ resistance from 0 to 255                                                                             ║
║     ││││                                                                                                          ║
║     │││└──── Keyword that means "resistance"                                                                      ║
║     │││                                                                                                           ║
║     └└└───── Keyword that means workng with Arduino                                                               ║
║                                                                                                                   ║
║   4. Change timings (NOT IMPLEMENTED)                                                                             ║
║     ardt123                                                                                                       ║
║     ││││└└└─ resistance from 0 to 65535                                                                           ║
║     ││││                                                                                                          ║
║     │││└──── Keyword that means "timing"                                                                          ║
║     │││                                                                                                           ║
║     └└└───── Keyword that means workng with Arduino                                                               ║
║                                                                                                                   ║
╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
*/

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

// extern struct OIN oins[10];
extern byte numOfOins;


