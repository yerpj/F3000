#ifndef _SERIAL_H_
#define _SERIAL_H
#include "main.h"


void Serial_SendLine(uint8_t *str, uint32_t length);
void Serial_SendRow(uint8_t *str, uint32_t length);
void Serial_SendString(uint8_t *str);
uint8_t Serial_Init(void);
void Serial_SendChar(uint8_t character);
void Serial_Callback(uint8_t character);

#endif /* _SERIAL_H_ */