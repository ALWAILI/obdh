/*
 * eps_interface_task.c
 *
 *  Created on: 18 de out de 2016
 *      Author: elder
 */

#include <eps_interface_task.h>

void eps_interface_task( void *pvParameters )
{
    TickType_t last_wake_time;
    last_wake_time = xTaskGetTickCount();
    eps_package_t eps_package;
    uint8_t eps_status;

    eps_setup();

    while(1)
    {
        if (xSemaphoreTake( i2c0_semaphore, I2C_SEMAPHORE_WAIT_TIME ) == pdPASS) {    //try to get the mutex

            eps_status = eps_read(&eps_package);

            xSemaphoreGive( i2c0_semaphore );                               //release the mutex

            xQueueOverwrite(status_eps_queue, &eps_status);

            if(eps_status == EPS_OK) {
                xQueueSendToBack(eps_queue, &eps_package, portMAX_DELAY);
            }
        }

        vTaskDelayUntil( (TickType_t *) &last_wake_time, EPS_INTERFACE_TASK_PERIOD_TICKS );
    }

    vTaskDelete( NULL );
}
