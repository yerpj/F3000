#ifndef _DS3231MZ_
#define _DS3231MZ_
#include "nolcsa.h"
#include "I2C.h"

#define DS3231MZ_ADDR                   (0xD0)  //or 0x68 or 0xD0

#define DS3231MZ_SECONDS_REG            (0x00)
#define DS3231MZ_MINUTES_REG            (0x01)
#define DS3231MZ_HOUR_REG               (0x02)
#define DS3231MZ_DAY_REG                (0x03)
#define DS3231MZ_DATE_REG               (0x04)
#define DS3231MZ_MONTH_REG              (0x05)
#define DS3231MZ_YEAR_REG               (0x06)

#define DS3231MZ_CONTROL_REG            (0x0E)
#define DS3231MZ_STATUS_REG             (0x0F)
#define DS3231MZ_AGING_OFFSET_REG       (0x10)
#define DS3231MZ_TEMP_MSB_REG           (0x11)
#define DS3231MZ_TEMP_LSB_REG           (0x12)

uint8_t DS3231MZ_Init(uint8_t DevAddr);
uint8_t DS3231MZ_read_reg(uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count);
uint8_t DS3231MZ_write_reg(uint8_t DevAddr, uint8_t reg, uint8_t value);


#endif /* DS3231MZ */
