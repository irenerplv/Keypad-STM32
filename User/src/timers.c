#include "timers.h"
#include "keyboard.h"

void timer_ini(void)
{
	TIM_TimeBaseInitTypeDef tim_init;												// Структура, содержащая настройки таймеров
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);		// Включаем тактирование таймеров
	TIM_TimeBaseStructInit(&tim_init);
	
	tim_init.TIM_Period      = 10000;												// Период отсчета таймера
	tim_init.TIM_Prescaler   = 16;													// Предделитель частоты таймера
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;									// Счет таймера "вверх"
	
	TIM_TimeBaseInit(TIM2, &tim_init);												// Применение прописанных настроек к таймеру 2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);										// разрешение прерываний по таймеру 2
	
	//tim_init.TIM_Period = 1000;
	TIM_TimeBaseInit(TIM3, &tim_init);												// Применение прописанных настроек к таймеру 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);										// разрешение прерываний по таймеру 3
	
	TIM_Cmd(TIM2, ENABLE);															// Включение таймера 2
	TIM_Cmd(TIM3, ENABLE);															// Включение таймера 3
}

void TIM2_IRQHandler(void) 
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	Change_Pins();
}

void TIM3_IRQHandler(void) 
{
//	uint8_t row_value;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	Key_Read();
	if(Key_Count == 3)
		All_buttons_filter();
	
	// если кнопка/кнопки нажаты дольше 1 сек 
	if(flag_GLOBAL == LONG_PRESSED)									
	{
		flag_GLOBAL = NO_PRESSED;
		
		// нажаты 2 кнопки
		if(n_key_pressed == 2) 										
		{
			double_key_pressed(Key_Pressed[0], Key_Pressed[1]);
			
		}
		// нажата одна кнопка
		else if(n_key_pressed == 1)									
		{
			single_key_pressed(Key_Pressed[0]);
		}
		flag_STATE_KEY[x_key[0]][y_key[0]] = NO_PRESSED;
		flag_STATE_KEY[x_key[1]][y_key[1]] = NO_PRESSED;
		
	}
	// короткое нажатие кнопок
	else if(flag_GLOBAL == PRESSED)									
	{
		flag_GLOBAL = NO_PRESSED;
		
		// нажаты 2 кнопки
		if(n_key_pressed == 2)										
		{
			double_key_long_pressed(Key_Pressed[0], Key_Pressed[1]);
		}
		
		// нажата одна кнопка
		else if(n_key_pressed == 1)									
		{
			single_key_long_pressed(Key_Pressed[0]);
		}
		flag_STATE_KEY[x_key[0]][y_key[0]] = NO_PRESSED;
		flag_STATE_KEY[x_key[1]][y_key[1]] = NO_PRESSED;
		
	}
	else 
	{
		n_key_pressed  = 0;
		Key_Pressed[0] = '\0';
		Key_Pressed[1] = '\0';
		flag_GLOBAL = NO_PRESSED;
		
	}
	
}
