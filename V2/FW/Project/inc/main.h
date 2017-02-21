#ifndef __MAIN_H
#define __MAIN_H
   
#include <stdio.h>   
#include "stm32f2xx.h"
//#include "stm32f2xx_it.h"

#define LED_TASK_PRIO     ( tskIDLE_PRIORITY + 1 )

/* Scheduler includes. */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 
#include "event_groups.h"
extern EventGroupHandle_t CU_Inputs_EventGroup;

#include "commonDefs.h"
#include "commontypes.h"
#include "strbuf.h"
#include "console.h"

#include "CU.h"
#include "CLI.h"
#include "UID.h"
#include "internal_temp_sensor.h"
#include "PCA9952.h"
#include "gear.h"
#include "timer.h"
#include "STBT.h"
#include "ledbuffer.h"
#include "SEG7.h"
#include "flash.h"
#include "paramcollection.h"
#include "indicator.h"
#include "tempSensor.h"
#ifndef USE_BREADBOARD
  #include "bargraph.h"
#endif /* USE_BREADBOARD */

enum {
  MainMode_App=0,
  MainMode_Diagnostic=1,
  MainMode_Configuration=2,
};

uint8_t MainAppGetMode(void);

#endif /* __MAIN_H */