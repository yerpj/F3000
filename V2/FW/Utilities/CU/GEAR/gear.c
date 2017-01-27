#include "gear.h"
#include "CU.h"


uint8_t gear_current_pos=gear_pos_lost;
uint8_t gear_moving=0;

uint8_t gear_increase(void)
{
  xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
  gear_up();
  xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdTRUE,5000);
  gear_stop();
  //setSysTick_Delay_Timer(1000,gear_stop);
  return 0;
}

uint8_t gear_decrease(void)
{
  gear_down();
  setSysTick_Delay_Timer(1000,gear_stop);
  return 0;
}

uint8_t gear_up(void)
{
  gear_moving=1;
#ifdef USE_BREADBOARD
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* USE_BREADBOARD */
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* USE_BREADBOARD */
  return 0;
}

uint8_t gear_down(void)
{
  gear_moving=1;
#ifdef USE_BREADBOARD
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* USE_BREADBOARD */
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* USE_BREADBOARD */
  return 0;
}

uint8_t gear_stop(void)
{
  gear_moving=0;
#ifdef USE_BREADBOARD
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* USE_BREADBOARD */
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* USE_BREADBOARD */
  return 0;
}

uint8_t gear_toNeutral(void)
{
  if(gear_current_pos!=gear_pos_N)
  {
    
  }
  return 0;
}

uint8_t gear_getPosition(void)
{
  return gear_current_pos;
}

uint8_t gear_isMoving(void)
{
  return gear_moving;
}