#ifndef __BARGRAPH_H__
#define __BARGRAPH_H__
#include "main.h"

#define BARGRAPH_NLEDS  (21)      //number of LEDS in the bargraph

enum{
  bargraph_FromLeftToRight=1,
  bargraph_FromRightToLeft=0
};

enum{
  bargraph_FilledMode=1,
  bargraph_DotMode=0
};

void bargraph_Init(void);
uint8_t bargraph_Set(uint8_t StartValue,uint8_t StopValue);
uint8_t bargraph_MaskSet(uint32_t mask);
uint8_t bargraph_getPotValue(void);
uint8_t bargraph_DisplayPotValue(void);

#endif /* __BARGRAPH_H__ */
