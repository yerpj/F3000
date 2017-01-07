#include "ledbuffer.h"
#include "PCA9952.h"

uint16_t LEDbuffer[3];
uint16_t LEDbuffer_last[3];

uint8_t LEDbuffer_Init(void)
{
  LEDbuffer[0]=0;
  LEDbuffer[1]=0;
  LEDbuffer[2]=0;
  return 0;
}

uint8_t LEDbuffer_refresh(void)
{
  if( (LEDbuffer_last[0]!=LEDbuffer[0]) || (LEDbuffer_last[1]!=LEDbuffer[1]) || (LEDbuffer_last[2]!=LEDbuffer[2]) )
  {
    PCA9952_LED_Control(PCA9952_MAIN_ADDR,LEDbuffer[0]);
  #ifndef USE_BREADBOARD
    PCA9952_LED_Control(PCA9952_BAR1_ADDR,LEDbuffer[1]);
    PCA9952_LED_Control(PCA9952_BAR2_ADDR,LEDbuffer[2]);
  #endif /* USE_BREADBOARD */
    LEDbuffer_last[0]=LEDbuffer[0];
    LEDbuffer_last[1]=LEDbuffer[1];
    LEDbuffer_last[2]=LEDbuffer[2];
  }
  return 0;
}

uint8_t LEDbuffer_MaskSet(uint64_t mask)
{
  LEDbuffer[0]|=(mask>>0)&0xFFFF;
  LEDbuffer[1]|=(mask>>16)&0xFFFF;
  LEDbuffer[2]|=(mask>>24)&0xFFFF;
}

uint8_t LEDbuffer_MaskReset(uint64_t mask)
{
  LEDbuffer[0]&=~((mask>>0)&0xFFFF);
  LEDbuffer[1]&=~((mask>>16)&0xFFFF);
  LEDbuffer[2]&=~((mask>>24)&0xFFFF);
}

uint8_t LEDbuffer_SetBit(uint16_t bit)
{
  if(bit<16)
  {
    LEDbuffer[0]|=0x01<<bit;
    return 0;
  }
  else if(bit<32)
  {
    LEDbuffer[1]|=0x01<<(bit-16);
    return 0;
  }
  else if(bit<48)
  {
    LEDbuffer[2]|=0x01<<(bit-32);
    return 0;
  }
  else 
    return 1;
}

uint8_t LEDbuffer_ResetBit(uint16_t bit)
{
  if(bit<16)
  {
    LEDbuffer[0]&=~(0x01<<bit);
    return 0;
  }
  else if(bit<32)
  {
    LEDbuffer[1]&=(0x01<<(bit-16));
    return 0;
  }
  else if(bit<48)
  {
    LEDbuffer[2]&=(0x01<<(bit-32));
    return 0;
  }
  else 
    return 1;
}