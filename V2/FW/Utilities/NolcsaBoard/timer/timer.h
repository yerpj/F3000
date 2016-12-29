#ifndef _TIMER_H_
#define _TIMER_H_
#include "nolcsa.h"

void Alarm_us(uint8_t channel, uint32_t time_us, void (*cb)(void));
void timer_set_alarm(uint8_t channel, uint32_t delta_t,void (*cb)(void));
void timer_unset_alarm(uint8_t channel);
void timer_init(void);
void timer_blocking_wait(uint32_t milliseconds);
void timer_debug(void);

#endif /* _TIMER_H_ */