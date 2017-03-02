#include "gear.h"
#include "CU.h"
#include "main.h"

//#define USE_DEVMOTOR

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
  uint32_t timeout=0;
  while(1)
  {
    if( MainAppGetMode()!=MainMode_App )
    {
      vTaskDelay(20);
      if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTp_BIT )
      {
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTp_BIT);
      }
      if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTm_BIT )
      {
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTm_BIT);
      }
      continue;
    }
    EventBits=xEventGroupWaitBits(gear_Events,GEAR_EVENT_INCREASE|GEAR_EVENT_DECREASE|GEAR_EVENT_TONEUTRAL,pdFALSE,pdFALSE,50);
    if( !EventBits )
    {//no event--> Handle SEG7 and continue
      if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTp_BIT )
      {
        if(gear_current_pos!=gear_pos_lost)
        {
          if(gear_current_pos==gear_pos_N)
          {
            gear_current_pos=gear_pos_2;
          }
          else
          {
            if(gear_current_pos<gear_pos_5)
              gear_current_pos++;
          }
        }
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTp_BIT);
      }
      else if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_RAPPORTm_BIT )
      {
        if(gear_current_pos!=gear_pos_lost)
        {
          if(gear_current_pos==gear_pos_N)
          {
            gear_current_pos=gear_pos_1;
          }
          else
          {
            if(gear_current_pos>gear_pos_1)
              gear_current_pos--;
          }
        }
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_RAPPORTm_BIT);
      }
      SEG7_Set(gear_current_pos);
      continue;
    }
    else if( (EventBits & GEAR_EVENT_TONEUTRAL) !=0)
/**/{//to neutral
      if(gear_current_pos==gear_pos_lost || gear_current_pos==gear_pos_1 || gear_current_pos==gear_pos_2 )
      {
        SEG7_Set(SEG7_DOT);
        //clear NEUTRAL event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT);
        
        if( gear_current_pos==gear_pos_1 || gear_current_pos==gear_pos_lost )
        {
          //begin turning motor
          gear_up();
          
          //wait on Neutral event
          if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_NEUTRAL_TIMEOUT_MS) )
          {  //error
            console_log("INFO: Missed Neutral event while going to Neutral position. Lost.");
            gear_current_pos=gear_pos_lost;
          }
          else
          {
            //clear CAME event bit
            xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
            
            //begin turning motor in reverse direction
            gear_down();
            
            if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_CAME_TIMEOUT_MS) )
            {  //error
              console_log("INFO: Missed Came event while going to Neutral position. Lost.");
              gear_current_pos=gear_pos_lost;
            }
            else
            {
              gear_current_pos=gear_pos_N;
            }
          }
          gear_stop();
        }
        else if( gear_current_pos==gear_pos_2 )
        {
          //begin turning motor
          gear_down();
          
          //wait on Neutral event
          if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_NEUTRAL_TIMEOUT_MS) )
          {  //error
            console_log("INFO: Missed Neutral event while going to Neutral position. Lost.");
            gear_current_pos=gear_pos_lost;
          }
          else
          {
            //clear CAME event bit
            xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
            
            //begin turning motor in reverse direction
            gear_up();
            
            if( !xEventGroupWaitBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT,pdTRUE,pdFALSE,GEAR_WAIT_ON_CAME_TIMEOUT_MS) )
            {  //error
              console_log("INFO: Missed Came event while going to Neutral position. Lost.");
              gear_current_pos=gear_pos_lost;
            }
            else
            {
              gear_current_pos=gear_pos_N;
            }
          }
          gear_stop();
        }
      }
      xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
    }
    else if( (EventBits & GEAR_EVENT_INCREASE) !=0 )
/**/{//increase
      
      //set 7SEG to DOT
      SEG7_Set(SEG7_DOT);
      
      //begin turning motor
      gear_up();
      
      //wait until CAME input is low
      timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
      while( CU_GetCameInput() && timeout>0 )// TODO: add a timeout mechanism HERE
      {
        if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
        {
          if(CU_GetShifterInput())
            CU_STOP_On();
          else
            CU_STOP_Off();
        }
        vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
        timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
      }
      
      //wait until CAME input is high
      timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
      while( !CU_GetCameInput() && timeout>0 )// TODO: add a timeout mechanism HERE
      {
        if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
        {
          if(CU_GetShifterInput())
            CU_STOP_On();
          else
            CU_STOP_Off();
        }
        vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
        timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
      }
      
      /* stop motor */
      CU_STOP_Off();
      gear_stop();
      
      /* update SEG7 */
      /*if(gear_current_pos!=gear_pos_lost)
      {
        if(gear_current_pos==gear_pos_N)
        {
          gear_current_pos=gear_pos_2;
          SEG7_Set(gear_current_pos);
        }
        else
        {
          if(gear_current_pos<gear_pos_6)
            gear_current_pos++;
          SEG7_Set(gear_current_pos);
        }
      }*/
      xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
    }
    else if( (EventBits & GEAR_EVENT_DECREASE) !=0 )
/**/{//decrease
      
      //set 7SEG to DOT
      SEG7_Set(SEG7_DOT);
      
      //begin turning motor
      gear_down();
      
      //wait until CAME input is low
      timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
      while( CU_GetCameInput() && timeout>0 )// TODO: add a timeout mechanism HERE
      {
        if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
        {
          if(CU_GetShifterInput())
            CU_STOP_On();
          else
            CU_STOP_Off();
        }
        vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
        timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
      }
      
      //wait until CAME input is high
      timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
      while( !CU_GetCameInput() && timeout>0 )// TODO: add a timeout mechanism HERE
      {
        if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
        {
          if(CU_GetShifterInput())
            CU_STOP_On();
          else
            CU_STOP_Off();
        }
        vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
        timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
      }
      
      /* stop motor */
      CU_STOP_Off();
      gear_stop();
      
      /* update SEG7 */
      /*if(gear_current_pos!=gear_pos_lost)
      {
        if(gear_current_pos==gear_pos_N)
        {
          gear_current_pos=gear_pos_1;
          SEG7_Set(gear_current_pos);
        }
        else
        {
          if(gear_current_pos>gear_pos_1)
            gear_current_pos--;
          SEG7_Set(gear_current_pos);
        }
      }*/
      xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
    }
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
  if(CU_GetNeutralInput())
    gear_current_pos=gear_pos_N;
  SEG7_Set(gear_getPosition());
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
  if( MainAppGetMode()==MainMode_App )
    xEventGroupSetBits(gear_Events,GEAR_EVENT_TONEUTRAL);
  return 0;
}

uint8_t gear_up(void)
{
  gear_moving=1;
#if  defined(USE_BREADBOARD) || defined(USE_DEVMOTOR)
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
  return 0;
}

uint8_t gear_down(void)
{
  gear_moving=1;
#if  defined(USE_BREADBOARD) || defined(USE_DEVMOTOR)
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
  return 0;
}

uint8_t gear_stop(void)
{
  gear_moving=0;
#if  defined(USE_BREADBOARD) || defined(USE_DEVMOTOR)
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);//dir
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);//enable
#else /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
#endif /* defined(USE_BREADBOARD) || defined(USE_DEVMOTOR) */
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