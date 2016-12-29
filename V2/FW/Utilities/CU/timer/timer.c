#include "timer.h"
extern uint32_t Delay_ms_tick;
extern uint32_t Tick_Delta_t_timer;
extern uint32_t Delta_t_timer;
uint16_t (*Timer2_OC_Ch1_callback)(void);
uint16_t (*Timer2_OC_Ch2_callback)(void);
uint16_t (*Timer2_OC_Ch3_callback)(void);

uint16_t dummyCB(void)
{
  uint8_t i=0;
  i++;
  return 0;
}

void timer_set_alarm(uint8_t channel, uint32_t delta_t,uint16_t (*cb)(void))
{ 
  uint16_t CNT_Val;
  //CNT_Val=TIM_GetPrescaler(TIM2);
  TIM_Cmd(TIM2, DISABLE);
  //Tick_Delta_t_timer=0;
  
  if(delta_t>0xFFFE)
    delta_t=0xFFFE;
  CNT_Val = delta_t;
  /*if((CNT_Val+TIM2->CNT)>0xFFFF)
    CNT_Val-=(0xFFFF-TIM2->CNT);
  else
    CNT_Val+=TIM2->CNT;*/
  
  TIM_SetCounter(TIM2,0);
  TIM2->ARR=0xFFFF;
  switch(channel)
  {
  case 1:
    Timer2_OC_Ch1_callback=cb;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
    TIM_SetCompare1(TIM2,CNT_Val);
    TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
    break;
  case 2:
    Timer2_OC_Ch2_callback=cb;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
    TIM_SetCompare2(TIM2,CNT_Val);
    TIM_ITConfig(TIM2, TIM_IT_CC2 , ENABLE);
    break;
  case 3:
    Timer2_OC_Ch3_callback=cb;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
    TIM_SetCompare3(TIM2,CNT_Val);
    TIM_ITConfig(TIM2, TIM_IT_CC3 , ENABLE);
    break;
  default:break;
  }
  TIM_Cmd(TIM2, ENABLE);
  //TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
}

void timer_init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  
  /* --------------------------- System Clocks Configuration ---------------------*/
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  /* Enable the TIMER global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 11;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1;//1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  /* Output Compare Toggle Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = 65535;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
  
    
  /* TIM IT disable */
  TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE);
  
  /* TIM2 disable counter */
  TIM_Cmd(TIM2, DISABLE);
  
  
  //timer_set_alarm(2,1,dummyCB);
}

void timer_unset_alarm(uint8_t channel)
{
  TIM_Cmd(TIM2, DISABLE);
  switch(channel)
  {
  case 1:
    TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
    Timer2_OC_Ch1_callback=0;
    break;
  case 2:
    TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
    Timer2_OC_Ch2_callback=0;
    break;
  case 3:
    TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE);
    Timer2_OC_Ch3_callback=0;
    break;
  default:break;
  }
  
}

void timer_blocking_wait(uint32_t milliseconds)
{
  Delay_ms_tick=0;
  while(Delay_ms_tick<milliseconds);
}


