#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "main.h"
#include "timer.h"

enum{
  BUTTON_PRESSED=1,
  BUTTON_RELEASED=0,
};

typedef union
{
  struct
  {
    uint32_t ShortPressEvent : 1;
    uint32_t LongPressEvent : 1;
    
  }Event;
  uint32_t GenericPressEvent;							/*!< short cut to all flags (for reset) */
}s_ButtonPressEvent;

typedef void (*button_callback_t)(uint8_t state);

void PushButtonInit(void (*button_callback)(uint8_t));
void PushButtonCallback(uint8_t state);
static uint16_t PushButtonLongPressTimeout(void);
static uint16_t PushButtonDoubleClickTimeout(void);
uint8_t PushButtonRead(void);

#endif /* _BUTTON_H_ */