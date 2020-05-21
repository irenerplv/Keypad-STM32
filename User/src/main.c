#include "main.h"
#include "keyboard.h"
#include "timers.h"




int main(void)
{
	timer_ini();	
	Keyboard_ini();
	
	//__enable_irq();
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
	
	flag_GLOBAL   = 0;
	n_key_pressed = 0;
	while(1)
	{			
	}
	
}

