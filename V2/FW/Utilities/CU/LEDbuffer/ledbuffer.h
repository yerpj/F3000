#ifndef __LEDBUFFER_H__
#define __LEDBUFFER_H__
#include "main.h"

uint8_t LEDbuffer_Init(void);
uint8_t LEDbuffer_refresh(void);
uint8_t LEDbuffer_MaskSet(uint64_t mask);
uint8_t LEDbuffer_MaskReset(uint64_t mask);
uint8_t LEDbuffer_SetBit(uint16_t bit);
uint8_t LEDbuffer_ResetBit(uint16_t bit);

#endif /* __LEDBUFFER_H__ */

