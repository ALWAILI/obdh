/*
 * imu_interface_task.h
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
 * \file imu_interface_task.h
 *
 * \brief Task that deals with the IMUs
 *
 * \author Elder Tramontin
 *
 */

#ifndef SRC_IMU_INTERFACE_TASK_H_
#define SRC_IMU_INTERFACE_TASK_H_

#include "../interface/imu.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "task_queues.h"
#ifdef _DEBUG
    #include "math.h"
#endif

#define IMU_INTERFACE_TASK_PRIORITY          5          /**< IMU task priority */
#define IMU_INTERFACE_TASK_PERIOD_MS         1000       /**< IMU task period in miliseconds */
#define IMU_INTERFACE_TASK_PERIOD_TICKS      ( IMU_INTERFACE_TASK_PERIOD_MS / portTICK_PERIOD_MS )  /**< IMU task period in ticks */

/**
 * \var static xTaskHandle imu_interface_task_handle
 * \brief variable which holds the task reference, to allow it handling
 */
static xTaskHandle imu_interface_task_handle;

/**
 * \fn imu_interface_task( void *pvParameters )
 * That task read the IMU data
 * \param pvParameters Not used
 * \return None
 */
void imu_interface_task( void *pvParameters );

#endif /* SRC_IMU_INTERFACE_TASK_H_ */
