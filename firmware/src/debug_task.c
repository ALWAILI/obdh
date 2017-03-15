/*
 * debug_task.c
 *
 *  Created on: 18 de out de 2016
 *      Author: elder
 */

#include <debug_task.h>

void debug_task( void *pvParameters ) {
    TickType_t last_wake_time;
    last_wake_time = xTaskGetTickCount();

    uint8_t uart_package[512];
    uint16_t package_size;
    char cmd[10];
    request_packet_t rqt_packet;

    while(1) {

#if _DEBUG_AS_LINK == 1
        uart_rx(cmd, 9);

        rqt_packet = decode((uint8_t *)cmd);
        
        if(rqt_packet.request_action == SEND_DATA_REQUEST) {
            while(rqt_packet.packages_count > 0) {
            	package_size = get_packet(uart_package, &rqt_packet);
            	if(package_size > 0) {
            		uart_tx_bytes((char *)uart_package, package_size);
            	}
            }
        }
#else
        uart_rx(cmd, 1);
        char answer[30];
        uint16_t temp_raw, voltage_raw, current_raw;
        float temperature, voltage, current;
        uint32_t systick;
        switch(cmd[0]) {
        case 't':
            temp_raw = (uint16_t)satellite_data.msp_sensors[0]<<8;
            temp_raw += satellite_data.msp_sensors[1];
            temperature = obdh_temperature_convert(temp_raw);
            sprintf(answer,"Temperature: %.2f C\n", temperature);
            break;
        case 'v':
            voltage_raw = (uint16_t)satellite_data.msp_sensors[2]<<8;
            voltage_raw += satellite_data.msp_sensors[3];
            voltage = obdh_voltage_convert(voltage_raw);
            sprintf(answer,"Voltage: %.2f V\n", voltage);
            break;
        case 'c':
            current_raw = (uint16_t)satellite_data.msp_sensors[4]<<8;
            current_raw += satellite_data.msp_sensors[5];
            current = obdh_current_convert(current_raw);
            sprintf(answer,"Current: %.4f A\n", current);
            break;
        case 's':
            systick = xTaskGetTickCount();
            sprintf(answer,"Systick: %lu\n", systick);
            break;
        default:
            sprintf(answer,"Invalid command\n");
        }
        uart_tx(answer);

#endif

        vTaskDelayUntil( (TickType_t *) &last_wake_time, DEBUG_TASK_PERIOD_TICKS );
    }

    vTaskDelete( NULL );
}

