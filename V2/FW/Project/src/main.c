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
    vTaskDelay(100);
    
  }
}

void F3000_Periodic(void * pvParameters)
{
  while(1)
  {
    vTaskDelay(100);
    //check MODE buttons
    //handle temperature sensor
    //handle OIL sensor
    //handle bargraph?
    //handle STOP button
  }
}

uint16_t ledCB(void)
{
  CU_LEDOff(LED_BLUE);
}

void F3000_App(void * pvParameters)
{
  uint16_t Inputs=0;
  while(1)
  {
    //CU_LEDOn(LED_BLUE);
    //timer_set_alarm_us(1,50000,ledCB);
    Inputs=CU_ReadInputsRaw();
    if(PCA9952_LED_Control(PCA9952_MAIN_ADDR,Inputs))
      I2C_abort_transaction(BUS_I2C3);
    gear_increase();
    while(gear_isMoving())
      vTaskDelay(50);
    vTaskDelay(1000);
    gear_decrease();
    while(gear_isMoving())
      vTaskDelay(50);
    vTaskDelay(1000);
  }
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
  PCA9952_Init(BUS_I2C3,PCA9952_MAIN_ADDR);
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