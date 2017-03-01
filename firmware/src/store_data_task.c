/*
 * store_data_task.c
 *
 *  Created on: 19 de out de 2016
 *      Author: elder
 */

#include <store_data_task.h>

uint32_t last_read_pointer, last_write_pointer;


void store_data_task( void *pvParameters ) {
    TickType_t last_wake_time;
    last_wake_time = xTaskGetTickCount();


    static unsigned long current_position = 1024; // to jump over the MBR data in SD

    /*** mmc initialization ***/
    volatile unsigned long card_size = 0;
    unsigned char status = 1;
    unsigned int timeout = 0;
    data_packet_t new_packet;

    last_read_pointer = 512;
    last_write_pointer = 512;

    while (status != 0) {                      // if return in not NULL an error did occur and the
                                                // MMC/SD-card will be initialized again
        status = mmcInit();
        timeout++;
        if (timeout == 150) {                     // Try 150 times till error
          //printf ("No MMC/SD-card found!! %x\n", status);
            break;
        }
    }


    while ((mmcPing() != MMC_SUCCESS));      // Wait till card is inserted

    // Read the Card Size from the CSD Register
    card_size =  mmcReadCardSize();


    while(1) {
        //TODO: TASK ROUTINE
        //save in the begining of the memory the log_status: (packages counter, resets counter, etc).
        new_packet = read_and_pack_data();
        store_data_on_flash(&new_packet);

//        mmcWriteSector(512, (unsigned char *) status_package);

        //TODO: corrigir sistema para salvar na memoria. Deve seguir o seguinte esquema:
        /* A cada iteração, no cabeçalho do pacote deve conter as flags cujos sensores foram lidos desde a execução anterior da tarefa de salvar. 
         * Desta forma, se a flag não estiver setada, aquele byte não deve ser enviado, poupando o downlink. 
         * Porém, o pacote é salvo no tamanho total no cartão, mesmo que ocupe mais espaço, com os bytes zerados onde a informação será ignorada.
         */

//        mmcWriteSector(current_position, flash_package);

        vTaskDelayUntil( (TickType_t *) &last_wake_time, STORE_DATA_TASK_PERIOD_TICKS );
    }

    vTaskDelete( NULL );
}

data_packet_t read_and_pack_data( void ) {
    data_packet_t packet = {0};
    uint16_t i;

    module_flags_t *flags = packet.package_flags;
    flags->imu_flag = 1;
    flags->msp_sensors_flag = 1;


    uint32_t systick = xTaskGetTickCount();
    packet.systick[0] = systick & 0xFF;
    packet.systick[1] = systick>>8 & 0xFF;
    packet.systick[2] = systick>>16 & 0xFF;
    packet.systick[3] = systick>>24 & 0xFF;

    uint32_t reset = 0;
    packet.system_status[0] = reset & 0xFF;
    packet.system_status[1] = reset>>8 & 0xFF;
    packet.system_status[2] = reset>>16 & 0xFF;
    packet.system_status[3] = 0;
    packet.system_status[4] = 0;


    for(i = 0; i < sizeof(packet.msp_sensors); i++)
        packet.msp_sensors[i] = msp_internal_data[i];

    for(i = 0; i < sizeof(packet.imu); i++)
        packet.imu[i] = imu_data[i];

    return packet;
}

void store_data_on_flash( data_packet_t *packet ) {
    //write new packet
    unsigned char data[512];
    int i;

    for(i = 0; i < sizeof(data_packet_t); i++) {
        data[i] = ((uint8_t *)packet)[i];
    }

    mmcWriteSector(++last_write_pointer, data);
    //write new status
//    mmcWriteSector(0, (unsigned char *) status_packet);
}


uint16_t grab_packet(uint8_t* to_send_packet, request_data_packet_t *rqst_data_packet) {
    uint8_t flash_package[512];
    uint16_t package_size = 0;
    uint16_t i;
    uint32_t read_sector;
    module_flags_t *to_send_flags;
    data_packet_t *p_data_packet;

    //mmcReadSector(older_package_sector, (unsigned char *) status_package);
    if(rqst_data_packet->packages_origin == OLDER_PACKAGES_ORIGIN) {
        read_sector =  last_read_pointer + rqst_data_packet->packages_offset;
    }
    else {
        read_sector = last_write_pointer + rqst_data_packet->packages_offset;;
    }


    mmcReadSector(read_sector, (unsigned char *) flash_package);
    p_data_packet = (data_packet_t*)flash_package;

    uint8_t flags[4] = {0xFF,0xFF,0xFF,0xFF};
//    flags[0] = ((uint8_t *)&rqst_data_packet->flags)[0] & p_data_packet->package_flags[0];
//    flags[1] = ((uint8_t *)&rqst_data_packet->flags)[1] & p_data_packet->package_flags[1];
//    flags[2] = ((uint8_t *)&rqst_data_packet->flags)[2] & p_data_packet->package_flags[2];
//    flags[3] = ((uint8_t *)&rqst_data_packet->flags)[3] & p_data_packet->package_flags[3];

    to_send_flags = flags;



    pack_module_data(to_send_flags->package_flags_flag,  p_data_packet->package_flags, sizeof(p_data_packet->package_flags), to_send_packet, &package_size);
    pack_module_data(to_send_flags->system_status_flag,  p_data_packet->system_status, sizeof(p_data_packet->system_status), to_send_packet, &package_size);
    pack_module_data(to_send_flags->imu_flag,  p_data_packet->imu, sizeof(p_data_packet->imu), to_send_packet, &package_size);
    pack_module_data(to_send_flags->msp_sensors_flag,  p_data_packet->msp_sensors, sizeof(p_data_packet->msp_sensors), to_send_packet, &package_size);
    pack_module_data(to_send_flags->systick_flag,  p_data_packet->systick, sizeof(p_data_packet->systick), to_send_packet, &package_size);
    pack_module_data(to_send_flags->solar_panels_flag,  p_data_packet->solar_panels, sizeof(p_data_packet->solar_panels), to_send_packet, &package_size);
    pack_module_data(to_send_flags->rtc_flag,  p_data_packet->rtc, sizeof(p_data_packet->rtc), to_send_packet, &package_size);
    pack_module_data(to_send_flags->radio_flag,  p_data_packet->radio, sizeof(p_data_packet->radio), to_send_packet, &package_size);
    pack_module_data(to_send_flags->adc_solar_panels_flag,  p_data_packet->adc_solar_panels, sizeof(p_data_packet->adc_solar_panels), to_send_packet, &package_size);
    pack_module_data(to_send_flags->msp430_adc_flag,  p_data_packet->msp430_adc, sizeof(p_data_packet->msp430_adc), to_send_packet, &package_size);
    pack_module_data(to_send_flags->battery_monitor_flag,  p_data_packet->battery_monitor, sizeof(p_data_packet->battery_monitor), to_send_packet, &package_size);
    pack_module_data(to_send_flags->ads1248_flag,  p_data_packet->ads1248, sizeof(p_data_packet->ads1248), to_send_packet, &package_size);
    pack_module_data(to_send_flags->task_scheduler_flag,  p_data_packet->task_scheduler, sizeof(p_data_packet->task_scheduler), to_send_packet, &package_size);
    pack_module_data(to_send_flags->beacon_flag,  p_data_packet->beacon, sizeof(p_data_packet->beacon), to_send_packet, &package_size);
    pack_module_data(to_send_flags->transceiver_flag,  p_data_packet->transceiver, sizeof(p_data_packet->transceiver), to_send_packet, &package_size);
    pack_module_data(to_send_flags->payload1_flag,  p_data_packet->payload1, sizeof(p_data_packet->payload1), to_send_packet, &package_size);
    pack_module_data(to_send_flags->payload2_flag,  p_data_packet->payload2, sizeof(p_data_packet->payload2), to_send_packet, &package_size);

    rqst_data_packet->packages_offset++;
    rqst_data_packet->packages_count--;

    return package_size;
}

void update_last_read_position(uint32_t new_position) {
//    last_read_pointer = new_position;
}

/*
while(count--){
grab_packet
offset++
send
}
update_last_read_position
*/


void pack_module_data(uint8_t flag, uint8_t *module_data, uint8_t module_size, uint8_t* to_send_packet, uint16_t *total_package_size) {
    uint16_t i;

    if(flag == 1) {
        for(i = 0; i < module_size; i++) {
            to_send_packet[*total_package_size + i] = module_data[i];
        }
        *total_package_size += module_size;
    }
}
