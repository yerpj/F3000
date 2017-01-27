#ifndef __INDICATOR_H__
#define __INDICATOR_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"


uint8_t Indicator_LED_OIL_Set(void);
uint8_t Indicator_LED_OIL_Reset(void);
uint8_t Indicator_LED_N_Set(void);
uint8_t Indicator_LED_N_Reset(void);
uint8_t Indicator_LED_Mode_Set(uint8_t Mode);
uint8_t Indicator_LED_Temp_Set(uint8_t Temp);


#endif /* __INDICATOR_H__ */
