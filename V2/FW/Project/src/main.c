#include "main.h"

#define UID_ADDRESS_BASE (uint8_t*)(0x1FFF7A10)
#define UID_BYTE_SIZE   (12)
uint8_t UID[8];
uint8_t NXS_UID[12];
uint8_t NXS_EUI64[8];

uint8_t str[300];

xTaskHandle AppTaskHandle,ConfigTaskHandle,PeriodicTaskHandle,DiagnosticTaskHandle;

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
  while(1)
  {
    vTaskDelay(100);
  }
}

void F3000_Diag(void * pvParameters)
{
  while(1)
  {
    vTaskDelay(10000);
    if(1)
    {
      vTaskResume(AppTaskHandle);
      vTaskSuspend(NULL);
    }
    
  }
}

void F3000_Periodic(void * pvParameters)
{
  while(1)
  {
    vTaskDelay(100);
    if(gear_getPosition()==gear_pos_N)
    {
      if(GPIO_ReadInputDataBit(NEUTRAL_INPUT_GPIO_PORT,NEUTRAL_INPUT_PIN))
      {
        vTaskResume(DiagnosticTaskHandle);
        vTaskSuspend(AppTaskHandle);
      }
      else
      {
        
      }
    }
    //check MODE buttons
    //handle temperature sensor
    //handle OIL sensor
    //handle bargraph?
    //handle STOP button
  }
}

EventGroupHandle_t CU_Inputs_EventGroup;

void F3000_App(void * pvParameters)
{
  uint8_t err=0;
  uint8_t i=1;
  uint16_t Inputs=0;
  
  CU_Inputs_EventGroup=xEventGroupCreate();
  if(CU_Inputs_EventGroup==NULL)
    err++;
  
  while(!err)
  {
#ifdef USE_BREADBOARD 
    if(GPIO_ReadInputDataBit(CAME_INPUT_GPIO_PORT,CAME_INPUT_PIN))
    {
      LEDbuffer_MaskSet(0x01<<D13_G_LED_INDEX | 
                        0x01<<D14_G_LED_INDEX | 
                        0x01<<D15_G_LED_INDEX | 
                        0x01<<D16_G_LED_INDEX  );
      LEDbuffer_MaskReset(0x01<<D13_B_LED_INDEX |
                          0x01<<D14_B_LED_INDEX |
                          0x01<<D15_B_LED_INDEX |
                          0x01<<D16_B_LED_INDEX  );
    }
    else
    {
      LEDbuffer_ResetBit(D13_G_LED_INDEX);
      LEDbuffer_ResetBit(D14_G_LED_INDEX);
      LEDbuffer_ResetBit(D15_G_LED_INDEX);
      LEDbuffer_ResetBit(D16_G_LED_INDEX);
      LEDbuffer_SetBit(D13_B_LED_INDEX);
      LEDbuffer_SetBit(D14_B_LED_INDEX);
      LEDbuffer_SetBit(D15_B_LED_INDEX);
      LEDbuffer_SetBit(D16_B_LED_INDEX);
    }
    LEDbuffer_refresh();
#else
    bargraph_Set(i++,0);
    if(i==22)
      i=0;
#endif /* USE_BREADBOARD */
   vTaskDelay(50);
    /*gear_increase();
    while(gear_isMoving())
      vTaskDelay(50);
    vTaskDelay(1000);
    gear_decrease();
    while(gear_isMoving())
      vTaskDelay(50);*/
    /*SEG7_Set(i++);
    if(i>8)
      i=0;*/
    
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
    while(gear_isMoving())
      vTaskDelay(50);
    CLI_Output("GEAR: OK");
  }
  else if(strstr(cmd,"GEAR -s DOWN")>0)
  {
    gear_decrease();
    while(gear_isMoving())
      vTaskDelay(50);
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
  LEDs_Init();
  timer_init();
  ITS_Init(NULL,0);
#ifdef USE_BREADBOARD
  PCA9952_Init(BUS_I2C3,PCA9952_MAIN_ADDR);
#else /* USE_BREADBOARD */
  PCA9952_Init(BUS_I2C1,PCA9952_MAIN_ADDR);
  PCA9952_Init(BUS_I2C1,PCA9952_BAR1_ADDR);
  PCA9952_Init(BUS_I2C1,PCA9952_BAR2_ADDR);
#endif /* USE_BREADBOARD */
  
  CU_IOInit();
  
  STBT_Init(COM2);
  console_Init(STBT_ConsoleOutput);
  CLI_Init(console_log,F3000CLIInterpreter);
  
  //xTaskCreate(ToggleLed1, "LED1", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  xTaskCreate(F3000_App, "Application", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &AppTaskHandle);
  xTaskCreate(F3000_Periodic, "PeriodicTask", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &PeriodicTaskHandle);
  xTaskCreate(F3000_Conf, "Config", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &ConfigTaskHandle);
  vTaskSuspend(ConfigTaskHandle);
  xTaskCreate(F3000_Diag, "Config", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, &DiagnosticTaskHandle);
  vTaskSuspend(DiagnosticTaskHandle);
  
  
  vTaskStartScheduler();
  
  /* We should never get here as control is now taken by the scheduler */
  for( ;; );
}

void vApplicationMallocFailedHook(void)
{
  uint8_t i;
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