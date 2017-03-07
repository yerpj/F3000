#ifndef __STBT_H__
#define __STBT_H__
#include "main.h"

#define STBT_RXSTR_MAXLENGTH 50
#define STBT_ESCAPE_SEQ "^#^$^%\n"

typedef enum{
  Standby_mode=0,
  Active_Bypass_mode=1,
  Active_Command_mode=2
}STBT_State_TypeDef;

void STBT_USART_RX_Callback(uint8_t rxchar);
void STBT_Init(COM_TypeDef SerialCOM);
void STBT_Send(uint8_t *str);
void STBT_SendLine(uint8_t *str, uint32_t length);
void STBT_Task(void * pvParameters);
uint8_t STBT_SPP_Active(void);
uint8_t STBT_SPP_Send(uint8_t *str);
void STBT_ConsoleOutput(uint8_t *str);

#endif /*__STBT_H__*/