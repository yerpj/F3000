#include "PCA9952.h"


extern I2C_TypeDef *I2C_PERIPH[];

uint8_t I2CInUse=0;


uint8_t PCA9952_Init(I2C_List_Typedef I2Cx,uint8_t devAddr)
{
  I2C_Driver_Init(I2Cx);
    
  I2CInUse=I2Cx;
  //software reset
  
  //verify MODE2==0x05 
  //not implemented if software reset is not performed 
  /*if(PCA9952_read_reg(devAddr,REG_MODE2,&tmp,1))
    return 1;*/
  
  /*if(tmp!=0x05)
    return 1;*/

  PCA9952_write_reg(devAddr,REG_MODE2,0x05);
  PCA9952_write_reg(devAddr,REG_IREFALL,255);//set maximum output current to 19.1 [mA] (0.9/Rext*255/4, with Rext=3k)
  
  /*Every LED off*/
  PCA9952_write_reg(devAddr,REG_LEDOUT0,0x00);
  PCA9952_write_reg(devAddr,REG_LEDOUT1,0x00);
  PCA9952_write_reg(devAddr,REG_LEDOUT2,0x00);
  PCA9952_write_reg(devAddr,REG_LEDOUT3,0x00);

  return 0;
}

uint8_t PCA9952_LED_Intensity_Control(uint8_t DevAddr,uint16_t Mask,uint8_t Percent)
{
  uint8_t i;
  uint8_t Intensity=(uint8_t)((float)Percent*2.55);
  if(Intensity==0)
    Intensity=1;
  if(Intensity>255)
    Intensity=255;
  for(i=0;i<16;i++)
  {
    if(Mask&(0x0001<<i))
    {
      if(PCA9952_write_reg(DevAddr,REG_PWM0+i,Intensity))
      {
        I2C_abort_transaction(I2CInUse);
        return 1;
      }
    }
  }
  return 0;
}

uint8_t PCA9952_LED_Control(uint8_t DevAddr,uint16_t mask)
{
  uint8_t i;
  uint8_t values[4];
  
  values[0]=0;
  values[1]=0;
  values[2]=0;
  values[3]=0;
  
  for(i=0;i<16;i++)
  {
    if(mask&(0x0001<<i))
      values[(i>>2)] |= 0x02<<((i%4)<<1);
    else
      values[(i>>2)] &= ~( 0x03<<(i<<1) );
  }
  
  if(PCA9952_write_burst(DevAddr,REG_LEDOUT0,values,4))
  {
    I2C_abort_transaction(I2CInUse);
    return 1;
  }
  return 0;
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
