#ifndef __GEAR_H__
#define __GEAR_H__
#include "main.h"


enum{
  gear_pos_1=0,
  gear_pos_N=1,
  gear_pos_2=2,
  gear_pos_3=3,
  gear_pos_4=4,
  gear_pos_5=5,
  gear_pos_lost=6
};

uint8_t gear_up(void);
uint8_t gear_down(void);
uint8_t gear_toNeutral(void);
uint8_t gear_getPosition(void);
uint8_t gear_isMoving(void);
uint8_t gear_stop(void);

#endif /* __GEAR_H__ */
