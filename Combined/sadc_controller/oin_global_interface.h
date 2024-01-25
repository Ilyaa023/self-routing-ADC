/*
╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║ Communications:                                                                                                   ║
╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
║   Communication is a process that implements transfer data from main board to OIN and back to main board          ║
║   Every OIN member the last called ID and if its matching with OIN's ID then all commands will be received        ║
║   Otherwise OIN will receive only request by ID command (0b10000000)                                              ║
║                                                                                                                   ║
╠═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
║ Process map:                                                                                                      ║
╟─────────────────────────────────────────────────────────┬─────────────────────────────────────────────────────────╢
║   1. 0bxxxxxxxx                                         │ 1. 0bxxxxxxxx - first byte                              ║
║        0 is for 1 byte to transmit/receive              │      1 is for 2 bytes to transmit/receive               ║
║        01xxxxxx is for change key states                │                                                         ║
║          │││││└── state of power/ground key             │      10000000 is for request by ID                      ║
║          │││││      0 is for ground                     │      10000001 is for change ID                          ║
║          │││││      1 is for power                      │                                                         ║
║          │││││                                          │      all another commands are reserved and              ║
║          │││└└─── state of keys to higher OIN           │      ready to implement new functionality               ║
║          │││        00 is for connect to minus 1 line   │                                                         ║
║          │││        01 is for connect to minus 2 line   │ 2. 0bxxxxxxxx - second byte                             ║
║          │││        10 is for connect to comparator     │                                                         ║
║          │││        11 reserved                         │     current version is just about to                    ║
║          │││                                            │     send ID (0 - 255) as data in second byte            ║
║          │└└───── state of keys to lower OIN or balance │                                                         ║
║          │          00 is for connect to plus 1 line    │     latest version would use that architecture          ║
║          │          01 is for connect to plus 2 line    │     to implement transmitting more data                 ║
║          │          10 is for connect to balance        │                                                         ║
║          │          11 reserved                         │                                                         ║
║          │                                              │                                                         ║
║          └─────── reserved                              │                                                         ║
║                                                         │                                                         ║
║        0 is for 1 byte to transmit/receive              │                                                         ║
║        0000000x is for turn on/off the OIN              │                                                         ║
║        0000001x is for change operability               │                                                         ║
║        00000100 is for send target ID                   │                                                         ║
║                                                         │                                                         ║
║                                                         │                                                         ║
║                                                         │                                                         ║
║                                                         │                                                         ║
╚═════════════════════════════════════════════════════════╧═════════════════════════════════════════════════════════╝
*/

#define COM_BALANCE     0b00010000                      // use the '|'
#define COM_OIN_PLUS2   0b00001000                      // use the '|'
#define COM_COMPORATOR  0b00000100                      // use the '|'
#define COM_OIN_MINUS2  0b00000010                      // use the '|'
#define COM_POWER       0b00000001                      // use the '|'

#define COM_OIN_PLUS    ~COM_BALANCE                    // use the '&'
#define COM_OIN_MINUS1  ~COM_OIN_MINUS2 & COM_OIN_MINUS // use the '&'
#define COM_OIN_MINUS   ~COM_COMPORATOR                 // use the '&'
#define COM_OIN_PLUS1   ~COM_OIN_PLUS2 & COM_OIN_PLUS   // use the '&'
#define COM_GROUND      ~COM_POWER                      // use the '&'

#define OIN_MIDDLE      0 & COM_OIN_PLUS1 & COM_OIN_MINUS1 & COM_GROUND  //OIN + 1, OIN - 1, Ground
#define OIN_HIGH        (COM_COMPORATOR | COM_POWER ) & COM_OIN_PLUS1  //OIN + 1, Comporator, Power, (OIN-2)
//#define OIN_LOW         (COM_BALANCE | COM_OIN_PLUS2 | COM_COMPORATOR | COM_OIN_MINUS2) & COM_GROUND
#define OIN_LOW         (COM_BALANCE | COM_OIN_PLUS2) & COM_OIN_MINUS1 & COM_GROUND  //Balance, OIN - 1, Ground, (OIN+2)

#define UART_SPEED      115200