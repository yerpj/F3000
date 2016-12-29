#include "DS3231MZ.h"


extern I2C_TypeDef *I2C_PERIPH[];

//#define DS3231MZ_WITH_INT_PIN

uint8_t DS3231MZ_Init(uint8_t DevAddr)
{
  /* 
 
  WARNING: The RTC reset pin is BIDIRECTIONAL! 
  Do not configure it in push-pull, but in OPEN-DRAIN, NOPULL!!!!!
  
 
  */
  uint8_t Status;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  I2C_Driver_Init(DS3231MZ_I2C_BUS);
  
  RCC_AHB1PeriphClockCmd(DS3231MZ_INT_GPIO_CLK | DS3231MZ_RST_GPIO_CLK, ENABLE);
  
  /* Set EXTI1 pin as Input PullUp - DS3231MZ_INT */
  GPIO_InitStructure.GPIO_Pin = DS3231MZ_INT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(DS3231MZ_INT_GPIO_PORT, &GPIO_InitStructure);
#ifdef DS3231MZ_WITH_INT_PIN
  /* Connect EXTI Line to  GPIO Pin */
  SYSCFG_EXTILineConfig(DS3231MZ_INT_EXTI_PORT_SOURCE, DS3231MZ_INT_EXTI_PIN_SOURCE); 
  
  /* Configure DS3231MZ_INT EXTI1 line */
  EXTI_InitStructure.EXTI_Line = DS3231MZ_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_ClearITPendingBit(DS3231MZ_INT_EXTI_LINE);
  
  /* Enable and set EXTI1 Interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = DS3231MZ_INT_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
#endif /* DS3231MZ_WITH_INT_PIN */  
  do
  {
    if(DS3231MZ_read_reg(DevAddr, DS3231MZ_STATUS_REG,&Status,1))
      return 1;
  }while(Status==0);
  
  return 0;
}

uint8_t DS3231MZ_read_reg(uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count)
{    
  return I2C_read_reg(I2C_PERIPH[BUS_I2C1],DevAddr,reg ,buf, count);
}

uint8_t DS3231MZ_write_reg(uint8_t DevAddr, uint8_t reg, uint8_t value)
{      
  return I2C_write_reg(I2C_PERIPH[BUS_I2C1],DevAddr,reg,value);
}

