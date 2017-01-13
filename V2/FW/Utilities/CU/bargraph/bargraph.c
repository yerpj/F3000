#include "bargraph.h"

uint32_t bargraph_table[21]={BAR_LED1,BAR_LED2,BAR_LED3,BAR_LED4,BAR_LED5,
                             BAR_LED6,BAR_LED7,BAR_LED8,BAR_LED9,BAR_LED10,
                             BAR_LED11,BAR_LED12,BAR_LED13,BAR_LED14,
                             BAR_LED15,BAR_LED16,BAR_LED17,BAR_LED18,
                             BAR_LED19,BAR_LED20,BAR_LED21};

uint8_t bargraph_Set(uint8_t value,uint8_t filledOrDot)
{
  uint8_t i;
  uint32_t filledMask=0;
  if(value<1 || value>21)
    return 1;
    
  LEDbuffer_MaskReset(BAR_ALL);
  
  if(filledOrDot)
  {
    //filled
    for(i=0;i<(value);i++)
      filledMask|=bargraph_table[i];
    LEDbuffer_MaskSet(filledMask);
  }
  else
  {
    //dot
    LEDbuffer_MaskSet(bargraph_table[value-1]);
  }
  LEDbuffer_refresh();
  return 0;
}