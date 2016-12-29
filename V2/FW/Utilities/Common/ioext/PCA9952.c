#include "PCA9952.h"


extern I2C_TypeDef *I2C_PERIPH[];


uint8_t PCA9952_Init(I2C_List_Typedef I2Cx,uint8_t devAddr)
{
  uint8_t tmp;
  I2C_Driver_Init(I2Cx);
  
#ifdef USE_BREADBOARD
  //no RST pin accessible
#else /* USE_BREADBOARD */
  //do not forget to assign RST pin!
#endif /* USE_BREADBOARD */
  
  //software reset?
  
  //verify MODE2==0x05 
  if(PCA9952_read_reg(devAddr,REG_MODE2,&tmp,1))
    return 1;
  
  /*if(tmp!=0x05)
    return 1;*/
  
  PCA9952_write_reg(devAddr,REG_MODE2,0x25);
  PCA9952_write_reg(devAddr,REG_IREFALL,20);
  
  PCA9952_write_reg(devAddr,REG_LEDOUT0,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT1,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT2,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT3,0xAA);
  
  //0x2409 is a mask that enables RED leds only
  PCA9952_LED_Control(devAddr,0x2409);
  PCA9952_LED_Control(devAddr,0x2409<<1);
  PCA9952_LED_Control(devAddr,0x2409<<2);
  
}

uint8_t PCA9952_LED_Control(uint8_t DevAddr,uint16_t mask)
{
  uint8_t i;
  uint8_t values[16];
  for(i=0;i<16;i++)
  {
    if(mask&(0x0001<<i))
      values[i]=0xFF;
    else
      values[i]=0x00;
  }
  PCA9952_write_burst(DevAddr,REG_PWM0,values,16);
}

uint8_t PCA9952_write_reg(uint8_t DevAddr, uint8_t reg, uint8_t value)
{      
  return I2C_write_reg(I2C_PERIPH[BUS_I2C3],DevAddr,reg| AUTO_INCREMENT_FLAG,value);
}

uint8_t PCA9952_write_burst(uint8_t DevAddr, uint8_t reg, uint8_t *buf,uint8_t count)
{      
  return I2C_write_burst(I2C_PERIPH[BUS_I2C3],DevAddr,reg| AUTO_INCREMENT_FLAG,buf,count);
}

uint8_t PCA9952_read_reg(uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count)
{    
  return I2C_read_reg(I2C_PERIPH[BUS_I2C3],DevAddr,reg| AUTO_INCREMENT_FLAG,buf, count);
}