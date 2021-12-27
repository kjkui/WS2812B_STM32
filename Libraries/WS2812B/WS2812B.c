/*
 * WS2812B.c
 *
 *  Created on: 12 июн. 2021 г.
 *      Author: iserg
 */

#include "WS2812B.h"
#include <math.h>

volatile int dataSentFlag=0; // Флаг который обозначает что все данные были переданы. 1 - переданы

void Set_LED (int LEDnum, int Red, int Green, int Blue) {
	LED_Data[LEDnum][0] = LEDnum; // LEDnum - номер светодиода который нужно засветить
	LED_Data[LEDnum][1] = Green; // Кол-во зелёного цвета
	LED_Data[LEDnum][2] = Red; // Кол-во красного цвета
	LED_Data[LEDnum][3] = Blue; // Кол-во синего цвета
}

void Set_Brightness (int brightness) { // 0 - 45
#if USE_BRIGHTNESS
	if (brightness > 45) brightness = 45;
	for (int i=0; i < MAX_LED; i++) {
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j = 1; j < 4; j++){
			float angle = 90-brightness; // Угол в градусах
			angle = angle*PI / 180; // Угол в радианах
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}

	}
#endif
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) { // Функция выполняющаяся после отправки данных
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	dataSentFlag=1; // Подняли флаг
}

void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 от 90
			}

			else pwmData[indx] = 30;  // 1/3 от 90

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	while (!dataSentFlag){};
	dataSentFlag = 0;
}
