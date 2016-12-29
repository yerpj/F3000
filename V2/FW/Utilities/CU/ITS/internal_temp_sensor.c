#include "internal_temp_sensor.h"
#include "ADC.h"



void (*ITS_OverTemp_cb)(float)=0;
float ITS_OverTempThreshold=90;

#define ITS_ADC_ACCU_SIZE 10
uint16_t ITS_ADCAccu[ITS_ADC_ACCU_SIZE];
uint8_t ITS_ADCAccuPtr=0;
float ITS_currentValue=0;


void ITS_Init(void (*callback)(float),float threshold)
{
  
  ADC_LowLevelInit();
  //callback init
  ITS_OverTempThreshold=threshold;
  ITS_OverTemp_cb=callback;
  ADC_RegisterCallback(ITS_ADC_CHANNEL,ITS_Monitor_callback);
}

float ITS_Get_Temp(void)
{
  return ITS_currentValue;
}

void ITS_Monitor_callback(uint16_t value)
{
  uint16_t ITS_Accu=0;
  float ITS_value;
  uint8_t i;
  ITS_ADCAccu[ITS_ADCAccuPtr++]=value;
  if(ITS_ADCAccuPtr>=ITS_ADC_ACCU_SIZE)
  {
      ITS_ADCAccuPtr=0;
      for(i=0;i<ITS_ADC_ACCU_SIZE;i++)
        ITS_Accu+=ITS_ADCAccu[i];
      ITS_value=(((float)ITS_Accu)/((float)ITS_ADC_ACCU_SIZE));
      ITS_currentValue=(float)( ( (ITS_value-ITS_V_TEMP_25)/ITS_AVG_SLOPE) +25 );
  }
}
