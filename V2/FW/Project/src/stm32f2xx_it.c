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


/* Private typedef -----------------------------------------------------------*/
    
    enum {
      RECV_HEADER,
      RECV_RESPONSE,
      RECV_FOOTER,
    };
/* Private define ------------------------------------------------------------*/
#define USART_BUFFER_LENGTH 256
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
    
uint32_t TimerVal1=0;
uint32_t TimerVal2=0;
    
uint8_t USART1_RXBuf[USART_BUFFER_LENGTH];
extern xSemaphoreHandle s_xSemaphore;
extern  xQueueHandle GSM_byte_rx_queue;
extern  xQueueHandle RPI_byte_rx_queue;

#ifdef BYPASS_GSM_SERIAL
extern  xQueueHandle GSM_COM_downlink_queue, GSM_COM_uplink_queue;
#endif /* BYPASS_GSM_SERIAL */
/* Private function prototypes -----------------------------------------------*/
extern void xPortSysTickHandler(void); 
extern uint16_t (*Timer2_OC_Ch1_callback)(void);
extern uint16_t (*Timer2_OC_Ch2_callback)(void);
extern uint16_t (*Timer2_OC_Ch3_callback)(void);

extern  void (*PushButton_cb)(uint8_t);
extern void (*NoiseSensor_cb)(uint16_t newvalue);
extern void (*PhotoTransistor_cb)(uint16_t newvalue);

extern void (*Accel_int1_cb)(void);
extern void (*Accel_int2_cb)(void);
extern  uint16_t (*gdo0_cb)(void);
extern  uint16_t (*gdo2_cb)(void);
extern  uint16_t (*GSM_COM_RX_cb)(uint8_t *, uint32_t);
extern void (*GSM_rx_cb)(uint8_t character);
extern void DebugBSP_Rpi_RX_Callback(uint8_t c);
extern void DistanceSensorPulseCallback(uint8_t pulse, uint8_t State);
extern void (*NGP02x_Console_IRQ_cb)(void);

uint32_t Delay_ms_tick=0;
#ifdef USE_NOVADEV
extern uint32_t DistanceSensorPulse1_ms;
extern uint32_t DistanceSensorPulse2_ms;
#endif /* USE_NOVADEV */
uint32_t Tick_Delta_t_timer=0;
uint32_t Delta_t_timer1=0;
uint32_t Delta_t_timer2=0;

extern void DMA2_Stream0_cb(void);

#if defined(USE_NOLCNP010) || defined(USE_OLCN011) || defined(USE_OLCN013)
extern void (*DigitalInput_cb)(uint8_t state);
extern void (*DALI_RX_PIN_cb)(uint8_t ,uint32_t);
extern void (*SerialCB)(uint8_t);
extern void (*Sable_X_RX_CB)(uint8_t);

extern void (*DALI_TX_PIN_cb)(void);
#endif /* defined(USE_NOLCNP010) || defined(USE_OLCN011) || defined(USE_OLCN013) */

#if defined(USE_NGP022)
extern void (*Sable_X_RX_CB)(uint8_t);
#endif /* defined(USE_NGP022) */

#if defined(USE_NODE)
extern void Node_Console_cb(void);
#endif  /* defined(USE_NODE) */

#if defined(USE_NC030_TESTER)
extern void NC030_Tester_Console_cb(void);
#endif  /* defined(USE_NC030_TESTER) */

#ifdef USE_NOVAPROGRAMMER
extern void (*SerialCB)(uint8_t);
#endif /* USE_NOVAPROGRAMMER */

/* Private functions ---------------------------------------------------------*/

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
  Tick_Delta_t_timer++;
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



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
