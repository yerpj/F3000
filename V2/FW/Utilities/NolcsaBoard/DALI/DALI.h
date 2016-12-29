#ifndef _DALI_H_
#define _DALI_H_
#include "nolcsa.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 

#include "timer.h"

#define DALIMASTER_MODE_RX (1)
#define DALIMASTER_MODE_TX (2)

#define TIM_TX_STATE_IDLE  (1)
#define TIM_TX_STATE_STARTBIT (2)
#define TIM_TX_STATE_ADDRESS  (3)
#define TIM_TX_STATE_DATA     (4)
#define TIM_TX_STATE_STOPBITS (5)

#define RXMACHINESTATE_IDLE     (0)
#define RXMACHINESTATE_STARTBIT (1)
#define RXMACHINESTATE_RXBYTE   (2)
#define RXMACHINESTATE_STOPBIT  (3)

#define MANCHESTER_3_4_BIT_TIME 625 //us
#define MANCHESTER_STOP_BIT_TIME 1670 //us

#define DALI_INTERFRAME_DURATION_US  (10000)    //us
#define DALI_DEMIBIT_TIME_US         (416)      //416us
#define DALI_STOP_TIME_US         (1670)      //1670us

/*#ifdef DALI_SLAVE_MODE
  #define DALI_RX_BITS_NUMBER_TO_RECEIVE        16
#else // DALI Master mode */
  #define DALI_RX_BITS_NUMBER_TO_RECEIVE        8
/*#endif // DALI_SLAVE_MODE */

void DALI_Init(void);
void DALI_MasterPowerEnable(uint8_t Enable);
uint8_t DALI_SendForwardFrame(uint8_t Addr, uint8_t Data);
void DALI_RX_bitbang_cb(uint8_t RxByte);
void DALI_RX(void);
void DALI_TX(void);
uint8_t DALI_TxDone(void);
void DALI_Reset(uint8_t Addr);
void DALI_Identify(uint8_t Addr);
void DALI_SetUnicastAddress(uint8_t Addr);
uint8_t DALI_EnableDeviceType(uint8_t Type);
uint8_t DALI_QueryGearType(uint8_t Addr);
uint8_t DALI_QueryStatus(uint8_t Addr);
uint8_t DALI_QueryLampFailure(uint8_t Addr);
uint8_t DALI_QueryControlGear(uint8_t Addr);
uint8_t DALI_QueryResetState(uint8_t Addr);
uint8_t DALI_QueryActualLevel(uint8_t Addr);
uint8_t DALI_QueryOperatingMode(uint8_t Addr);
uint8_t DALI_ReturnPhysicalMinimumLevel(uint8_t Addr);
uint8_t DALI_ReturnDeviceType(uint8_t Addr);
void DALI_SendUnicastArcPowerLevel(uint8_t Addr,uint8_t Level);
void DALI_SendBroadcastArcPowerLevel(uint8_t Level);
void DALI_SendUnicastCommand(uint8_t Addr,uint8_t Cmd);
void DALI_SendBroadcastCommand(uint8_t Cmd);
void DALI_SendExtendedCommand(uint8_t Xaddr, uint8_t Cmd);

void DALI_GoToScene(uint8_t Addr,uint8_t scene);
void DALI_StepDownAndOFF(uint8_t Addr);


void EndOfSmartBlankingCB(void);
void DALI_SmartCurrentSense(uint8_t mode);
void DALI_ISenseCB(uint16_t Current);

uint8_t DALI_DidSlaveAnswer(void);
uint8_t DALI_GetSlaveAnswer(void);


#endif /* _DALI_H_ */
