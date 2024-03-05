#include "iostm8s003f3.h"

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

void CLK_Init();
void UART1_Init();
void GPIO_Init();
void UART1_send_char(char ch);
void UART1_print_string(char *str);
void UART1_print_bcd(unsigned char num);
void SetResistor(unsigned char num, unsigned char value);

static void delay(unsigned long t){ while(t--); }

unsigned char data = 0;
unsigned char ID = 195; 	//individual ID minimum 192, maximum 255
unsigned char state = 0; 	//active or inactive
unsigned char mode = 0;		//0 -> comand, 1 -> resistance 0, 2 -> resistance 1
unsigned long delayTimeRes = 320;
/*char firstHalfByteResistor = 0;
char secondHalfByteResistor = 0;
char buttonState = 0;*/

int main( void )
{
  CLK_Init();
	UART1_Init();
  GPIO_Init();

//	while(1){
//		PD_ODR_ODR4 = 0;
//		delay(100000);
//		PD_ODR_ODR4 = 1;
//		delay(100000);

		SetResistor(0, 0xFF);
		SetResistor(1, 0xFF);
//	}
	while(1){
		data = 0;
		while (!UART1_SR_RXNE);
		data = UART1_DR;
		switch (mode) {
			case 0:
				switch (data >> 5){
					case 0: //keys
						if (state == 1) {
							PD_ODR_ODR3 = !(data & 1);
							PC_ODR_ODR5 = ((data >> 1) & 1);
							PC_ODR_ODR6 = !((data >> 2) & 1);
							PC_ODR_ODR3 = ((data >> 3) & 1);
							PB_ODR_ODR4 = (data >> 4) & 1;//(data & 16);
							//PC_ODR_ODR4 = 1;
						}
						break;
					case 3:	//set res 0 error
						//show diode
					case 1: //set res 0
						if (state == 1)
							mode = 1;
						break;
					case 4: //set res 1 error
						//show diode
					case 2: //set res 1
						if (state == 1)
							mode = 2;
						break;
					/*case 5:
						//reserved
						break;*/
					case 6:
					case 7:
						state = (ID == data) ? 1 : 0;
						break;
				}
				break;
			case 1:
				SetResistor(0, data);
				mode = 0;
				break;
			case 2:
				SetResistor(1, data);
				mode = 0;
				break;
		}
		/*switch(data >> 6){
		case 3: {
			if (ID == data) state = 1; else state = 0;
			break;
		}
		case 0: {
			if (state == 1) {
				//keysControl
				PD_ODR_ODR4 = !(data & 1);
				PC_ODR_ODR7 = !(data & 2);
				PC_ODR_ODR6 = !(data & 4);
				PC_ODR_ODR5 = !(data & 8);
				PC_ODR_ODR4 = !(data & 16);
			}
			break;
		}
		case 1: {
			if (state == 1){
				//R1
				PB_ODR_ODR5 = 1; //rst = 1
				firstHalfByteResistor = data & 63; //0b00111111
				for (char i = 0; i < 8; i++) {
					PA_ODR_ODR2 = (firstHalfByteResistor >> i) & 1 == 1; //R1 data
					PA_ODR_ODR1 = 1; //clk = 1
					delay(2);
					PA_ODR_ODR1 = 0; //clk = 0
					delay(2);
				}
				for (char i = 0; i < 8; i++) {
					PA_ODR_ODR2 = (secondHalfByteResistor >> i) & 1 == 1; //R2 data
					PA_ODR_ODR1 = 1; //clk = 1
					delay(2);
					PA_ODR_ODR1 = 0; //clk = 0
					delay(2);
				}
				PB_ODR_ODR5 = 0; //rst = 0
			}
			break;
		}
		case 2: {
			if (state == 1){
				//R2
				PB_ODR_ODR5 = 1;
				secondHalfByteResistor = data & 63;
				for (char i = 0; i < 8; i++) {
					PA_ODR_ODR2 = (firstHalfByteResistor >> i) & 1 == 1;
					PA_ODR_ODR1 = 1;
					delay(2);
					PA_ODR_ODR1 = 0;
					delay(2);
				}
				for (char i = 0; i < 8; i++) {
					PA_ODR_ODR2 = (secondHalfByteResistor >> i) & 1 == 1;
					PA_ODR_ODR1 = 1;
					delay(2);
					PA_ODR_ODR1 = 0;
					delay(2);
				}
				PB_ODR_ODR5 = 0;
			}
			break;
		}
		}*/
	}
  return 0;
}

void CLK_Init(){
	//fCPU = 16 MHz
	CLK_CKDIVR_HSIDIV = 0;
	CLK_CKDIVR_CPUDIV = 0;
	// Enable HSE
	/*CLK_SWR = 0xB4;*/
	CLK_PCKENR1 = 0xFF;
	CLK_PCKENR2 = 0xFF;
}

void UART1_Init(){
	UART1_CR1_UART0 = 1;  // set UARTD, UART1 disable
	// 115200 Baud Rate, when fMASTER=16MHz
	UART1_BRR2=0x0b;
	UART1_BRR1=0x08;
	// 1000000 Baud Rate, when fMASTER=16MHz
//	UART1_BRR2=0x00;
//	UART1_BRR1=0x01;
	UART1_CR2_TEN = 1;    // set TEN, Transmission Enable
	UART1_CR2_REN = 1;    // set REN, Recieve Enable
//	UART1_CR2_RWU = 1;		// set RWU, Receiver wakeup
	UART1_CR1_UART0 = 0;  // clear UARTD, UART1 enable
}

void GPIO_Init(){
	PA_DDR_DDR1 = 1;
	PA_DDR_DDR2 = 1;
	PA_DDR_DDR3 = 1;
	PB_DDR_DDR4 = 1;
	PC_DDR_DDR3 = 1;
	PC_DDR_DDR4 = 0;
	PC_DDR_DDR5 = 1;
	PC_DDR_DDR6 = 1;
	PC_DDR_DDR7 = 1;
//	PD_DDR_DDR2 = 1;
	PD_DDR_DDR3 = 1;
	PD_DDR_DDR4 = 1;

	PA_CR1_C11 = 1;
	PA_CR1_C12 = 1;
	PA_CR1_C13 = 1;
	PB_CR1_C14 = 1;
	PC_CR1_C13 = 1;
	PC_CR1_C14 = 0;
	PC_CR1_C15 = 1;
	PC_CR1_C16 = 1;
	PC_CR1_C17 = 1;
//	PD_CR1_C12 = 1;
	PD_CR1_C13 = 1;
	PD_CR1_C14 = 1;

	PA_CR2_C21 = 0;
	PA_CR2_C22 = 0;
	PA_CR2_C23 = 0;
	PB_CR2_C24 = 0;
	PC_CR2_C23 = 0;
	PC_CR2_C24 = 0;
	PC_CR2_C25 = 0;
	PC_CR2_C26 = 0;
	PC_CR2_C27 = 0;
//	PD_CR2_C22 = 0;
	PD_CR2_C23 = 0;
	PD_CR2_C24 = 0;

	PA_ODR_ODR1 = 1;
	PA_ODR_ODR2 = 1;
	PA_ODR_ODR3 = 1;
	PB_ODR_ODR4 = 1;
	PC_ODR_ODR3 = 1;
	PC_ODR_ODR4 = 0;
	PC_ODR_ODR5 = 1;
	PC_ODR_ODR6 = 0;
	PC_ODR_ODR7 = 1;
//	PD_ODR_ODR2 = 1;
	PD_ODR_ODR3 = 1;
	PD_ODR_ODR4 = 1;
}

void SetResistor(unsigned char num, unsigned char value){
	/*PB_ODR_ODR5 = 0;
	for (int i = 1; i >= 0; i--){
		PA_ODR_ODR2 = num >> i & 1;
		PA_ODR_ODR1 = 0;
		delay(delayTimeRes);
		PA_ODR_ODR1 = 1;
		delay(delayTimeRes);
	}
	for (int i = 7; i >= 0; i--){
		PA_ODR_ODR2 = value >> i & 1;
		PA_ODR_ODR1 = 0;
		delay(delayTimeRes);
		PA_ODR_ODR1 = 1;
		delay(delayTimeRes);
	}
	PB_ODR_ODR5 = 1;*/
	PC_ODR_ODR7 = 0;
	for(int i = 1; i >= 0; i--){
		PA_ODR_ODR3 = (num >> i) & 1;
		PA_ODR_ODR1 = 0;
		delay(delayTimeRes);
		PA_ODR_ODR1 = 1;
		delay(delayTimeRes);
	}
	for (int i = 7; i >= 0; i--){
		PA_ODR_ODR3 = (value >> i) & 1;
		PA_ODR_ODR1 = 0;
		delay(delayTimeRes);
		PA_ODR_ODR1 = 1;
		delay(delayTimeRes);
	}
//	int addrAndCom = 0;
//	for (int i = 0; i < 10; i++){
//		PA_ODR_ODR3 = ( addrAndCom >> i) & 1;
//		PA_ODR_ODR1 = 0;
//		delay(delayTimeRes);
//		PA_ODR_ODR1 = 1;
//		delay(delayTimeRes);
//	}
//	addrAndCom = 2;
//	for (int i = 0; i < 10; i++){
//		PA_ODR_ODR3 = ( addrAndCom >> i) & 1;
//		PA_ODR_ODR1 = 0;
//		delay(delayTimeRes);
//		PA_ODR_ODR1 = 1;
//		delay(delayTimeRes);
//	}
	PC_ODR_ODR7 = 1;
}