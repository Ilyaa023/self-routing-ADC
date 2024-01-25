#include "main.h"

/*char firstHalfByteResistor = 0;
char secondHalfByteResistor = 0;
char buttonState = 0;*/

unsigned char state = 0; 	//active or inactive
unsigned char mode = 0;		//0 -> comand, 1 -> resistance 0, 2 -> resistance 1

int main( void )
{
  CLK_Init();
	UART1_Init();
  GPIO_Init();

		SetResistor(0, 0xFF);
		SetResistor(1, 0xFF);

	while(1){
		unsigned char data = 0;
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

	}
  return 0;
}