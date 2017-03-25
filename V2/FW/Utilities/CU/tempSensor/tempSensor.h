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
#define TEMPSENSOR_THRESHOLD_1_V        (0.67)
#define TEMPSENSOR_THRESHOLD_2_V        (0.64)
#define TEMPSENSOR_THRESHOLD_3_V        (0.60)
#define TEMPSENSOR_THRESHOLD_4_V        (0.58)
#define TEMPSENSOR_THRESHOLD_5_V        (0.54)
#define TEMPSENSOR_THRESHOLD_6_V        (0.52)

enum{
  TempSensor_Cold=1,
  TempSensor_Medium=2,
  TempSensor_Hot=3
};

void tempSensor_Init(void (*callback)(float));

float tempSensor_Get_Temp(void);
uint8_t tempSensor_Get_State(void);


#endif /* __TEMPSENSOR_H__ */
