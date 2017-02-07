#include "gear.h"
#include "CU.h"

//gearbox task 
xTaskHandle Gear_taskHandler;
EventGroupHandle_t gear_Events;
uint8_t gear_mode=gear_mode_manual;
extern EventGroupHandle_t CU_Inputs_EventGroup;

uint8_t gear_current_pos=gear_pos_lost;
uint8_t gear_moving=0;

void gear_task(void * pvParameters)
{
  EventBits_t EventBits;
  uint32_t i=0;
  while(1)
  {
    EventBits=xEventGroupWaitBits(gear_Events,GEAR_EVENT_INCREASE|GEAR_EVENT_DECREASE|GEAR_EVENT_TONEUTRAL,pdFALSE,pdFALSE,1000);
    if( !EventBits )
    {//no event. continue
      continue;
    }
    else if( (EventBits & GEAR_EVENT_TONEUTRAL) !=0 )
    {//to neutral
      xEventGroupClearBits(gear_Events,GEAR_EVENT_TONEUTRAL);
      if( (gear_current_pos==gear_pos_lost) || (gear_current_pos==gear_pos_1) || (!CU_GetNeutralInput() && (gear_current_pos==gear_pos_N)) )   //TO BE VFERIFIED
      {
        SEG7_Set(DEG7_DOT);
        
        //clear CAME event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
        
        //clear NEUTRAL event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT);
        
        //begin turning motor
        gear_up();
        
        i=(GEAR_WAIT_ON_NEUTRAL_TIMEOUT_MS/2 /*same time as in while loop below*/ );
      
        //wait for NEUTRAL INPUT TO BE ASSERTED with timeout
        while( i && !(xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_NEUTRAL_BIT) )
        {
          if( (xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT) )
          {
            gear_stop();
            gear_current_pos=gear_pos_lost;
          }
          vTaskDelay(2);
          i--;
        }
        //clear CAME event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
        //begin turning motor
        gear_down();
        //wait on CAME event
        if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_CAME_TIMEOUT_MS) )
        {
          console_log("INFO: Missed CAME event");
          gear_current_pos=gear_pos_lost;
        }
        else
        {
          gear_current_pos=gear_pos_N;
        }
        gear_stop();
      }
      else if( gear_current_pos==gear_pos_2 )
      {
        SEG7_Set(DEG7_DOT);
        //clear CAME event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
        //begin turning motor
        gear_down();
        //wait on CAME event
        if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_CAME_TIMEOUT_MS) )
        {
          console_log("INFO: Missed CAME event");
          gear_current_pos=gear_pos_lost;
          gear_stop();
          SEG7_Set(DEG7_LOST);
          continue;
        }
        else
        {
          gear_current_pos=gear_pos_N;
        }
      }      
      SEG7_Set(DEG7_0);
    }
    else if( (EventBits & GEAR_EVENT_INCREASE) !=0 )
    {//increase
      xEventGroupClearBits(gear_Events,GEAR_EVENT_INCREASE);
      
      //set 7SEG to DOT
      SEG7_Set(DEG7_DOT);
      
      //clear CAME event bit
      xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
      
      //clear SHIFTER event bit
      xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_SHIFTER_BIT);
      
      //begin turning motor
      gear_up();
      
      i=(GEAR_WAIT_ON_CAME_TIMEOUT_MS/5 /*same time as in while loop below*/ );
      
      //wait on CAME event of input HIGH with timeout
      while( i && !(xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT) && !CU_GetCameInput())
      {
        if(gear_mode!=gear_mode_manual)
        {
          if(CU_GetShifterInput() && (!CU_GetEmbrayInput()) )
            CU_STOP_On();
          else
            CU_STOP_Off();
        }
        vTaskDelay(5);
        i--;
      }
      if(i==0)
        console_log("INFO: Missed CAME event");
      gear_stop();
      
      //set 7SEG to a valid value
      SEG7_Set(DEG7_0);
    }
    else if( (EventBits & GEAR_EVENT_DECREASE) !=0 )
    {//decrease
      xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE);
      
      //set 7SEG to DOT
      SEG7_Set(DEG7_DOT);
      
      //clear CAME event bit
      xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
      
      //begin turning motor
      gear_down();
      
      //wait on CAME or timeout if CAME is not already HIGH
      if(!CU_GetCameInput()) /* WROOOOOOONG !!!!! NEED SOME POLLING ON EACH OF INCREASE/DECREASE/TONEUTRAL FUNCTIONS!!! */
      {
        if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_CAME_TIMEOUT_MS) )
          console_log("INFO: Missed CAME event");
      }
      gear_stop();
      
      //set 7SEG to a valid value
      SEG7_Set(DEG7_0);
    }
    //vTaskDelay(50);
  }
}

uint8_t gear_SetMode(uint8_t mode)
{
  if( (mode!=gear_mode_manual) && (mode!=gear_mode_semiauto) && (mode!=gear_mode_auto) )
    return 1;
  
  gear_mode=mode;
  
  return 0;
}

uint8_t gear_GetMode(void)
{
  return gear_mode;
}

uint8_t gear_Init(void)
{
  gear_Events= xEventGroupCreate();
  if(gear_Events == NULL)
    return 1;
  xTaskCreate(gear_task, "GearBox", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &Gear_taskHandler);
  return 0;
}



uint8_t gear_increase(void)
{
  /*SEG7_Set(DEG7_DOT);
  xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
  gear_up();
  xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdTRUE,5000);
  gear_stop();*/
  xEventGroupSetBits(gear_Events,GEAR_EVENT_INCREASE);
  //setSysTick_Delay_Timer(1000,gear_stop);
  return 0;
}

uint8_t gear_decrease(void)
{
  /*gear_down();
  setSysTick_Delay_Timer(1000,gear_stop);*/
  xEventGroupSetBits(gear_Events,GEAR_EVENT_DECREASE);
  return 0;
}

uint8_t gear_toNeutral(void)
{
  xEventGroupSetBits(gear_Events,GEAR_EVENT_TONEUTRAL);
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

uint8_t gear_getPosition(void)
{
  return gear_current_pos;
}

uint8_t gear_isMoving(void)
{
  return gear_moving;
}