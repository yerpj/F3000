#include "serial.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 

xSemaphoreHandle SerialUART_sem;

void (*SerialCB)(uint8_t)=0;

uint8_t Serial_RXBuf[255];
uint32_t Serial_RXPtr=0;

uint8_t Serial_Init(void)
{
  if(Console_LowLevelInit())
    return 1;
  vSemaphoreCreateBinary(SerialUART_sem);
  //SerialUART_sem=xSemaphoreCreateBinary();
  SerialCB=Serial_Callback;
  //xSemaphoreTake(SerialUART_sem, 0);
  return 0;
}

void Serial_SendRow(uint8_t *str, uint32_t length)
{
  uint32_t x=0;
  if(xSemaphoreTake(SerialUART_sem, ( TickType_t ) 50)!=pdTRUE )
     return ;
#if defined(USE_NGP020) || defined(USE_NGP022)
#include "SC16IS750IBS.h"
  do
  {
    SC16IS750IBS_UARTPutc(SC16IS750IBS_I2C_ADDR,str[x]);
    x++;
  }while( x<length );
#else
  do
  {
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
    USART_SendData(EVAL_COM2,str[x]);
    x++;
  }while( x<length );
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
#endif /*  defined(USE_NGP020) || defined(USE_NGP022) */
  xSemaphoreGive(SerialUART_sem);
}

void Serial_SendLine(uint8_t *str, uint32_t length)
{
  uint32_t x=0;
  if(xSemaphoreTake(SerialUART_sem, ( TickType_t ) 50)!=pdTRUE )
     return ;
#if defined(USE_NGP020) || defined(USE_NGP022)
#include "SC16IS750IBS.h"
  do
  {
    SC16IS750IBS_UARTPutc(SC16IS750IBS_I2C_ADDR,str[x]);
    x++;
  }while( (str[x]!=0) && (x<length) );
#else
  do
  {
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
    USART_SendData(EVAL_COM2,str[x]);
    x++;
  }while( (str[x]!=0) && (x<length) );
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
#endif /*  defined(USE_NGP020) || defined(USE_NGP022) */
  xSemaphoreGive(SerialUART_sem);
}

void Serial_SendString(uint8_t *str)
{
  uint32_t x=0;
  if(xSemaphoreTake(SerialUART_sem, ( TickType_t ) 50)!=pdTRUE )
     return ;
#if defined(USE_NGP020) || defined(USE_NGP022)
#include "SC16IS750IBS.h"
  do
  {
    SC16IS750IBS_UARTPutc(SC16IS750IBS_I2C_ADDR,str[x]);
    x++;
  }while( (str[x]!=0) );
#else
  do
  {
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
    USART_SendData(CONSOLEPORT_USART,str[x]);
    x++;
  }while( (str[x]!=0) );
    while( !(CONSOLEPORT_USART->SR & 0x00000040) );
#endif /*  defined(USE_NGP020) || defined(USE_NGP022) */
  
  xSemaphoreGive(SerialUART_sem);
}

void Serial_SendChar(uint8_t character)
{
#if defined(USE_NGP020) || defined(USE_NGP022)
#include "SC16IS750IBS.h"
  SC16IS750IBS_UARTPutc(SC16IS750IBS_I2C_ADDR,character);
#else
  xSemaphoreTake(SerialUART_sem, portMAX_DELAY);
  while( !(CONSOLEPORT_USART->SR & 0x00000040) );
  USART_SendData(CONSOLEPORT_USART,character);
  while( !(CONSOLEPORT_USART->SR & 0x00000040) );
  xSemaphoreGive(SerialUART_sem);
#endif /*  defined(USE_NGP020) || defined(USE_NGP022) */
}

void Serial_Callback(uint8_t character)
{
  Serial_RXBuf[Serial_RXPtr++]=character;
  if(Serial_RXPtr>255)
    Serial_RXPtr=0;
}

