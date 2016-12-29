#ifndef _INTERNAL_TEMP_SENSOR_H_
#define _INTERNAL_TEMP_SENSOR_H_

#include "stm32f2xx.h"
#include "main.h"

#define ITS_V_TEMP_25   (940.0) 
#define ITS_AVG_SLOPE   (2.5)  // [V/°c]  (see datasheet @p. 127)
#define ITS_REFINT      (1.21)  // [V]  (see datasheet @p. 128)

void ITS_Init(void (*callback)(float),float threshold);
float ITS_Get_Temp(void);
void ITS_Monitor_callback(uint16_t value);

#endif /*_INTERNAL_TEMP_SENSOR_H_ */

