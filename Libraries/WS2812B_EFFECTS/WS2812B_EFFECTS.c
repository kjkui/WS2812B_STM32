/*
 * WS2812B_EFFECTS.c
 *
 *  Created on: Nov 4, 2021
 *      Author: iserg
 *
 *      Большинство эффектов взяты с https://github.com/AlexGyver/WS2812_FX
 */

#include "WS2812B_EFFECTS.h"


//-----------------------------плавное заполнение цветом-----------------------------------------
void colorWipe(int red, int green, int blue, int SpeedDelay) {
  for (uint16_t i = 0; i < MAX_LED; i++) {
    Set_LED(i, red, green, blue);

#if USE_BRIGHTNESS
    Set_Brightness(5);
#endif

    WS2812_Send();
    HAL_Delay(SpeedDelay);
  }
}

//-----------------------------заполнение цветом-----------------------------------------
void fill(int red, int green, int blue) {
  for (uint16_t i = 0; i < MAX_LED; i++) {
    Set_LED(i, red, green, blue);
  }
#if USE_BRIGHTNESS
    Set_Brightness(3);
#endif
  WS2812_Send();
}

//-----------------------------Плавное изменение яркости-----------------------------------------
void fadeBrightness(int red, int green, int blue, int SpeedDelay, int MaxBright) {
  for (uint16_t i = 0; i < MAX_LED; i++) {
    Set_LED(i, red, green, blue);
  }

  for (uint16_t i = MaxBright; i > 0; i--) {
	  Set_Brightness(i);
	  WS2812_Send();
	  HAL_Delay(SpeedDelay);
  }

  for (uint16_t i = 0; i < MaxBright; i++) {
	  Set_Brightness(i);
	  WS2812_Send();
	  HAL_Delay(SpeedDelay);
  }
}

