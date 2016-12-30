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

/* Scheduler includes */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 



    


/* Private function prototypes -----------------------------------------------*/
extern void xPortSysTickHandler(void); 

extern uint16_t (*Timer2_OC_Ch1_callback)(void);
extern uint16_t (*Timer2_OC_Ch2_callback)(void);
extern uint16_t (*Timer2_OC_Ch3_callback)(void);

uint8_t (*SysTick_Delay_cb)(void)=NULL;


uint32_t Delay_ms_tick=0;
uint32_t SysTick_Delay_ms=0;



extern void DMA2_Stream0_cb(void);


/* Private functions ---------------------------------------------------------*/
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



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
