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

#define ID 192							//individual ID minimum 192, maximum 255 (except cases when logging via the same port)
#define DELAY_TIME_RES 320

static void delay(unsigned long t){ while(t--); }

void CLK_Init();
void UART1_Init();
void GPIO_Init();
void UART1_send_char(char ch);
void UART1_print_string(char *str);
void UART1_print_bcd(unsigned char num);
void SetResistor(unsigned char num, unsigned char value);

unsigned char state = 0; 	//active or inactive
unsigned char mode = 0;		//0 -> comand, 1 -> resistance 0, 2 -> resistance 1