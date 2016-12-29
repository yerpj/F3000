#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include "stm32f2xx.h"
#include "commonDefs.h"

void console_Init(void consoleOut(uint8_t *));
void console_log(uint8_t *str);
#endif /* __CONSOLE_H__ */
