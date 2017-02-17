#ifndef __GEAR_H__
#define __GEAR_H__
#include "main.h"

#define GEAR_EVENT_INCREASE     (0x01<<0)
#define GEAR_EVENT_DECREASE     (0x01<<1)
#define GEAR_EVENT_TONEUTRAL    (0x01<<2)


#define GEAR_WAIT_ON_CAME_TIMEOUT_MS (2000)
#define GEAR_WAIT_ON_NEUTRAL_TIMEOUT_MS (1000)

enum{
  gear_pos_1=1,
  gear_pos_N=0,
  gear_pos_2=2,
  gear_pos_3=3,
  gear_pos_4=4,
  gear_pos_5=5,
  gear_pos_6=6,
  gear_pos_lost=9
};

enum{
  gear_mode_manual=0,
  gear_mode_semiauto=1,
  gear_mode_auto=2
};

uint8_t gear_Init(void);
uint8_t gear_GetMode(void);
uint8_t gear_SetMode(uint8_t mode);
uint8_t gear_up(void);
uint8_t gear_down(void);
uint8_t gear_getPosition(void);
uint8_t gear_isMoving(void);
uint8_t gear_stop(void);

uint8_t gear_increase(void);
uint8_t gear_decrease(void);
uint8_t gear_toNeutral(void);

#endif /* __GEAR_H__ */
