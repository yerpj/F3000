#include "bargraph.h"
#include "ADC.h"

extern uint32_t CU_bargraph_table[];

void Vreg_Monitor_callback(uint16_t value);

#define Vreg_ADC_ACCU_SIZE 3
uint16_t Vreg_ADCAccu[Vreg_ADC_ACCU_SIZE];
uint8_t Vreg_ADCAccuPtr=0;
float Vreg_currentValue=0;
uint8_t NegativeMask=0;
uint8_t NegativeMaskEnabled=0;

uint8_t bargraph_NegMaskState(uint8_t state)
{
  NegativeMaskEnabled=state?1:0;
}

uint8_t bargraph_DisplayPotValue(void)
{
  uint32_t filledMask=0;
    
  LEDbuffer_MaskReset(BAR_ALL);    
  if(NegativeMask>0)
  {
    filledMask=CU_bargraph_table[NegativeMask-1];
  }
  LEDbuffer_MaskSet(filledMask);
  LEDbuffer_refresh(0);
  return 0;
}

uint8_t bargraph_Set(uint8_t StartValue,uint8_t StopValue)
{
  uint8_t i;
  uint64_t filledMask=0;
  if(StartValue<1 || StartValue>BARGRAPH_NLEDS)
    return 1;
  if(StopValue<1)
    StopValue=1;
  else if(StopValue>BARGRAPH_NLEDS)
    return 1;
  if(NegativeMask>BARGRAPH_NLEDS)
    return 1;
    
  LEDbuffer_MaskReset(BAR_ALL);    
  
  for(i=(StartValue-1);i<(StopValue);i++)
    filledMask|=CU_bargraph_table[i];
  
  if(NegativeMaskEnabled)
  {
    filledMask^=CU_bargraph_table[NegativeMask-1];
  }
  LEDbuffer_MaskSet(filledMask);

  LEDbuffer_refresh(0);

  return 0;
}

uint8_t bargraph_MaskSet(uint32_t mask)
{
  uint8_t i=0;
  uint32_t filledMask=0;
  
  /* clear bargraph */
  LEDbuffer_MaskReset(BAR_ALL);   
  
  /* set leds of interest */
  for(i=0;i<BARGRAPH_NLEDS;i++)
    if(mask&(1<<i))
      filledMask|=CU_bargraph_table[i];
  LEDbuffer_MaskSet(filledMask);
  
  /* refresh bargraph */
  LEDbuffer_refresh(0);
  return 0;
}

void bargraph_Init(void)
{
  
  ADC_LowLevelInit();
  ADC_RegisterCallback(VREG_ADC_CHANNEL,Vreg_Monitor_callback);
}

void Vreg_Monitor_callback(uint16_t value)
{
  uint8_t Mask=0;
#define INVERT_VREG_VALUE
  uint16_t Vreg_Accu=0;
  float Vreg_value;
  uint8_t i;
  Vreg_ADCAccu[Vreg_ADCAccuPtr++]=value;
  if(Vreg_ADCAccuPtr>=Vreg_ADC_ACCU_SIZE)
  {
      Vreg_ADCAccuPtr=0;
      for(i=0;i<Vreg_ADC_ACCU_SIZE;i++)
        Vreg_Accu+=Vreg_ADCAccu[i];
      Vreg_value=0.0054*(((float)Vreg_Accu)/((float)Vreg_ADC_ACCU_SIZE));
      if(Vreg_value>BARGRAPH_NLEDS)
        Mask=BARGRAPH_NLEDS;
      else if(Vreg_value<1)
        Mask=1;
      else
        Mask=(uint8_t)Vreg_value;
#ifdef INVERT_VREG_VALUE
    Mask=(BARGRAPH_NLEDS+1)-Mask;
#endif /* INVERT_VREG_VALUE */
      //Vreg_currentValue=(float)( ( (Vreg_value-Vreg_V_TEMP_25)/Vreg_AVG_SLOPE) +25 );
    if(NegativeMaskEnabled)
      NegativeMask=Mask;
    else
      NegativeMask=0;
  }
}

uint8_t bargraph_getPotValue(void)
{
  return NegativeMask;//goes from 1 to BARGRAPH_NLEDS
}
