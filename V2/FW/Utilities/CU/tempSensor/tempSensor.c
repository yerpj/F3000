#include "tempSensor.h"
#include "ADC.h"

void tempSensor_Monitor_callback(uint16_t value);

void (*tempSensor_cb)(float)=0;

#define TEMPSENSOR_ADC_ACCU_SIZE 2
uint16_t tempSensor_ADCAccu[TEMPSENSOR_ADC_ACCU_SIZE];
uint8_t tempSensor_ADCAccuPtr=0;
float tempSensor_currentValue=0;//defined as the input voltage (on header). range: [0..5]V
uint8_t tempSensor_currentState=TempSensor_Cold;//can be cold, medium or hot


void tempSensor_Init(void (*callback)(float))
{
  
  ADC_LowLevelInit();
  //callback init
  if(callback!=NULL)
  {
    tempSensor_cb=callback;
    //ADC_RegisterCallback(TEMP_IN_ADC_CHANNEL,tempSensor_cb);
  }
  else
    ADC_RegisterCallback(TEMP_IN_ADC_CHANNEL,tempSensor_Monitor_callback);
}

uint8_t tempSensor_Get_State(void)
{
  return tempSensor_currentState;
}

float tempSensor_Get_Temp(void)
{
  return tempSensor_currentValue;
}

void tempSensor_Monitor_callback(uint16_t value)
{
  uint32_t tempSensor_Accu=0;
  float tempSensor_value;
  uint8_t i;
  
  tempSensor_ADCAccu[tempSensor_ADCAccuPtr++]=value;
  if(tempSensor_ADCAccuPtr>=TEMPSENSOR_ADC_ACCU_SIZE)
  {
    tempSensor_ADCAccuPtr=0;
    for(i=0;i<TEMPSENSOR_ADC_ACCU_SIZE;i++)
      tempSensor_Accu+=tempSensor_ADCAccu[i];
    tempSensor_value=(((float)tempSensor_Accu)/((float)TEMPSENSOR_ADC_ACCU_SIZE));
    tempSensor_currentValue=tempSensor_value*0.001245;//conversion to be fine-tuned
    
    if(tempSensor_currentValue>TEMPSENSOR_COLD_TO_MEDIUM_VOLTAGE)
      tempSensor_currentState=TempSensor_Cold;
    else if(tempSensor_currentValue>=TEMPSENSOR_MEDIUM_TO_HOT_VOLTAGE)
      tempSensor_currentState=TempSensor_Medium;
    else 
      tempSensor_currentState=TempSensor_Hot;
  }
}


