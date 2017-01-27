#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define TEMPSENSOR_COLD_TO_MEDIUM_VOLTAGE      (4.5)
#define TEMPSENSOR_MEDIUM_TO_HOT_VOLTAGE       (3.0)
#define TEMPSENSOR_HYSTERESIS_VOLTAGE   (0.5)

enum{
  TempSensor_Cold=1,
  TempSensor_Medium=2,
  TempSensor_Hot=3
};

void tempSensor_Init(void (*callback)(float));

float tempSensor_Get_Temp(void);


#endif /* __TEMPSENSOR_H__ */
