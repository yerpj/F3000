#include "STBT.h"
#include "semphr.h" 


xSemaphoreHandle BT_UART_sem;
QueueHandle_t BT_UART_RX_Queue;
//extern xSemaphoreHandle LogFileMutex;

uint8_t BTRXedStr[STBT_RXSTR_MAXLENGTH];
uint32_t BTRXedStrPtr=0;

COM_TypeDef BTCOM=COM1;

STBT_State_TypeDef BT_State;

//extern xSemaphoreHandle Console_rx_sem;

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
  BT_UART_RX_Queue = xQueueCreate( 100, sizeof( uint8_t ) );

  xTaskCreate(STBT_Task, "BlueTooth", 5*configMINIMAL_STACK_SIZE, NULL, 9, NULL);
}

void STBT_Send(uint8_t *str)
{
  uint32_t x=0;
  xSemaphoreTake(BT_UART_sem, portMAX_DELAY);
  do
  {
    while( !(USART1->SR & 0x00000040) );
    USART_SendData(USART1,str[x]);
    x++;
  }while( (str[x]!=0) );
    while( !(USART1->SR & 0x00000040) );
  xSemaphoreGive(BT_UART_sem);
}

void STBT_SendLine(uint8_t *str, uint32_t length)
{
  uint32_t x=0;
  xSemaphoreTake(BT_UART_sem, portMAX_DELAY);
  do
  {
    while( !(USART1->SR & 0x00000040) );
    USART_SendData(USART1,str[x]);
    x++;
  }while( (str[x]!=0) && (x<length) );
    while( !(USART1->SR & 0x00000040) );
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
  //uint32_t numbytesread,numbyteswritten;
  uint8_t i=0;
  /*Update the module name*/
  STBT_Send("AT+AB Config DeviceName=F3000\n");
  vTaskDelay(100);
  /*Reset the BT module*/
  STBT_Send(STBT_ESCAPE_SEQ);
  vTaskDelay(2100);
  STBT_Send("AT+AB Reset \n");
  vTaskDelay(7000);
  /*Enable autoBonding*/
  STBT_Send("AT+AB EnableBond\n");
  vTaskDelay(100);
  //STBT_Send("AT+AB Config PIN=1234\n");
  vTaskDelay(100);
  for(;;)
  {
    if(xQueueReceive( BT_UART_RX_Queue, &BTRXedStr[BTRXedStrPtr++], portMAX_DELAY) )
    {
      switch(BT_State)
      {
      case Standby_mode:
        break;
      case Active_Bypass_mode:
        if( (BTRXedStr[BTRXedStrPtr-1]==0x0A) && (BTRXedStr[BTRXedStrPtr-2]==0x0D) && BTRXedStrPtr>2 )
        {
          //new command received
          if(strstr(BTRXedStr,"SPPConnectionClosed"))
          {
            BT_State=Active_Command_mode;           
          }
          else if(strstr(BTRXedStr,"ConnectionDown"))
          {
            BT_State=Active_Command_mode;           
          }
          else if(strstr(BTRXedStr,"CommandMode"))
          {
            BT_State=Active_Command_mode;           
          }
          buffer_init(BTRXedStr,0,BTRXedStrPtr-1);
          BTRXedStrPtr=0;
        }
        else
        {
          if(BTRXedStr[BTRXedStrPtr-1]=='#')
          {
            BTRXedStrPtr-=1;//reduce pointer to end of relevant string
            for(i=0;i<BTRXedStrPtr;i++)
              CLI_Input(BTRXedStr[i]);
            CLI_Input('\r');
            CLI_Input('\n');
            buffer_init(BTRXedStr,0,BTRXedStrPtr-1);
            BTRXedStrPtr=0;
          }
        }
        break;
      case Active_Command_mode:
        if( (BTRXedStr[BTRXedStrPtr-1]==0x0A) && (BTRXedStr[BTRXedStrPtr-2]==0x0D) && BTRXedStrPtr>2 )
        {
          //new command received
          if(strstr(BTRXedStr,"BypassMode"))
          {
            BT_State=Active_Bypass_mode;              
          }
          else if(strstr(BTRXedStr,"SPPConnectionClosed"))
          {
            BT_State=Active_Command_mode;
          }
          else if(strstr(BTRXedStr,"CommandMode"))
          {
            BT_State=Active_Command_mode;
          }
          buffer_init(BTRXedStr,0,BTRXedStrPtr-1);
          BTRXedStrPtr=0;
          
        }
        break;
      default:break;
      }
    }
    
    /*check the RX str pointer*/
    if(BTRXedStrPtr==STBT_RXSTR_MAXLENGTH)
      BTRXedStrPtr=0;
  }
}

void STBT_USART_RX_Callback(uint8_t rxchar)
{
  xQueueSendToBackFromISR( BT_UART_RX_Queue, &rxchar, NULL );
}
