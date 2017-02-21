#ifndef __PARAMCOLLECTION_H__
#define __PARAMCOLLECTION_H__
#include "stm32f2xx.h"

#define PC_PARAM_NAME_LENGTH    20
#define PC_NUMPARAM             10
#define PC_PARAM_LENGTH         4  //bytes

uint8_t PC_Init(void);
uint8_t PC_GetParam(uint8_t *data,uint8_t *name);
uint8_t PC_SetParam(uint8_t *data,uint8_t *name);
uint8_t PC_AddParam(uint8_t *name);

#endif /* __PARAMCOLLECTION_H__ */
