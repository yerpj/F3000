#include "bargraph.h"
#include "ADC.h"

extern uint32_t CU_bargraph_table[];

void Vreg_Monitor_callback(uint16_t value);

#define Vreg_ADC_ACCU_SIZE 3
uint16_t Vreg_ADCAccu[Vreg_ADC_ACCU_SIZE];
uint8_t Vreg_ADCAccuPtr=0;
float Vreg_currentValue=0;
uint8_t NegativeMask=0;

uint8_t bargraph_Set(uint8_t StartValue,uint8_t StopValue)
{
  uint8_t i;
  uint32_t filledMask=0;
  if(StartValue<1 || StartValue>BARGRAPH_NLEDS)
    return 1;
  if(StopValue<1 || StopValue>BARGRAPH_NLEDS)
    return 1;
  if(NegativeMask>BARGRAPH_NLEDS)
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
  LEDbuffer_refresh();
  return 0;
}

void bargraph_Init(void)
{
  
  ADC_LowLevelInit();
  ADC_RegisterCallback(VREG_ADC_CHANNEL,Vreg_Monitor_callback);
}

void Vreg_Monitor_callback(uint16_t value)
{
  uint16_t Vreg_Accu=0;
  float Vreg_value;
  uint8_t i;
  Vreg_ADCAccu[Vreg_ADCAccuPtr++]=value;
  if(Vreg_ADCAccuPtr>=Vreg_ADC_ACCU_SIZE)
  {
      Vreg_ADCAccuPtr=0;
      for(i=0;i<Vreg_ADC_ACCU_SIZE;i++)
        Vreg_Accu+=Vreg_ADCAccu[i];
      Vreg_value=0.0051335*(((float)Vreg_Accu)/((float)Vreg_ADC_ACCU_SIZE));
      if(Vreg_value>21)
        NegativeMask=21;
      else if(Vreg_value<1)
        NegativeMask=1;
      else
        NegativeMask=(uint8_t)Vreg_value;
      //Vreg_currentValue=(float)( ( (Vreg_value-Vreg_V_TEMP_25)/Vreg_AVG_SLOPE) +25 );
  }
}