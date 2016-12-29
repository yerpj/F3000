#ifndef _TIMER_H
#define _TIMER_H

#include "main.h"



void timer_set_alarm(uint8_t channel, uint32_t delta_t,uint16_t (*cb)(void));
void timer_unset_alarm(uint8_t channel);
void timer_init(void);
void timer_blocking_wait(uint32_t milliseconds);
void timer_debug(void);

#endif /* _TIMER_H */