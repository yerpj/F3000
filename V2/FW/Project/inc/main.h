#ifndef __MAIN_H
#define __MAIN_H
   
#include <stdio.h>   
#include "stm32f2xx.h"

#define LED_TASK_PRIO     ( tskIDLE_PRIORITY + 1 )

/* Scheduler includes. */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 
#include "semphr.h" 

#include "commonDefs.h"
#include "strbuf.h"
#include "console.h"

#include "CU.h"
#include "CLI.h"
#include "UID.h"
#include "internal_temp_sensor.h"

#endif /* __MAIN_H */