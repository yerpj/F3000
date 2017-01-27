#include "bargraph.h"

extern uint32_t CU_bargraph_table[];

uint8_t bargraph_Set(uint8_t StartValue,uint8_t StopValue,uint8_t NegativeMask)
{
  uint8_t i;
  uint32_t filledMask=0;
  if(StartValue<1 || StartValue>21)
    return 1;
  if(StopValue<1 || StopValue>21)
    return 1;
  if(NegativeMask>21)
    return 1;
    
  LEDbuffer_MaskReset(BAR_ALL);    
  
  for(i=(StartValue-1);i<(StopValue);i++)
    filledMask|=CU_bargraph_table[i];
  
  if(NegativeMask>0)
  {
    filledMask^=CU_bargraph_table[NegativeMask-1];
  }
  LEDbuffer_MaskSet(filledMask);

  LEDbuffer_refresh();

  return 0;
}