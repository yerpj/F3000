#ifndef _I2C_H_
#define _I2C_H_

#include "nolcsa.h"
#include "stm32f2xx_i2c.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

uint8_t I2C_read_reg(I2C_TypeDef* I2Cx, uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count);
uint8_t I2C_write_reg(I2C_TypeDef* I2Cx, uint8_t DevAddr, uint8_t reg, uint8_t value);
uint8_t I2C_Driver_Init(I2C_List_Typedef I2Cx);
void I2C_scan(I2C_List_Typedef I2Cx);
void I2C_abort_transaction(I2C_List_Typedef I2Cx);


#endif /* _I2C_H_ */
