/*
 * solar_panels_interface_task.h
 *
 *  Created on: 04 de nov de 2016
 *      Author: elder
 */

#ifndef SRC_SOLAR_PANELS_INTERFACE_TASK_H_
#define SRC_SOLAR_PANELS_INTERFACE_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

/*
 * PRIORITY =   5
 * FREQUENCY =  1Hz
 */

#define SOLAR_PANELS_INTERFACE_TASK_PRIORITY          5
#define SOLAR_PANELS_INTERFACE_TASK_PERIOD_MS         100
#define SOLAR_PANELS_INTERFACE_TASK_PERIOD_TICKS      ( SOLAR_PANELS_INTERFACE_TASK_PERIOD_MS / portTICK_PERIOD_MS )

/**
 * \var static xTaskHandle xSolarPanelsInterfaceTask
 * \brief variable which holds the task reference
 */
static xTaskHandle solar_panels_interface_task_handle;

/**
 * \fn void prvSolarPanelsTask( void *pvParameters )
 * That task manage the solar panels sensors
 * \param pvParameters Not used
 */
void solar_panels_interface_task( void *pvParameters );

#endif /* SRC_SOLAR_PANELS_INTERFACE_TASK_H_ */
