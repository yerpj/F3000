#include "CU.h"
#include "main.h"

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

//void Console_Rx_Task(void * pvParameters);
//xSemaphoreHandle Console_rx_sem;
//uint8_t ConsoleRXBuf[50];
//uint8_t ConsoleRXPtr=0;
//uint8_t ConsoleRXReady=0;

void LEDs_Init(void)
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
}

void CU_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(GPIO_CLK[Led], ENABLE);


  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
  
  CU_LEDOn(Led);
  CU_LEDOff(Led);
}

void CU_LEDDeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(GPIO_CLK[Led], ENABLE);
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

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
void CU_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRH = GPIO_PIN[Led]; 
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
void CU_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRL = GPIO_PIN[Led]; 
}

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
void CU_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

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

uint8_t CU_IOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* INPUTS */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //-->REGIME_INPUT_PIN
  RCC_AHB1PeriphClockCmd(REGIME_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =REGIME_INPUT_PIN;
  GPIO_Init(REGIME_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->OIL_INPUT_PIN
  RCC_AHB1PeriphClockCmd(OIL_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =OIL_INPUT_PIN;
  GPIO_Init(OIL_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->EMBRAY_INPUT_PIN
  RCC_AHB1PeriphClockCmd(EMBRAY_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =EMBRAY_INPUT_PIN;
  GPIO_Init(EMBRAY_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->GAZ_INPUT_PIN
  RCC_AHB1PeriphClockCmd(GAZ_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GAZ_INPUT_PIN;
  GPIO_Init(GAZ_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->NEUTRAL_INPUT_PIN
  RCC_AHB1PeriphClockCmd(NEUTRAL_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =NEUTRAL_INPUT_PIN;
  GPIO_Init(NEUTRAL_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->RAPPORTp_INPUT_PIN
  RCC_AHB1PeriphClockCmd(RAPPORTp_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RAPPORTp_INPUT_PIN;
  GPIO_Init(RAPPORTp_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->RAPPORTm_INPUT_PIN
  RCC_AHB1PeriphClockCmd(RAPPORTm_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RAPPORTm_INPUT_PIN;
  GPIO_Init(RAPPORTm_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->P2_INPUT_PIN
  RCC_AHB1PeriphClockCmd(P2_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =P2_INPUT_PIN;
  GPIO_Init(P2_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->P1_INPUT_PIN
  RCC_AHB1PeriphClockCmd(P1_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =P1_INPUT_PIN;
  GPIO_Init(P1_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->RESERVED_INPUT_PIN
  RCC_AHB1PeriphClockCmd(RESERVED_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =RESERVED_INPUT_PIN;
  GPIO_Init(RESERVED_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->PALG_INPUT_PIN
  RCC_AHB1PeriphClockCmd(PALG_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =PALG_INPUT_PIN;
  GPIO_Init(PALG_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->PALD_INPUT_PIN
  RCC_AHB1PeriphClockCmd(PALD_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =PALD_INPUT_PIN;
  GPIO_Init(PALD_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->MODE0_INPUT_PIN
  RCC_AHB1PeriphClockCmd(MODE0_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MODE0_INPUT_PIN;
  GPIO_Init(MODE0_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  //-->MODE1_INPUT_PIN
  RCC_AHB1PeriphClockCmd(MODE1_INPUT_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =MODE1_INPUT_PIN;
  GPIO_Init(MODE1_INPUT_GPIO_PORT, &GPIO_InitStructure);
  
  /* OUTPUTS */
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
  
  if(GPIO_ReadInputDataBit(P2_INPUT_GPIO_PORT,P2_INPUT_PIN))
    InputMask |= CU_P2_INPUT;   
  
  if(GPIO_ReadInputDataBit(P1_INPUT_GPIO_PORT,P1_INPUT_PIN))
    InputMask |= CU_P1_INPUT;   
  
  if(GPIO_ReadInputDataBit(RESERVED_INPUT_GPIO_PORT,RESERVED_INPUT_PIN))
    InputMask |= CU_RESERVED_INPUT;   
  
  if(GPIO_ReadInputDataBit(PALG_INPUT_GPIO_PORT,PALG_INPUT_PIN))
    InputMask |= CU_PALG_INPUT;   
  
  if(GPIO_ReadInputDataBit(PALD_INPUT_GPIO_PORT,PALD_INPUT_PIN))
    InputMask |= CU_PALD_INPUT;   
  
  if(GPIO_ReadInputDataBit(MODE0_INPUT_GPIO_PORT,MODE0_INPUT_PIN))
    InputMask |= CU_MODE0_INPUT;   
  
  if(GPIO_ReadInputDataBit(MODE1_INPUT_GPIO_PORT,MODE1_INPUT_PIN))
    InputMask |= CU_MODE1_INPUT;   
  return InputMask;
}


