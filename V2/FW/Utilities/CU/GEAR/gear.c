#include "gear.h"
#include "CU.h"
#include "main.h"
#include "SEG7.h"
#include "stm32f2xx_it.h"

//#define USE_DEVMOTOR

//gearbox task 
xTaskHandle Gear_taskHandler;
EventGroupHandle_t gear_Events;
uint8_t gear_mode=gear_mode_manual;
extern EventGroupHandle_t CU_Inputs_EventGroup;

uint8_t gear_current_pos=gear_pos_lost;
uint8_t gear_moving=0;
uint32_t Rapport_pm=0;
  
EventBits_t RapportsEvents;

void gear_task(void * pvParameters)
{
  EventBits_t EventBits;
  uint32_t i=0;
  int32_t timeout=0;
  vTaskDelay(2000);
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
      RapportsEvents=xEventGroupGetBits(CU_Inputs_EventGroup);
      if( RapportsEvents&CU_INPUT_EVENT_RAPPORTp_BIT )
      {
        if(RapportsEvents&CU_INPUT_EVENT_NEUTRAL_BIT)
        {
          xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT);
          gear_current_pos=gear_pos_2;
        }
        else if(gear_current_pos!=gear_pos_lost)
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
      else if( RapportsEvents&CU_INPUT_EVENT_RAPPORTm_BIT )
      {
        if(RapportsEvents&CU_INPUT_EVENT_NEUTRAL_BIT)
          gear_current_pos=gear_pos_1;
        else if(gear_current_pos!=gear_pos_lost)
        {
          if(gear_current_pos==gear_pos_N)
          {
            xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT);
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
      if( CU_GetNeutralInput() )
      {
        gear_current_pos=gear_pos_N;
      }
      else if(gear_current_pos==gear_pos_N)
      { //handle the case where we think gear is N but N input is not active
        gear_current_pos=gear_pos_lost;
      }
      SEG7_Set(gear_current_pos);
      continue;
    }
    else if( (EventBits & GEAR_EVENT_TONEUTRAL) !=0)
/**/{//to neutral
      if(gear_current_pos==gear_pos_lost || gear_current_pos==gear_pos_1 || gear_current_pos==gear_pos_2 )
      {
        SEG7_Set(SEG7_DOT);
        
        //clear CAME event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_CAME_BIT);
        //clear NEUTRAL event bit
        xEventGroupClearBits(CU_Inputs_EventGroup,CU_INPUT_EVENT_NEUTRAL_BIT);
        
        if( gear_current_pos==gear_pos_1 || gear_current_pos==gear_pos_lost )
        {
          //begin turning motor
          gear_up();
          
          timeout=GEAR_WAIT_ON_NEUTRAL_TIMEOUT_MS;
        
          //wait on Neutral event
          while( !(xEventGroupGetBits(CU_Inputs_EventGroup) & CU_INPUT_EVENT_NEUTRAL_BIT ) && timeout>0)
          {
            vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
            timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
            if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT )
            {//error. Put timeout to zero to force exiting the loop
              timeout=0;
              console_log("INFO: Missed Neutral event while going to Neutral position. Lost.");
              gear_current_pos=gear_pos_lost;
            }
          }
          
          if(timeout>0)
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
              //gear_current_pos=gear_pos_N;
            }
          }
          gear_stop();
        }
        else if( gear_current_pos==gear_pos_2 )
        {
          //begin turning motor
          gear_down();
          
          //wait on Neutral event
          while( !(xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_NEUTRAL_BIT ) && timeout>0)
          {
            vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
            timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
            if( xEventGroupGetBits(CU_Inputs_EventGroup)&CU_INPUT_EVENT_CAME_BIT )
            {//error. Put timeout to zero to force exiting the loop
              timeout=0;
              console_log("INFO: Missed Neutral event while going to Neutral position. Lost.");
              gear_current_pos=gear_pos_lost;
            }
          }
          if(timeout>0)
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
              //gear_current_pos=gear_pos_N;
            }
          }
          gear_stop();
        }
      }
      xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
    }
    else if( (EventBits & GEAR_EVENT_INCREASE) !=0 )
/**/{//increase
      //check if EMBRAY is pressed when in neutral or if RPM is below "ralenti"
      if( (gear_current_pos!=gear_pos_N) || ( CU_GetEmbrayInput() || ( Regime_getRPM()<(CU_RPM_MIN-100) ) ) )
      {
        //set 7SEG to DOT
        SEG7_Set(SEG7_DOT);
        
        //clear Neutral event. In case of Neutral event while increasing, will be used to determine we are in gear 2
        xEventGroupClearBits(gear_Events,CU_INPUT_EVENT_NEUTRAL_BIT);
        
        //begin turning motor
        gear_up();
        
        //wait until CAME input is low
        timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
        while( CU_GetCameInput() && timeout>0 )
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
        while( !CU_GetCameInput() && timeout>0 )
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
        vTaskDelay(GetBlankingTime_ms());  //delay is mandatory when increasing gear
        xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
      }
      else
      {
        xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
      }
    }
    else if( (EventBits & GEAR_EVENT_DECREASE) !=0 )
/**/{//decrease
  
      //check if EMBRAY is pressed when in neutral or if RPM is below "ralenti"
      if( (gear_current_pos!=gear_pos_N) || ( CU_GetEmbrayInput() || ( Regime_getRPM()<(CU_RPM_MIN-100) ) ) )
      {
        //set 7SEG to DOT
        SEG7_Set(SEG7_DOT);
        
        //clear Neutral event. In case of Neutral event while decreasing, will be used to determine we are in gear 1
        xEventGroupClearBits(gear_Events,CU_INPUT_EVENT_NEUTRAL_BIT);
        
        //begin turning motor
        gear_down();
        
        //wait until CAME input is low
        timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
        while( CU_GetCameInput() && timeout>0 )
        {
          /*if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
          {
            if(CU_GetShifterInput())
              CU_STOP_On();
            else
              CU_STOP_Off();
          }*/
          vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
          timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
        }
        
        //wait until CAME input is high
        timeout=GEAR_WAIT_ON_CAME_TIMEOUT_MS;
        while( !CU_GetCameInput() && timeout>0 )
        {
          /*if( gear_mode!=gear_mode_manual && !CU_GetEmbrayInput() )
          {
            if(CU_GetShifterInput())
              CU_STOP_On();
            else
              CU_STOP_Off();
          }*/
          vTaskDelay(GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS);
          timeout-=GEAR_WAIT_ON_SIGNAL_POLLING_DELAY_MS; 
        }
        
        /* stop motor */
        CU_STOP_Off();
        gear_stop();
        vTaskDelay(GetBlankingTime_ms());//delay is optionnal when decreasing gear. Final user prefers to keep it anyway...
        xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
      }
      else
      {
        xEventGroupClearBits(gear_Events,GEAR_EVENT_DECREASE|GEAR_EVENT_INCREASE|GEAR_EVENT_TONEUTRAL);
      }
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
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_ResetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
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
  GPIO_ResetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
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
  GPIO_SetBits(MOTEURm_OUTPUT_GPIO_PORT,MOTEURm_OUTPUT_PIN);
  GPIO_SetBits(MOTEURp_OUTPUT_GPIO_PORT,MOTEURp_OUTPUT_PIN);
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
