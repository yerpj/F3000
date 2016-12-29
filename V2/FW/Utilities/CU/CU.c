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


void Console_Rx_Task(void * pvParameters);
static xSemaphoreHandle Serial_rx_sem;
uint8_t NodeConsoleRXBuf[50];
uint8_t NodeConsoleRXPtr=0;
uint8_t NodeConsoleRXReady=0;

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
  
  vSemaphoreCreateBinary(Serial_rx_sem);
  xTaskCreate(Console_Rx_Task, "ConsoleRX", 3*configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  
  /* Enable USART */
  USART_Cmd(CONSOLEPORT_USART, ENABLE);
  return 0;
}

void Node_Console_cb(void)
{  
  static portBASE_TYPE yield;
  if(!NodeConsoleRXReady)
  {
    NodeConsoleRXBuf[NodeConsoleRXPtr++]=USART_ReceiveData(CONSOLEPORT_USART);
    if(NodeConsoleRXPtr>49 || (NodeConsoleRXBuf[NodeConsoleRXPtr-1]=='\n') )
    {
      NodeConsoleRXReady=1;
      xSemaphoreGiveFromISR(Serial_rx_sem, &yield);
      NodeConsoleRXPtr=0;
    }
  }
}

void Console_Rx_Task(void * pvParameters)
{
  uint8_t tmpreg=0;
  uint8_t i=0;
  while (1) 
  {
    if (xSemaphoreTake(Serial_rx_sem, portMAX_DELAY) == pdTRUE) 
    {
      if(NodeConsoleRXReady)
      { 
        i=0;
        while(NodeConsoleRXBuf[i]!='\n')
          CLI_Input(NodeConsoleRXBuf[i++]);
        CLI_Input(NodeConsoleRXBuf[i]);
        NodeConsoleRXReady=0;
      }
    }
  }
  vTaskDelete(NULL);
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
void NCP020_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
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


