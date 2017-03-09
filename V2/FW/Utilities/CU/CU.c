#include "CU.h"
#include "main.h"
#include "stm32f2xx_it.h"

GPIO_TypeDef* GPIO_PORT[IOn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[IOn] = {LED1_PIN, LED2_PIN, LED3_PIN};
const uint32_t GPIO_CLK[IOn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1,EVAL_COM2}; 
GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT,EVAL_COM2_TX_GPIO_PORT};
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT,EVAL_COM2_RX_GPIO_PORT};
const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK,EVAL_COM2_CLK};
const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK,EVAL_COM2_TX_GPIO_CLK};
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK,EVAL_COM2_RX_GPIO_CLK};
const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN,EVAL_COM2_TX_PIN};
const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN,EVAL_COM2_RX_PIN};
const uint8_t COM_TX_PIN_SOURCE[COMn] = {EVAL_COM1_TX_SOURCE,EVAL_COM2_TX_SOURCE};
const uint8_t COM_RX_PIN_SOURCE[COMn] = {EVAL_COM1_RX_SOURCE,EVAL_COM2_RX_SOURCE};
const uint8_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF,EVAL_COM2_TX_AF};
const uint8_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF,EVAL_COM2_RX_AF};
const uint16_t COM_IRQn[COMn] = {EVAL_COM1_IRQn, EVAL_COM2_IRQn};

I2C_TypeDef * I2C_PERIPH[I2Cn] = {PCA9952_I2C,PCA9952_I2C,PCA9952_I2C};
const uint32_t I2C_CLK[I2Cn] = {PCA9952_I2C_CLK,PCA9952_I2C_CLK,PCA9952_I2C_CLK};
const uint16_t I2C_SCL_PIN[I2Cn] = {PCA9952_I2C_SCL_PIN,PCA9952_I2C_SCL_PIN,PCA9952_I2C_SCL_PIN};
GPIO_TypeDef* I2C_SCL_GPIO_PORT[I2Cn] = {PCA9952_I2C_SCL_GPIO_PORT,PCA9952_I2C_SCL_GPIO_PORT,PCA9952_I2C_SCL_GPIO_PORT};
const uint32_t I2C_SCL_GPIO_CLK[I2Cn] = {PCA9952_I2C_SCL_GPIO_CLK,PCA9952_I2C_SCL_GPIO_CLK,PCA9952_I2C_SCL_GPIO_CLK};
const uint8_t I2C_SCL_SOURCE[I2Cn] = {PCA9952_I2C_SCL_SOURCE,PCA9952_I2C_SCL_SOURCE,PCA9952_I2C_SCL_SOURCE};
const uint8_t I2C_SCL_AF[I2Cn] = {PCA9952_I2C_SCL_AF,PCA9952_I2C_SCL_AF,PCA9952_I2C_SCL_AF};
const uint16_t I2C_SDA_PIN[I2Cn] = {PCA9952_I2C_SDA_PIN,PCA9952_I2C_SDA_PIN,PCA9952_I2C_SDA_PIN};
GPIO_TypeDef* I2C_SDA_GPIO_PORT[I2Cn] = {PCA9952_I2C_SDA_GPIO_PORT,PCA9952_I2C_SDA_GPIO_PORT,PCA9952_I2C_SDA_GPIO_PORT};
const uint32_t I2C_SDA_GPIO_CLK[I2Cn] = {PCA9952_I2C_SDA_GPIO_CLK,PCA9952_I2C_SDA_GPIO_CLK,PCA9952_I2C_SDA_GPIO_CLK};
const uint8_t I2C_SDA_SOURCE[I2Cn] = {PCA9952_I2C_SDA_SOURCE,PCA9952_I2C_SDA_SOURCE,PCA9952_I2C_SDA_SOURCE};
const uint8_t I2C_SDA_AF[I2Cn] = {PCA9952_I2C_SDA_AF,PCA9952_I2C_SDA_AF,PCA9952_I2C_SDA_AF};
const uint32_t I2C_SPEED[I2Cn] = {PCA9952_I2C_SPEED,PCA9952_I2C_SPEED,PCA9952_I2C_SPEED};

uint64_t CU_CommonLeds_table[16]={SEG7_SEG_A_MASK,
                                  SEG7_SEG_B_MASK,
                                  SEG7_SEG_C_MASK,
                                  SEG7_SEG_D_MASK,
                                  SEG7_SEG_E_MASK,
                                  SEG7_SEG_F_MASK,
                                  SEG7_SEG_G_MASK,
                                  SEG7_SEG_DP_MASK,
                                  LED_TEMP1_MASK,
                                  LED_TEMP2_MASK,
                                  LED_TEMP3_MASK,
                                  LED_MODE1_MASK,
                                  LED_MODE2_MASK,
                                  LED_MODE3_MASK,
                                  LED_N_MASK,
                                  LED_OIL_MASK};

uint32_t CU_CommonLeds_intensity[16]={SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      SEG7_SEG_INTENSITY,
                                      LED_TEMP1_INTENSITY,
                                      LED_TEMP2_INTENSITY,
                                      LED_TEMP3_INTENSITY,
                                      LED_MODE1_INTENSITY,
                                      LED_MODE2_INTENSITY,
                                      LED_MODE3_INTENSITY,
                                      LED_N_INTENSITY,
                                      LED_OIL_INTENSITY};
                                  
                                  

uint32_t CU_bargraph_table[21]={ BAR_LED1,
                              BAR_LED2,
                              BAR_LED3,
                              BAR_LED4,
                              BAR_LED5,
                              BAR_LED6,
                              BAR_LED7,
                              BAR_LED8,
                              BAR_LED9,
                              BAR_LED10,
                              BAR_LED11,
                              BAR_LED12,
                              BAR_LED13,
                              BAR_LED14,
                              BAR_LED15,
                              BAR_LED16,
                              BAR_LED17,
                              BAR_LED18,
                              BAR_LED19,
                              BAR_LED20,
                              BAR_LED21};

uint32_t CU_bargraph_intensity[21]={ (uint32_t)((float)BAR_LED1_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED2_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED3_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED4_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED5_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED6_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED7_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED8_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED9_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED10_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED11_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED12_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED13_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED14_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED15_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED16_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED17_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED18_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED19_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED20_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/),
                                     (uint32_t)((float)BAR_LED21_INTENSITY/**BAR_LED_INTENSITY_GLOBAL_FACTOR*/)};

//void Console_Rx_Task(void * pvParameters);
//xSemaphoreHandle Console_rx_sem;
//uint8_t ConsoleRXBuf[50];
//uint8_t ConsoleRXPtr=0;
//uint8_t ConsoleRXReady=0;

uint8_t CU_Mode=CU_Mode_Manual;

/*void LEDs_Init(void)
{
  
  CU_LEDInit(LED_BLUE);
  CU_LEDInit(LED_RED);
  CU_LEDInit(LED_GREEN);

  CU_LEDOn(LED_BLUE);
  CU_LEDOn(LED_RED);
  CU_LEDOn(LED_GREEN);

  CU_LEDOff(LED_BLUE);
  CU_LEDOff(LED_RED);
  CU_LEDOff(LED_GREEN);
}*/

/*void CU_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  

  RCC_AHB1PeriphClockCmd(GPIO_CLK[Led], ENABLE);



  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
  
  CU_LEDOn(Led);
  CU_LEDOff(Led);
}*/

/*void CU_LEDDeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  

  RCC_AHB1PeriphClockCmd(GPIO_CLK[Led], ENABLE);
  

  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}*/

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
/*void CU_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRH = GPIO_PIN[Led]; 
}*/

void CU_STOP_On(void)
{
  GPIO_SetBits(STOP_OUTPUT_GPIO_PORT,STOP_OUTPUT_PIN);
}

void CU_STOP_Off(void)
{
  GPIO_ResetBits(STOP_OUTPUT_GPIO_PORT,STOP_OUTPUT_PIN);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
/*void CU_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRL = GPIO_PIN[Led]; 
}*/

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
/*void CU_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}*/

void CU_RNGInit(void)
{
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
  RNG_Cmd(ENABLE);
}

uint32_t CU_RandomValue(void)
{
  while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
  {
  }
  return RNG_GetRandomNumber();
}


uint8_t Console_LowLevelInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CONSOLEPORT_UART_TX_GPIO_CLK | CONSOLEPORT_UART_RX_GPIO_CLK, ENABLE);
  
  /* Enable UART peripheral clock */
  if( (CONSOLEPORT_UART_CLK==RCC_APB2Periph_USART1) || (CONSOLEPORT_UART_CLK==RCC_APB2Periph_USART6) )
    RCC_APB2PeriphClockCmd(CONSOLEPORT_UART_CLK, ENABLE);
  else
    RCC_APB1PeriphClockCmd(CONSOLEPORT_UART_CLK, ENABLE);
    
  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(CONSOLEPORT_UART_TX_GPIO_PORT, CONSOLEPORT_UART_TX_SOURCE,CONSOLEPORT_UART_TX_AF);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(CONSOLEPORT_UART_RX_GPIO_PORT, CONSOLEPORT_UART_RX_SOURCE, CONSOLEPORT_UART_RX_AF);
  
  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = CONSOLEPORT_UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CONSOLEPORT_UART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = CONSOLEPORT_UART_RX_PIN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CONSOLEPORT_UART_RX_GPIO_PORT, &GPIO_InitStructure);
  


  /* USART configuration */
  USART_InitStructure.USART_BaudRate=CONSOLEPORT_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(CONSOLEPORT_USART, &USART_InitStructure);
  
  /* USART RX Interrupt enable */
  USART_ITConfig(CONSOLEPORT_USART, USART_IT_RXNE, ENABLE);   
  
  /* Setup NVIC for USART interrupt request */
  NVIC_InitStructure.NVIC_IRQChannel = CONSOLEPORT_UART_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  //vSemaphoreCreateBinary(Console_rx_sem);
  //xTaskCreate(Console_Rx_Task, "ConsoleRX", 3*configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  
  /* Enable USART */
  USART_Cmd(CONSOLEPORT_USART, ENABLE);
  return 0;
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:    
  *     @arg COM1
  *     @arg COM2  
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *   contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void CU_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  if ((COM == COM1))
  {
    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }
  else if(COM == COM2)
  {
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }
  
  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
  
  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
  
  /* USART RX Interrupt enable */
  USART_ITConfig(COM_USART[COM], USART_IT_RXNE, ENABLE);   
  
  /* Setup NVIC for USART interrupt request */
  NVIC_InitStructure.NVIC_IRQChannel = COM_IRQn[COM];
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}

/*void Console_Rx_Task(void * pvParameters)
{
  uint8_t tmpreg=0;
  uint8_t i=0;
  while (1) 
  {
    if (xSemaphoreTake(Console_rx_sem, portMAX_DELAY) == pdTRUE) 
    {
      if(ConsoleRXReady)
      { 
        i=0;
        while(ConsoleRXBuf[i]!='\n')
          CLI_Input(ConsoleRXBuf[i++]);
        CLI_Input(ConsoleRXBuf[i]);
        ConsoleRXReady=0;
      }
    }
  }
  vTaskDelete(NULL);
}*/

void I2C_Bus_Init(I2C_List_Typedef I2Cx)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;

  /* Enable I2C and I2C_GPIO_PORT & Alternate Function clocks */
  RCC_APB1PeriphClockCmd(I2C_CLK[I2Cx], ENABLE);
  RCC_AHB1PeriphClockCmd(I2C_SCL_GPIO_CLK[I2Cx] | I2C_SDA_GPIO_CLK[I2Cx], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Reset I2C IP */
  RCC_APB1PeriphResetCmd(I2C_CLK[I2Cx], ENABLE);
  /* Release reset signal of I2C  */
  RCC_APB1PeriphResetCmd(I2C_CLK[I2Cx], DISABLE);
  
  /* Connect  I2C_SCL*/
  GPIO_PinAFConfig(I2C_SCL_GPIO_PORT[I2Cx], I2C_SCL_SOURCE[I2Cx], I2C_SCL_AF[I2Cx]);
  /* Connect  I2C_SDA*/
  GPIO_PinAFConfig(I2C_SDA_GPIO_PORT[I2Cx], I2C_SDA_SOURCE[I2Cx], I2C_SDA_AF[I2Cx]); 
  
  /* I2C SCL and SDA pins configuration */
  GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN[I2Cx];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
#ifdef USE_BREADBOARD
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
#else /* USE_BREADBOARD */
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
#endif /* USE_BREADBOARD */
  
  GPIO_Init(I2C_SCL_GPIO_PORT[I2Cx], &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN[I2Cx];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
#ifdef USE_BREADBOARD
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
#else /* USE_BREADBOARD */
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
#endif /* USE_BREADBOARD */
  GPIO_Init(I2C_SDA_GPIO_PORT[I2Cx], &GPIO_InitStructure);    

  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED[I2Cx];
  
  /* Enable the I2C peripheral */
  I2C_Cmd(I2C_PERIPH[I2Cx], ENABLE);
  
  /* Initialize the I2C peripheral */
  I2C_Init(I2C_PERIPH[I2Cx] , &I2C_InitStructure);
}

uint8_t CU_LEDsSetIntensity(float intensity)
{
  uint32_t i=0;
  /* Set bargraph LEDs intensity */
  for(i=0;i<21;i++)
  {
    if(CU_bargraph_table[i]>0x8000)
      PCA9952_LED_Intensity_Control(PCA9952_BAR2_ADDR,(CU_bargraph_table[i]>>16),(uint32_t)CU_bargraph_intensity[i]*intensity);
    else
      PCA9952_LED_Intensity_Control(PCA9952_BAR1_ADDR,CU_bargraph_table[i],(uint32_t)CU_bargraph_intensity[i]*intensity);
  }
  
  /* Set other leds intensity */
  for(i=0;i<16;i++)
  {
    if(CU_CommonLeds_table[i]>0xFFFFFFFF)
      PCA9952_LED_Intensity_Control(PCA9952_MAIN_ADDR,(CU_CommonLeds_table[i]>>32),(uint32_t)CU_CommonLeds_intensity[i]*intensity);
    else
      PCA9952_LED_Intensity_Control(PCA9952_BAR1_ADDR,CU_CommonLeds_table[i],(uint32_t)CU_CommonLeds_intensity[i]*intensity);
  }
  return 0;
}

uint8_t CU_LEDsInit(float intensity)
{
#ifdef USE_BREADBOARD
  PCA9952_Init(BUS_I2C3,PCA9952_MAIN_ADDR);
#else /* USE_BREADBOARD */
  PCA9952_Init(BUS_I2C1,PCA9952_MAIN_ADDR);
  PCA9952_Init(BUS_I2C1,PCA9952_BAR1_ADDR);
  PCA9952_Init(BUS_I2C1,PCA9952_BAR2_ADDR);
#endif /* USE_BREADBOARD */
  
  CU_LEDsSetIntensity(intensity);
  return 0;
}

uint8_t CU_IOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    
  /* DIGITAL INPUTS *********************************************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //-->REGIME_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = REGIME_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(REGIME_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =REGIME_INPUT_PIN;
  GPIO_Init(REGIME_INPUT_GPIO_PORT, &GPIO_InitStructure);
  SYSCFG_EXTILineConfig(REGIME_INPUT_EXTI_PORT_SOURCE,REGIME_INPUT_EXTI_PIN_SOURCE);
  /* REGIME_INPUT_PIN EXTI line */
  EXTI_InitStructure.EXTI_Line = REGIME_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = REGIME_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure); 
  
  
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = REGIME_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  //EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = REGIME_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure);   
  
  //-->OIL_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = OIL_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(OIL_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =OIL_INPUT_PIN;
  GPIO_Init(OIL_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(OIL_INPUT_EXTI_PORT_SOURCE,OIL_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = OIL_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  //EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = OIL_INPUT_EXTI_IRQn;
  //NVIC_Init(&NVIC_InitStructure); 
  
  //-->EMBRAY_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = EMBRAY_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(EMBRAY_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =EMBRAY_INPUT_PIN;
  GPIO_Init(EMBRAY_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(EMBRAY_INPUT_EXTI_PORT_SOURCE,EMBRAY_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = EMBRAY_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  //EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EMBRAY_INPUT_EXTI_IRQn;
  //NVIC_Init(&NVIC_InitStructure);   
  
  //-->GAZ_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = GAZ_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(GAZ_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GAZ_INPUT_PIN;
  GPIO_Init(GAZ_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(GAZ_INPUT_EXTI_PORT_SOURCE,GAZ_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = GAZ_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  //EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = GAZ_INPUT_EXTI_IRQn;
  //NVIC_Init(&NVIC_InitStructure);
  
  //-->NEUTRAL_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = NEUTRAL_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(NEUTRAL_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =NEUTRAL_INPUT_PIN;
  GPIO_Init(NEUTRAL_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(NEUTRAL_INPUT_EXTI_PORT_SOURCE,NEUTRAL_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = NEUTRAL_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = NEUTRAL_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure);   
  
  //-->RAPPORTp_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = RAPPORTp_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(RAPPORTp_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RAPPORTp_INPUT_PIN;
  GPIO_Init(RAPPORTp_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(RAPPORTp_INPUT_EXTI_PORT_SOURCE,RAPPORTp_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = RAPPORTp_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = RAPPORTp_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure);
  
  //-->RAPPORTm_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = RAPPORTm_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(RAPPORTm_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RAPPORTm_INPUT_PIN;
  GPIO_Init(RAPPORTm_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(RAPPORTm_INPUT_EXTI_PORT_SOURCE,RAPPORTm_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = RAPPORTm_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = RAPPORTm_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure);
  
  //-->SHIFTER_INPUT_PIN        formerly P2
  GPIO_InitStructure.GPIO_PuPd = SHIFTER_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(SHIFTER_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =SHIFTER_INPUT_PIN;
  GPIO_Init(SHIFTER_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(SHIFTER_INPUT_EXTI_PORT_SOURCE,SHIFTER_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = SHIFTER_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  //EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = SHIFTER_INPUT_EXTI_IRQn;
  //NVIC_Init(&NVIC_InitStructure);
  
  //-->CAME_INPUT_PIN        formerly P1
  GPIO_InitStructure.GPIO_PuPd = CAME_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(CAME_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =CAME_INPUT_PIN;
  GPIO_Init(CAME_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(CAME_INPUT_EXTI_PORT_SOURCE,CAME_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = CAME_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = CAME_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure); 
  
  //-->RESERVED1_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = RESERVED1_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(RESERVED1_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RESERVED1_INPUT_PIN;
  GPIO_Init(RESERVED1_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->RESERVED2_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = RESERVED2_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(RESERVED2_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RESERVED2_INPUT_PIN;
  GPIO_Init(RESERVED2_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->RESERVED3_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = RESERVED3_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(RESERVED3_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RESERVED3_INPUT_PIN;
  GPIO_Init(RESERVED3_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->PALG_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = PALG_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(PALG_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =PALG_INPUT_PIN;
  GPIO_Init(PALG_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(PALG_INPUT_EXTI_PORT_SOURCE,PALG_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = PALG_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = PALG_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure);   
  
  //-->PALD_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = PALD_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(PALD_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =PALD_INPUT_PIN;
  GPIO_Init(PALD_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(PALD_INPUT_EXTI_PORT_SOURCE,PALD_INPUT_EXTI_PIN_SOURCE);
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = PALD_INPUT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_Init(&EXTI_InitStructure);
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = PALD_INPUT_EXTI_IRQn;
  NVIC_Init(&NVIC_InitStructure); 
  
  //-->MODE0_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = MODE0_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(MODE0_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MODE0_INPUT_PIN;
  GPIO_Init(MODE0_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->MODE1_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = MODE1_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(MODE1_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MODE1_INPUT_PIN;
  GPIO_Init(MODE1_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->BUT_SP_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = BUT_SP_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(BUT_ST_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =BUT_SP_INPUT_PIN;
  GPIO_Init(BUT_SP_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->BUT_ST_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHB1PeriphClockCmd(MODE1_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =BUT_ST_INPUT_PIN;
  GPIO_Init(BUT_ST_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->BUT_N_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = BUT_N_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(BUT_N_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =BUT_N_INPUT_PIN;
  GPIO_Init(BUT_N_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  /* ANALOG INPUT ********************************************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //-->VREG_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = VREG_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(VREG_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =VREG_INPUT_PIN;
  GPIO_Init(VREG_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->TEMP_IN_INPUT_PIN
  GPIO_InitStructure.GPIO_PuPd = TEMP_IN_INPUT_PUPD;
  RCC_AHB1PeriphClockCmd(TEMP_IN_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =TEMP_IN_INPUT_PIN;
  GPIO_Init(TEMP_IN_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  /* OUTPUTS **************************************************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_OType= GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //-->MOTEURm_OUTPUT_PIN
  RCC_AHB1PeriphClockCmd(MOTEURm_OUTPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MOTEURm_OUTPUT_PIN;
  GPIO_Init(MOTEURm_OUTPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->MOTEURp_OUTPUT_PIN
  RCC_AHB1PeriphClockCmd(MOTEURp_OUTPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MOTEURp_OUTPUT_PIN;
  GPIO_Init(MOTEURp_OUTPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->STOP_OUTPUT_PIN
  RCC_AHB1PeriphClockCmd(STOP_OUTPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =STOP_OUTPUT_PIN;
  GPIO_Init(STOP_OUTPUT_GPIO_PORT, &GPIO_InitStructure);
  
  return 0;
}

uint8_t CU_GetMode(void)
{
  if(GPIO_ReadInputDataBit(MODE0_INPUT_GPIO_PORT,MODE0_INPUT_PIN) && GPIO_ReadInputDataBit(MODE1_INPUT_GPIO_PORT,MODE1_INPUT_PIN))
  {
    CU_Mode=CU_Mode_Manual;
  }
  else if( GPIO_ReadInputDataBit(MODE0_INPUT_GPIO_PORT,MODE0_INPUT_PIN) && ( !GPIO_ReadInputDataBit(MODE1_INPUT_GPIO_PORT,MODE1_INPUT_PIN) ) )
  {
    CU_Mode=CU_Mode_Auto;
  }
  else if( GPIO_ReadInputDataBit(MODE1_INPUT_GPIO_PORT,MODE1_INPUT_PIN) && ( !GPIO_ReadInputDataBit(MODE0_INPUT_GPIO_PORT,MODE0_INPUT_PIN) ) )
  {
    CU_Mode=CU_Mode_SemiAuto;
  }
  else
    return 0;
  return CU_Mode;
}

uint8_t CU_GetOilWarning(void)
{
  return GPIO_ReadInputDataBit(OIL_INPUT_GPIO_PORT,OIL_INPUT_PIN);
}

uint8_t CU_GetStopButton(void)
{
  return !GPIO_ReadInputDataBit(BUT_SP_INPUT_GPIO_PORT,BUT_SP_INPUT_PIN);
}

uint8_t CU_GetStartButton(void)
{
  return !GPIO_ReadInputDataBit(BUT_ST_INPUT_GPIO_PORT,BUT_ST_INPUT_PIN);
}

uint8_t CU_GetNeutralButton(void)
{
  return !GPIO_ReadInputDataBit(BUT_N_INPUT_GPIO_PORT,BUT_N_INPUT_PIN);
}

uint8_t CU_GetShifterInput(void)
{
  return GPIO_ReadInputDataBit(SHIFTER_INPUT_GPIO_PORT,SHIFTER_INPUT_PIN);
}

uint8_t CU_GetEmbrayInput(void)
{
  return GPIO_ReadInputDataBit(EMBRAY_INPUT_GPIO_PORT,EMBRAY_INPUT_PIN);
}

uint8_t CU_GetNeutralInput(void)
{
  return GPIO_ReadInputDataBit(NEUTRAL_INPUT_GPIO_PORT,NEUTRAL_INPUT_PIN);
}

uint8_t CU_GetCameInput(void)
{
  return GPIO_ReadInputDataBit(CAME_INPUT_GPIO_PORT,CAME_INPUT_PIN);
}

uint16_t CU_ReadInputsRaw(void)
{
  uint16_t InputMask=0x0000;
  
  if(GPIO_ReadInputDataBit(REGIME_INPUT_GPIO_PORT,REGIME_INPUT_PIN))
    InputMask |= CU_REGIME_INPUT;
  
  if(GPIO_ReadInputDataBit(OIL_INPUT_GPIO_PORT,OIL_INPUT_PIN))
    InputMask |= CU_OIL_INPUT;   
  
  if(GPIO_ReadInputDataBit(EMBRAY_INPUT_GPIO_PORT,EMBRAY_INPUT_PIN))
    InputMask |= CU_EMBRAY_INPUT;   
  
  if(GPIO_ReadInputDataBit(GAZ_INPUT_GPIO_PORT,GAZ_INPUT_PIN))
    InputMask |= CU_GAZ_INPUT;   
  
  if(GPIO_ReadInputDataBit(NEUTRAL_INPUT_GPIO_PORT,NEUTRAL_INPUT_PIN))
    InputMask |= CU_NEUTRAL_INPUT;   
  
  if(GPIO_ReadInputDataBit(RAPPORTp_INPUT_GPIO_PORT,RAPPORTp_INPUT_PIN))
    InputMask |= CU_RAPPORTp_INPUT;   
  
  if(GPIO_ReadInputDataBit(RAPPORTm_INPUT_GPIO_PORT,RAPPORTm_INPUT_PIN))
    InputMask |= CU_RAPPORTm_INPUT;   
  
  if(GPIO_ReadInputDataBit(CAME_INPUT_GPIO_PORT,CAME_INPUT_PIN))
    InputMask |= CU_CAME_INPUT;   
  
  if(GPIO_ReadInputDataBit(RESERVED1_INPUT_GPIO_PORT,RESERVED1_INPUT_PIN))
    InputMask |= CU_RESERVED1_INPUT;   
  
  if(GPIO_ReadInputDataBit(RESERVED2_INPUT_GPIO_PORT,RESERVED2_INPUT_PIN))
    InputMask |= CU_RESERVED2_INPUT;   
  
  if(GPIO_ReadInputDataBit(RESERVED3_INPUT_GPIO_PORT,RESERVED3_INPUT_PIN))
    InputMask |= CU_RESERVED3_INPUT;   
  
  if(!GPIO_ReadInputDataBit(PALG_INPUT_GPIO_PORT,PALG_INPUT_PIN))
    InputMask |= CU_PALG_INPUT;   
  
  if(!GPIO_ReadInputDataBit(PALD_INPUT_GPIO_PORT,PALD_INPUT_PIN))
    InputMask |= CU_PALD_INPUT;   
  
  if(GPIO_ReadInputDataBit(MODE0_INPUT_GPIO_PORT,MODE0_INPUT_PIN))
    InputMask |= CU_MODE0_INPUT;   
  
  if(GPIO_ReadInputDataBit(MODE1_INPUT_GPIO_PORT,MODE1_INPUT_PIN))
    InputMask |= CU_MODE1_INPUT;   
  return InputMask;
}

uint8_t CU_RPMToBargraph(void)
{
  uint32_t ScaledRPM=0;
  ScaledRPM=(uint32_t)(CU_RPM_A*(float)Regime_getRPM()+CU_RPM_B);
  if(ScaledRPM<1)
    ScaledRPM=1;
  if(ScaledRPM>BARGRAPH_NLEDS)
    ScaledRPM=BARGRAPH_NLEDS;
  return (uint8_t)ScaledRPM;
}

uint8_t CU_UserInputToBargraph(uint32_t RPM)
{
  uint32_t ScaledRPM=0;
  ScaledRPM=(uint32_t)(CU_RPM_A*(float)RPM+CU_RPM_B);
  if(ScaledRPM<1)
    ScaledRPM=1;
  if(ScaledRPM>BARGRAPH_NLEDS)
    ScaledRPM=BARGRAPH_NLEDS;
  return (uint8_t)ScaledRPM;
}

void CU_MX25L1606E_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  /* Enable SCK GPIO clocks */
  RCC_AHB1PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK, ENABLE);
  
  /* Enable SPI  clock */
  RCC_APB1PeriphClockCmd(FLASH_SPI_CLK, ENABLE);
  
  /* SPI */
  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);
  GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF);
  GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(FLASH_SPI);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(FLASH_SPI, &SPI_InitStructure);

  /* Enable SPI  */
  SPI_Cmd(FLASH_SPI, ENABLE);
  
  /* Enable CS GPIO clocks */
  RCC_AHB1PeriphClockCmd(FLASH_SPI_CS_GPIO_CLK, ENABLE);
 
  /* Configure GPIO PIN for Memory Chip select */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Deselect : Chip Select high */
  GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN);
}

void CU_MX25L1606E_transfer(uint8_t *buffer,uint32_t length,uint8_t immediateCSRelease)
{
  uint32_t count;
  for(count=0;count<length;count++)
  {
    FLASH_SPI->DR = buffer[count];
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);//while empty
    buffer[count] = FLASH_SPI->DR;
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_BSY));
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);//while not empty
  }
  if(immediateCSRelease)
    GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN);
}

void CU_MX25L1606E_CS(uint8_t state)
{
  if(state==FLASH_CS_ASSERTED)
    GPIO_ResetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN);
  else
    GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN);
}




