#include "button.h"

//#define debug

uint8_t Button_ShortPressEvent=0;
uint8_t Button_LongPressEvent=0;
uint8_t PushButtonLongPressEvent=0;
uint8_t PushButtonDoubleClickEvent=0;

s_ButtonPressEvent ButtonEvents;

void (*PushButton_cb)(uint8_t state)=0;

void PushButtonInit(void (*button_callback)(uint8_t))
{

  if(button_callback)
    PushButton_cb=button_callback;      //user defined callback
  else
    PushButton_cb=PushButtonCallback;//local callback
  STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_EXTI);

}

uint8_t PushButtonRead(void)
{
  return GPIO_ReadInputDataBit(USER_BUTTON_GPIO_PORT,USER_BUTTON_PIN);
}

void PushButtonCallback(uint8_t state)
{
  switch(state)
  {
    case BUTTON_PRESSED:
      timer_set_alarm(3,500,PushButtonLongPressTimeout);
      break;
    case BUTTON_RELEASED:
      if(PushButtonLongPressEvent)
      {
        PushButtonLongPressEvent=0;
#ifdef debug
        Serial_SendLine("\r\nButton: Long Press Event\r\n",80);  
#endif /* debug */
        Button_LongPressEvent=1;
        ButtonEvents.Event.LongPressEvent=1;
      }
      else
      {
#ifdef debug
        Serial_SendLine("\r\nButton: Short Press Event\r\n",80);
#endif /* debug */
        Button_ShortPressEvent=1;
        ButtonEvents.Event.ShortPressEvent=1;
      }
      timer_unset_alarm(2);
      break;
    default:break;
  }
}

static uint16_t PushButtonLongPressTimeout(void)
{
  PushButtonLongPressEvent=1;
  return 0;
}

static uint16_t PushButtonDoubleClickTimeout(void)
{
  PushButtonDoubleClickEvent=1;
  return 0;
}