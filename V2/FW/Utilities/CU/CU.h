#ifndef __CU_H__
#define __CU_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "commontypes.h"


typedef enum 
{
  LED1 = 0,     //LED RGB R
  LED2 = 1,     //LED RGB G
  LED3 = 2      //LED RGB B
} Led_TypeDef;

typedef enum 
{
  COM1 = 0,
  COM2 = 1,
} COM_TypeDef;


#define LED_BLUE LED3
#define LED_RED LED1
#define LED_GREEN LED2



    
#define LEDn                             3
#define IOn                             LEDn

#define LED1_PIN                         GPIO_Pin_4
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOC 
  
#define LED2_PIN                         GPIO_Pin_0
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
  
#define LED3_PIN                         GPIO_Pin_5
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOC 


/* CU 7 segment display */
#define SEG7_SEG_A_MASK                 (0x0001<<12)
#define SEG7_SEG_B_MASK                 (0x0001<<11)
#define SEG7_SEG_C_MASK                 (0x0001<<6 )
#define SEG7_SEG_D_MASK                 (0x0001<<5 )
#define SEG7_SEG_E_MASK                 (0x0001<<4 )
#define SEG7_SEG_F_MASK                 (0x0001<<13)
#define SEG7_SEG_G_MASK                 (0x0001<<14)
#define SEG7_SEG_DP_MASK                (0x0001<<7 )

/* Bargraph */
#ifdef USE_BREADBOARD
#define D16_R_LED_INDEX                 13
#define D16_G_LED_INDEX                 15
#define D16_B_LED_INDEX                 14

#define D15_R_LED_INDEX                 10
#define D15_G_LED_INDEX                 12
#define D15_B_LED_INDEX                 11

#define D14_R_LED_INDEX                 3
#define D14_G_LED_INDEX                 5
#define D14_B_LED_INDEX                 4

#define D13_R_LED_INDEX                 0
#define D13_G_LED_INDEX                 2
#define D13_B_LED_INDEX                 1
#else /* USE_BREADBOARD */
#endif /* USE_BREADBOARD */


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

/**
 * @brief Definition for HEADER_RS232 UART connection
 */ 
   
#define CONSOLEPORT_BAUDRATE                       115200
#define CONSOLEPORT_USART			   EVAL_COM1
#define CONSOLEPORT_UART_CLK                       EVAL_COM1_CLK
#define CONSOLEPORT_UART_TX_PIN                    EVAL_COM1_TX_PIN
#define CONSOLEPORT_UART_TX_GPIO_PORT              EVAL_COM1_TX_GPIO_PORT
#define CONSOLEPORT_UART_TX_GPIO_CLK               EVAL_COM1_TX_GPIO_CLK
#define CONSOLEPORT_UART_TX_SOURCE                 EVAL_COM1_TX_SOURCE
#define CONSOLEPORT_UART_TX_AF                     EVAL_COM1_TX_AF
#define CONSOLEPORT_UART_RX_PIN                    EVAL_COM1_RX_PIN
#define CONSOLEPORT_UART_RX_GPIO_PORT              EVAL_COM1_RX_GPIO_PORT
#define CONSOLEPORT_UART_RX_GPIO_CLK               EVAL_COM1_RX_GPIO_CLK
#define CONSOLEPORT_UART_RX_SOURCE                 EVAL_COM1_RX_SOURCE
#define CONSOLEPORT_UART_RX_AF                     EVAL_COM1_RX_AF 
#define CONSOLEPORT_UART_IRQn                      EVAL_COM1_IRQn

/**
 * @brief Definition for RTC Battery monitor
 */
#define RTC_BATTERY_ADC_CHANNEL                 ADC_Channel_18

/**
 * @brief Definition for Internal Temperature Sensor
 */
#define ITS_ADC_CHANNEL                         ADC_Channel_16

#define I2Cn    3

/* I2C io extenders */
#ifdef USE_BREADBOARD
  #define PCA9952_I2C_BUS                      BUS_I2C3
  #define PCA9952_I2C                          I2C3
  #define PCA9952_I2C_CLK                      RCC_APB1Periph_I2C3
  #define PCA9952_I2C_SCL_PIN                  GPIO_Pin_8
  #define PCA9952_I2C_SCL_GPIO_PORT            GPIOA
  #define PCA9952_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOA
  #define PCA9952_I2C_SCL_SOURCE               GPIO_PinSource8
  #define PCA9952_I2C_SCL_AF                   GPIO_AF_I2C3
  #define PCA9952_I2C_SDA_PIN                  GPIO_Pin_9
  #define PCA9952_I2C_SDA_GPIO_PORT            GPIOC
  #define PCA9952_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOC
  #define PCA9952_I2C_SDA_SOURCE               GPIO_PinSource9
  #define PCA9952_I2C_SDA_AF                   GPIO_AF_I2C3
#else /* USE_BREADBOARD */
  #define PCA9952_I2C_BUS                      BUS_I2C1
  #define PCA9952_I2C                          I2C1
  #define PCA9952_I2C_CLK                      RCC_APB1Periph_I2C1
  #define PCA9952_I2C_SCL_PIN                  GPIO_Pin_8
  #define PCA9952_I2C_SCL_GPIO_PORT            GPIOB
  #define PCA9952_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
  #define PCA9952_I2C_SCL_SOURCE               GPIO_PinSource8
  #define PCA9952_I2C_SCL_AF                   GPIO_AF_I2C1
  #define PCA9952_I2C_SDA_PIN                  GPIO_Pin_9
  #define PCA9952_I2C_SDA_GPIO_PORT            GPIOB
  #define PCA9952_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
  #define PCA9952_I2C_SDA_SOURCE               GPIO_PinSource9
  #define PCA9952_I2C_SDA_AF                   GPIO_AF_I2C1
#endif /* USE_BREADBOARD */

#ifdef USE_BREADBOARD
  #define PCA9952_I2C_SPEED                    50000  
#else /* USE_BREADBOARD */
  #define PCA9952_I2C_SPEED                    95000  
#endif /* USE_BREADBOARD */

#ifdef USE_BREADBOARD
  #define PCA9952_MAIN_ADDR                     (0x60<<1)
#else /* USE_BREADBOARD */
  #define PCA9952_MAIN_ADDR                     (0x62<<1)
  #define PCA9952_BAR1_ADDR                     (0x60<<1)
  #define PCA9952_BAR2_ADDR                     (0x61<<1)
#endif /* USE_BREADBOARD */

#define CU_REGIME_INPUT                         0x0001
#define CU_OIL_INPUT                            0x0002
#define CU_EMBRAY_INPUT                         0x0004
#define CU_GAZ_INPUT                            0x0008
#define CU_NEUTRAL_INPUT                        0x0010
#define CU_RAPPORTp_INPUT                       0x0020
#define CU_RAPPORTm_INPUT                       0x0040
#define CU_SHIFTER_INPUT                        0x0080
#define CU_CAME_INPUT                           0x0100
#define CU_RESERVED1_INPUT                      0x0200
#define CU_RESERVED2_INPUT                      0x0400
#define CU_RESERVED3_INPUT                      0x0500
#define CU_PALG_INPUT                           0x1000
#define CU_PALD_INPUT                           0x2000
#define CU_MODE0_INPUT                          0x4000
#define CU_MODE1_INPUT                          0x8000

#ifdef USE_BREADBOARD
  #define REGIME_INPUT_PUPD                               GPIO_PuPd_UP 
  #define REGIME_INPUT_PIN                                GPIO_Pin_6
  #define REGIME_INPUT_GPIO_PORT                          GPIOC
  #define REGIME_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
  #define REGIME_INPUT_EXTI_LINE                            EXTI_Line6
  #define REGIME_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define REGIME_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define REGIME_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define OIL_INPUT_PUPD                                  GPIO_PuPd_UP 
  #define OIL_INPUT_PIN                                   GPIO_Pin_6
  #define OIL_INPUT_GPIO_PORT                             GPIOC
  #define OIL_INPUT_GPIO_CLK                              RCC_AHB1Periph_GPIOC 
  #define OIL_INPUT_EXTI_LINE                            EXTI_Line6
  #define OIL_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define OIL_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define OIL_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define EMBRAY_INPUT_PUPD                               GPIO_PuPd_UP 
  #define EMBRAY_INPUT_PIN                                GPIO_Pin_6
  #define EMBRAY_INPUT_GPIO_PORT                          GPIOC
  #define EMBRAY_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
  #define EMBRAY_INPUT_EXTI_LINE                            EXTI_Line6
  #define EMBRAY_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define EMBRAY_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define EMBRAY_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define GAZ_INPUT_PUPD                                  GPIO_PuPd_UP 
  #define GAZ_INPUT_PIN                                   GPIO_Pin_6
  #define GAZ_INPUT_GPIO_PORT                             GPIOC
  #define GAZ_INPUT_GPIO_CLK                              RCC_AHB1Periph_GPIOC 
  #define GAZ_INPUT_EXTI_LINE                            EXTI_Line6
  #define GAZ_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define GAZ_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define GAZ_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define NEUTRAL_INPUT_PUPD                              GPIO_PuPd_UP 
  #define NEUTRAL_INPUT_PIN                               GPIO_Pin_6
  #define NEUTRAL_INPUT_GPIO_PORT                         GPIOC
  #define NEUTRAL_INPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOC
  #define NEUTRAL_INPUT_EXTI_LINE                            EXTI_Line6
  #define NEUTRAL_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define NEUTRAL_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define NEUTRAL_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_NEUTRAL_BIT                      BIT6

  #define RAPPORTp_INPUT_PUPD                             GPIO_PuPd_UP 
  #define RAPPORTp_INPUT_PIN                              GPIO_Pin_6
  #define RAPPORTp_INPUT_GPIO_PORT                        GPIOC
  #define RAPPORTp_INPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOC 
  #define RAPPORTp_INPUT_EXTI_LINE                            EXTI_Line6
  #define RAPPORTp_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define RAPPORTp_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define RAPPORTp_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
   
  #define RAPPORTm_INPUT_PUPD                             GPIO_PuPd_UP 
  #define RAPPORTm_INPUT_PIN                              GPIO_Pin_6
  #define RAPPORTm_INPUT_GPIO_PORT                        GPIOC
  #define RAPPORTm_INPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOC 
  #define RAPPORTm_INPUT_EXTI_LINE                            EXTI_Line6
  #define RAPPORTm_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define RAPPORTm_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define RAPPORTm_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define SHIFTER_INPUT_PUPD                              GPIO_PuPd_UP 
  #define SHIFTER_INPUT_PIN                               GPIO_Pin_6
  #define SHIFTER_INPUT_GPIO_PORT                         GPIOC
  #define SHIFTER_INPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOC 
  #define SHIFTER_INPUT_EXTI_LINE                            EXTI_Line6
  #define SHIFTER_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define SHIFTER_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define SHIFTER_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define CAME_INPUT_PUPD                                 GPIO_PuPd_UP 
  #define CAME_INPUT_PIN                                  GPIO_Pin_10
  #define CAME_INPUT_GPIO_PORT                            GPIOB
  #define CAME_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOB
  #define CAME_INPUT_EXTI_LINE                            EXTI_Line10
  #define CAME_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define CAME_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource10
  #define CAME_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_CAME_BIT                      BIT10

  #define RESERVED1_INPUT_PUPD                            GPIO_PuPd_UP 
  #define RESERVED1_INPUT_PIN                             GPIO_Pin_6
  #define RESERVED1_INPUT_GPIO_PORT                       GPIOC
  #define RESERVED1_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOC 
  
  #define RESERVED2_INPUT_PUPD                            GPIO_PuPd_UP 
  #define RESERVED2_INPUT_PIN                             GPIO_Pin_6
  #define RESERVED2_INPUT_GPIO_PORT                       GPIOC
  #define RESERVED2_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOC
  
  #define RESERVED3_INPUT_PUPD                            GPIO_PuPd_UP 
  #define RESERVED3_INPUT_PIN                             GPIO_Pin_6
  #define RESERVED3_INPUT_GPIO_PORT                       GPIOC
  #define RESERVED3_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOC

  #define PALG_INPUT_PUPD                                 GPIO_PuPd_UP 
  #define PALG_INPUT_PIN                                  GPIO_Pin_6
  #define PALG_INPUT_GPIO_PORT                            GPIOC
  #define PALG_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOC
  #define PALG_INPUT_EXTI_LINE                            EXTI_Line6
  #define PALG_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define PALG_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define PALG_INPUT_EXTI_IRQn                            EXTI9_5_IRQn

  #define PALD_INPUT_PUPD                                 GPIO_PuPd_UP 
  #define PALD_INPUT_PIN                                  GPIO_Pin_0
  #define PALD_INPUT_GPIO_PORT                            GPIOC
  #define PALD_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOC 
  #define PALD_INPUT_EXTI_LINE                            EXTI_Line0
  #define PALD_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define PALD_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource0
  #define PALD_INPUT_EXTI_IRQn                            EXTI0_IRQn

  #define MODE0_INPUT_PUPD                                GPIO_PuPd_UP 
  #define MODE0_INPUT_PIN                                 GPIO_Pin_8
  #define MODE0_INPUT_GPIO_PORT                           GPIOC
  #define MODE0_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC 

  #define MODE1_INPUT_PUPD                                GPIO_PuPd_UP 
  #define MODE1_INPUT_PIN                                 GPIO_Pin_6              
  #define MODE1_INPUT_GPIO_PORT                           GPIOC
  #define MODE1_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC 
   
  #define BUT_SP_INPUT_PUPD                               GPIO_PuPd_UP 
  #define BUT_SP_INPUT_PIN                                GPIO_Pin_6              
  #define BUT_SP_INPUT_GPIO_PORT                          GPIOC
  #define BUT_SP_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
   
  #define BUT_ST_INPUT_PUPD                               GPIO_PuPd_UP
  #define BUT_ST_INPUT_PIN                                GPIO_Pin_6              
  #define BUT_ST_INPUT_GPIO_PORT                          GPIOC
  #define BUT_ST_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
   
  #define BUT_N_INPUT_PUPD                                GPIO_PuPd_UP
  #define BUT_N_INPUT_PIN                                 GPIO_Pin_6              
  #define BUT_N_INPUT_GPIO_PORT                           GPIOC
  #define BUT_N_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC 
   
  #define VREG_INPUT_PUPD                                 GPIO_PuPd_NOPULL
  #define VREG_INPUT_PIN                                  GPIO_Pin_1              
  #define VREG_INPUT_GPIO_PORT                            GPIOB
  #define VREG_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOB 
#else /* USE_BREADBOARD */
  #define REGIME_INPUT_PUPD                               GPIO_PuPd_NOPULL 
  #define REGIME_INPUT_PIN                                GPIO_Pin_7
  #define REGIME_INPUT_GPIO_PORT                          GPIOC
  #define REGIME_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
  #define REGIME_INPUT_EXTI_LINE                            EXTI_Line7
  #define REGIME_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define REGIME_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource7
  #define REGIME_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_REGIME_BIT                      BIT7

  #define OIL_INPUT_PUPD                                  GPIO_PuPd_NOPULL 
  #define OIL_INPUT_PIN                                   GPIO_Pin_14
  #define OIL_INPUT_GPIO_PORT                             GPIOB
  #define OIL_INPUT_GPIO_CLK                              RCC_AHB1Periph_GPIOB 
  #define OIL_INPUT_EXTI_LINE                            EXTI_Line14
  #define OIL_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define OIL_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource14
  #define OIL_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_OIL_BIT                      BIT14

  #define EMBRAY_INPUT_PUPD                               GPIO_PuPd_NOPULL 
  #define EMBRAY_INPUT_PIN                                GPIO_Pin_15
  #define EMBRAY_INPUT_GPIO_PORT                          GPIOB
  #define EMBRAY_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOB 
  #define EMBRAY_INPUT_EXTI_LINE                            EXTI_Line15
  #define EMBRAY_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define EMBRAY_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource15
  #define EMBRAY_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_EMBRAY_BIT                      BIT15

  #define GAZ_INPUT_PUPD                                  GPIO_PuPd_NOPULL 
  #define GAZ_INPUT_PIN                                   GPIO_Pin_3
  #define GAZ_INPUT_GPIO_PORT                             GPIOC
  #define GAZ_INPUT_GPIO_CLK                              RCC_AHB1Periph_GPIOC 
  #define GAZ_INPUT_EXTI_LINE                            EXTI_Line3
  #define GAZ_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define GAZ_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource3
  #define GAZ_INPUT_EXTI_IRQn                            EXTI3_IRQn
  #define CU_INPUT_EVENT_GAZ_BIT                      BIT3

  #define NEUTRAL_INPUT_PUPD                              GPIO_PuPd_NOPULL 
  #define NEUTRAL_INPUT_PIN                               GPIO_Pin_6
  #define NEUTRAL_INPUT_GPIO_PORT                         GPIOC
  #define NEUTRAL_INPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOC
  #define NEUTRAL_INPUT_EXTI_LINE                            EXTI_Line6
  #define NEUTRAL_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define NEUTRAL_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define NEUTRAL_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_NEUTRAL_BIT                      BIT6

  #define RAPPORTp_INPUT_PUPD                             GPIO_PuPd_NOPULL 
  #define RAPPORTp_INPUT_PIN                              GPIO_Pin_4
  #define RAPPORTp_INPUT_GPIO_PORT                        GPIOA
  #define RAPPORTp_INPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOA
  #define RAPPORTp_INPUT_EXTI_LINE                            EXTI_Line4
  #define RAPPORTp_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define RAPPORTp_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource4
  #define RAPPORTp_INPUT_EXTI_IRQn                            EXTI4_IRQn
  #define CU_INPUT_EVENT_RAPPORTp_BIT                      BIT4

  #define RAPPORTm_INPUT_PUPD                             GPIO_PuPd_NOPULL 
  #define RAPPORTm_INPUT_PIN                              GPIO_Pin_1
  #define RAPPORTm_INPUT_GPIO_PORT                        GPIOA
  #define RAPPORTm_INPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOA 
  #define RAPPORTm_INPUT_EXTI_LINE                            EXTI_Line1
  #define RAPPORTm_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define RAPPORTm_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource1
  #define RAPPORTm_INPUT_EXTI_IRQn                            EXTI1_IRQn
  #define CU_INPUT_EVENT_RAPPORTm_BIT                      BIT1

  #define SHIFTER_INPUT_PUPD                              GPIO_PuPd_NOPULL 
  #define SHIFTER_INPUT_PIN                               GPIO_Pin_12
  #define SHIFTER_INPUT_GPIO_PORT                         GPIOB
  #define SHIFTER_INPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOB 
  #define SHIFTER_INPUT_EXTI_LINE                            EXTI_Line12
  #define SHIFTER_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define SHIFTER_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource12
  #define SHIFTER_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_SHIFTER_BIT                      BIT12

  #define CAME_INPUT_PUPD                                 GPIO_PuPd_NOPULL 
  #define CAME_INPUT_PIN                                  GPIO_Pin_13
  #define CAME_INPUT_GPIO_PORT                            GPIOB
  #define CAME_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOB
  #define CAME_INPUT_EXTI_LINE                            EXTI_Line13
  #define CAME_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define CAME_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define CAME_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_CAME_BIT                      BIT13

  #define RESERVED1_INPUT_PUPD                            GPIO_PuPd_NOPULL 
  #define RESERVED1_INPUT_PIN                             GPIO_Pin_5
  #define RESERVED1_INPUT_GPIO_PORT                       GPIOA
  #define RESERVED1_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOA
  #define RESERVED1_INPUT_EXTI_LINE                            EXTI_Line13
  #define RESERVED1_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define RESERVED1_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define RESERVED1_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_RESERVED1_BIT                      BIT5
  
  #define RESERVED2_INPUT_PUPD                            GPIO_PuPd_NOPULL 
  #define RESERVED2_INPUT_PIN                             GPIO_Pin_6
  #define RESERVED2_INPUT_GPIO_PORT                       GPIOA
  #define RESERVED2_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOA
  #define RESERVED2_INPUT_EXTI_LINE                            EXTI_Line13
  #define RESERVED2_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define RESERVED2_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define RESERVED2_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_RESERVED2_BIT                      BIT6
  
  #define RESERVED3_INPUT_PUPD                            GPIO_PuPd_NOPULL 
  #define RESERVED3_INPUT_PIN                             GPIO_Pin_2
  #define RESERVED3_INPUT_GPIO_PORT                       GPIOA
  #define RESERVED3_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOA
  #define RESERVED3_INPUT_EXTI_LINE                            EXTI_Line13
  #define RESERVED3_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define RESERVED3_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define RESERVED3_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_RESERVED3_BIT                      BIT2

  #define PALG_INPUT_PUPD                                 GPIO_PuPd_NOPULL 
  #define PALG_INPUT_PIN                                  GPIO_Pin_8
  #define PALG_INPUT_GPIO_PORT                            GPIOA
  #define PALG_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOA
  #define PALG_INPUT_EXTI_LINE                            EXTI_Line13
  #define PALG_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define PALG_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define PALG_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_PALG_BIT                      BIT8

  #define PALD_INPUT_PUPD                                 GPIO_PuPd_NOPULL 
  #define PALD_INPUT_PIN                                  GPIO_Pin_0
  #define PALD_INPUT_GPIO_PORT                            GPIOC
  #define PALD_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOC 
  #define PALD_INPUT_EXTI_LINE                            EXTI_Line13
  #define PALD_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOB
  #define PALD_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource13
  #define PALD_INPUT_EXTI_IRQn                            EXTI15_10_IRQn
  #define CU_INPUT_EVENT_PALD_BIT                      BIT0

  #define MODE0_INPUT_PUPD                                GPIO_PuPd_NOPULL 
  #define MODE0_INPUT_PIN                                 GPIO_Pin_8
  #define MODE0_INPUT_GPIO_PORT                           GPIOC
  #define MODE0_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC 

  #define MODE1_INPUT_PUPD                                GPIO_PuPd_NOPULL 
  #define MODE1_INPUT_PIN                                 GPIO_Pin_9              
  #define MODE1_INPUT_GPIO_PORT                           GPIOC
  #define MODE1_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC  
   
  #define BUT_SP_INPUT_PUPD                               GPIO_PuPd_NOPULL 
  #define BUT_SP_INPUT_PIN                                GPIO_Pin_2              
  #define BUT_SP_INPUT_GPIO_PORT                          GPIOC
  #define BUT_SP_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
   
  #define BUT_ST_INPUT_PUPD                               GPIO_PuPd_DOWN
  #define BUT_ST_INPUT_PIN                                GPIO_Pin_5              
  #define BUT_ST_INPUT_GPIO_PORT                          GPIOC
  #define BUT_ST_INPUT_GPIO_CLK                           RCC_AHB1Periph_GPIOC 
   
  #define BUT_N_INPUT_PUPD                                GPIO_PuPd_NOPULL
  #define BUT_N_INPUT_PIN                                 GPIO_Pin_1              
  #define BUT_N_INPUT_GPIO_PORT                           GPIOC
  #define BUT_N_INPUT_GPIO_CLK                            RCC_AHB1Periph_GPIOC 
   
  #define VREG_INPUT_PUPD                                 GPIO_PuPd_NOPULL
  #define VREG_INPUT_PIN                                  GPIO_Pin_1              
  #define VREG_INPUT_GPIO_PORT                            GPIOB
  #define VREG_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOB 
#endif /* USE_BREADBOARD */

/* when using breadboard, MOTEURm_OUTPUT_PIN=DIR, MOTEURp_OUTPUT_PIN=EN */
#ifdef USE_BREADBOARD
  #define MOTEURm_OUTPUT_PIN                              GPIO_Pin_0
  #define MOTEURm_OUTPUT_GPIO_PORT                        GPIOA
  #define MOTEURm_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOA

  #define MOTEURp_OUTPUT_PIN                              GPIO_Pin_14              
  #define MOTEURp_OUTPUT_GPIO_PORT                        GPIOC
  #define MOTEURp_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOC 

  #define STOP_OUTPUT_PIN                               GPIO_Pin_2              
  #define STOP_OUTPUT_GPIO_PORT                         GPIOD
  #define STOP_OUTPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOD 

#else /* USE_BREADBOARD */
  #define MOTEURm_OUTPUT_PIN                              GPIO_Pin_0
  #define MOTEURm_OUTPUT_GPIO_PORT                        GPIOB
  #define MOTEURm_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOB

  #define MOTEURp_OUTPUT_PIN                              GPIO_Pin_4              
  #define MOTEURp_OUTPUT_GPIO_PORT                        GPIOC
  #define MOTEURp_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOC 
   
  #define STOP_OUTPUT_PIN                               GPIO_Pin_4              
  #define STOP_OUTPUT_GPIO_PORT                         GPIOC
  #define STOP_OUTPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOC 
#endif /* USE_BREADBOARD */


    

void LEDs_Init(void);
void CU_LEDInit(Led_TypeDef Led);
void CU_LEDDeInit(Led_TypeDef Led);
void CU_LEDOn(Led_TypeDef Led);
void CU_LEDOff(Led_TypeDef Led);
void CU_LEDToggle(Led_TypeDef Led);
void CU_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct); 
void CU_RNGInit(void);
uint32_t CU_RandomValue(void);
uint8_t Console_LowLevelInit(void);
void I2C_Bus_Init(I2C_List_Typedef I2Cx);
uint16_t CU_ReadInputsRaw(void);
uint8_t CU_IOInit(void);



#endif /* __CU_H__ */
