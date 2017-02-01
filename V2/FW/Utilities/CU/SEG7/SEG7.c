#include "SEG7.h"

uint8_t SEG7_Set(uint8_t value)
{
  LEDbuffer_MaskReset(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_DP_MASK );
  switch(value)
  {
  case DEG7_0:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK );
    break;
  case DEG7_1:
    LEDbuffer_MaskSet(SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case DEG7_2:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case DEG7_3:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case DEG7_4:
    LEDbuffer_MaskSet(SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case DEG7_5:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case DEG7_6:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK );
    break;
  case DEG7_7:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case DEG7_DOT:
    LEDbuffer_MaskSet(SEG7_SEG_DP_MASK);
    break;
  case DEG7_LOST:
    LEDbuffer_MaskSet(SEG7_SEG_G_MASK);
    break;
  case DEG7_ALL:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_DP_MASK);
    break;
  case DEG7_NONE:
    break;
  case DEG7_A:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case DEG7_d:
    LEDbuffer_MaskSet(SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case DEG7_C:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK );
    break;
  default:break;
  }
  LEDbuffer_refresh();
  return 0;
}


