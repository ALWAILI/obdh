/*
 * floripasat_def.h
 *
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 *
 * This file is part of FloripaSat-OBDH.
 *
 * FloripaSat-OBDH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FloripaSat-OBDH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-OBDH.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 /**
 * \file floripasat_def.h
 *
 * \brief Project definitions, structures and macros
 *
 * \author Elder Tramontin
 *
 */

#ifndef FLORIPASATDEF_H_
#define FLORIPASATDEF_H_

#include <stdint.h>

#define has_flag(x,y)   (x & y)

/**
 * \defgroup flags
 * \brief submodules flags of the data packet
 * \{
 */
#define  SYSTEM_STATUS_FLAG         BIT0
#define  IMU_FLAG                   BIT1
#define  MSP_SENSORS_FLAG           BIT2
#define  SYSTICK_FLAG               BIT3
#define  SOLAR_PANELS_FLAG          BIT4
#define  TRANSCEIVER_FLAG           BIT5

#define  ADC_SOLAR_PANELS_FLAG      BIT6
#define  MSP430_ADC_FLAG            BIT7
#define  BATTERY_MONITOR_FLAG       BIT8
#define  ADS1248_FLAG               BIT9
#define  TASK_SCHEDULER_FLAG        BITA

#define  PAYLOAD1_FLAG              BITB
#define  PAYLOAD2_FLAG              BITC
//! \} End of flags

/**
 * \struct request_packet_t
 *
 * \brief The struct to decode a request command
 */
typedef struct {
    uint16_t flags;         /**< modules flags to request just the wanted data*/
    uint8_t packages_count; /**< number of packages to read, from offset */
    uint8_t packages_origin;/**< position used as reference for the offset */
    int32_t packages_offset;/**< number of packages to offset from origin */
} request_data_packet_t;

typedef struct {
    uint8_t ID[6];
    uint16_t request_action; /**< the action (send data, shutdown..) */
    uint8_t arguments[8];
    uint8_t reserved[12];
} telecommand_t;

#define PACKET_LENGTH   58  /**< according NGHAM packet sizes */

typedef struct {
    uint16_t package_flags;
    //obdh
    uint8_t system_status      [6];
    uint8_t imu                [24];
    uint8_t msp_sensors        [6];
    uint8_t systick            [4];
    uint8_t solar_panels       [12];
    uint8_t transceiver        [85];
    //eps
    uint8_t adc_solar_panels   [18];
    uint8_t msp430_adc         [8];
    uint8_t battery_monitor    [21];
    uint8_t ads1248            [21];
    uint8_t task_scheduler     [1];
    //payloads
    uint8_t payload1           [7];
    uint8_t payload2           [100]; 
} data_packet_t;

typedef struct {
    uint8_t batteries[12];          /**< bat_1_voltage[2], bat_2_voltage[2], bat_1_temp[3], bat_2_temp[3], bat_charge[2] */
    uint8_t solar_panels[18];       /**< sp_1_volt[2], sp_2_volt[2], sp_3_volt[2], sp_1_cur[2], sp_2_cur[2], sp_3_cur[2], sp_4_cur[2], sp_5_cur[2], sp_6_cur[2] */
    uint8_t satellite_status[2];    /**< energy_mode,  */
    uint8_t imu[12];                /**< accel_0_x[1], accel_0_y[1], accel_0_z[1], gyr_0_x[1], gyr_0_y[1], gyr_0_z[1], accel_1_x[1], accel_1_y[1], accel_1_z[1], gyr_1_x[1], gyr_1_y[1], gyr_1_z[1] */
    uint8_t system_time[4];         /**< time, in minutes, since deploy */
    uint8_t reset_counter[2];       /**< increment each time a reset happens */
} beacon_packet_t;

typedef struct {
    uint8_t start_of_frame;          /**< 0x7E */
    beacon_packet_t data;           /**< valid data */
    uint8_t crc_result;             /**< 8-bit crc value of the data */
} ttc_packet_t;


/**
 * \defgroup current_state_masks
 * \{
 */
#define OPERATION_MODE_MASK         0xF0    /**< to retrieve from current state register just the operation mode */
#define ENERGY_LEVEL_MASK           0x0F    /**< to retrieve from current state register just the energy level */
//! \} End of current_state_masks

/**
 * \defgroup operation_modes
 * \brief valid operation modes of the satellite
 * \{
 */
#define NORMAL_OPERATION_MODE       0x10    /**< Normal operation               */
#define BOOT_MODE                   0x20    /**< While configuring the basic settings and buses  */
#define SHUTDOWN_MODE               0x30    /**< 24-hours shutdown              */
#define ANTENNA_DEPLOYMENT_MODE     0x40    /**< While waiting to do the deployment (45 minutes) */
//! \} End of operation_modes


/**
 * \defgroup energy_levels
 * \brief valid operation modes of the satellite
 * \{
 */
#define ENERGY_L1_MODE              0x01    /**< Energy level 1 - Tx on , Beacon 10s, TLM 60s , Payload on  */
#define ENERGY_L2_MODE              0x02    /**< Energy level 2 - Tx on , Beacon 10s, TLM 60s , Payload off */
#define ENERGY_L3_MODE              0x03    /**< Energy level 3 - Tx on , Beacon 20s, TLM 120s, Payload off */
#define ENERGY_L4_MODE              0x04    /**< Energy level 4 - Tx off, Beacon 30s, TLM off , Payload off */
//! \} End of energy_levels

/**
 * \defgroup uplink_commands
 * \brief valid commands to be sent from the earth segment
 * \{
 */
#define REQUEST_DATA_TELECOMMAND            0x7764    /**< uplink command to request whole data orbit - dw */
#define REQUEST_SHUTDOWN_TELECOMMAND        0x6473    /**< uplink command to request a 24 hours shutdown - sd */
#define REQUEST_PING_TELECOMMAND            0x6770    /**< ping request - pg */
//! \} End of uplink_commands


/**
 * \defgroup communications
 * \brief some team definition of values used in the communications
 * \{
 */
#define CRC_SEED        0x03                    /**< The initial value of the crc operation */
#define CRC_POLYNOMIAL  0b10010010              /**< The CRC polynomial: x^7 + x^4 + x^1 */
#define START_OF_FRAME  0x7E                    /**< Initial byte of some communications: '{' */
//! \} End of communications

/**
 * \defgroup packet_origin
 * \brief used to refers to a position in the memory where are packet to read
 * \{
 */
#define OLDER_PACKAGES_ORIGIN       0   /**< refers to the older packets in the memory */
#define NEWER_PACKAGES_ORIGIN       1   /**< refers to the newer packets in the memory */
//! \} End of packet_origin

//INTERFACES
#define IMU1    0x01
#define IMU2    0x02
#define EPS     0x03
#define TTC     0x04
#define SD      0x05

//#define _DEBUG_AS_LINK  0               /**< to simulate the radio link through UART */

#define MINUTES_BEFORE_DEPLOY_ANTENNAS  45

#define PING_MSG "Hello from FloripaSat, telecommand received from "


#define BOOTING_MSG     "FSAT booting...\n Firmware v 0.9 - 07/07/2017\n\n"
#define CLOCK_INFO_MSG  " CLOCKS:\n  Master = 16MHz\n  Subsystem master = 16MHz\n  Auxiliary = 32768kHz \n\n"
#define CLOCK_FAIL_MSG  " *CLOCKS SETUP FAIL* \n\n"
#define UART_INFO_MSG   " UART:\n  Baudrate = 9600\n  Data bits = 8\n  Parity = None\n  Stop bits = 1\n\n"
#define I2C_INFO_MSG    " I2C:\n  Freq =~ 100kHz\n\n"
#define SPI_INF_MSG     " SPI:\n  Freq =~ 8MHz\n\n"
#define ADC_INFO_MSG    " ADC:\n  Vref+ = 3.0V\n  Vref- = GND\n\n"

volatile data_packet_t satellite_data;


#endif /* FLORIPASATDEF_H_ */

