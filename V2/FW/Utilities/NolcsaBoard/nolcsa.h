/**
  ******************************************************************************
  * @file    nolcsa.h
  * @author  MCD Application Team
  * @version V5.0.0
  * @date    07-October-2011
  * @brief   This file contains definitions for nolcsa's Leds, push-buttons
  *          and COM ports hardware resources.
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
#ifndef __NOLCSA_EVAL_H
#define __NOLCSA_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "stm32f2xx_dma.h"


   


typedef enum 
{
  LED1 = 0,     //main blue LED
  LED2 = 1,     //LED RGB R
  LED3 = 2,     //LED RGB G
  LED4 = 3,      //LED RGB B
  LED5 = 4,      //LED YELLOW
  LED6 = 5,      //LED RGB R 2
  LED7 = 6,      //LED RGB G 2
  LED8 = 7      //LED RGB B 2
} Led_TypeDef;

typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;

typedef enum
{
  BUS_I2C1 = 0
} I2C_List_Typedef;

    
#define LED_BLUE LED4
#define LED_RED LED3
#define LED_GREEN LED2
#define LED_BLUE_ALONE LED1

#define LED_YELLOW LED5
#define LED_RED2 LED7
#define LED_GREEN2 LED6
#define LED_BLUE2 LED8

/** @addtogroup nolcsa_LOW_LEVEL_LED
  * @{
  */
    
#define LEDn                             8

#define LED1_PIN                         GPIO_Pin_1
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOB 
  
#define LED2_PIN                         GPIO_Pin_4
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOC  
  
#define LED3_PIN                         GPIO_Pin_0
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
  
#define LED4_PIN                         GPIO_Pin_5
#define LED4_GPIO_PORT                   GPIOC
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOC
  
#define LED5_PIN                         GPIO_Pin_7
#define LED5_GPIO_PORT                   GPIOC
#define LED5_GPIO_CLK                    RCC_AHB1Periph_GPIOC
  
#define LED6_PIN                         GPIO_Pin_3
#define LED6_GPIO_PORT                   GPIOA
#define LED6_GPIO_CLK                    RCC_AHB1Periph_GPIOA
  
#define LED7_PIN                         GPIO_Pin_1
#define LED7_GPIO_PORT                   GPIOA
#define LED7_GPIO_CLK                    RCC_AHB1Periph_GPIOA
  
#define LED8_PIN                         GPIO_Pin_2
#define LED8_GPIO_PORT                   GPIOA
#define LED8_GPIO_CLK                    RCC_AHB1Periph_GPIOA




/** @addtogroup nolcsa_LOW_LEVEL_COM
  * @{
  */
#define COMn                             2

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_6
#define EVAL_COM1_TX_GPIO_PORT           GPIOB
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource6
#define EVAL_COM1_TX_AF                  GPIO_AF_USART1
#define EVAL_COM1_RX_PIN                 GPIO_Pin_7
#define EVAL_COM1_RX_GPIO_PORT           GPIOB
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource7
#define EVAL_COM1_RX_AF                  GPIO_AF_USART1
#define EVAL_COM1_IRQn                   USART1_IRQn

/**
 * @brief Definition for COM port2, connected to USART3
 */ 
#define EVAL_COM2                        USART3
#define EVAL_COM2_CLK                    RCC_APB1Periph_USART3
#define EVAL_COM2_TX_PIN                 GPIO_Pin_10
#define EVAL_COM2_TX_GPIO_PORT           GPIOC
#define EVAL_COM2_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define EVAL_COM2_TX_SOURCE              GPIO_PinSource10
#define EVAL_COM2_TX_AF                  GPIO_AF_USART3
#define EVAL_COM2_RX_PIN                 GPIO_Pin_11
#define EVAL_COM2_RX_GPIO_PORT           GPIOC
#define EVAL_COM2_RX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define EVAL_COM2_RX_SOURCE              GPIO_PinSource11
#define EVAL_COM2_RX_AF                  GPIO_AF_USART3
#define EVAL_COM2_IRQn                   USART3_IRQn



/**
 * @brief Definition for SPI1
 */ 
#define FLASH_SPI                       SPI1
#define FLASH_SPI_CLK                   RCC_APB2Periph_SPI1 

#define FLASH_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.5 */
#define FLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define FLASH_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define FLASH_SPI_SCK_SOURCE            GPIO_PinSource5
#define FLASH_SPI_SCK_AF                GPIO_AF_SPI1

#define FLASH_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.6 */
#define FLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define FLASH_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define FLASH_SPI_MISO_SOURCE           GPIO_PinSource6
#define FLASH_SPI_MISO_AF               GPIO_AF_SPI1

#define FLASH_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.7 */
#define FLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define FLASH_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define FLASH_SPI_MOSI_SOURCE           GPIO_PinSource7
#define FLASH_SPI_MOSI_AF               GPIO_AF_SPI1

#define FLASH_SPI_CS_PIN                GPIO_Pin_4                  /* PA.4 */
#define FLASH_SPI_CS_GPIO_PORT          GPIOA                       /* GPIOA */
#define FLASH_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOA

#define I2Cn                            1

/** 
  * @brief  DS3231MZ I2C interface
  */ 

#define DS3231MZ_I2C_BUS                      BUS_I2C1
#define DS3231MZ_I2C                          I2C3
#define DS3231MZ_I2C_CLK                      RCC_APB1Periph_I2C3
#define DS3231MZ_I2C_SCL_PIN                  GPIO_Pin_8
#define DS3231MZ_I2C_SCL_GPIO_PORT            GPIOA
#define DS3231MZ_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define DS3231MZ_I2C_SCL_SOURCE               GPIO_PinSource8
#define DS3231MZ_I2C_SCL_AF                   GPIO_AF_I2C3
#define DS3231MZ_I2C_SDA_PIN                  GPIO_Pin_9
#define DS3231MZ_I2C_SDA_GPIO_PORT            GPIOC
#define DS3231MZ_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOC
#define DS3231MZ_I2C_SDA_SOURCE               GPIO_PinSource9
#define DS3231MZ_I2C_SDA_AF                   GPIO_AF_I2C3
#define DS3231MZ_I2C_SPEED                    10000

#define DS3231MZ_RST_PIN                      GPIO_Pin_10                  /* PB.10 */
#define DS3231MZ_RST_GPIO_PORT                GPIOB                       /* GPIOB */
#define DS3231MZ_RST_GPIO_CLK                 RCC_AHB1Periph_GPIOB

#define DS3231MZ_INT_PIN                      GPIO_Pin_0                  /* PA.0 */
#define DS3231MZ_INT_GPIO_PORT                GPIOA                       /* GPIOA */
#define DS3231MZ_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DS3231MZ_INT_EXTI_PORT_SOURCE         EXTI_PortSourceGPIOA
#define DS3231MZ_INT_EXTI_PIN_SOURCE          EXTI_PinSource0
#define DS3231MZ_INT_EXTI_LINE                EXTI_Line0
#define DS3231MZ_INT_EXTI_IRQn                EXTI0_IRQn   
    
/** 
  * @brief  DALI interface
  */ 

#define DALI_POWER_ENABLE_PIN                 GPIO_Pin_2                  /* PC.2 */
#define DALI_POWER_ENABLE_GPIO_PORT           GPIOC                       /* GPIOC */
#define DALI_POWER_ENABLE_GPIO_CLK            RCC_AHB1Periph_GPIOC

#define DALI_TX_PIN                           GPIO_Pin_9                  /* PA.9 */
#define DALI_TX_GPIO_PORT                     GPIOA                       /* GPIOA */
#define DALI_TX_GPIO_CLK                      RCC_AHB1Periph_GPIOA

#define DALI_RX_PIN                           GPIO_Pin_0                  /* PC.0 */
#define DALI_RX_GPIO_PORT                     GPIOC                       /* GPIOC */
#define DALI_RX_GPIO_CLK                      RCC_AHB1Periph_GPIOC
#define DALI_RX_EXTI_PORT_SOURCE              EXTI_PortSourceGPIOC
#define DALI_RX_EXTI_PIN_SOURCE               EXTI_PinSource0
#define DALI_RX_EXTI_LINE                     EXTI_Line0
#define DALI_RX_EXTI_IRQn                     EXTI0_IRQn  

#define DALI_ISENSE_PIN                       GPIO_Pin_3
#define DALI_ISENSE_GPIO_PORT                 GPIOC
#define DALI_ISENSE_GPIO_CLK                  RCC_AHB1Periph_GPIOC
#define DALI_ISENSE_ADC_CHANNEL               ADC_Channel_13
    

void nolcsa_LEDInit(Led_TypeDef Led);
void nolcsa_LEDDeInit(Led_TypeDef Led);
void nolcsa_LEDOn(Led_TypeDef Led);
void nolcsa_LEDOff(Led_TypeDef Led);
void nolcsa_LEDToggle(Led_TypeDef Led);
void nolcsa_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct); 

void nolcsa_MX25L1606E_LowLevel_Init(void);
void I2C_Bus_Init(I2C_List_Typedef I2Cx);
void DALI_LowLevel_Init(void);
void nolcsa_ADC_Init(void);

void nolcsa_RNGInit(void);
uint32_t nolcsa_RandomValue(void);

  
#ifdef __cplusplus
}
#endif

#endif /* __NOLCSA_EVAL_H */
