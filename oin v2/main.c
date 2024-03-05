#include "main.h"

/*char firstHalfByteResistor = 0;
char secondHalfByteResistor = 0;
char buttonState = 0;*/



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
	PB_ODR_ODR4 = 0;
	PC_ODR_ODR3 = 1;
	PC_ODR_ODR4 = 0;
	PC_ODR_ODR5 = 1;
	PC_ODR_ODR6 = 0;
	PC_ODR_ODR7 = 1;
//	PD_ODR_ODR2 = 1;
	PD_ODR_ODR3 = 1;
	PD_ODR_ODR4 = 1;
}




int main( void )
{
  CLK_Init();
	UART1_Init();
  GPIO_Init();

//		SetResistor(0, 0xFF);
//		SetResistor(1, 0xFF);

	while(1){
		unsigned char data = 0;
		while (!UART1_SR_RXNE);
		data = UART1_DR;
		switch (mode) {
			case 0:
				switch (data >> 5){
					case 0: //keys
						if (state == 1) {
							PD_ODR_ODR4 = (data & 1);
							PD_ODR_ODR3 = ((data >> 1) & 1);
							PA_ODR_ODR1 = ((data >> 2) & 1);
							PD_ODR_ODR2 = ((data >> 3) & 1);
							PC_ODR_ODR7 = (data >> 4) & 1;//(data & 16);
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
//				SetResistor(0, data);
				mode = 0;
				break;
			case 2:
//				SetResistor(1, data);
				mode = 0;
				break;
		}

	}
  return 0;
}