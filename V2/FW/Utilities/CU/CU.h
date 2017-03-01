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

enum{
  CU_Mode_Manual=1,
  CU_Mode_SemiAuto=2,
  CU_Mode_Auto=3
};


#define LED_BLUE LED3
#define LED_RED LED1
#define LED_GREEN LED2

/* Bargraph RPM constants */
#define CU_RPM_MIN      (float)600 //(raw per minute)
#define CU_RPM_MAX      (float)8000 //(raw per minute)
#define CU_RPM_A        (float)(20/(CU_RPM_MAX-CU_RPM_MIN))
#define CU_RPM_B        (float)( (CU_RPM_MAX-21*CU_RPM_MIN) / (CU_RPM_MAX-CU_RPM_MIN) )



    
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


#define BAR_LED_INTENSITY_GLOBAL_FACTOR (float)(0.3)

#define LED_BLUE_3MM_INTENSITY            25
#define LED_RED_3MM_INTENSITY             40
#define LED_GREEN_3MM_INTENSITY           7
#define LED_RED_5MM_INTENSITY             35
#define LED_GREEN_5MM_INTENSITY           7

#define LED_OIL_IOEXP_OFFSET                2
#define LED_OIL_INTENSITY                   LED_RED_5MM_INTENSITY
#define LED_N_IOEXP_OFFSET                  2
#define LED_N_INTENSITY                     LED_GREEN_5MM_INTENSITY
#define LED_TEMP_IOEXP_OFFSET               2
#define LED_TEMP1_INTENSITY                 LED_BLUE_3MM_INTENSITY
#define LED_TEMP2_INTENSITY                 LED_GREEN_3MM_INTENSITY
#define LED_TEMP3_INTENSITY                 LED_RED_5MM_INTENSITY
#define LED_MODE_IOEXP_OFFSET               0
#define LED_MODE1_INTENSITY                 LED_GREEN_3MM_INTENSITY
#define LED_MODE2_INTENSITY                 LED_BLUE_3MM_INTENSITY
#define LED_MODE3_INTENSITY                 LED_GREEN_3MM_INTENSITY

#define LED_OIL_MASK                           ((uint64_t)0x0000000000000001<<(15+(16*LED_OIL_IOEXP_OFFSET)))
#define LED_N_MASK                             ((uint64_t)0x0000000000000001<<(3+(16*LED_N_IOEXP_OFFSET)))
#define LED_TEMP1_MASK                         ((uint64_t)0x0000000000000001<<(8+(16*LED_TEMP_IOEXP_OFFSET)))
#define LED_TEMP2_MASK                         ((uint64_t)0x0000000000000001<<(9+(16*LED_TEMP_IOEXP_OFFSET)))
#define LED_TEMP3_MASK                         ((uint64_t)0x0000000000000001<<(10+(16*LED_TEMP_IOEXP_OFFSET)))
#define LED_MODE1_MASK                         ((uint64_t)0x0000000000000001<<(8+(16*LED_MODE_IOEXP_OFFSET)))
#define LED_MODE2_MASK                         ((uint64_t)0x0000000000000001<<(9+(16*LED_MODE_IOEXP_OFFSET)))
#define LED_MODE3_MASK                         ((uint64_t)0x0000000000000001<<(10+(16*LED_MODE_IOEXP_OFFSET)))

#define SEG7_IOEXP_OFFSET               2
/* CU 7 segment display */
#define SEG7_SEG_INTENSITY              40//8
#if (SEG7_SEG_INTENSITY>40)
  #warning SEG7 current limited to 40% (8mA)
  #undef SEG7_SEG_INTENSITY
  #define SEG7_SEG_INTENSITY 40
#endif 
#define SEG7_SEG_A_MASK                 ((uint64_t)0x0000000000000001<<(12+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_B_MASK                 ((uint64_t)0x0000000000000001<<(11+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_C_MASK                 ((uint64_t)0x0000000000000001<<(6+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_D_MASK                 ((uint64_t)0x0000000000000001<<(5+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_E_MASK                 ((uint64_t)0x0000000000000001<<(4+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_F_MASK                 ((uint64_t)0x0000000000000001<<(13+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_G_MASK                 ((uint64_t)0x0000000000000001<<(14+(16*SEG7_IOEXP_OFFSET)))
#define SEG7_SEG_DP_MASK                ((uint64_t)0x0000000000000001<<(7+(16*SEG7_IOEXP_OFFSET)))

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
#define BAR_ALL                         0x3F0FE0FF      //previous value: 0x3F0FE7FF



#define BAR_LED1                        (0x0001<<7) 
#define BAR_LED1_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED2                        (0x0001<<6) 
#define BAR_LED2_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED3                        (0x0001<<5) 
#define BAR_LED3_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED4                        (0x0001<<4) 
#define BAR_LED4_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED5                        (0x0001<<3) 
#define BAR_LED5_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED6                        (0x0001<<2) 
#define BAR_LED6_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED7                        (0x0001<<1)
#define BAR_LED7_INTENSITY              LED_BLUE_3MM_INTENSITY 
#define BAR_LED8                        (0x0001<<0) 
#define BAR_LED8_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED9                        (0x0001<<15) 
#define BAR_LED9_INTENSITY              LED_BLUE_3MM_INTENSITY
#define BAR_LED10                       (0x0001<<14) 
#define BAR_LED10_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED11                       (0x0001<<13) 
#define BAR_LED11_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED12                       (0x0001<<19) 
#define BAR_LED12_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED13                       (0x0001<<18) 
#define BAR_LED13_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED14                       (0x0001<<17) 
#define BAR_LED14_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED15                       (0x0001<<16) 
#define BAR_LED15_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED16                       (0x0001<<29)
#define BAR_LED16_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED17                       (0x0001<<28)
#define BAR_LED17_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED18                       (0x0001<<27) 
#define BAR_LED18_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED19                       (0x0001<<26) 
#define BAR_LED19_INTENSITY             LED_GREEN_3MM_INTENSITY
#define BAR_LED20                       (0x0001<<25) 
#define BAR_LED20_INTENSITY             LED_RED_3MM_INTENSITY
#define BAR_LED21                       (0x0001<<24) 
#define BAR_LED21_INTENSITY             LED_RED_3MM_INTENSITY                           
#endif /* USE_BREADBOARD */


#define COMn                             2

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource9
#define EVAL_COM1_TX_AF                  GPIO_AF_USART1
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource10
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
#define TEMP_IN_ADC_CHANNEL                     ADC_Channel_8
#define VREG_ADC_CHANNEL                        ADC_Channel_9


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
#define CU_RESERVED3_INPUT                      0x0800
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
  #define RESERVED1_INPUT_EXTI_LINE                            EXTI_Line5
  #define RESERVED1_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define RESERVED1_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource5
  #define RESERVED1_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_RESERVED1_BIT                      BIT5
  
  #define RESERVED2_INPUT_PUPD                            GPIO_PuPd_NOPULL 
  #define RESERVED2_INPUT_PIN                             GPIO_Pin_6
  #define RESERVED2_INPUT_GPIO_PORT                       GPIOA
  #define RESERVED2_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOA
  #define RESERVED2_INPUT_EXTI_LINE                            EXTI_Line6
  #define RESERVED2_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define RESERVED2_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource6
  #define RESERVED2_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_RESERVED2_BIT                      BIT6
  
  #define RESERVED3_INPUT_PUPD                            GPIO_PuPd_NOPULL 
  #define RESERVED3_INPUT_PIN                             GPIO_Pin_2
  #define RESERVED3_INPUT_GPIO_PORT                       GPIOA
  #define RESERVED3_INPUT_GPIO_CLK                        RCC_AHB1Periph_GPIOA
  #define RESERVED3_INPUT_EXTI_LINE                            EXTI_Line2
  #define RESERVED3_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define RESERVED3_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource2
  #define RESERVED3_INPUT_EXTI_IRQn                            EXTI2_IRQn
  #define CU_INPUT_EVENT_RESERVED3_BIT                      BIT2

  #define PALG_INPUT_PUPD                                 GPIO_PuPd_NOPULL 
  #define PALG_INPUT_PIN                                  GPIO_Pin_8
  #define PALG_INPUT_GPIO_PORT                            GPIOA
  #define PALG_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOA
  #define PALG_INPUT_EXTI_LINE                            EXTI_Line8
  #define PALG_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOA
  #define PALG_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource8
  #define PALG_INPUT_EXTI_IRQn                            EXTI9_5_IRQn
  #define CU_INPUT_EVENT_PALG_BIT                      BIT8

  #define PALD_INPUT_PUPD                                 GPIO_PuPd_NOPULL 
  #define PALD_INPUT_PIN                                  GPIO_Pin_0
  #define PALD_INPUT_GPIO_PORT                            GPIOC
  #define PALD_INPUT_GPIO_CLK                             RCC_AHB1Periph_GPIOC 
  #define PALD_INPUT_EXTI_LINE                            EXTI_Line0
  #define PALD_INPUT_EXTI_PORT_SOURCE                     EXTI_PortSourceGPIOC
  #define PALD_INPUT_EXTI_PIN_SOURCE                      EXTI_PinSource0
  #define PALD_INPUT_EXTI_IRQn                            EXTI0_IRQn
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

  #define TEMP_IN_INPUT_PUPD                              GPIO_PuPd_NOPULL 
  #define TEMP_IN_INPUT_PIN                               GPIO_Pin_0
  #define TEMP_IN_INPUT_GPIO_PORT                         GPIOB
  #define TEMP_IN_INPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOB
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
  #define MOTEURm_OUTPUT_PIN                              GPIO_Pin_3
  #define MOTEURm_OUTPUT_GPIO_PORT                        GPIOA
  #define MOTEURm_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOA

  #define MOTEURp_OUTPUT_PIN                              GPIO_Pin_7              
  #define MOTEURp_OUTPUT_GPIO_PORT                        GPIOA
  #define MOTEURp_OUTPUT_GPIO_CLK                         RCC_AHB1Periph_GPIOA 
   
  #define STOP_OUTPUT_PIN                               GPIO_Pin_4              
  #define STOP_OUTPUT_GPIO_PORT                         GPIOC
  #define STOP_OUTPUT_GPIO_CLK                          RCC_AHB1Periph_GPIOC 
#endif /* USE_BREADBOARD */

/*******Serial FLASH********/
#define FLASH_SPI                       SPI3
#define FLASH_SPI_CLK                   RCC_APB1Periph_SPI3

#define FLASH_SPI_SCK_PIN               GPIO_Pin_10                  /* PC.10 */
#define FLASH_SPI_SCK_GPIO_PORT         GPIOC                       /* GPIOC */
#define FLASH_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define FLASH_SPI_SCK_SOURCE            GPIO_PinSource10
#define FLASH_SPI_SCK_AF                GPIO_AF_SPI3

#define FLASH_SPI_MISO_PIN              GPIO_Pin_11                  /* PC.11 */
#define FLASH_SPI_MISO_GPIO_PORT        GPIOC                       /* GPIOC */
#define FLASH_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOC
#define FLASH_SPI_MISO_SOURCE           GPIO_PinSource11
#define FLASH_SPI_MISO_AF               GPIO_AF_SPI3

#define FLASH_SPI_MOSI_PIN              GPIO_Pin_12                  /* PC.12 */
#define FLASH_SPI_MOSI_GPIO_PORT        GPIOC                       /* GPIOC */
#define FLASH_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOC
#define FLASH_SPI_MOSI_SOURCE           GPIO_PinSource12
#define FLASH_SPI_MOSI_AF               GPIO_AF_SPI3

#define FLASH_SPI_CS_PIN                GPIO_Pin_15                  /* PA.15 */
#define FLASH_SPI_CS_GPIO_PORT          GPIOA                       /* GPIOA */
#define FLASH_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOA


    

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
uint8_t CU_LEDsInit(float intensityPercent);
uint8_t CU_LEDsSetIntensity(float intensity);
uint8_t CU_GetMode(void);
uint8_t CU_GetOilWarning(void);
uint8_t CU_GetStopButton(void);
uint8_t CU_GetStartButton(void);
uint8_t CU_GetNeutralButton(void);
uint8_t CU_GetShifterInput(void);
uint8_t CU_GetEmbrayInput(void);
uint8_t CU_GetNeutralInput(void);
uint8_t CU_GetCameInput(void);
void CU_STOP_On(void);
void CU_STOP_Off(void);
uint8_t CU_RPMToBargraph(void);
void CU_MX25L1606E_LowLevel_Init(void);
void CU_MX25L1606E_transfer(uint8_t *buffer,uint32_t length,uint8_t immediateCSRelease);
void CU_MX25L1606E_CS(uint8_t state);




#endif /* __CU_H__ */
