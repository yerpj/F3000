#ifndef _COMMONDEFS_H_
#define _COMMONDEFS_H_
#include "stm32f2xx.h"

#define BIT0 (0x01)
#define BIT1 (BIT0<<1)
#define BIT2 (BIT0<<2)
#define BIT3 (BIT0<<3)
#define BIT4 (BIT0<<4)
#define BIT5 (BIT0<<5)
#define BIT6 (BIT0<<6)
#define BIT7 (BIT0<<7)
#define BIT8 (BIT0<<8)
#define BIT9 (BIT0<<9)
#define BIT10 (BIT0<<10)
#define BIT11 (BIT0<<11)
#define BIT12 (BIT0<<12)
#define BIT13 (BIT0<<13)
#define BIT14 (BIT0<<14)
#define BIT15 (BIT0<<15)
#define BIT16 (BIT0<<16)
#define BIT17 (BIT0<<17)
#define BIT18 (BIT0<<18)
#define BIT19 (BIT0<<19)
#define BIT20 (BIT0<<20)

typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins */
  GPIO_TypeDef *GPIO_Port;              /*!< Specifies the GPIO port*/
}GPIO_Def;

#endif /* _COMMONDEFS_H_ */