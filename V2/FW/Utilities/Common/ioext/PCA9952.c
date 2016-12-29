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
  PCA9952_write_reg(devAddr,REG_IREFALL,10);
  
  PCA9952_write_reg(devAddr,REG_LEDOUT0,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT1,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT2,0xAA);
  PCA9952_write_reg(devAddr,REG_LEDOUT3,0xAA);
  
  PCA9952_write_reg(devAddr,REG_PWM0,255);
  PCA9952_write_reg(devAddr,REG_PWM1,255);
  PCA9952_write_reg(devAddr,REG_PWM2,255);
  PCA9952_write_reg(devAddr,REG_PWM3,255);
  PCA9952_write_reg(devAddr,REG_PWM4,255);
  PCA9952_write_reg(devAddr,REG_PWM5,255);
  PCA9952_write_reg(devAddr,REG_PWM6,255);
  PCA9952_write_reg(devAddr,REG_PWM7,255);
  PCA9952_write_reg(devAddr,REG_PWM8,255);
  PCA9952_write_reg(devAddr,REG_PWM9,255);
  PCA9952_write_reg(devAddr,REG_PWM10,255);
  PCA9952_write_reg(devAddr,REG_PWM11,255);
  PCA9952_write_reg(devAddr,REG_PWM12,255);
  PCA9952_write_reg(devAddr,REG_PWM13,255);
  PCA9952_write_reg(devAddr,REG_PWM14,255);
  PCA9952_write_reg(devAddr,REG_PWM15,255);

}

uint8_t PCA9952_write_reg(uint8_t DevAddr, uint8_t reg, uint8_t value)
{      
  return I2C_write_reg(I2C_PERIPH[BUS_I2C3],DevAddr,reg| AUTO_INCREMENT_FLAG,value);
}

uint8_t PCA9952_read_reg(uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count)
{    
  return I2C_read_reg(I2C_PERIPH[BUS_I2C3],DevAddr,reg| AUTO_INCREMENT_FLAG,buf, count);
}