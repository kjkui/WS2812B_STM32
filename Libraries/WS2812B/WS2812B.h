/*
 * WS2812.h
 *
 *  Created on: 12 июн. 2021 г.
 *      Author: iserg
 */

#ifndef WS2812B_H_
#define WS2812B_H_

#include "stm32f4xx_hal.h"

#define MAX_LED 60 //Количество светодиодов
#define USE_BRIGHTNESS 0 //Нужно ли управлять яркостью? 0 - Нет, 1 - Да
#define TOP_INDEX MAX_LED / 2
#define PI 3.14159265

TIM_HandleTypeDef htim1;

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4]; // Для яркости

extern volatile int dataSentFlag; // Флаг который обозначает что все данные были переданы. 1 - переданы

uint16_t pwmData[(24*MAX_LED)+50]; // Массив который сформируется и отправится на ленту

void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness); // 0 - 45
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim); // Функция выполняющаяся после отправки данных
void WS2812_Send (void); // Отправка массива на ленту

#endif /* WS2812B_H_ */
