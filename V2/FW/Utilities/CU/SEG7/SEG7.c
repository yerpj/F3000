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
  case 0:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK );
    break;
  case 1:
    LEDbuffer_MaskSet(SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case 2:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case 3:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case 4:
    LEDbuffer_MaskSet(SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case 5:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK );
    break;
  case 6:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK );
    break;
  case 7:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK );
    break;
  case 8:
    LEDbuffer_MaskSet(SEG7_SEG_DP_MASK);
    break;
  case 9:
    LEDbuffer_MaskSet(SEG7_SEG_G_MASK);
    break;
  case 10:
    LEDbuffer_MaskSet(SEG7_SEG_A_MASK |
                      SEG7_SEG_B_MASK |
                      SEG7_SEG_C_MASK |
                      SEG7_SEG_D_MASK |
                      SEG7_SEG_E_MASK |
                      SEG7_SEG_F_MASK |
                      SEG7_SEG_G_MASK |
                      SEG7_SEG_DP_MASK);
    break;
  case 11:
    //nothing
    break;
  default:break;
  }
  LEDbuffer_refresh();
}


