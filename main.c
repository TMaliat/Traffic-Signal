#include "stm32f4xx.h"
#include "CLOCK.h"
#include "SYS_INIT.h"
#include "GPIO.h"
#include <stdlib.h>
#include <time.h>

void GPIO_Config(void){
	
	RCC -> AHB1ENR |= (1<<0); //enables GPIOA clock
	RCC -> AHB1ENR |= (1<<1); //enables GPIOB clock
	RCC -> AHB1ENR |= (1<<2); //enables GPIOC clock
	
	GPIOA -> OTYPER = 0;
	GPIOB -> OTYPER = 0;
	
	GPIOA -> OSPEEDR = 01;
	GPIOB -> OSPEEDR = 01;
	GPIOC -> OSPEEDR = 01;
}

int main(void){
	
	initClock();
	sysInit();
	GPIO_Config();
	
	GPIO_InitTypeDef op;
	GPIO_InitTypeDef ip;
	op.Mode = 01;
	ip.Mode = 00;
	
	
	GPIO_Init(GPIOA, &op);
	GPIO_Init(GPIOB, &op);
	GPIO_Init(GPIOC, &ip);
	srand(89);
	
	while(1)
	{
		int v11, v12, v21, v22;
		 
		 v11 = (rand() % 3); //traffic load of road1
		 v12 = (rand() % 3);
		 v21 = (rand() % 3); //traffic load of road2
		 v22 = (rand() % 3);
		
		if(v21>=2){
			GPIO_WritePin(GPIOB, GPIO_PIN_g1, GPIO_PIN_SET);
		}
		if(v22>=2){	
			GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		}
		if(v11>=2){
			GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
		}
		if(v12>=2){		
			GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
		}
		if(v21>=1){
			GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);	
		}
		if(v22>=1){	
			GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		}
		if(v11>=1){
			GPIO_WritePin(GPIOB, GPIO_PIN_g2, GPIO_PIN_SET);
		}
		if(v12>=1){	
			GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		}
		if(v21>=0){
			GPIO_WritePin(GPIOB, GPIO_PIN_r2, GPIO_PIN_SET);
		}
		if(v22>=0){
			GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		}
		if(v11>=0){
			GPIO_WritePin(GPIOB, GPIO_PIN_r1, GPIO_PIN_SET);
		}
		if(v12>=0){	
			GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		}
	
	  GPIO_WritePin(GPIOA, GPIO_PIN_r1, GPIO_PIN_SET); //turn on red light of road1
		
		if((GPIOC->IDR & (1<<7)) != 0)	
				GPIO_WritePin(GPIOA, GPIO_PIN_g2, GPIO_PIN_SET); //turn on green light of road2
	 
		ms_delay(10000);
		
		if(((GPIOC->IDR & (1<<5)) == 0 ) && ((GPIOC->IDR & (1<<6)) == 0 ))	ms_delay(5000); //if traffic is less in road1 then keep green ON road2 
		
		GPIO_WritePin(GPIOA, GPIO_PIN_g2, GPIO_PIN_RESET); //turn off green light of road2
		GPIO_WritePin(GPIOA, GPIO_PIN_y2, GPIO_PIN_SET); //turn on yellow light of road2
		ms_delay(3000);
		
	  GPIO_WritePin(GPIOA, GPIO_PIN_y2, GPIO_PIN_RESET); //turn off yellow light of road2
  	GPIO_WritePin(GPIOA, GPIO_PIN_r1, GPIO_PIN_RESET); //turn off red light of road1
		GPIO_WritePin(GPIOA, GPIO_PIN_r2, GPIO_PIN_SET); //turn on red light of road2
		
		//if((GPIOC->IDR & (1<<1)) != 0)	//checks if red of road2 is on
				GPIO_WritePin(GPIOA, GPIO_PIN_g1, GPIO_PIN_SET); //turn on green light of road1
	 
		ms_delay(10000);
		
		if(((GPIOC->IDR & (1<<3)) == 0 ) && ((GPIOC->IDR & (1<<2)) == 0 ))	ms_delay(5000);//if traffic is less in road2 then keep green ON road1
			
		GPIO_WritePin(GPIOA, GPIO_PIN_g1, GPIO_PIN_RESET); //turn off green light of road1
		GPIO_WritePin(GPIOA, GPIO_PIN_y1, GPIO_PIN_SET); 	//turn on yellow light of road1
		ms_delay(3000);
		
		GPIO_WritePin(GPIOA, GPIO_PIN_r2, GPIO_PIN_RESET);//turn off red light of road2
		GPIO_WritePin(GPIOA, GPIO_PIN_y1, GPIO_PIN_RESET);//turn off yellow light of road1

		//turn off the traffic load lights of road2
		GPIO_WritePin(GPIOB, GPIO_PIN_y1, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_r2, GPIO_PIN_RESET);
		
		GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_y2, GPIO_PIN_RESET);
		
		//turn off the traffic load lights of road1
		GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_g2, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, GPIO_PIN_r1, GPIO_PIN_RESET);
		
		GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	
	}
}
