#include "main.h"

void SetResistor(unsigned char num, unsigned char value){
	PC_ODR_ODR7 = 0;
	for(int i = 1; i >= 0; i--){
		PA_ODR_ODR3 = (num >> i) & 1;
		PA_ODR_ODR1 = 0;
		delay(DELAY_TIME_RES);
		PA_ODR_ODR1 = 1;
		delay(DELAY_TIME_RES);
	}
	for (int i = 7; i >= 0; i--){
		PA_ODR_ODR3 = (value >> i) & 1;
		PA_ODR_ODR1 = 0;
		delay(DELAY_TIME_RES);
		PA_ODR_ODR1 = 1;
		delay(DELAY_TIME_RES);
	}
	PC_ODR_ODR7 = 1;
}