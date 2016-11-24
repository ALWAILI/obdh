/*
 * wdt_task.c
 *
 *  Created on: 18 de out de 2016
 *      Author: elder
 */

#include "../include/wdt_task.h"

void wdtTask( void *pvParameters )
{
    volatile TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();



    while(1)
    {
        //TODO: TASK ROUTINE
        wdt_reset_counter();

        P5OUT |= BIT4; //set pin

        vTaskDelayUntil( &xLastWakeTime, 10 );

        P5OUT ^= BIT4; //clear pin


        vTaskDelayUntil( &xLastWakeTime, WDT_TASK_PERIOD_TICKS -10 );
    }

    vTaskDelete( NULL );
}

