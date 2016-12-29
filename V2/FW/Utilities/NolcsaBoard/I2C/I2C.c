#include "I2C.h"

#define Timed(x) Timeout = 0x0FFF; while (x) { if (--Timeout ==0) {bus_error=1;break;}}

//#define DEBUG 1

xSemaphoreHandle I2C_sem;
extern I2C_TypeDef *I2C_PERIPH[];
extern const uint16_t I2C_SCL_PIN[I2Cn];
extern GPIO_TypeDef* I2C_SCL_GPIO_PORT[I2Cn];
uint8_t I2C_Inited_flag[I2Cn]={0};

uint8_t I2C_Driver_Init(I2C_List_Typedef I2Cx)
{
  if(!I2C_Inited_flag[I2Cx])
  {
    vSemaphoreCreateBinary(I2C_sem);
    //I2C_Bus_Init(I2Cx);
    I2C_abort_transaction(I2Cx);
    //I2C_abort_transaction(I2Cx);
    I2C_Bus_Init(I2Cx);
    //I2C_abort_transaction(I2Cx);
    I2C_Inited_flag[I2Cx]=1;
  }
  
  return 0;
}

void I2C_scan(I2C_List_Typedef I2Cx)
{
  uint8_t i;
  uint8_t str[100];
  uint8_t dummy;
  
  //I2C_abort_transaction(I2Cx);
  I2C_Driver_Init(I2Cx);
  for(i=1;i<127;i++)
  {
    if(!I2C_read_reg(I2C_PERIPH[I2Cx],(i<<1), 0x07,&dummy, 1))
    {
#ifdef DEBUG
      sprintf(str,"\nI2C device found at address 0x%02x",(i<<1));
      Serial_SendString(str);
#endif /* DEBUG */
      dummy++;
    } 
  }
    
}

void I2C_abort_transaction(I2C_List_Typedef I2Cx)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  uint32_t i=0,j=0;
  
  
  I2C_DeInit(I2C_PERIPH[I2Cx] );
  I2C_Inited_flag[I2Cx]=0;
  
  /* SCL manually managed */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN[I2Cx];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(I2C_SCL_GPIO_PORT[I2Cx], &GPIO_InitStructure);
  for(i=0;i<18;i++)
  {
    GPIO_SetBits(I2C_SCL_GPIO_PORT[I2Cx],I2C_SCL_PIN[I2Cx]);
    for(j=0;j<6000;j++);
    GPIO_ResetBits(I2C_SCL_GPIO_PORT[I2Cx],I2C_SCL_PIN[I2Cx]);
    for(j=0;j<6000;j++);
  }
  /* I2C SCL pins configuration */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN[I2Cx];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(I2C_SCL_GPIO_PORT[I2Cx], &GPIO_InitStructure);
}

uint8_t I2C_read_reg(I2C_TypeDef* I2Cx, uint8_t DevAddr, uint8_t reg, uint8_t *buf, uint8_t count)
{   
  uint8_t nbr,i;
  uint32_t Timeout;
  uint8_t bus_error=0;
  nbr=count-1;
  
  xSemaphoreTake(I2C_sem, portMAX_DELAY);
  
  I2C_AcknowledgeConfig(I2Cx, DISABLE); 
  
  Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

  I2C_GenerateSTART(I2Cx, ENABLE);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
          
  I2C_Send7bitAddress(I2Cx,DevAddr, I2C_Direction_Transmitter);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  I2C_SendData(I2Cx, reg);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  I2C_GenerateSTART(I2Cx, ENABLE);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
          
  I2C_Send7bitAddress(I2Cx,DevAddr, I2C_Direction_Receiver);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  I2C_AcknowledgeConfig(I2Cx, ENABLE);  
  
  i=0;
  while(nbr)
  {
    Timed( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
    buf[i] = I2C_ReceiveData(I2Cx); 
    i++;
    nbr--;
  }
  
  I2C_AcknowledgeConfig(I2Cx, DISABLE);  
  I2C_GenerateSTOP(I2Cx, ENABLE);

  Timed( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );

  buf[i] = I2C_ReceiveData(I2Cx); 
  
  xSemaphoreGive(I2C_sem);
  
  if(bus_error)
    return 1;
  return 0;
}

uint8_t I2C_write_reg(I2C_TypeDef* I2Cx, uint8_t DevAddr, uint8_t reg, uint8_t value)
{      
  uint32_t Timeout;
  uint8_t bus_error=0;
  
  xSemaphoreTake(I2C_sem, portMAX_DELAY);
  
  Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  
  I2C_GenerateSTART(I2Cx, ENABLE);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
          
  I2C_Send7bitAddress(I2Cx,DevAddr, I2C_Direction_Transmitter);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  I2C_SendData(I2Cx, reg);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  I2C_SendData(I2Cx, value);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  I2C_GenerateSTOP(I2Cx, ENABLE);  
  
  xSemaphoreGive(I2C_sem);
  
  if(bus_error)
    return 1;
  return 0;
}


