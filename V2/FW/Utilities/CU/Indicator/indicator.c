#include "indicator.h"

uint8_t Indicator_LED_OIL_Set(void)
{
  LEDbuffer_MaskSet(LED_OIL_MASK);
  LEDbuffer_refresh(0);
  return 0;
}

uint8_t Indicator_LED_OIL_Reset(void)
{
  LEDbuffer_MaskReset(LED_OIL_MASK);
  LEDbuffer_refresh(0);
  return 0;
}

uint8_t Indicator_LED_N_Set(void)
{
  LEDbuffer_MaskSet(LED_N_MASK);
  LEDbuffer_refresh(0);
  return 0;
}

uint8_t Indicator_LED_N_Reset(void)
{
  LEDbuffer_MaskReset(LED_N_MASK);
  LEDbuffer_refresh(0);
  return 0;
}
uint8_t Indicator_LED_Mode_Set(uint8_t Mode)
{
  LEDbuffer_MaskReset(LED_MODE1_MASK|LED_MODE2_MASK|LED_MODE3_MASK);
  switch(Mode)
  {
  case 1:
    LEDbuffer_MaskSet(LED_MODE2_MASK);
    break;
  case 2:
    LEDbuffer_MaskSet(LED_MODE3_MASK);
    break;
  case 3:
    LEDbuffer_MaskSet(LED_MODE1_MASK);
    break;
  default:
    return 1;
  }
  LEDbuffer_refresh(0);
  return 0;
}

uint8_t Indicator_LED_Temp_Set(uint8_t TempState)
{
  static uint8_t blinkState=0;
  LEDbuffer_MaskReset(LED_TEMP1_MASK|LED_TEMP2_MASK|LED_TEMP3_MASK);
  switch(TempState)
  {
  case 0:
  case 1:
    break;
  case 2:
    LEDbuffer_MaskSet(LED_TEMP1_MASK);
    break;
  case 3:
    LEDbuffer_MaskSet(LED_TEMP1_MASK|LED_TEMP2_MASK);
    break;
  case 4:
    LEDbuffer_MaskSet(LED_TEMP2_MASK);
    break;
  case 5:
    LEDbuffer_MaskSet(LED_TEMP2_MASK|LED_TEMP3_MASK);
    break;
  case 6:
    LEDbuffer_MaskSet(LED_TEMP3_MASK);
    break;
  case 7:
    if(blinkState)
    {
      LEDbuffer_MaskSet(LED_TEMP3_MASK);
      blinkState=0;
    }
    else
    {
      LEDbuffer_MaskReset(LED_TEMP3_MASK);
      blinkState=1;
    }
    break;
  default:
    return 1;
  }
  LEDbuffer_refresh(0);
  return 0;
}




