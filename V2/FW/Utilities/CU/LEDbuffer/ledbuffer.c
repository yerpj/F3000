#include "ledbuffer.h"
#include "PCA9952.h"

uint16_t LEDbuffer[3];
uint16_t LEDbuffer_last[3];

SemaphoreHandle_t LEDbufferMutex;

uint8_t LEDbuffer_Init(void)
{
  
  LEDbuffer[0]=0;
  LEDbuffer[1]=0;
  LEDbuffer[2]=0;
  
  LEDbufferMutex = xSemaphoreCreateMutex();
  if( LEDbufferMutex != NULL )
  {
    return 0;
  }
  return 1;
}

uint8_t LEDbuffer_refresh(void)
{
  if( xSemaphoreTake( LEDbufferMutex, ( TickType_t ) 100 ) != pdTRUE )
  {
    return 1;
  }
  if( (LEDbuffer_last[0]!=LEDbuffer[0]) || (LEDbuffer_last[1]!=LEDbuffer[1]) || (LEDbuffer_last[2]!=LEDbuffer[2]) )
  {
  #ifdef USE_BREADBOARD
    PCA9952_LED_Control(PCA9952_MAIN_ADDR,LEDbuffer[0]);
  #else /* USE_BREADBOARD */
    PCA9952_LED_Control(PCA9952_BAR1_ADDR,LEDbuffer[0]);
    PCA9952_LED_Control(PCA9952_BAR2_ADDR,LEDbuffer[1]);
    PCA9952_LED_Control(PCA9952_MAIN_ADDR,LEDbuffer[2]);
  #endif /* USE_BREADBOARD */
    LEDbuffer_last[0]=LEDbuffer[0];
    LEDbuffer_last[1]=LEDbuffer[1];
    LEDbuffer_last[2]=LEDbuffer[2];
  }
  xSemaphoreGive( LEDbufferMutex );
  return 0;
}

uint8_t LEDbuffer_MaskSet(uint64_t mask)
{
  if( xSemaphoreTake( LEDbufferMutex, ( TickType_t ) 100 ) != pdTRUE )
  {
    return 1;
  }
  LEDbuffer[0]|=(mask>>0)&0xFFFF;
  LEDbuffer[1]|=(mask>>16)&0xFFFF;
  LEDbuffer[2]|=(mask>>32)&0xFFFF;
  xSemaphoreGive( LEDbufferMutex );
  return 0;
}

uint8_t LEDbuffer_MaskReset(uint64_t mask)
{
  if( xSemaphoreTake( LEDbufferMutex, ( TickType_t ) 100 ) != pdTRUE )
  {
    return 1;
  }
  LEDbuffer[0]&=~((mask>>0)&0xFFFF);
  LEDbuffer[1]&=~((mask>>16)&0xFFFF);
  LEDbuffer[2]&=~((mask>>32)&0xFFFF);
  xSemaphoreGive( LEDbufferMutex );
  return 0;
}

uint8_t LEDbuffer_SetBit(uint16_t bit)
{
  uint8_t err;
  if( xSemaphoreTake( LEDbufferMutex, ( TickType_t ) 100 ) != pdTRUE )
  {
    return 1;
  }
  if(bit<16)
  {
    LEDbuffer[0]|=0x01<<bit;
    err=0;
  }
  else if(bit<32)
  {
    LEDbuffer[1]|=0x01<<(bit-16);
    err=0;
  }
  else if(bit<48)
  {
    LEDbuffer[2]|=0x01<<(bit-32);
    err=0;
  }
  else 
    err=1;
  xSemaphoreGive( LEDbufferMutex );
  if(err)
    return 1;
  else
    return 0;
}

uint8_t LEDbuffer_ResetBit(uint16_t bit)
{
  uint8_t err;
  if( xSemaphoreTake( LEDbufferMutex, ( TickType_t ) 100 ) != pdTRUE )
  {
    return 1;
  }
  if(bit<16)
  {
    LEDbuffer[0]&=~(0x01<<bit);
    err=0;
  }
  else if(bit<32)
  {
    LEDbuffer[1]&=(0x01<<(bit-16));
    err=0;
  }
  else if(bit<48)
  {
    LEDbuffer[2]&=(0x01<<(bit-32));
    err=0;
  }
  else 
    err=1;
  xSemaphoreGive( LEDbufferMutex );
  if(err)
    return 1;
  else
    return 0;
}