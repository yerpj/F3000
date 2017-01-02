#include "STBT.h"

xSemaphoreHandle BT_UART_sem;
QueueHandle_t BT_UART_RX_Queue;
extern xSemaphoreHandle LogFileMutex;
extern QueueHandle_t UI_RX_Queue;


uint8_t BTRXedStr[STBT_RXSTR_MAXLENGTH];
uint32_t BTRXedStrPtr=0;

COM_TypeDef BTCOM=COM1;

STBT_State_TypeDef BT_State;


//uint8_t BTstr[50];

void STBT_ConsoleOutput(uint8_t *str)
{
  STBT_SPP_Send(str);
}

void STBT_Init(COM_TypeDef SerialCOM)
{
  USART_InitTypeDef USART_InitStruct;
  BT_State=Active_Command_mode;
  BTCOM=SerialCOM;
  
  USART_InitStruct.USART_BaudRate=115200;
  USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStruct.USART_Parity=USART_Parity_No;
  USART_InitStruct.USART_StopBits=USART_StopBits_1;
  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
  
  CU_COMInit(SerialCOM,&USART_InitStruct);
  vSemaphoreCreateBinary(BT_UART_sem);
  BT_UART_RX_Queue = xQueueCreate( 50, sizeof( uint8_t ) );

  xTaskCreate(STBT_Task, "BlueTooth", 5*configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}

void STBT_Send(uint8_t *str)
{
  uint32_t x=0;
  xSemaphoreTake(BT_UART_sem, portMAX_DELAY);
  do
  {
    while( !(USART3->SR & 0x00000040) );
    USART_SendData(USART3,str[x]);
    x++;
  }while( (str[x]!=0) );
    while( !(USART3->SR & 0x00000040) );
  xSemaphoreGive(BT_UART_sem);
}

void STBT_SendLine(uint8_t *str, uint32_t length)
{
  uint32_t x=0;
  xSemaphoreTake(BT_UART_sem, portMAX_DELAY);
  do
  {
    while( !(USART3->SR & 0x00000040) );
    USART_SendData(USART3,str[x]);
    x++;
  }while( (str[x]!=0) && (x<length) );
    while( !(USART3->SR & 0x00000040) );
  xSemaphoreGive(BT_UART_sem);
}


uint8_t STBT_SPP_Active(void)
{
  if(BT_State==Active_Bypass_mode)
    return 1;
  return 0;
}
uint8_t STBT_SPP_Send(uint8_t *str)
{
  if(BT_State==Active_Bypass_mode)
  {
    STBT_Send(str);
    STBT_Send("\r\n");
    return 0;
  }
  else
    return 1;
}

void STBT_Task(void * pvParameters)
{
  uint32_t numbytesread,numbyteswritten;
  /*Update the module name*/
  STBT_Send("AT+AB Config DeviceName=F3000\n");
  vTaskDelay(100);
  /*Reset the BT module*/
  STBT_Send("AT+AB Reset \n");
  vTaskDelay(7000);
  /*Enable autoBonding*/
  STBT_Send("AT+AB EnableBond\n");
  vTaskDelay(100);
  STBT_Send("AT+AB Config PIN=1234\n");
  vTaskDelay(100);
  for(;;)
  {
    if(xQueueReceive( BT_UART_RX_Queue, &BTRXedStr[BTRXedStrPtr], portMAX_DELAY) )
    {
#ifdef BRIDGE_BT_SERIAL
      while( !(USART1->SR & 0x00000040) );
      USART_SendData(USART1,BTRXedStr[BTRXedStrPtr]);
#else /* BRIDGE_BT_SERIAL */
      switch(BT_State)
      {
      case Standby_mode:
        break;
      case Active_Bypass_mode:
        if(BTRXedStr[BTRXedStrPtr]==0x0A && BTRXedStrPtr>0)
        {
          if(BTRXedStr[BTRXedStrPtr-1]==0x0D)
          {
            //new command received
            if(strstr(BTRXedStr,"SPPConnectionClosed"))
            {
              BT_State=Active_Command_mode;           
              //STM_EVAL_LEDOff(LED2);
              //fr = f_close(&fd);
            }
            else if(strstr(BTRXedStr,"ConnectionDown"))
            {
              BT_State=Active_Command_mode;           
              //STM_EVAL_LEDOff(LED2);
              //fr = f_close(&fd);
            }
            else if(strstr(BTRXedStr,"CommandMode"))
            {
              BT_State=Active_Command_mode;           
              //STM_EVAL_LEDOff(LED2);
              //fr = f_close(&fd);
            }
            BTRXedStrPtr=STBT_RXSTR_MAXLENGTH-1;
          }
        }
        else
        {
          //xQueueSendToBack( UI_RX_Queue, &BTRXedStr[BTRXedStrPtr], NULL );
        }
        break;
      case Active_Command_mode:
        if(BTRXedStr[BTRXedStrPtr]==0x0A && BTRXedStrPtr>0)
        {
          if(BTRXedStr[BTRXedStrPtr-1]==0x0D)
          {
            //new command received
            if(strstr(BTRXedStr,"BypassMode"))
            {
              BT_State=Active_Bypass_mode;              
              //STM_EVAL_LEDOn(LED2);
              //fr = f_open(&fd,"BTlog.txt", FA_WRITE| FA_OPEN_ALWAYS);
              //fr = f_lseek(&fd, f_size(&fd));
            }
            else if(strstr(BTRXedStr,"SPPConnectionClosed"))
            {
              BT_State=Active_Command_mode;
            }
            else if(strstr(BTRXedStr,"CommandMode"))
            {
              BT_State=Active_Command_mode;
            }
            BTRXedStrPtr=STBT_RXSTR_MAXLENGTH-1;
          }
        }
        break;
      default:break;
      
      
      
      }
#endif /* BRIDGE_BT_SERIAL */
    }
    /*Update the RX str pointer*/
    BTRXedStrPtr++;
    BTRXedStrPtr%=STBT_RXSTR_MAXLENGTH;
  }
}

void STBT_USART_RX_Callback(uint8_t rxchar)
{
  xQueueSendToBackFromISR( BT_UART_RX_Queue, &rxchar, NULL );
}