/*
 * debug_task.h
 *
 *  Created on: 18 de out de 2016
 *      Author: elder
 */

#ifndef INCLUDE_DEBUG_TASK_H_
#define INCLUDE_DEBUG_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "../include/obdh_def.h"

/*
 * PRIORITY =   5
 * FREQUENCY =  1Hz
 */

#define DEBUG_TASK_PRIORITY          6
#define DEBUG_TASK_PERIOD_MS         500
#define DEBUG_TASK_PERIOD_TICKS      ( DEBUG_TASK_PERIOD_MS / portTICK_PERIOD_MS )

/**
 * \var static xTaskHandle xDebugTask;
 * \brief variable which holds the task reference
 */
static xTaskHandle xDebugTask;

/**
 * \fn void prvDebugTask( void *pvParameters )
 * The task witch do the Debug module main function
 * \param pvParameters Not used
 */
void prvDebugTask( void *pvParameters );

#endif /* INCLUDE_DEBUG_TASK_H_ */
