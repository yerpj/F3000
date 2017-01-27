#ifndef __PCA9952_H__
#define __PCA9952_H__

#include "commontypes.h"
#include "main.h"
#include "I2C.h"


#define        REG_MODE1      0x00
#define        REG_MODE2      0x01
#define        REG_LEDOUT0    0x02
#define        REG_LEDOUT1    0x03
#define        REG_LEDOUT2    0x04
#define        REG_LEDOUT3    0x05
#define        REG_GRPPWM     0x08
#define        REG_GRPFREQ    0x09
#define        REG_PWM0       0x0A
#define        REG_PWM1       0x0B
#define        REG_PWM2       0x0C
#define        REG_PWM3       0x0D
#define        REG_PWM4       0x0E
#define        REG_PWM5       0x0F
#define        REG_PWM6       0x10
#define        REG_PWM7       0x11
#define        REG_PWM8       0x12
#define        REG_PWM9       0x13
#define        REG_PWM10      0x14
#define        REG_PWM11      0x15
#define        REG_PWM12      0x16
#define        REG_PWM13      0x17
#define        REG_PWM14      0x18
#define        REG_PWM15      0x19
#define        REG_IREF0      0x22
#define        REG_IREF1      0x23
#define        REG_IREF2      0x24
#define        REG_IREF3      0x25
#define        REG_IREF4      0x26
#define        REG_IREF5      0x27
#define        REG_IREF6      0x28
#define        REG_IREF7      0x29
#define        REG_IREF8      0x2A
#define        REG_IREF9      0x2B
#define        REG_IREF10     0x2C
#define        REG_IREF11     0x2D
#define        REG_IREF12     0x2E
#define        REG_IREF13     0x2F
#define        REG_IREF14     0x30
#define        REG_IREF15     0x31
#define        REG_OFFSET     0x3A
#define        REG_SUBADR1    0x3B
#define        REG_SUBADR2    0x3C
#define        REG_SUBADR3    0x3D
#define        REG_ALLCALLADR 0x3E
#define        REG_RESERVED1  0x3F
#define        REG_RESERVED2  0x40
#define        REG_RESERVED3  0x41
#define        REG_PWMALL     0x42
#define        REG_IREFALL    0x43
#define        REG_EFLAG0     0x44
#define        REG_EFLAG1     0x45

#define        AUTO_INCREMENT_FLAG 0x80

uint8_t PCA9952_Init(I2C_List_Typedef I2Cx,uint8_t devAddr);
uint8_t PCA9952_read_reg(uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count);
uint8_t PCA9952_write_reg(uint8_t DevAddr, uint8_t reg, uint8_t value);
uint8_t PCA9952_write_burst(uint8_t DevAddr, uint8_t reg, uint8_t *buf,uint8_t count);
uint8_t PCA9952_LED_Control(uint8_t DevAddr,uint16_t mask);
uint8_t PCA9952_LED_Intensity_Control(uint8_t DevAddr,uint16_t Mask,uint8_t Intensity);

#endif /* __PCA9952_H__ */