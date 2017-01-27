#include "ADC.h"
#include "stm32f2xx_adc.h"

#define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)

#define ADC_MAX_NUMBER_OF_CHANNELS      19
#define ADC_CB_TABLE_SIZE       ADC_MAX_NUMBER_OF_CHANNELS

uint16_t ADCConvertedValues[ADC_MAX_NUMBER_OF_CHANNELS];
uint8_t ADCInited=0;



uint8_t ADCChannelValueMapping[ADC_CB_TABLE_SIZE];
void (*ADC_cb_table[ADC_CB_TABLE_SIZE])(uint16_t);

uint8_t ADC_RegisterCallback(uint8_t channel, void (* cb)(uint16_t))
{
  if( (channel > ADC_Channel_18) || (channel < ADC_Channel_0) )
    return 1;
  if(cb==0)
    return 1;
  if(ADC_cb_table[channel]!=0)
    return 1;
  ADC_cb_table[channel]=cb;
  if(channel == ADC_Channel_16)
    ADC_TempSensorVrefintCmd(ENABLE);
  return 0;
}

uint8_t ADC_UnregisterCallback(uint8_t channel)
{
  if( (channel > ADC_Channel_18) || (channel < ADC_Channel_0) )
    return 1;
  ADC_cb_table[channel]=0;
  if(channel == ADC_Channel_16)
    ADC_TempSensorVrefintCmd(DISABLE);
  return 0;
}

void ADC_CallbackHandler(void)
{
  uint8_t i=0;
  //void (* cb)(void)=0;
  for(i=0;i<ADC_CB_TABLE_SIZE;i++)
  {
    if(ADC_cb_table[i])
      ADC_cb_table[i](ADCConvertedValues[ADCChannelValueMapping[i]]);
  }
}

void ADC_LowLevelInit(void)
{
  uint8_t i=0,j=0;
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  NVIC_InitTypeDef      NVIC_InitStructure;
  
  if(!ADCInited)
  {
    /* Enable peripheral clocks *************************************************/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    
    /* NVIC config for DMA TC interrupt *****************************************/
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);

    /* DMA2_Stream0 channel0 configuration **************************************/
    DMA_DeInit(DMA2_Stream0);
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADCConvertedValues;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = ADC1_CHANNELS_IN_USE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    /* DMA2_Stream0 enable */
    DMA_Cmd(DMA2_Stream0, ENABLE);
    
    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
      
    /* ADC Common Init **********************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ADC1 Init ****************************************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;  
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = ADC1_CHANNELS_IN_USE;
    ADC_Init(ADC1, &ADC_InitStructure);

    
    
    /* ADC1 regular channels  configuration ******************************/
    while(i<ADC1_CHANNELS_IN_USE)
    {
      if( (ADC1_CHANNELS_MAP & (BIT0<<j)))
      {
        ADC_RegularChannelConfig(ADC1,j ,i+1, ADC_SampleTime_56Cycles);
        ADCChannelValueMapping[j]=i;
        if(j==ADC_Channel_Vbat)
          ADC_Cmd(ADC1, ENABLE);//  ?!?!?!?
        i++;
      }
      j++;
    }

    /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
    
    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* Enable ADC1 **************************************************************/
    ADC_Cmd(ADC1, ENABLE);
    
    ADC_SoftwareStartConv(ADC1);
  }
  ADCInited=1;
}

void DMA2_Stream0_cb(void)
{
  static uint32_t i=0;
  i++;
  if(i==1000)
  {
    i=0;
    ADC_CallbackHandler();
  }
}

