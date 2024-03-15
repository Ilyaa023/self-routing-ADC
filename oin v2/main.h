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
#include "legacy.h"

#define SET_POWER       PD_ODR_ODR4 = 0
#define SET_GROUND      PD_ODR_ODR4 = 1
#define RESET_PLUS      {PD_ODR_ODR3 = 0; PC_ODR_ODR3 = 1; PD_ODR_ODR2 = 1;}
#define SET_PLUS1       {PD_ODR_ODR3 = 0; PC_ODR_ODR3 = 1; PD_ODR_ODR2 = 0;}
#define SET_PLUS2       {PD_ODR_ODR3 = 0; PC_ODR_ODR3 = 0; PD_ODR_ODR2 = 1;}
#define SET_BALANCE     {PD_ODR_ODR3 = 1; PC_ODR_ODR3 = 1; PD_ODR_ODR2 = 1;}
#define RESET_MINUS     {PA_ODR_ODR1 = 1; PC_ODR_ODR7 = 1; PC_ODR_ODR4 = 1;}
#define SET_MINUS1      {PA_ODR_ODR1 = 1; PC_ODR_ODR7 = 0; PC_ODR_ODR4 = 1;}
#define SET_MINUS2      {PA_ODR_ODR1 = 1; PC_ODR_ODR7 = 1; PC_ODR_ODR4 = 0;}
#define SET_COM         {PA_ODR_ODR1 = 0; PC_ODR_ODR7 = 1; PC_ODR_ODR4 = 1;}

#define SET_LED4       	PB_ODR_ODR4 = 0
#define RESET_LED4     	PB_ODR_ODR4 = 1

#define ID 193							//individual ID minimum 192, maximum 255 (except cases when logging via the same port)
#define DELAY_TIME_RES 320

static void delay(unsigned long t){ while(t--); }

void CLK_Init();
void UART1_Init();
void GPIO_Init();
void UART1_send_char(char ch);
void UART1_print_string(char *str);
void UART1_print_bcd(unsigned char num);
void SetResistor(unsigned char num, unsigned char value);

void DecomposeCom (unsigned char data);
void Ping ();

