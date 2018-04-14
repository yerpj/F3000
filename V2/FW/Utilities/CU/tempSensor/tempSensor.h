#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*7 different states:

from cold to hot:

1) nothing
2) blue led
3) blue+green led
4) green led
5) green+red led
6) red led
7) flashing red led

*/
#define TEMPSENSOR_THRESHOLD_1        (1.5)
#define TEMPSENSOR_THRESHOLD_2        (1.009)
#define TEMPSENSOR_THRESHOLD_3        (0.715)
#define TEMPSENSOR_THRESHOLD_4        (0.577)
#define TEMPSENSOR_THRESHOLD_5        (0.332)
#define TEMPSENSOR_THRESHOLD_6        (0.256)

enum{
  TempSensor_Cold=1,
  TempSensor_Medium=2,
  TempSensor_Hot=3
};

void tempSensor_Init(void (*callback)(float));

float tempSensor_Get_Temp(void);
uint8_t tempSensor_Get_State(void);


#endif /* __TEMPSENSOR_H__ */
