#ifndef KEYBOARD_H
#define KEYBOARD_H


	#include "main.h"

	#define N_ROWS			4
	#define N_CLMS			3
	

	
	#define GPIO_ROW_1_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_ROW_1_RCC				RCC_AHBPeriph_GPIOE
	#define GPIO_ROW_1_PIN				GPIO_Pin_8
	#define GPIO_ROW_1_PORT				GPIOE
	
	#define GPIO_ROW_2_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_ROW_2_RCC				RCC_AHBPeriph_GPIOE
	#define GPIO_ROW_2_PIN				GPIO_Pin_10
	#define GPIO_ROW_2_PORT				GPIOE
	
	#define GPIO_ROW_3_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_ROW_3_RCC				RCC_AHBPeriph_GPIOE
	#define GPIO_ROW_3_PIN				GPIO_Pin_12
	#define GPIO_ROW_3_PORT				GPIOE
	
	#define GPIO_ROW_4_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_ROW_4_RCC				RCC_AHBPeriph_GPIOE
	#define GPIO_ROW_4_PIN				GPIO_Pin_14
	#define GPIO_ROW_4_PORT				GPIOE
	
	#define GPIO_CLM_1_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_CLM_1_RCC				RCC_AHBPeriph_GPIOB
	#define GPIO_CLM_1_PIN				GPIO_Pin_10
	#define GPIO_CLM_1_PORT				GPIOB
	
	#define GPIO_CLM_2_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_CLM_2_RCC				RCC_AHBPeriph_GPIOB
	#define GPIO_CLM_2_PIN				GPIO_Pin_12
	#define GPIO_CLM_2_PORT				GPIOB
	
	#define GPIO_CLM_3_RCC_FUNC			RCC_AHBPeriphClockCmd
	#define GPIO_CLM_3_RCC				RCC_AHBPeriph_GPIOB
	#define GPIO_CLM_3_PIN				GPIO_Pin_14
	#define GPIO_CLM_3_PORT				GPIOB
	
	#define GPIO_ROW_1_HIGH		GPIO_SetBits(GPIO_ROW_1_PORT, GPIO_ROW_1_PIN);
	#define GPIO_ROW_1_LOW		GPIO_ResetBits(GPIO_ROW_1_PORT, GPIO_ROW_1_PIN);
	
	#define GPIO_ROW_2_HIGH		GPIO_SetBits(GPIO_ROW_2_PORT, GPIO_ROW_2_PIN);
	#define GPIO_ROW_2_LOW		GPIO_ResetBits(GPIO_ROW_2_PORT, GPIO_ROW_2_PIN);
	
	#define GPIO_ROW_3_HIGH		GPIO_SetBits(GPIO_ROW_3_PORT, GPIO_ROW_3_PIN);
	#define GPIO_ROW_3_LOW		GPIO_ResetBits(GPIO_ROW_3_PORT, GPIO_ROW_3_PIN);
	
	#define GPIO_ROW_4_HIGH		GPIO_SetBits(GPIO_ROW_4_PORT, GPIO_ROW_4_PIN);
	#define GPIO_ROW_4_LOW		GPIO_ResetBits(GPIO_ROW_4_PORT, GPIO_ROW_4_PIN);
	
	
	
	#define GPIO_CLM_1_INPUT	GPIO_ReadInputDataBit(GPIO_CLM_1_PORT, GPIO_CLM_1_PIN)
	#define GPIO_CLM_2_INPUT	GPIO_ReadInputDataBit(GPIO_CLM_2_PORT, GPIO_CLM_2_PIN)
	#define GPIO_CLM_3_INPUT	GPIO_ReadInputDataBit(GPIO_CLM_3_PORT, GPIO_CLM_3_PIN)
	

	#define KEY_SENSE	100		// константа для фиксации 1 секунды

	
	enum STATE_KEY {NO_PRESSED, PRESSED, LONG_PRESSED};
	

	extern uint8_t flag_STATE_KEY[N_ROWS][N_CLMS];	
	extern uint8_t flag_GLOBAL;
	extern uint8_t n_key_pressed;
	
	extern uint8_t x_key[2];		// координата по строке нажатой кнопки
	extern uint8_t y_key[2];		// координата по строке нажатой кнопки

	
	extern uint8_t Key_Count;
	extern uint8_t Key_input[N_ROWS][N_CLMS];		// массив для считывания данных
	extern uint8_t Key_input_filter[N_ROWS][N_CLMS];
	extern uint8_t Key_input_count[N_ROWS][N_CLMS];


	extern char KeyBoard[N_ROWS][N_CLMS];
	
	void Keyboard_ini(void);
	extern uint8_t  read_keyboard(void);
	extern char Key_Pressed[2];

	void Change_Pins(void);
	void Key_Read(void);
	void key_one_filter(uint8_t x, uint8_t y);
	void All_buttons_filter(void);
	
	void single_key_pressed(char key);
	void double_key_pressed(char key1, char key2);
	void single_key_long_pressed(char key);
	void double_key_long_pressed(char key1, char key2);

#endif
