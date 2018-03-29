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
  case SEG7_0:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK );
    break;
  case SEG7_1:
    LEDbuffer_MaskSet(SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case SEG7_2:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case SEG7_3:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case SEG7_4:
    LEDbuffer_MaskSet(SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case SEG7_5:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case SEG7_6:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK );
    break;
  case SEG7_7:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case SEG7_8:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case SEG7_9:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case SEG7_DOT:
    LEDbuffer_MaskSet(SEG7_SEG_DP_MASK);
    break;
  case SEG7_LOST:
    LEDbuffer_MaskSet(SEG7_SEG_G_MASK);
    break;
  case SEG7_ALL:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_DP_MASK);
    break;
  case SEG7_NONE:
    break;
  case SEG7_A:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case SEG7_d:
    LEDbuffer_MaskSet(SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_G_MASK );
    break;
  case SEG7_C:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK );
    break;
  case SEG7_E:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_D_MASK );
    break;
  default:break;
  }
  LEDbuffer_refresh(0);
  return 0;
}


