#ifndef _ADC_H_
#define _ADC_H_
#include "stm32f2xx.h"
#include "main.h"

#define ADC1_CHANNELS_IN_USE    3
#define ADC1_CHANNELS_MAP       ( BIT18 | BIT9 | BIT16) // TEMP_IN, VREG(potentiometer),IntTempSens

void ADC_LowLevelInit(void);
uint8_t ADC_RegisterCallback(uint8_t channel, void (* cb)(uint16_t));
uint8_t ADC_UnregisterCallback(uint8_t channel);
void DMA2_Stream0_cb(void);


#endif /* _ADC_H_ */