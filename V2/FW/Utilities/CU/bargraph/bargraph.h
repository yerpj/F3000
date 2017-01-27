#ifndef __BARGRAPH_H__
#define __BARGRAPH_H__
#include "main.h"

enum{
  bargraph_FromLeftToRight=1,
  bargraph_FromRightToLeft=0
};

enum{
  bargraph_FilledMode=1,
  bargraph_DotMode=0
};

uint8_t bargraph_Set(uint8_t StartValue,uint8_t StopValue,uint8_t NegativeMask);

#endif /* __BARGRAPH_H__ */
