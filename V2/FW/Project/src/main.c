#include "main.h"

#define UID_ADDRESS_BASE (uint8_t*)(0x1FFF7A10)
#define UID_BYTE_SIZE   (12)
uint8_t UID[8];
uint8_t NXS_UID[12];
uint8_t NXS_EUI64[8];

//applications
xTaskHandle AppTaskHandle,ConfigTaskHandle,PeriodicTaskHandle,DiagnosticTaskHandle;
SemaphoreHandle_t MainAppMutex;
SemaphoreHandle_t MainConfigMutex;
SemaphoreHandle_t MainDiagMutex;

//application modes
uint8_t MainMode=MainMode_App;

//other variables
uint8_t Vreg_based_LED=0;
uint8_t str[300];
EventGroupHandle_t CU_Inputs_EventGroup;

uint8_t MainAppGetMode(void)
{
  return MainMode;
}

uint8_t MainAppChangeMode(uint8_t Mode)
{
  //take MainAppMutex first
  if( xSemaphoreTake( MainAppMutex, ( TickType_t ) 1000 ) != pdTRUE )
  {
    return 1;
  }
  //then take MainConfigMutex too
  if( xSemaphoreTake( MainConfigMutex, ( TickType_t ) 1000 ) != pdTRUE )
  {
    xSemaphoreGive(MainAppMutex);
    return 1;
  }
  //finally take MainDiagMutex too
  if( xSemaphoreTake( MainDiagMutex, ( TickType_t ) 1000 ) != pdTRUE )
  {
    xSemaphoreGive(MainConfigMutex);
    xSemaphoreGive(MainAppMutex);
    return 1;
  }
  
  switch(Mode)
  {
  case MainMode_App:
    MainMode=MainMode_App;
    break;
  case MainMode_Diagnostic:
    MainMode=MainMode_Diagnostic;
    break;
  case MainMode_Configuration:
    MainMode=MainMode_Configuration;
    break;
  default:break;
  }
  //release mutexes 
  xSemaphoreGive(MainAppMutex);
  xSemaphoreGive(MainConfigMutex);
  xSemaphoreGive(MainDiagMutex);
  return 0;
}

void ToggleLed1(void * pvParameters)
{
  uint32_t led_value=1, direction=0, max=20;
  for( ;; )
  {
    if(direction)
    {
      if(led_value<max)
        led_value++;
      else
        direction=0;      
    }
    else
    {
      
      if(led_value>1)
        led_value--;
      else
        direction=1;    
    }
    CU_LEDOn(LED_BLUE);
    vTaskDelay(led_value);
    CU_LEDOff(LED_BLUE);
    vTaskDelay(max-led_value);
  }
}

void F3000_Conf(void * pvParameters)
{
  uint8_t dummy=0;
  while(1)
  {
    if(MainMode==MainMode_Configuration)
    {
      SEG7_Set(DEG7_C);
      //take MainConfigMutex 
      if( xSemaphoreTake( MainConfigMutex, ( TickType_t ) 100 ) != pdTRUE )
      {
        continue;
      }
      
      dummy++;
      
      //release MainConfigMutex 
      xSemaphoreGive(MainConfigMutex);
      vTaskDelay(100);
    }
    else
      vTaskDelay(200);
    
  }
}

void F3000_Diag(void * pvParameters)
{
  uint8_t dummy=0;
  while(1)
  {
    if(MainMode==MainMode_Diagnostic)
    {
      SEG7_Set(DEG7_d);
      //take MainDiagMutex 
      if( xSemaphoreTake( MainDiagMutex, ( TickType_t ) 100 ) != pdTRUE )
      {
        continue;
      }
      
      bargraph_MaskSet(CU_ReadInputsRaw());
     
      //release MainDiagMutex 
      xSemaphoreGive(MainDiagMutex);
      
      if(CU_GetStopButton())
      {
        MainAppChangeMode(MainMode_App);
      }
      vTaskDelay(20);
    }
    else
      vTaskDelay(200);
  }
}

void F3000_Periodic(void * pvParameters)
{
  uint32_t i=0;
  while(1)
  {
    vTaskDelay(100);
    
    if(CU_GetNeutralButton())
    {
      if(gear_getPosition()==gear_pos_N)
      {
        i=20;
        while(i && CU_GetNeutralButton())
        {
          vTaskDelay(100);
          i--;
        }
        if(CU_GetNeutralButton())
        {
          if(MainMode==MainMode_App)
          {
            if(MainAppChangeMode(MainMode_Diagnostic))
            {
              //problem
            }
            //bargraph_Set(1,7,0);
          }
          else if(MainMode==MainMode_Diagnostic)
          {
            if(MainAppChangeMode(MainMode_Configuration))
            {
              //problem
            }
            //bargraph_Set(7,14,0);
          }
          else if(MainMode==MainMode_Configuration)
          {
            if(MainAppChangeMode(MainMode_App))
            {
              //problem
            }
          }
        }
      }
      else
      {
        gear_toNeutral();
      }
    }
    //check MODE buttons
    Indicator_LED_Mode_Set(CU_GetMode());
    //handle temperature sensor
    Indicator_LED_Temp_Set(0/*tempSensor_Get_State()*/);
    Vreg_based_LED=((uint8_t)(tempSensor_Get_Temp()*4.2))%22;

    //handle OIL sensor
    if(CU_GetOilWarning())
      Indicator_LED_OIL_Set();
    else
      Indicator_LED_OIL_Reset();
    //handle bargraph
    
    
    //handle STOP button
    if(CU_GetStopButton())
      CU_STOP_On();
    else
      CU_STOP_Off();
  }
}

void F3000_App(void * pvParameters)
{
  uint8_t err=0;
  if(CU_Inputs_EventGroup==NULL)
    err++;
  
  DebouncerInit(CU_Inputs_EventGroup);
  //uint32_t InputMask,GPIO_TypeDef* GPIO,uint16_t Pin,uint8_t Edge,uint32_t Event,uint32_t DebounceTime_ms
  DebouncerAddInput(CU_INPUT_EVENT_CAME_BIT,CAME_INPUT_GPIO_PORT,CAME_INPUT_PIN,EXTI_Trigger_Rising,CU_INPUT_EVENT_CAME_BIT,500);
  
  
  
  /*bargraph_Set(1,1,Vreg_based_LED);
  LEDbuffer_MaskSet(0xFFFFFFFFFFFF);
  LEDbuffer_refresh();
  LEDbuffer_MaskReset(0xFFFFFFFFFFFF);
  LEDbuffer_refresh();*/
  uint8_t helloWorld[]="Hello World";
  uint8_t readback[12]={0,0,0,0,0,0,0,0,0,0,0,0};
  uint8_t status;
  uint8_t Flash_ID[3];
  flash_read_ID(Flash_ID);
  
  flash_Write_Enable();
  status=flash_read_Status();
  flash_Sector_Erase(0);
  status=flash_read_Status();
  flash_Write_Enable();
  status=flash_read_Status();
  flash_Write_Sector(helloWorld,12,0);
  status=flash_read_Status();
  flash_read_Data(readback,12,0);
  status=flash_read_Status();
  status=flash_read_Status();
  flash_read_ID(Flash_ID);

  while(!err)
  {
    if(MainMode==MainMode_App)
    {
      //take MainAppMutex first
      if( xSemaphoreTake( MainAppMutex, ( TickType_t ) 100 ) != pdTRUE )
      {
        continue;
      }
      
      /*if(CU_GetNeutralButton())
      {
       gear_toNeutral();
      }*/
      bargraph_Set(1,CU_RPMToBargraph());
      
      //release MainAppMutex 
      xSemaphoreGive(MainAppMutex);
      vTaskDelay(50);
    }
    else
      vTaskDelay(200);
    
  }
  while(1)
    vTaskDelay(1000);
}

uint8_t F3000CLIInterpreter(uint8_t *raw)
{
  uint8_t *cmd=raw;
  if(strstr(cmd,"SYS -g BuildDate")>0)
  {
    CLI_Output(__DATE__":"__TIME__);
    return 0;
  }
  if(strstr(cmd,"SYS -g Temp")>0)
  {
    CLI_Output("Temp: not yet measured");
    return 0;
  }
  else if(strstr(cmd,"SYS -r")>0)
  {
    CLI_Output("Rebooting... Please unconnect and reconnect Bluetooth app");
    vTaskDelay(2000);
    NVIC_SystemReset();
  }
  else if(strstr(cmd,"GEAR -s UP")>0)
  {
    gear_increase();
    CLI_Output("GEAR: OK");
  }
  else if(strstr(cmd,"GEAR -s DOWN")>0)
  {
    gear_decrease();
    CLI_Output("GEAR: OK");
  }
  else if(strstr(cmd,"GEAR -s NEUTRAL")>0)
  {
    gear_toNeutral();
    CLI_Output("GEAR: OK");
  }
  else
  {
    CLI_Output("\r\nCommand ERROR");
    return 1;
  }
  CLI_Output("\r\nDone");
  return 0;
}

void main(void)
{
  /* System function that updates the SystemCoreClock variable. */
  SystemCoreClockUpdate();
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );//no bits of sub-priority. Only preemption priorities are used
  UID_Init(UID_ADDRESS_BASE,UID_BYTE_SIZE);
  UID_getUID(UID);
  UID_getNXSFormat(NXS_UID);
  EUI64_getNXSFormat(NXS_EUI64);
  //LEDs_Init();
  LEDbuffer_Init();
  timer_init();
  ITS_Init(NULL,0);
  tempSensor_Init(NULL);
  bargraph_Init();
  flash_init();
  
  //Applications mutexes
  MainAppMutex = xSemaphoreCreateMutex();
  MainConfigMutex = xSemaphoreCreateMutex();
  MainDiagMutex = xSemaphoreCreateMutex();

  //events
  CU_Inputs_EventGroup=xEventGroupCreate();
  
  CU_IOInit();
  CU_LEDsInit();
  
  STBT_Init(COM1);
  console_Init(STBT_ConsoleOutput);
  CLI_Init(console_log,F3000CLIInterpreter);
  if(gear_Init())
  {
    console_log("can't init GearBox");
  }
  
  //xTaskCreate(ToggleLed1, "LED1", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  xTaskCreate(F3000_App, "Application", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &AppTaskHandle);
  xTaskCreate(F3000_Periodic, "PeriodicTask", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &PeriodicTaskHandle);
  xTaskCreate(F3000_Conf, "Config", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &ConfigTaskHandle);
  //vTaskSuspend(ConfigTaskHandle);
  xTaskCreate(F3000_Diag, "Config", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &DiagnosticTaskHandle);
  //vTaskSuspend(DiagnosticTaskHandle);
  
  
  vTaskStartScheduler();
  
  /* We should never get here as control is now taken by the scheduler */
  for( ;; );
}

void vApplicationMallocFailedHook(void)
{
  uint8_t i=0; 
  console_log("\nERROR: Failed to allocate a ressource!\n");
  /*while(1)
  {
    ;
  }*/
  i++;
}

void vApplicationStackOverflowHook( xTaskHandle xTask,
                                    signed portCHAR *pcTaskName )
{
  console_log("\nERROR: Stack overflow!\n");
  while(1);
}

void assert_failed(uint8_t* file, uint32_t line)
{
  uint8_t i=1;
  console_log("\nAssert failed. File: ");
  console_log(file);
  sprintf(str,"\nLine: %i",line);
  console_log(str);
  while(i)
  {
    vTaskDelay(100);
  }
} 