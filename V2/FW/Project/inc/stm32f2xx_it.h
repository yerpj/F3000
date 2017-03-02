/**
  ******************************************************************************
  * @file    stm32f2xx_it.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    07-October-2011
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F2xx_IT_H
#define __STM32F2xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/* Exported types ------------------------------------------------------------*/
#define DEBOUNCER_INT_EDGE_RISING  1
#define DEBOUNCER_INT_EDGE_FALLING 0
typedef struct
{
  uint32_t IsDebouncing;
  uint32_t EdgeMask;//rising:1, falling:0
  uint32_t DebounceTime_ms[32];
  uint32_t DebounceCurVal_ms[32];
  uint32_t AssociatedEvent[32];
  void (*AssociatedCallback[32])(void);
  GPIO_TypeDef* InputGPIOPort[32];
  uint16_t InputGPIOPin[32];
} DebouncedArray_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#include "main.h"
#include "event_groups.h"
uint8_t DebouncerInit(EventGroupHandle_t xEventGroup);
uint8_t DebouncerAddInput(uint32_t InputMask,GPIO_TypeDef* GPIO,uint16_t Pin,uint8_t Edge,uint32_t Event,void cb(void),uint32_t DebounceTime_ms);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
uint32_t Regime_getRPM(void);

void setSysTick_Delay_Timer(uint32_t Delayms,uint8_t (*cb)(void));

#ifdef __cplusplus
}
#endif

#endif /* __STM32F2xx_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
