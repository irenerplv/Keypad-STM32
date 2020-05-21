#include "keyboard.h"



uint8_t Key_Count = 0;
uint8_t Key_input[N_ROWS][N_CLMS]			= {0};		// массив для считывания состояния СТОЛБЦОВ
uint8_t Key_input_filter[N_ROWS][N_CLMS]	= {0};		// массив для фиксирования физического состояния кнопок
uint8_t Key_input_count[N_ROWS][N_CLMS] 	= {0};		// счетчик событий

uint8_t x_key[2]							= {0};		// координата по строке нажатой кнопки
uint8_t y_key[2]							= {0};		// координата по строке нажатой кнопки

//uint8_t flag_STATE_KEY = NO_PRESSED;
uint8_t flag_STATE_KEY[N_ROWS][N_CLMS]		= {0};		// массив флагов состояний кнопок
uint8_t flag_GLOBAL = NO_PRESSED;						// глобальный флаг, говорящий о том, что пришло какое-то событие
uint8_t n_key_pressed = 0;								// количество нажатых кнопок (максимально допустимое значение - 2)

char KeyBoard[N_ROWS][N_CLMS]				= {'1', '2', '3',
											   '4', '5', '6',
								               '7', '8', '9',
											   '*', '0', '#'};

char Key_Pressed[2] 						= {'\0', '\0'};	// массив для фиксирования значений нажатых кнопок 

// ициализация клавиатуры
void Keyboard_ini(void)
{
	GPIO_InitTypeDef 	GPIO_Init_KEY;
	
	//////////////////////////////////////////////
	// ПРИМЕРНАЯ ИНИЦИАЛИЗАЦИЯ СТРОК
	//////////////////////////////////////////////
	
	// настройка выводов на ВЫХОД С ОТКРЫТЫМ СТОКОМ (защита от КЗ) 
	GPIO_ROW_1_RCC_FUNC(GPIO_ROW_1_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_ROW_1_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_OD;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIO_ROW_1_PORT, &GPIO_Init_KEY);
	
	GPIO_ROW_2_RCC_FUNC(GPIO_ROW_2_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_ROW_2_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_OD;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIO_ROW_2_PORT, &GPIO_Init_KEY);
	
	GPIO_ROW_3_RCC_FUNC(GPIO_ROW_3_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_ROW_3_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_OD;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_NOPULL;		
	
	GPIO_Init(GPIO_ROW_3_PORT, &GPIO_Init_KEY);
	
	GPIO_ROW_4_RCC_FUNC(GPIO_ROW_4_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_ROW_4_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_OD;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIO_ROW_4_PORT, &GPIO_Init_KEY);
	
	//////////////////////////////////////////////
	// ПРИМЕРНАЯ ИНИЦИАЛИЗАЦИЯ СТОЛБЦОВ
	//////////////////////////////////////////////
	
	// настройка выводов на ВХОД - подтяжка к "1" 
	GPIO_CLM_1_RCC_FUNC(GPIO_CLM_1_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_CLM_1_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_IN;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_PP;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_UP;		// подтяжка к питанию
	
	GPIO_Init(GPIO_CLM_1_PORT, &GPIO_Init_KEY);
	
	GPIO_CLM_2_RCC_FUNC(GPIO_CLM_2_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_CLM_2_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_IN;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_PP;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_UP;		
	
	GPIO_Init(GPIO_CLM_2_PORT, &GPIO_Init_KEY);
	
	GPIO_CLM_3_RCC_FUNC(GPIO_CLM_3_RCC, ENABLE);
	
	GPIO_Init_KEY.GPIO_Pin 		= GPIO_CLM_3_PIN;
	GPIO_Init_KEY.GPIO_Mode		= GPIO_Mode_IN;
	GPIO_Init_KEY.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init_KEY.GPIO_OType	= GPIO_OType_PP;
	GPIO_Init_KEY.GPIO_PuPd		= GPIO_PuPd_UP;		
	
	GPIO_Init(GPIO_CLM_3_PORT, &GPIO_Init_KEY);	
}

//-------------------------------------------
// Функция, выставляющая "1" на нужной строке
//-------------------------------------------
void Change_Pins(void)					
{
	Key_Count = (Key_Count + 1) % 4;
	
	if (Key_Count == 0)
	{
		GPIO_ROW_2_HIGH
		GPIO_ROW_3_HIGH
		GPIO_ROW_4_HIGH
		GPIO_ROW_1_LOW
	}
	else if (Key_Count == 1)
	{
		GPIO_ROW_1_HIGH
		GPIO_ROW_3_HIGH
		GPIO_ROW_4_HIGH
		GPIO_ROW_2_LOW
	}
	else if (Key_Count == 2)
	{
		GPIO_ROW_2_HIGH
		GPIO_ROW_1_HIGH
		GPIO_ROW_4_HIGH
		GPIO_ROW_3_LOW
	}
	else if (Key_Count == 3)
	{
		GPIO_ROW_2_HIGH
		GPIO_ROW_1_HIGH
		GPIO_ROW_3_HIGH
		GPIO_ROW_4_LOW
	}
	
}
//----------------------------- 
// Чтение столбцов
//-----------------------------
void Key_Read(void)								
{
	Key_input[Key_Count][0] = GPIO_CLM_1_INPUT;
	Key_input[Key_Count][1] = GPIO_CLM_2_INPUT;
	Key_input[Key_Count][2] = GPIO_CLM_3_INPUT;
}
 
// фльтр для одной кнопки
void key_one_filter(uint8_t x, uint8_t y)
{
	if(Key_input[x][y] == 0)							// если кнопка нажата
	{
		if(Key_input_count[x][y] < KEY_SENSE)			// нажатие кнопки меньше секунды
		{
			Key_input_count[x][y]++;
			flag_STATE_KEY[x][y]	= NO_PRESSED;		// статус кнопки - "не нажата"
			Key_input_filter[x][y]	= PRESSED;			// физически нажата
		}
		else											// нажатие кнопки дольше секунды
		{
			if(Key_input_filter[x][y] != LONG_PRESSED)	// фиксируем событие удержание кнопки (1 раз)
				flag_STATE_KEY[x][y] = LONG_PRESSED;
			else
				flag_STATE_KEY[x][y] = NO_PRESSED;
			
			Key_input_filter[x][y] 	= LONG_PRESSED;
		}
	}
	else												// если кнопка отпущена
	{
		if(Key_input_count[x][y] > 0)					// кнопка была нажата
		{
			if(Key_input_count[x][y] < KEY_SENSE)		// была нажата меньше 1 секунды
			{
				Key_input_filter[x][y] 	= NO_PRESSED;	// физически уже не нажата
				flag_STATE_KEY[x][y] 	= PRESSED;		// статус "кнопка нажата"
			}
			else										// была нажата дольше 1 секунды
			{
				Key_input_filter[x][y] = NO_PRESSED;	// физически уже не нажата	
				flag_STATE_KEY[x][y]   = NO_PRESSED;	// статус "кнопка не нажата"
			}
		}
		else											// кнопка не нажималась
		{
			Key_input_filter[x][y] 	= NO_PRESSED;		// физически не нажата
			flag_STATE_KEY[x][y]   	= NO_PRESSED;		// статус "кнопка не нажата"
		}
		Key_input_count[x][y] = 0;
	}
}
//-----------------------------
// фильтрация всех кнопок
//-----------------------------
void All_buttons_filter(void)
{
	uint8_t i, j;
	for(i = 0; i < N_ROWS; i ++)
	{
		for(j = 0; j < N_CLMS; j++)
		{
			key_one_filter(i, j);
			
			if(flag_GLOBAL < flag_STATE_KEY[i][j])
				flag_GLOBAL = flag_STATE_KEY[i][j];
			
			if(flag_STATE_KEY[i][j] != NO_PRESSED && n_key_pressed < 2)
			{
				//if(Key_Pressed[0] != KeyBoard[i][j])
				Key_Pressed[n_key_pressed] 	= KeyBoard[i][j];
				x_key[n_key_pressed]		= i;
				y_key[n_key_pressed++]		= j;
			}
		}
	}
}

//-----------------------------
// ТЕСТОВЫЕ ФУНКЦИИ
//-----------------------------
void single_key_pressed(char key)
{
	/*...*/
}
void double_key_pressed(char key1, char key2)
{
	/*...*/

}
void single_key_long_pressed(char key)
{
	/*...*/
	
}
void double_key_long_pressed(char key1, char key2)
{
	/*...*/
	
}


