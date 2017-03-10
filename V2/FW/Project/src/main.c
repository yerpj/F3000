#include "main.h"
#include "stm32f2xx_it.h"

#define UID_ADDRESS_BASE (uint8_t*)(0x1FFF7A10)
#define UID_BYTE_SIZE   (12)

//#define FLASH_REINIT
#define FAKE_ENGINE_SPEED_DATA
uint8_t UID[8];
uint8_t NXS_UID[12];
uint8_t NXS_EUI64[8];

//applications
xTaskHandle AppTaskHandle,ConfigTaskHandle,PeriodicTaskHandle,DiagnosticTaskHandle;
SemaphoreHandle_t MainAppMutex;
SemaphoreHandle_t MainConfigMutex;
SemaphoreHandle_t MainDiagMutex;

//application modes
uint8_t MainMode=MainMode_Init;

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
  uint8_t state=0;
  uint8_t varNum=0;
  uint8_t paramValue=0;
  uint32_t ledIntensity=0;
  while(1)
  {
    if(MainMode==MainMode_Configuration)
    {
      //take MainConfigMutex 
      if( xSemaphoreTake( MainConfigMutex, ( TickType_t ) 100 ) != pdTRUE )
      {
        continue;
      }
      
      switch(state)
      {
      case 0:
        SEG7_Set(SEG7_C);
        vTaskDelay(1000);
        while(CU_GetNeutralButton())
          vTaskDelay(20);
        state=1;
        break;
      case 1:
        varNum=bargraph_getPotValue();
        if(varNum>9)
          varNum=9;
        SEG7_Set(varNum);
        if(CU_GetNeutralButton())
        {
          state=2;
          while(CU_GetNeutralButton())
            vTaskDelay(20);
        }
        break;
      case 2:
        SEG7_Set(varNum);
        bargraph_DisplayPotValue();
        paramValue=bargraph_getPotValue();
        switch(varNum)
        {
        case 9:
          if(CU_GetNeutralButton())
          {
            ledIntensity=(uint32_t)((float)paramValue*4.7619);
            PC_SetParam((uint8_t*)&ledIntensity,"LED_I");
            PC_GetParam((uint8_t*)&ledIntensity,"LED_I");
            CU_LEDsSetIntensity( (((float)ledIntensity)/100) );
            while(CU_GetNeutralButton())
            vTaskDelay(20);
            state=1;
          }
          break;
        default:break;
        }
        break;
      default:break;
      }
      
      //release MainConfigMutex 
      xSemaphoreGive(MainConfigMutex);
      if(CU_GetStopButton())
      {
        state=0;
        MainAppChangeMode(MainMode_App);
      }
      vTaskDelay(20);
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
      SEG7_Set(SEG7_d);
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
#ifdef FAKE_ENGINE_SPEED_DATA
  uint8_t updown=1;
  uint32_t userRPM=500;
#endif /* FAKE_ENGINE_SPEED_DATA */
  uint32_t i=0;
  uint8_t GearMode;
  while(1)
  {
    vTaskDelay(100);
    
    //handle App, Conf or Diag modes
    if(CU_GetNeutralButton())
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
      else
      {
        gear_toNeutral();
      }
    }

    //check MODE buttons
    GearMode=CU_GetMode();
    gear_SetMode(GearMode);
    Indicator_LED_Mode_Set(GearMode);
    if(GearMode==CU_Mode_Auto && CU_UserInputToBargraph(userRPM)>=bargraph_getPotValue())
    {
      if(gear_getPosition()<gear_pos_5 && gear_getPosition()!=gear_pos_N)
      {
        gear_increase();
        updown=1;
        userRPM=800;
      }
    }
    //handle temperature sensor
    Indicator_LED_Temp_Set(0/*tempSensor_Get_State()*/);
    Vreg_based_LED=((uint8_t)(tempSensor_Get_Temp()*4.2))%22;

    //handle OIL sensor
    if(CU_GetOilWarning())
      Indicator_LED_OIL_Set();
    else
      Indicator_LED_OIL_Reset();
    
    //handle bargraph
#ifdef FAKE_ENGINE_SPEED_DATA
    bargraph_Set(1,CU_UserInputToBargraph(userRPM));
    if(updown)
    {
      userRPM+=75;
      if(userRPM>CU_RPM_MAX)
        updown=0;
    }
    else
    {
      userRPM-=75;
      if(userRPM<CU_RPM_MIN)
        updown=1;
    }
#else /*FAKE_ENGINE_SPEED_DATA */
    bargraph_Set(1,CU_RPMToBargraph());
#endif /* FAKE_ENGINE_SPEED_DATA */
    
    
    
    
    //handle STOP button
    if(CU_GetStopButton())
      CU_STOP_On();
    else
      CU_STOP_Off();
    
    //Neutral LED 
    if(gear_getPosition()==gear_pos_N)
      Indicator_LED_N_Set();
    else
      Indicator_LED_N_Reset();
  }
}

extern EventGroupHandle_t gear_Events;
void PALG_Gear_cb(void){
  xEventGroupSetBitsFromISR(gear_Events,GEAR_EVENT_DECREASE,0);
}

void PALD_Gear_cb(void){
  xEventGroupSetBitsFromISR(gear_Events,GEAR_EVENT_INCREASE,0);
}

void F3000_App(void * pvParameters)
{
  uint8_t err=0;
  uint32_t param;
  if(CU_Inputs_EventGroup==NULL)
    err++;
  
  DebouncerInit(CU_Inputs_EventGroup);
  //uint32_t InputMask,GPIO_TypeDef* GPIO,uint16_t Pin,uint8_t Edge,uint32_t Event,uint32_t DebounceTime_ms
  DebouncerAddInput(CU_INPUT_EVENT_CAME_BIT,CAME_INPUT_GPIO_PORT,CAME_INPUT_PIN,DEBOUNCER_INT_EDGE_RISING,CU_INPUT_EVENT_CAME_BIT,0,10);
  
  /* debounce and calls respective callbacks conditionally on PALG and PALD */
  DebouncerAddInput(CU_INPUT_EVENT_PALG_BIT,PALG_INPUT_GPIO_PORT,PALG_INPUT_PIN,DEBOUNCER_INT_EDGE_FALLING,CU_INPUT_EVENT_PALG_BIT,PALG_Gear_cb,50);
  DebouncerAddInput(CU_INPUT_EVENT_PALD_BIT,PALD_INPUT_GPIO_PORT,PALD_INPUT_PIN,DEBOUNCER_INT_EDGE_FALLING,CU_INPUT_EVENT_PALD_BIT,PALD_Gear_cb,50);
  
  /* debounce and generate Events on Rapport+ and Rapport- signals*/
  DebouncerAddInput(CU_INPUT_EVENT_RAPPORTp_BIT,RAPPORTp_INPUT_GPIO_PORT,RAPPORTp_INPUT_PIN,DEBOUNCER_INT_EDGE_RISING,CU_INPUT_EVENT_RAPPORTp_BIT,NULL,10);
  DebouncerAddInput(CU_INPUT_EVENT_RAPPORTm_BIT,RAPPORTm_INPUT_GPIO_PORT,RAPPORTm_INPUT_PIN,DEBOUNCER_INT_EDGE_RISING,CU_INPUT_EVENT_RAPPORTm_BIT,NULL,10);
  

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
      //LEDbuffer_MaskSet(0xFFFFFFFFFFFF);
      //LEDbuffer_refresh(0);
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
  if(strstr(cmd,"SYS -s Lum")>0)
  {
    uint32_t lum=0;
    cmd=strstr(cmd,"SYS -s Lum");
    if(strstr(cmd,"=")>0)
    {
      cmd=strstr(cmd,"=")+1;
      if(cmd[0]>='0' && cmd[0]<='9')
      {
        if(cmd[1]>='0' && cmd[1]<='9')
        {
          if(cmd[2]>='0' && cmd[2]<='9')
          {
            lum+=(cmd[0]-'0')*100;
            lum+=(cmd[1]-'0')*10;
            lum+=cmd[2]-'0';
          }
          else
          {
            lum+=(cmd[0]-'0')*10;
            lum+=cmd[1]-'0';
          }
        }
        else
          lum+=cmd[0]-'0';
      }
      if(lum>0 && lum<=100)
      {
        PC_SetParam((uint8_t*)&lum,"LED_I");
        PC_GetParam((uint8_t*)&lum,"LED_I");
        CU_LEDsInit( (((float)lum)/100) );
        LEDbuffer_refresh(1);
        sprintf(str,"luminosity set to %3i [\%]",lum);
        CLI_Output(str);
      }
    }
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

void F3000_Init(void * pvParameters)
{
  uint32_t param;
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
  if(flash_init())
     console_log("can't init flash");
  if( PC_Init() )
    console_log("can't init Parameter Collection. Flash problem?");
#ifdef FLASH_REINIT
  param=50;
  PC_SetParam((uint8_t*)&param,"LED_I");
#endif /* FLASH_REINIT */
  
  PC_GetParam((uint8_t*)&param,"LED_I");
  CU_LEDsInit( (((float)param)/100) );
  if(gear_Init())
  {
    console_log("can't init GearBox");
  }
  //Applications mutexes
  MainAppMutex = xSemaphoreCreateMutex();
  MainConfigMutex = xSemaphoreCreateMutex();
  MainDiagMutex = xSemaphoreCreateMutex();

  //events
  CU_Inputs_EventGroup=xEventGroupCreate();
  
  CU_IOInit();
  
  
  STBT_Init(COM1);
  console_Init(STBT_ConsoleOutput);
  CLI_Init(console_log,F3000CLIInterpreter);
  
  /* WELCOME SEQUENCE */
  uint8_t a,b;
  bargraph_NegMaskState(0);
  a=1;
  b=1;
  /* everything OFF */
  LEDbuffer_MaskReset(0xFFFFFFFFFFFF);
  LEDbuffer_refresh(0);
  
  /* simulate engine speed increase */
  while(b<=21)
  {
    bargraph_Set(a,b);
    b++;
    vTaskDelay(15);
  }
  
  /* everything ON */
  LEDbuffer_MaskSet(0xFFFFFFFFFFFF);
  LEDbuffer_refresh(0);
  vTaskDelay(700);
  
  /* Everything OFF */
  LEDbuffer_MaskReset(0xFFFFFFFFFFFF);
  LEDbuffer_refresh(0);
  
  /* Simulate engine speed decrease */
  while(b>0)
  {
    bargraph_Set(a,b);
    b--;
    vTaskDelay(15);
  }
  bargraph_NegMaskState(1);
  
  /* restore normal tasks */
  vTaskResume(ConfigTaskHandle);
  vTaskResume(DiagnosticTaskHandle);
  vTaskResume(PeriodicTaskHandle);
  vTaskResume(AppTaskHandle);
  MainMode=MainMode_App;
  vTaskDelete(NULL);
}

void F3000_System_Start(void)
{
  //xTaskCreate(ToggleLed1, "LED1", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  xTaskCreate(F3000_App, "Application", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &AppTaskHandle);
  xTaskCreate(F3000_Periodic, "PeriodicTask", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &PeriodicTaskHandle);
  xTaskCreate(F3000_Conf, "Config", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &ConfigTaskHandle);
  xTaskCreate(F3000_Diag, "Diag", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &DiagnosticTaskHandle);
  vTaskSuspend(ConfigTaskHandle);
  vTaskSuspend(DiagnosticTaskHandle);
  vTaskSuspend(PeriodicTaskHandle);
  vTaskSuspend(AppTaskHandle);
  xTaskCreate(F3000_Init, "F3000Init", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  vTaskStartScheduler();
}

void main(void)
{
  /* System function that updates the SystemCoreClock variable. */
  SystemCoreClockUpdate();
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );//no bits of sub-priority. Only preemption priorities are used
  F3000_System_Start();
  
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