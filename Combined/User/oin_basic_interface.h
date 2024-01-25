/*
A1 -> clkRES (write when LOW)
A2 -> two LEDs
A3 -> dataRES

B4 -> balanceControl
B5 -> NC

C7 -> csRES (LOW to write in resistor via spi, HIGH to set resistance)
C6 -> comparatorControl
C5 -> oinMinusControl
C4 <- oin+1 input
C3 -> oinPlusControl

D1 -> SWIM
D2 -> shotdown in/out
D3 -> powerControl (blue resistor)
D4 -> single LED
D5 -> TX
D6 -> RX
*/

#include "iostm8s003f3.h"
#include "oin_global_interface.h"
#include "AD8402.h"


#define ID 192							//individual ID minimum 192, maximum 255 (except cases when logging via the same port)
#define DELAY_TIME_RES 320

#define PIN_CS          PC_ODR_ODR7
#define PIN_CLK         PA_ODR_ODR1
#define PIN_MOSI        PA_ODR_ODR3

#define PIN_BALANCE     PB_ODR_ODR4
#define PIN_COMP        PC_ODR_ODR6
#define PIN_MINUS       PC_ODR_ODR5
#define PIN_PLUS        PC_ODR_ODR3
#define PIN_POWER       PD_ODR_ODR3

#define PIN_COUPLE_LEDS PA_ODR_ODR2
#define PIN_SINGLE_LED  PD_ODR_ODR4

enum MinusKey{
    COMPARATOR,
    MINUS_1,
    MINIS_2
};

enum PlusKey{
    BALANCE,
    PLUS_1,
    PLIS_2
};

enum PowerKey{
    GROUND,
    POWER
};

enum LedState{
    COUPLE_GREEN,
    COUPLE_RED,
    SINGLE_RED
}

static void delay(unsigned long t){ while(t--); }

void CLK_Init();
void UART1_Init();
void GPIO_Init();

void UART1_send_char(char ch);
void UART1_print_string(char *str);
void UART1_print_bcd(unsigned char num);

void setMinusLink (enum MinusKey mk);
void setPlusLink (enum PlusKey pk);
void setPowerLink (enum PowerKey pk);

void setLedState (enum LedState ls);

extern unsigned char state = 0; 	//active or inactive
extern unsigned char mode = 0;		//0 -> comand, 1 -> resistance 0, 2 -> resistance 1