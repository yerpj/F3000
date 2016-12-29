#include "DALI.h"

void (*DALI_RX_cb)(uint8_t RxByte)=0;
uint8_t RxByteValid;
static uint8_t RxedByte=0;
uint8_t TxAddr=0, TxData=0,TxDataReadyToBeSent=0, TxFinished=1;
uint8_t DALIMaster_Mode=DALIMASTER_MODE_TX;


uint8_t RxMachineState=RXMACHINESTATE_IDLE;
uint16_t StartBit_DemiBitDuration=0;
uint8_t StartBitPolarity=0;     //0 = ../´´        1 = ´´\..
uint8_t NewInputLevel=0;
uint8_t TIMFlag3_4=0;
uint8_t RxFrameBitPosition=(DALI_RX_BITS_NUMBER_TO_RECEIVE-1);

uint8_t SmartBlankingInhibited=0;

#define TX_LOW() DALI_TX_GPIO_PORT->BSRRH = DALI_TX_PIN
#define TX_HIGH() DALI_TX_GPIO_PORT->BSRRL = DALI_TX_PIN
#define TX_PINSTATE (DALI_TX_GPIO_PORT->IDR & DALI_TX_PIN)
#define RX_PINSTATE (DALI_RX_GPIO_PORT->IDR & DALI_RX_PIN)

void DALI_Init(void)
{
  DALI_LowLevel_Init();
  DALI_RX_cb=DALI_RX_bitbang_cb;
  //DALI_SmartCurrentSense(1);
  DALI_RX();
  RxByteValid=0;
}

void DALI_RX(void)
{
  DALIMaster_Mode=DALIMASTER_MODE_RX;
}

void DALI_TX(void)
{
  DALIMaster_Mode=DALIMASTER_MODE_TX;
}

uint8_t DALI_TxDone(void)
{ 
  if(TxFinished)
    return 1;
  else 
    return 0;
}

void DALI_SetUnicastAddress(uint8_t Addr)
{  
  DALI_Reset(Addr);
  
  DALI_SendExtendedCommand(0xA5,0x00);     //init: starts a 30min. window 
  DALI_SendExtendedCommand(0xA5,0x00);     //repeat init
  
  DALI_SendExtendedCommand(0xB7,(((Addr<<1)&0x7E)|0x01));  //program short address
  DALI_SendExtendedCommand(0xA3,(((Addr<<1)&0x7E)|0x01));  //store short address into DTR
  DALI_SendUnicastCommand(Addr,0x80);                   //store DTR as short address
  DALI_SendUnicastCommand(Addr,0x80);                   //store DTR as short address
  
  DALI_SendExtendedCommand(0xA1,0x00);     //terminate
}

uint8_t DALI_SetPhysicalMinimumLevel(uint8_t Addr, uint8_t level)
{
  uint8_t PhyMinLevel=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x9A);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    PhyMinLevel=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return PhyMinLevel;
}

uint8_t DALI_EnableDeviceType(uint8_t Type)
{
  DALI_SendExtendedCommand(0xC1,Type);
  return 0;
}

uint8_t DALI_QueryGearType(uint8_t Addr)
{
  uint8_t GearType=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0xED);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    GearType=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return GearType;
}

uint8_t DALI_QueryOperatingMode(uint8_t Addr)
{
  uint8_t OperatingMode=0;
  DALI_SendUnicastCommand(Addr,0xFC);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    OperatingMode=DALI_GetSlaveAnswer();
  return OperatingMode;
}

uint8_t DALI_QueryStatus(uint8_t Addr)
{
  uint8_t Status=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x90);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    Status=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return Status;
}

uint8_t DALI_QueryLampFailure(uint8_t Addr)
{
  uint8_t LampFailure=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x92);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    LampFailure=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return LampFailure;
}



uint8_t DALI_QueryControlGear(uint8_t Addr)
{
  uint8_t Status=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x91);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    Status=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return Status;
}

uint8_t DALI_QueryResetState(uint8_t Addr)
{
  uint8_t Status=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x95);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    Status=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return Status;
}

uint8_t DALI_QueryActualLevel(uint8_t Addr)
{
  uint8_t Status=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0xA0);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    Status=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return Status;
}

uint8_t DALI_ReturnDeviceType(uint8_t Addr)
{
  uint8_t DevType=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x99);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    DevType=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return DevType;
}

uint8_t DALI_ReturnPhysicalMinimumLevel(uint8_t Addr)
{
  uint8_t PhyMinLevel=0;
  //nolcsa_LEDOn(LED_RED2);
  DALI_SendUnicastCommand(Addr,0x9A);
  vTaskDelay(20);
  if(DALI_DidSlaveAnswer())
    PhyMinLevel=DALI_GetSlaveAnswer();
  //nolcsa_LEDOff(LED_RED2);
  return PhyMinLevel;
}

void DALI_SendUnicastArcPowerLevel(uint8_t Addr,uint8_t Level)
{
  uint8_t FormattedAddr=0;
  
  DALI_TX();
  //Addr is of type 'YAAAAAAS'
  FormattedAddr=((Addr<<1)&0x7E);//'Y' bit set to 0, 'S' bit set to 0
  DALI_SendForwardFrame(FormattedAddr,Level);
  while(!DALI_TxDone());
  DALI_RX();
}

void DALI_StepDownAndOFF(uint8_t Addr)
{
  uint8_t FormattedAddr=0;
  
  DALI_TX();
  //Addr is of type 'YAAAAAA1'
  FormattedAddr=(((Addr<<1)&0x7F)|0x01);//'Y' bit set to 0, 'S' bit set to 1
  DALI_SendForwardFrame(FormattedAddr,0x07);
  while(!DALI_TxDone());
  DALI_RX();
}

void DALI_GoToScene(uint8_t Addr,uint8_t scene)
{
  uint8_t FormattedScene=0;
  
  FormattedScene=0x10+(scene&0x0F);
  DALI_SendUnicastCommand(Addr,FormattedScene);
}

void DALI_Reset(uint8_t Addr)
{
  DALI_SendUnicastCommand(Addr,0x20);
  DALI_SendUnicastCommand(Addr,0x20);
}

void DALI_Identify(uint8_t Addr)
{
  DALI_SendExtendedCommand((Addr<<1)|0x01,0x25);
  DALI_SendExtendedCommand((Addr<<1)|0x01,0x25);
}


void DALI_SendBroadcastArcPowerLevel(uint8_t Level)
{
  DALI_TX();
  DALI_SendForwardFrame(0xFE,Level);
  while(!DALI_TxDone());
  DALI_RX();
}

void DALI_SendUnicastCommand(uint8_t Addr,uint8_t Cmd)
{
  uint8_t FormattedAddr;
  DALI_TX();
  //Addr is of type 'YAAAAAA1'
  FormattedAddr=(((Addr<<1)&0x7F)|0x01);//'Y' bit set to 0, 'S' bit set to 1
  DALI_SendForwardFrame(FormattedAddr,Cmd);
  while(!DALI_TxDone());
  DALI_RX();
}



void DALI_SendBroadcastCommand(uint8_t Cmd)
{
  DALI_TX();
  DALI_SendForwardFrame(0xFF,Cmd);
  while(!DALI_TxDone());
  DALI_RX();
}

void DALI_SendExtendedCommand(uint8_t Xaddr, uint8_t Cmd)
{
  DALI_TX();
  DALI_SendForwardFrame(Xaddr,Cmd);
  while(!DALI_TxDone());
  DALI_RX();
}
  
uint8_t DALI_SendForwardFrame(uint8_t Addr, uint8_t Data)
{ 
  if(DALIMaster_Mode==DALIMASTER_MODE_TX)
  {
    if(TxFinished)
    {
      TxFinished=0;
      TxAddr=Addr;
      TxData=Data;
      
      TxDataReadyToBeSent=1;

      /* Trig a dummy TIM CC interrupt */
      TIM_SetCompare1(TIM2,2);
      TIM_SetCounter(TIM2,0);
      TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
      TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
      TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE);
      TIM_Cmd(TIM2, ENABLE);
      return 0;
    }
  }
  return 1;
}

uint8_t DALI_DidSlaveAnswer(void)
{
  if(RxByteValid)
  {
    RxByteValid=0;
    return 1;
  }
  else
    return 0;
}
uint8_t DALI_GetSlaveAnswer(void)
{
  uint8_t Answer;
  Answer=RxedByte;
  RxedByte=0;
  RxByteValid=0;
  return Answer;
}

void DALI_MasterPowerEnable(uint8_t Enable)
{
  if(Enable)
    DALI_POWER_ENABLE_GPIO_PORT->BSRRL = DALI_POWER_ENABLE_PIN;
  else
    DALI_POWER_ENABLE_GPIO_PORT->BSRRH = DALI_POWER_ENABLE_PIN;
}

void DALI_SmartCurrentSense(uint8_t mode)
{
  switch(mode)
  {
  case 1:
    //ON
    timer_init();
    /* Enable the ADC peripheral */
    ADC_Cmd(ADC2, ENABLE);     
    ADC_SoftwareStartConv(ADC2);
    
    break;
  case 0:
    //OFF
    /* Disable the ADC peripheral */
    ADC_Cmd(ADC2, DISABLE);    
    break;
  default:break;
  }
}

void EndOfSmartBlankingInhibition(void)
{
  SmartBlankingInhibited=0;
}

void EndOfSmartBlankingCB(void)
{
  DALI_MasterPowerEnable(1);
  SmartBlankingInhibited=0;
  //Alarm_us(1,370/*us*/,EndOfSmartBlankingInhibition);
}

void DALI_ISenseCB(uint16_t Current)
{
  if(Current>620)//620 is the ADC value when 500mA is flowing through DALI lines
  {
    DALI_MasterPowerEnable(0);
    if(!SmartBlankingInhibited)
    {
      SmartBlankingInhibited=1;
      Alarm_us(1,50/*us*/,EndOfSmartBlankingCB);
    }
  }
}



void DALI_TX_Done_cb(void)
{
  ;
}

void TIM2_IRQHandler()
{
  static uint8_t TXState=TIM_TX_STATE_IDLE;
  static uint8_t TXAddrByteMask=0,TXDataByteMask=0;
  static uint8_t TXFirstHalfOfBit=0;
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {     //CC1 is used for TX ONLY!
    /* Stop TIM2 counter */
    TIM_Cmd(TIM2, DISABLE);
    TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
    switch(TXState)
    {
    case TIM_TX_STATE_IDLE:
      if(TxDataReadyToBeSent)
      {
        TX_LOW();
        TxDataReadyToBeSent=0;
        TXDataByteMask=0x80;
        TXFirstHalfOfBit=1;
        
        /* Prepare next state */
        TXState=TIM_TX_STATE_STARTBIT;
        
        /* Set the minimum wait before a Forward frame */
        TIM_SetCompare1(TIM2,DALI_INTERFRAME_DURATION_US);
        TIM_SetCounter(TIM2,0);
        TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
        TIM_Cmd(TIM2, ENABLE);
      }
      else
      {
        TxFinished=1;
        TIM_SetCounter(TIM2,0);
        TIM_ITConfig(TIM2, TIM_IT_CC1 , DISABLE);
        TIM_Cmd(TIM2, DISABLE);
      }
      break;
    case TIM_TX_STATE_STARTBIT:
      if(TXFirstHalfOfBit)
      {
        /* Update TX bit */
        TX_HIGH();
        
        /* Update Half Bit status */
        TXFirstHalfOfBit=0;
      }
      else
      {
        /* Prepare next state */
        TXState=TIM_TX_STATE_ADDRESS;
        TXFirstHalfOfBit=1;
        TXAddrByteMask=0x80;
        
        /* Update TX bit */
        TX_LOW();
      }
      /* Wait a demi-bit time */
      TIM_SetCompare1(TIM2,DALI_DEMIBIT_TIME_US);
      TIM_SetCounter(TIM2,0);
      TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
      TIM_Cmd(TIM2, ENABLE);
      break;
    case TIM_TX_STATE_ADDRESS:
      if(TXFirstHalfOfBit)
      {
        /* Update TX bit */
        if(TxAddr&TXAddrByteMask)
          TX_HIGH();
        else
          TX_LOW();
        
        /* Update Half Bit status */
        TXFirstHalfOfBit=0;        
      }
      else
      {
        /* Update TX bit */
        if(TxAddr&TXAddrByteMask)
          TX_LOW();
        else
          TX_HIGH();
        
        /* Update the Addr Bit pointer */
        TXAddrByteMask>>=1; 
        
        /* Update Half Bit status */
        TXFirstHalfOfBit=1;
        
        /* Test if whole Addr has been sent */
        if(TXAddrByteMask==0x00)
        {
          /* Prepare next state */
          TXState=TIM_TX_STATE_DATA;
          TXFirstHalfOfBit=1;
          TXDataByteMask=0x80;
        }
      }
      /* Wait a demi-bit time */
      TIM_SetCompare1(TIM2,DALI_DEMIBIT_TIME_US);
      TIM_SetCounter(TIM2,0);
      TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
      TIM_Cmd(TIM2, ENABLE);
      break;
    case TIM_TX_STATE_DATA:
      if(TXFirstHalfOfBit)
      {
        /* Update TX bit */
        if(TxData&TXDataByteMask)
          TX_HIGH();
        else
          TX_LOW();
        
        /* Update Half Bit status */
        TXFirstHalfOfBit=0;        
      }
      else
      {
        /* Update TX bit */
        if(TxData&TXDataByteMask)
          TX_LOW();
        else
          TX_HIGH();
        
        /* Update the Addr Bit pointer */
        TXDataByteMask>>=1; 
        
        /* Update Half Bit status */
        TXFirstHalfOfBit=1;
        
        /* Test if whole Addr has been sent */
        if(TXDataByteMask==0x00)
        {
          /* Prepare next state */
          TXState=TIM_TX_STATE_STOPBITS;
          TXFirstHalfOfBit=1;
        }
      }
      /* Wait a demi-bit time */
      TIM_SetCompare1(TIM2,DALI_DEMIBIT_TIME_US);
      TIM_SetCounter(TIM2,0);
      TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
      TIM_Cmd(TIM2, ENABLE);
      break;
    case TIM_TX_STATE_STOPBITS:
      
      /* STOP State */
      TX_LOW();
      
      /* Prepare next state */
      TXState=TIM_TX_STATE_IDLE;
      
      /* Wait a STOP time */
      TIM_SetCompare1(TIM2,DALI_STOP_TIME_US);
      TIM_SetCounter(TIM2,0);
      TIM_ITConfig(TIM2, TIM_IT_CC1 , ENABLE);
      TIM_Cmd(TIM2, ENABLE);
      break;
    default: TXState=TIM_TX_STATE_IDLE;
      break;
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
  }
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {     //MANCHESTER_3_4_BIT_TIME timeout has occured
    TIMFlag3_4=1;
    /* Get the input state */
    NewInputLevel=RX_PINSTATE?1:0;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
  }
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {    //MANCHESTER_STOP_BIT_TIME timeout has occured
    if(RxMachineState==RXMACHINESTATE_STOPBIT)
      RxByteValid=1;
    else
      RxByteValid=0;
    RxMachineState=RXMACHINESTATE_IDLE;
    TIM_Cmd(TIM2, DISABLE);
    TIM_SetCounter(TIM2,0);
    TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE); 
    TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);   
  }
}

void DALI_RX_bitbang_cb(uint8_t RxBit)
{ 
  if(DALIMaster_Mode==DALIMASTER_MODE_RX)
  {
    switch(RxMachineState)
    {
    case RXMACHINESTATE_IDLE:
      // Reset the TIM2.  
      TIM_ITConfig(TIM2, TIM_IT_CC3 , DISABLE); 
      TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
      TIM_SetCounter(TIM2,0);
      TIM_Cmd(TIM2, ENABLE);
      
      RxMachineState=RXMACHINESTATE_STARTBIT;
      break;
    case RXMACHINESTATE_STARTBIT: 
      TIM_Cmd(TIM2, DISABLE);
      // Detect Start bit bitrate 
      //TODO: Adapt MANCHESTER_3_4_BIT_TIME and MANCHESTER_STOP_BIT_TIME
      StartBit_DemiBitDuration=TIM_GetCounter(TIM2);
      
      // Detect Start Bit polarity 
      if(RX_PINSTATE)
        StartBitPolarity=0;     //Start bit is __/''
      else
        StartBitPolarity=1;     //Start bit is ''\__
      
      
      RxFrameBitPosition=(DALI_RX_BITS_NUMBER_TO_RECEIVE-1);
      RxMachineState=RXMACHINESTATE_RXBYTE;
      RxedByte=0;
      TIMFlag3_4=0;   
      TIM_SetCompare2(TIM2,MANCHESTER_3_4_BIT_TIME);
      TIM_SetCompare3(TIM2,MANCHESTER_STOP_BIT_TIME);
      TIM_Cmd(TIM2, ENABLE);
      TIM_SetCounter(TIM2,0);
      TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
      TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
      TIM_ITConfig(TIM2, TIM_IT_CC2 , ENABLE);
      TIM_ITConfig(TIM2, TIM_IT_CC3 , ENABLE);
      break;
    case RXMACHINESTATE_RXBYTE:
      if(TIMFlag3_4)
      {
        
        RxedByte |= (NewInputLevel<<(RxFrameBitPosition));
        TIMFlag3_4=0;
        
        if(RxFrameBitPosition==0)
        {
          TIM_ITConfig(TIM2, TIM_IT_CC2 , DISABLE);
          if(StartBitPolarity==0)
            RxedByte=~RxedByte;
          RxMachineState=RXMACHINESTATE_STOPBIT;
        }
        else
          RxFrameBitPosition--;
        
        // Reset the counter 
        TIM_Cmd(TIM2, DISABLE);
        TIM_SetCounter(TIM2,0);
        TIM_Cmd(TIM2, ENABLE);
      }      
      else
      { //should
        
      }
      break;
    case RXMACHINESTATE_STOPBIT:
      //wait for the timer to detect STOP bits
      break;
    default:break;
    }
  }
}
