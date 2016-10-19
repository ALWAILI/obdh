/*
 * eps_task.c
 *
 *  Created on: 18 de out de 2016
 *      Author: elder
 */

#include "../include/eps_task.h"

void prvEpsTask( void *pvParameters )
{
    volatile TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    static uint8_t usCounter = 0;

    while(1)
    {
        //TODO: TASK ROUTINE

        sprintf(eps_data,"EPS DATA: %u ",usCounter);
        usCounter = (usCounter+1)%10;

        vTaskDelayUntil( &xLastWakeTime, EPS_TASK_PERIOD_TICKS );
    }

    vTaskDelete( NULL );
}
