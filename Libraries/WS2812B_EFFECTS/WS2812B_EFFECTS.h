/*
 * WS2812B_EFFECTS.h
 *
 *  Created on: Nov 4, 2021
 *      Author: iserg
 *
 *      Большинство эффектов взяты с https://github.com/AlexGyver/WS2812_FX
 */

#ifndef WS2812B_EFFECTS_H_
#define WS2812B_EFFECTS_H_

#include "../../Libraries/WS2812B/WS2812B.h"

//-----------------------------плавное заполнение цветом-----------------------------------------
void colorWipe(int red, int green, int blue, int SpeedDelay);

//-----------------------------заполнение цветом-----------------------------------------
void fill(int red, int green, int blue);


//-----------------------------Плавное изменение яркости-----------------------------------------
void fadeBrightness(int red, int green, int blue, int SpeedDelay, int MaxBright);





#endif /* WS2812B_EFFECTS_H_ */
