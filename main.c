#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"
#include "INIT.h"

#include <string.h>
#include <stdio.h>

int main(void){

	System_Clock_Init(); 
	UART2_Init();
	timer_init();
	pwm_init();
	
	TIM2->CCR1=1; 	//Start PWM
	
	while (1);
	
	return 0;
}