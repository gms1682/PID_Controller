#include "INIT.h"


void timer_init()
{
	// Enable the peripheral clock of GPIO Port	B
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOBEN;
	
	//Select Pin PB2 to generate PWM
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)	
	
	GPIOB->MODER = ~(3U<<(2*3));  	//Clear the bits 12 and 13 
	GPIOB->MODER |= 2U<<(2*3);      //Set Pin PB6 to AlterFunc(10) 
	GPIOB->AFR[0] |= 0X2<<(4*6);		//PIN PB6 AS AF TIM4
	
	TIM4->PSC=80;                  //Prescaler
  TIM4->EGR  |= TIM_EGR_UG;      //Force load new prescaler in to the register
	
  TIM4->CCER &= ~(0XFFFFFFFF);
  TIM4->CCMR1 |= 0X1;            //Select Channel 1 for Timer 4
  TIM4->CCER |= (1<<1 | 1<<3);   //Select rising edge
  TIM4->CCER |= 0X1;
	
  TIM4->CR1 |= TIM_CR1_CEN;			//Start Input Capture Mode
}

void pwm_init()
{
	// Enable the peripheral clock of GPIO Port	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;	
	
	// PA0 is now in input mode
	GPIOA->MODER &= ~3 ;				
	GPIOA->MODER |= 2 ;
	GPIOA->AFR[0] |= 0X1; 														//PIN PA0 AS AF TIM2_CH1


	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	
	TIM2->PSC=8000;  																//Prescaler	
	TIM2->EGR|=TIM_EGR_UG;														//Force load new prescaler in to the register
	
	TIM2->ARR =200-1;
	
	TIM2->CCMR1|=TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2;
	TIM2->CCMR1|=TIM_CCMR1_OC1PE;
	TIM2->CR1|=TIM_CR1_ARPE;
	TIM2->CCER|=TIM_CCER_CC1E;
	
	TIM2->SR &= ~TIM_SR_UIF;
	TIM2->DIER|= TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
}
