#include "timer.h"
extern uint32_t Delay_ms_tick;
//extern uint32_t Tick_Delta_t_timer;
extern uint32_t Delta_t_timer;
void (*Timer3_OC_Ch1_callback)(void);
void (*Timer3_OC_Ch2_callback)(void);
uint32_t Alarm_us_value1=0,Alarm_us_value2=0;

void Alarm_us(uint8_t channel, uint32_t time_us, void (*cb)(void))
{
  
  
  switch(channel)
  {
  case 1:
    Timer3_OC_Ch1_callback=cb;
    Alarm_us_value1=time_us;
    if(Alarm_us_value1>0xFFFF)
    {
      TIM_SetCounter(TIM3,0xFFFF);
      TIM_SetCompare1(TIM3,0);
      Alarm_us_value1-=0xFFFF;
    }
    else
    {
      TIM_SetCounter(TIM3,Alarm_us_value1);
      TIM_SetCompare1(TIM3,0);
      Alarm_us_value1=0;
    }
    TIM_ITConfig(TIM3, TIM_IT_CC1 , ENABLE);
    break;
  case 2:
    Alarm_us_value2=time_us;
    break;
  default:break;
  }
  TIM_Cmd(TIM3, ENABLE);
  
}

/*void timer_set_alarm(uint8_t channel, uint32_t delta_t_ms,void (*cb)(void))
{ 
  uint16_t CNT_Val;
  
  
 // Tick_Delta_t_timer=0;
  
  if(delta_t_ms>0xFFFF)
    delta_t_ms=0xFFFF;
  CNT_Val = delta_t_ms;
  
  TIM_SetCounter(TIM3,0);
  switch(channel)
  {
  case 1:
    Timer3_OC_Ch1_callback=cb;
    TIM_SetCompare1(TIM3,CNT_Val);
    TIM_ITConfig(TIM3, TIM_IT_CC1 , ENABLE);
    break;
  case 2:
    Timer3_OC_Ch2_callback=cb;
    TIM_SetCompare2(TIM3,CNT_Val);
    TIM_ITConfig(TIM3, TIM_IT_CC2 , ENABLE);
    break;
  default:break;
  }
  TIM_Cmd(TIM3, ENABLE);
  //TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
}*/

void timer_init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  
  /* --------------------------- System Clocks Configuration ---------------------*/
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /* Enable the TIMER global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=11;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/2000000)-1;      //1Mhz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* Output Compare Toggle Mode configuration: Channel1 */
  /*TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 65535;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);*/
  
    
  /* TIM IT disable */
  TIM_ITConfig(TIM3, TIM_IT_CC1 , DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC2 , DISABLE);
  
  /* TIM3 disable counter */
  TIM_Cmd(TIM3, DISABLE);
}

void timer_unset_alarm(uint8_t channel)
{
  TIM_Cmd(TIM3, DISABLE);
  switch(channel)
  {
  case 1:
    TIM_ITConfig(TIM3, TIM_IT_CC1 , DISABLE);
    Timer3_OC_Ch1_callback=0;
    break;
  case 2:
    TIM_ITConfig(TIM3, TIM_IT_CC2 , DISABLE);
    Timer3_OC_Ch2_callback=0;
    break;
  default:break;
  }
  
}

void timer_blocking_wait(uint32_t milliseconds)
{
  Delay_ms_tick=0;
  while(Delay_ms_tick<milliseconds);
}

void TIM3_IRQHandler()
{
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_Cmd(TIM3, DISABLE);
    /* Clear TIM3 Capture Compare1 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    if(Alarm_us_value1)
    {
      if(Alarm_us_value1>0xFFFF)
      {
        TIM_SetCounter(TIM3,0xFFFF);
        Alarm_us_value1-=0xFFFF;
      }
      else
      {
        TIM_SetCounter(TIM3,Alarm_us_value1);
        Alarm_us_value1=0;
      }
      TIM_SetCompare1(TIM3,0);
        TIM_Cmd(TIM3, ENABLE);
    }
    else
    {
      TIM_ITConfig(TIM3, TIM_IT_CC1 , DISABLE);
      if(Timer3_OC_Ch1_callback)
      {
        Timer3_OC_Ch1_callback();
      }
    }
  }
}


