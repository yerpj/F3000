/**
  ******************************************************************************
  * @file    stm32f2xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    07-October-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_it.h"
#include "main.h"



/* Private function prototypes -----------------------------------------------*/
extern void xPortSysTickHandler(void); 
//extern EventGroupHandle_t CU_Inputs_EventGroup;
extern uint16_t (*Timer2_OC_Ch1_callback)(void);
extern uint16_t (*Timer2_OC_Ch2_callback)(void);
extern uint16_t (*Timer2_OC_Ch3_callback)(void);


extern void STBT_USART_RX_Callback(uint8_t rxchar);

uint8_t (*SysTick_Delay_cb)(void)=NULL;


uint32_t Delay_ms_tick=0;
uint32_t SysTick_Delay_ms=0;

uint32_t Regime_Delay_ms=0;
uint32_t Regime_RPM=0;
uint32_t RegimeIRQEvents=0;





extern void DMA2_Stream0_cb(void);


/* Private functions ---------------------------------------------------------*/
DebouncedArray_t ExtInterrupts;
EventGroupHandle_t * DebouncerEventGroup=NULL;
uint8_t DebouncerInit(EventGroupHandle_t xEventGroup)
{
  uint8_t i=0;
  if(xEventGroup==NULL)
    return 1;
  DebouncerEventGroup=xEventGroup;
  ExtInterrupts.EdgeMask=0;
  ExtInterrupts.IsDebouncing=0;
  for(i=0;i<32;i++)
    ExtInterrupts.AssociatedCallback[i]=0;
  return 0;
}

uint32_t Regime_getRPM(void)
{
  return Regime_RPM;
}

uint8_t DebouncerAddInput(uint32_t InputMask,GPIO_TypeDef* GPIO,uint16_t Pin,uint8_t Edge,uint32_t Event,void cb(void),uint32_t DebounceTime_ms)
{
  uint8_t InputIndex=0;
  while( ((InputMask>>InputIndex)&0x01)==0 && InputIndex<32 )
    InputIndex++;
  if(InputIndex>=32)
    return 1;
  ExtInterrupts.InputGPIOPort[InputIndex]=GPIO;
  ExtInterrupts.InputGPIOPin[InputIndex]=Pin;
  if(Edge)
    ExtInterrupts.EdgeMask|=InputMask;
  else
    ExtInterrupts.EdgeMask&=~InputMask;
  ExtInterrupts.AssociatedEvent[InputIndex]=Event;
  if(cb)
    ExtInterrupts.AssociatedCallback[InputIndex]=cb;
  ExtInterrupts.IsDebouncing&=~InputMask;
  ExtInterrupts.DebounceTime_ms[InputIndex]=DebounceTime_ms;
  return 0;
}

//call this function whenever an EXTI event happened
uint8_t Debounce(uint32_t InputMask)
{
  uint8_t InputIndex=0;
  while( ((InputMask>>InputIndex)&0x01)==0 && InputIndex<32 )
    InputIndex++;
  if(ExtInterrupts.IsDebouncing&InputMask)
    return 0;//nothing to do. Systick is handling the debouncer
  else
  {
    ExtInterrupts.IsDebouncing|=InputMask;
    ExtInterrupts.DebounceCurVal_ms[InputIndex]=ExtInterrupts.DebounceTime_ms[InputIndex];//load base debouncing delay
  }
}

uint8_t DebouncerHandle(void)
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  uint8_t i;
  if(ExtInterrupts.IsDebouncing)
  {
    for(i=0;i<32;i++)
    {
      if(!ExtInterrupts.IsDebouncing)
        return 0;
      else
      {
        if(ExtInterrupts.DebounceCurVal_ms[i])
        {
          ExtInterrupts.DebounceCurVal_ms[i]--;
          if(ExtInterrupts.DebounceCurVal_ms[i]==0)
          {
             (ExtInterrupts.IsDebouncing&=~(0x01<<i));
             if(ExtInterrupts.EdgeMask&(0x01<<i))
             {
               if( !GPIO_ReadInputDataBit(ExtInterrupts.InputGPIOPort[i],ExtInterrupts.InputGPIOPin[i]) )
                 continue;
             }
             else
             {
               if( GPIO_ReadInputDataBit(ExtInterrupts.InputGPIOPort[i],ExtInterrupts.InputGPIOPin[i]) )
                 continue;
             }
             
             if(DebouncerEventGroup!=NULL)
             {
              if( (xEventGroupGetBitsFromISR(DebouncerEventGroup) & ExtInterrupts.AssociatedEvent[i]) ==RESET)
                xEventGroupSetBitsFromISR(DebouncerEventGroup,ExtInterrupts.AssociatedEvent[i],&xHigherPriorityTaskWoken);
              if(ExtInterrupts.AssociatedCallback[i])
              {
                ExtInterrupts.AssociatedCallback[i]();
              }
             }
          }
        }
      }
    }
    return 0;
  }
}


void setSysTick_Delay_Timer(uint32_t Delayms,uint8_t (*cb)(void))
{
  SysTick_Delay_cb=cb;
  SysTick_Delay_ms=Delayms;
}

void printErrorMsg(const char * errMsg) { while(*errMsg != '\0'){ ITM_SendChar(*errMsg); ++errMsg; } }

void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; /* Link register. */
volatile uint32_t pc; /* Program counter. */
volatile uint32_t psr;/* Program status register. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */

void HardFault_Handler(void)
{
  //printErrorMsg("In Hard Fault Handler");
  __ASM volatile("BKPT #01");
  while (1);
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  xPortSysTickHandler(); 
  Delay_ms_tick++;
  if(SysTick_Delay_ms)
  {
    SysTick_Delay_ms--;
    if(SysTick_Delay_ms==0 && SysTick_Delay_cb)
    {
      SysTick_Delay_cb();
      SysTick_Delay_cb=0;
    }
  }
  DebouncerHandle();
  
  if(++Regime_Delay_ms>200)
  {
    Regime_RPM=300*RegimeIRQEvents;
    RegimeIRQEvents=0;
    Regime_Delay_ms=0;
  }
  
}

void DMA2_Stream0_IRQHandler(void)
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
    DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);  
    if(DMA2_Stream0_cb)
      DMA2_Stream0_cb();
  }
}

void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    STBT_USART_RX_Callback(USART_ReceiveData(USART1));
  }
}

void TIM2_IRQHandler()
{
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    //Delta_t_timer1=Tick_Delta_t_timer;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);

    TIM_Cmd(TIM2, DISABLE);
    TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
    
    Timer2_OC_Ch1_callback();
  }
  if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    //Delta_t_timer2=Tick_Delta_t_timer;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);

    TIM_Cmd(TIM2, DISABLE);
    TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
    
    Timer2_OC_Ch2_callback();
    TIM_SetCounter(TIM2,0);
  }
  if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {
    //Delta_t_timer2=Tick_Delta_t_timer;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);

    TIM_Cmd(TIM2, DISABLE);
    TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE);
    
    Timer2_OC_Ch3_callback();
    TIM_SetCounter(TIM2,0);
  }
}

#ifdef USE_BREADBOARD
void EXTI15_10_IRQHandler()
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  if(EXTI_GetITStatus(NEUTRAL_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_NEUTRAL_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(NEUTRAL_INPUT_EXTI_LINE);}
  
  if(EXTI_GetITStatus(CAME_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_CAME_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(CAME_INPUT_EXTI_LINE);}
}

void EXTI9_5_IRQHandler()
{  
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
}
#else /* USE_BREADBOARD */
void EXTI15_10_IRQHandler()
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Shifter: PB12
  if(EXTI_GetITStatus(SHIFTER_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_SHIFTER_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_SHIFTER_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(SHIFTER_INPUT_EXTI_LINE);}
  
  //Came: PB13
  if(EXTI_GetITStatus(CAME_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_CAME_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(CAME_INPUT_EXTI_LINE);}
  
  //Oil: PB14
  if(EXTI_GetITStatus(OIL_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_OIL_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_OIL_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(OIL_INPUT_EXTI_LINE);}
  
  //Embray: PB15
  if(EXTI_GetITStatus(EMBRAY_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_EMBRAY_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_EMBRAY_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(EMBRAY_INPUT_EXTI_LINE);}
}

void EXTI9_5_IRQHandler()
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Reserved1: PA5
  if(EXTI_GetITStatus(RESERVED1_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RESERVED1_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_RESERVED1_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(RESERVED1_INPUT_EXTI_LINE);}
  
  //Reserved2: PA6//conflict with Neutre, do not activate interrupt on this line!
  if(EXTI_GetITStatus(RESERVED2_INPUT_EXTI_LINE) != RESET){
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RESERVED2_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_RESERVED2_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(RESERVED2_INPUT_EXTI_LINE);}
  
  //Neutral: PC6
  if(EXTI_GetITStatus(NEUTRAL_INPUT_EXTI_LINE) != RESET)
  {
    if(!GPIO_ReadInputDataBit(NEUTRAL_INPUT_GPIO_PORT,NEUTRAL_INPUT_PIN))
    {
      if(CU_Inputs_EventGroup!=NULL){
        if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_NEUTRAL_BIT) ==RESET)
          xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT,&xHigherPriorityTaskWoken);}
    }
    EXTI_ClearITPendingBit(NEUTRAL_INPUT_EXTI_LINE);
  }
  
  //Regime: PC7
  if(EXTI_GetITStatus(REGIME_INPUT_EXTI_LINE) != RESET){
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_REGIME_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_REGIME_BIT,&xHigherPriorityTaskWoken);}*/
    RegimeIRQEvents++;
    EXTI_ClearITPendingBit(REGIME_INPUT_EXTI_LINE);}
  
  //PAL_g: PA8
  if(EXTI_GetITStatus(PALG_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_PALG_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_PALG_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_PALG_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(PALG_INPUT_EXTI_LINE);}
}
void EXTI4_IRQHandler() 
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Rapport+: PA4
  if(EXTI_GetITStatus(RAPPORTp_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_RAPPORTp_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTp_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTp_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(RAPPORTp_INPUT_EXTI_LINE);}
}

void EXTI3_IRQHandler() 
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Gaz: PC3
  if(EXTI_GetITStatus(GAZ_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_GAZ_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_GAZ_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(GAZ_INPUT_EXTI_LINE);}
}

void EXTI2_IRQHandler() 
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Reserved3: PA2
  if(EXTI_GetITStatus(RESERVED3_INPUT_EXTI_LINE) != RESET){
    if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RESERVED3_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_RESERVED3_BIT,&xHigherPriorityTaskWoken);}
    EXTI_ClearITPendingBit(RESERVED3_INPUT_EXTI_LINE);}
}

void EXTI1_IRQHandler() 
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //Rapport-: PA1
  if(EXTI_GetITStatus(RAPPORTm_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_RAPPORTm_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTm_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTm_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(RAPPORTm_INPUT_EXTI_LINE);}
}

void EXTI0_IRQHandler() 
{
  BaseType_t xHigherPriorityTaskWoken=pdFALSE;
  
  //PAL_d: PC0
  if(EXTI_GetITStatus(PALD_INPUT_EXTI_LINE) != RESET){
    Debounce(CU_INPUT_EVENT_PALD_BIT);
    /*if(CU_Inputs_EventGroup!=NULL){
      if( (xEventGroupGetBitsFromISR(CU_Inputs_EventGroup)&CU_INPUT_EVENT_PALD_BIT) ==RESET)
        xEventGroupSetBitsFromISR(CU_Inputs_EventGroup,CU_INPUT_EVENT_PALD_BIT,&xHigherPriorityTaskWoken);}*/
    EXTI_ClearITPendingBit(PALD_INPUT_EXTI_LINE);}
}

#endif /* USE_BREADBOARD */



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
