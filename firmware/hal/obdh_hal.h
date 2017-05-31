/*
 * HAL_obdh.h
 *
 *  Created on: 27 de abr de 2016
 *      Author: mario
 */

#ifndef DRIVER_HAL_OBDH_H_
#define DRIVER_HAL_OBDH_H_

#include <msp430.h>
#include "../hw_memmap.h"

#define HAL_V1          1           /**< Reference value of HAL version V1.0 */
#define HAL_V2_0        2           /**< Reference value of HAL version V2.0 */
#define HAL_V2_1        3           /**< Reference value of HAL version V2.1 */

#define HAL_VERSION     HAL_V2_1    /**< Current HAL version */

//I2C SLAVE ADDRESS
#define IMU0_I2C_SLAVE_ADRESS               0x68    /**< I2C SLAVE ADRESS OF IMU0 */
#define IMU1_I2C_SLAVE_ADRESS               0x69    /**< I2C SLAVE ADRESS OF IMU1 */
#define EPS_I2C_SLAVE_ADRESS                0x48    /**< I2C SLAVE ADRESS OF EPS INTERFACE */
#define ANTENNA_SYSTEM_I2C_SLAVE_ADDRESS    0x12   //TODO: FIX THE ADDRESS

//USCI CONNECTED DEVICES (DRIVERLIB)
#define EPS_BASE_ADDRESS            USCI_B0_BASE
#define IMU_BASE_ADDRESS            USCI_B1_BASE
#define ANTENNA_BASE_ADDRESS        USCI_B2_BASE

#define RADIO_BASE_ADDRESS          USCI_A0_BASE
#define NV_MEM_BASE_ADDRESS         USCI_A1_BASE
#define SOLAR_PANEL_BASE_ADDRESS    USCI_A1_BASE



//PMM
#define OBDH_V_CORE         3           /**< Level of core's voltage */
#define PMM_STATUS_OK       0
#define PMM_STATUS_ERROR    1
#define _HAL_PMM_SVMLE      (SVMLE)
#define _HAL_PMM_SVSLE      (SVSLE)
#define _HAL_PMM_SVSFP      (SVSLFP)
#define _HAL_PMM_SVMFP      (SVMLFP)


// @ 16Mhz internal ref, 1 cycle ~= 62.5 nS
// Delays below adjusted empiricaly based on tests/mesurements (to fix internal clock drift)
#define DELAY_100_uS_IN_CYCLES        1540
#define DELAY_500_uS_IN_CYCLES        7940
#define DELAY_1_MS_IN_CYCLES	     15856
#define DELAY_5_MS_IN_CYCLES	     79532
#define DELAY_10_MS_IN_CYCLES	    159132
#define DELAY_50_MS_IN_CYCLES	    795600
#define DELAY_100_MS_IN_CYCLES	   1591600
#define DELAY_150_MS_IN_CYCLES	   2387400
#define DELAY_1_S_IN_CYCLES	      16000000
#define DELAY_5_S_IN_CYCLES	      80000000
#define DELAY_60_S_IN_CYCLES     960000000
#define DELAY_120_S_IN_CYCLES   1920000000


/********************************************/

// Define some macros that allow us to direct-access the ADC12 calibration
// constants that we need. See device datasheet for the full TLV table memory
// mapping.

// Calibration constant for ADC 1.5-V Reference, Temp. Sensor 30°C
#define CALADC12_15V_30C        (*((unsigned int *)0x1A1A))
// Calibration constant for ADC 1.5-V Reference, Temp. Sensor 85°C
#define CALADC12_15V_85C        (*((unsigned int *)0x1A1C))


/********************************************/

#define     TEST_SUCESS     0x01
#define     TEST_FAIL       0x00

#define BIT_TOGGLE(REG, BIT)    (REG ^= BIT)        /**< macro that toggles a bit in a register */
#define BIT_SET(REG, BIT)       (REG |= BIT)        /**< macro that set a bit in a register */
#define BIT_CLEAR(REG, BIT)     (REG &= ~BIT)       /**< macro that clear a bit in a register */
#define BIT_READ(REG, BIT)      (REG & BIT)         /**< macro that read a bit in a register */
/**
 * \defgroup OBDH_pins
 * \brief MCU pins description
 */

/**
 * \defgroup supply
 * \ingroup OBDH_pins
 * \brief supply pins of the MCU
 * \{
 */
#define VCC_5V_EN_DIR P1DIR
#define VCC_5V_EN_OUT P1OUT
#define VCC_5V_EN_PIN BIT0

#define VREF_DIR P5DIR
#define VREF_SEL P5SEL
#define VREF_PIN BIT0

#define AGND_DIR P5DIR
#define AGND_SEL P5SEL
#define AGND_PIN BIT1
//! \} End of supply

/**
 * \defgroup led
 * \ingroup OBDH_pins
 * \brief led pin of the MCU
 * \{
 */
#define LED_SYSTEM_DIR P5DIR
#define LED_SYSTEM_OUT P5OUT
#define LED_SYSTEM_PIN BIT3
//! \} End of led

/**
 * \defgroup payloads
 * \ingroup OBDH_pins
 * \brief payloads enable pins
 * \{
 */
#define PAYLOAD_0_EN_DIR P5DIR
#define PAYLOAD_0_EN_OUT P5OUT
#define PAYLOAD_0_EN_PIN BIT6

#define PAYLOAD_1_EN_DIR P5DIR
#define PAYLOAD_1_EN_OUT P5OUT
#define PAYLOAD_1_EN_PIN BIT2
//! \} End of payloads

/**
 * \defgroup xt2
 * \ingroup OBDH_pins
 * \brief high frequency crystal pins of MCU
 * \{
 */
#define XT2_N_DIR P7DIR
#define XT2_N_SEL P7SEL
#define XT2_N_PIN BIT2

#define XT2_P_DIR P7DIR
#define XT2_P_SEL P7SEL
#define XT2_P_PIN BIT3
//! \} End of xt2

/**
 * \defgroup antenna_debbug
 * \ingroup OBDH_pins
 * \brief antenna debbug pin
 * \{
 */
#define ANTENNA_DEBUG_DIR P8DIR
#define ANTENNA_DEBUG_OUT P8OUT
#define ANTENNA_DEBUG_PIN BIT7
//! \} End of antenna_debbug

/**
 * \defgroup watchdog
 * \ingroup OBDH_pins
 * \brief watchdog pins
 * \{
 */
#define WDI_EXT_DIR P9DIR
#define WDI_EXT_OUT P9OUT
#define WDI_EXT_PIN BIT4

#define MR_WDog_DIR P9DIR
#define MR_WDog_OUT P9OUT
#define MR_WDog_PIN BIT7
//! \} End of watchdog

/**
 * \defgroup adc
 * \ingroup OBDH_pins
 * \brief adc pins of MCU
 * \{
 */
#define ADC_SEL     P6SEL

#if HAL_VERSION == HAL_V2_0
#define X_SUNSEN_ADC_CH             0
#define Y_SUNSEN_ADC_CH             1
#define Z_SUNSEN_ADC_CH             2
#define OBDH_CURRENT_ADC_CH         3
#define VREF_TEMP_ADC_CH            4
#define VCC_3V3_ADC_CH              5
#define INTERNAL_TEMP_SENSOR_ADC_CH 6
#endif

#if HAL_VERSION == HAL_V2_1
#define X_SUNSEN_ADC_CH             0
#define Y_SUNSEN_ADC_CH             1
#define Z_SUNSEN_ADC_CH             2
#define OBDH_CURRENT_ADC_CH         3
#define VCC_3V3_ADC_CH              4
#define INTERNAL_TEMP_SENSOR_ADC_CH 5
#endif

#define X_SUNSEN_ADC_DIR P6DIR
#define X_SUNSEN_ADC_SEL P6SEL
#define X_SUNSEN_ADC_PIN BIT0

#define Y_SUNSEN_ADC_DIR P6DIR
#define Y_SUNSEN_ADC_SEL P6SEL
#define Y_SUNSEN_ADC_PIN BIT1

#define Z_SUNSEN_ADC_DIR P6DIR
#define Z_SUNSEN_ADC_SEL P6SEL
#define Z_SUNSEN_ADC_PIN BIT2

#define OBDH_CURRENT_ADC_DIR P6DIR
#define OBDH_CURRENT_ADC_SEL P6SEL
#define OBDH_CURRENT_ADC_PIN BIT3

#if HAL_VERSION == HAL_V2_0

#define ADC_Vref_TEMP_DIR P6DIR
#define ADC_Vref_TEMP_SEL P6SEL
#define ADC_Vref_TEMP_PIN BIT4

#define VCC_3V3_DIR P6DIR
#define VCC_3V3_SEL P6SEL
#define VCC_3V3_PIN BIT5

#endif

#if HAL_VERSION == HAL_V2_1

#define VCC_3V3_DIR P6DIR
#define VCC_3V3_SEL P6SEL
#define VCC_3V3_PIN BIT4

#endif
//! \} End of adc

/**
 * \defgroup i2c
 * \ingroup OBDH_pins
 * \brief i2c interface pins of MCU
 * \{
 */
#define I2C0_DIR P2DIR
#define I2C0_REN P2REN
#define I2C0_OUT P2OUT
#define I2C0_SEL P2SEL
#define I2C0_SDA BIT1
#define I2C0_SCL BIT2

#define I2C1_DIR P8DIR
#define I2C1_REN P8REN
#define I2C1_OUT P8OUT
#define I2C1_SEL P8SEL
#define I2C1_SDA BIT5
#define I2C1_SCL BIT6

#define I2C2_DIR P9DIR
#define I2C2_REN P9REN
#define I2C2_OUT P9OUT
#define I2C2_SEL P9SEL
#define I2C2_SDA BIT5
#define I2C2_SCL BIT6

#define I2C0_SDA_DIR P2DIR
#define I2C0_SDA_SEL P2SEL
#define I2C0_SDA_PIN BIT1

#define I2C0_SCL_DIR P2DIR
#define I2C0_SCL_SEL P2SEL
#define I2C0_SCL_PIN BIT2

#define I2C1_SDA_DIR P8DIR
#define I2C1_SDA_SEL P8SEL
#define I2C1_SDA_PIN BIT5

#define I2C1_SCL_DIR P8DIR
#define I2C1_SCL_SEL P8SEL
#define I2C1_SCL_PIN BIT6

#define I2C2_SDA_DIR P9DIR
#define I2C2_SDA_SEL P9SEL
#define I2C2_SDA_PIN BIT5

#define I2C2_SCL_DIR P9DIR
#define I2C2_SCL_SEL P9SEL
#define I2C2_SCL_PIN BIT6
//! \} End of i2c


/**
 * \defgroup spi
 * \ingroup OBDH_pins
 * \brief spi interface pins of MCU
 * \{
 */
#define SPI0_SEL P2SEL
#define SPI1_SEL P8SEL

#define SPI1_CLK_DIR P8DIR
#define SPI1_CLK_SEL P8SEL
#define SPI1_CLK_PIN BIT1

#define SPI1_MOSI_DIR P8DIR
#define SPI1_MOSI_SEL P8SEL
#define SPI1_MOSI_PIN BIT2

#define SPI1_MISO_DIR P8DIR
#define SPI1_MISO_SEL P8SEL
#define SPI1_MISO_PIN BIT3

#define SPI0_CLK_DIR P2DIR
#define SPI0_CLK_SEL P2SEL
#define SPI0_CLK_PIN BIT0

#define SPI0_MOSI_DIR P2DIR
#define SPI0_MOSI_SEL P2SEL
#define SPI0_MOSI_PIN BIT4

#define SPI0_MISO_DIR P2DIR
#define SPI0_MISO_SEL P2SEL
#define SPI0_MISO_PIN BIT5

#define SPI0_CSn_DIR P2DIR
#define SPI0_CSn_SEL P2SEL
#define SPI0_CSn_PIN BIT3
//! \} End of spi

/**
 * \defgroup uart
 * \ingroup OBDH_pins
 * \brief uart interface pins of MCU
 * \{
 */
#define UART0_SEL P9SEL
#define UART0_TX BIT2
#define UART0_RX BIT3

#define UART0_TX_DIR P9DIR
#define UART0_TX_SEL P9SEL
#define UART0_TX_PIN BIT2

#define UART0_RX_DIR P9DIR
#define UART0_RX_SEL P9SEL
#define UART0_RX_PIN BIT3
//! \} End of uart

/**
 * \defgroup radio
 * \ingroup OBDH_pins
 * \brief radio interface pins
 * \{
 */
#define TTC_3V3_PA_EN_DIR P1DIR
#define TTC_3V3_PA_EN_OUT P1OUT
#define TTC_3V3_PA_EN_PIN BIT1

#define TTC_RESETn_MAIN_DIR P1DIR
#define TTC_RESETn_MAIN_OUT P1OUT
#define TTC_RESETn_MAIN_PIN BIT2

#define TTC_GPIO2_MAIN_DIR P1DIR
#define TTC_GPIO2_MAIN_OUT P1OUT
#define TTC_GPIO2_MAIN_PIN BIT3

//TODO: GPIO1 pin should be disconnected in future versions
#if HAL_VERSION == HAL_V2_0
#define TTC_GPIO1_MAIN_DIR P1DIR
#define TTC_GPIO1_MAIN_OUT P1OUT
#define TTC_GPIO1_MAIN_PIN BIT4
#endif

#if HAL_VERSION == HAL_V2_1
#define TTC_GPIO1_MAIN_DIR P1DIR
#define TTC_GPIO1_MAIN_OUT P1OUT
#define TTC_GPIO1_MAIN_PIN BIT4
#endif

#define TTC_GPIO0_MAIN_DIR P1DIR
#define TTC_GPIO0_MAIN_OUT P1OUT
#define TTC_GPIO0_MAIN_PIN BIT5

#define TTC_CTRL_RF_SWT_TX_DIR P1DIR
#define TTC_CTRL_RF_SWT_TX_OUT P1OUT
#define TTC_CTRL_RF_SWT_TX_PIN BIT6

#define TTC_CTRL_RF_SWT_RX_DIR P1DIR
#define TTC_CTRL_RF_SWT_RX_OUT P1OUT
#define TTC_CTRL_RF_SWT_RX_PIN BIT7
//! \} End of radio

/**
 * \defgroup mcu_beacon
 * \ingroup OBDH_pins
 * \brief mcu beacon interface pins
 * \{
 */
#define uC_BEACON_0_DIR P5DIR
#define uC_BEACON_0_SEL P5SEL
#define uC_BEACON_0_OUT P5OUT
#define uC_BEACON_0_REN P5REN
#define uC_BEACON_0_PIN BIT4

#define uC_BEACON_1_DIR P5DIR
#define uC_BEACON_1_SEL P5SEL
#define uC_BEACON_1_OUT P5OUT
#define uC_BEACON_1_REN P5REN
#define uC_BEACON_1_PIN BIT5

#define uC_BEACON_2_DIR P2DIR
#define uC_BEACON_2_SEL P2SEL
#define uC_BEACON_2_OUT P2OUT
#define uC_BEACON_2_REN P2REN
#define uC_BEACON_2_PIN BIT6

#define uC_BEACON_3_DIR P2DIR
#define uC_BEACON_3_SEL P2SEL
#define uC_BEACON_3_OUT P2OUT
#define uC_BEACON_3_REN P2REN
#define uC_BEACON_3_IN  P2IN
#define uC_BEACON_3_PIN BIT7

#define TTC_INTERRUPT_DIR   uC_BEACON_0_DIR
#define TTC_INTERRUPT_SEL   uC_BEACON_0_SEL
#define TTC_INTERRUPT_OUT   uC_BEACON_0_OUT
#define TTC_INTERRUPT_REN   uC_BEACON_0_REN
#define TTC_INTERRUPT_PIN   uC_BEACON_0_PIN

#define TTC_SHUTDOWN_DIR    uC_BEACON_1_DIR
#define TTC_SHUTDOWN_SEL    uC_BEACON_1_SEL
#define TTC_SHUTDOWN_OUT    uC_BEACON_1_OUT
#define TTC_SHUTDOWN_REN    uC_BEACON_1_REN
#define TTC_SHUTDOWN_PIN    uC_BEACON_1_PIN

#define TTC_TX_REQUEST_DIR  uC_BEACON_2_DIR
#define TTC_TX_REQUEST_SEL  uC_BEACON_2_SEL
#define TTC_TX_REQUEST_OUT  uC_BEACON_2_OUT
#define TTC_TX_REQUEST_REN  uC_BEACON_2_REN
#define TTC_TX_REQUEST_PIN  uC_BEACON_2_PIN

#define TTC_TX_BUSY_DIR     uC_BEACON_3_DIR
#define TTC_TX_BUSY_SEL     uC_BEACON_3_SEL
#define TTC_TX_BUSY_OUT     uC_BEACON_3_OUT
#define TTC_TX_BUSY_IN      uC_BEACON_3_IN
#define TTC_TX_BUSY_REN     uC_BEACON_3_REN
#define TTC_TX_BUSY_PIN     uC_BEACON_3_PIN
//! \} End of mcu_beacon

/**
 * \defgroup memories
 * \ingroup OBDH_pins
 * \brief memories interface with MCU
 * \{
 */
#define Mem_WP_DIR P7DIR
#define Mem_WP_OUT P7OUT
#define Mem_WP_PIN BIT4

#define Mem0_CE_DIR P7DIR
#define Mem0_CE_OUT P7OUT
#define Mem0_CE_PIN BIT5

#define Mem1_CE_DIR P7DIR
#define Mem1_CE_OUT P7OUT
#define Mem1_CE_PIN BIT6

#define Mem2_CE_DIR P7DIR
#define Mem2_CE_OUT P7OUT
#define Mem2_CE_PIN BIT7

#define uSDCard_CE_DIR P4DIR
#define uSDCard_CE_OUT P4OUT
#define uSDCard_CE_PIN BIT6
//! \} End of memories

/**
 * \defgroup solar_panel_modules
 * \ingroup OBDH_pins
 * \brief interface between MCU and 3 solar panel modules
 * \{
 */

//TODO: gyro pins should be disconnected in future versions
#if HAL_VERSION == HAL_V2_0
#define GYRO_Z_CSn_DIR P4DIR
#define GYRO_Z_CSn_OUT P4OUT
#define GYRO_Z_CSn_PIN BIT0

#define TEMP_Z_CSn_DIR P4DIR
#define TEMP_Z_CSn_OUT P4OUT
#define TEMP_Z_CSn_PIN BIT1

#define GYRO_Y_CSn_DIR P4DIR
#define GYRO_Y_CSn_OUT P4OUT
#define GYRO_Y_CSn_PIN BIT2

#define TEMP_Y_CSn_DIR P4DIR
#define TEMP_Y_CSn_OUT P4OUT
#define TEMP_Y_CSn_PIN BIT3

#define GYRO_X_CSn_DIR P4DIR
#define GYRO_X_CSn_OUT P4OUT
#define GYRO_X_CSn_PIN BIT4

#define TEMP_X_CSn_DIR P4DIR
#define TEMP_X_CSn_OUT P4OUT
#define TEMP_X_CSn_PIN BIT5
#endif

#if HAL_VERSION == HAL_V2_1
#define GYRO_Z_CSn_DIR P4DIR
#define GYRO_Z_CSn_OUT P4OUT
#define GYRO_Z_CSn_PIN BIT0

#define TEMP_Z_CSn_DIR P4DIR
#define TEMP_Z_CSn_OUT P4OUT
#define TEMP_Z_CSn_PIN BIT1

#define GYRO_Y_CSn_DIR P4DIR
#define GYRO_Y_CSn_OUT P4OUT
#define GYRO_Y_CSn_PIN BIT2

#define TEMP_Y_CSn_DIR P4DIR
#define TEMP_Y_CSn_OUT P4OUT
#define TEMP_Y_CSn_PIN BIT3

#define GYRO_X_CSn_DIR P4DIR
#define GYRO_X_CSn_OUT P4OUT
#define GYRO_X_CSn_PIN BIT4

#define TEMP_X_CSn_DIR P4DIR
#define TEMP_X_CSn_OUT P4OUT
#define TEMP_X_CSn_PIN BIT5
#endif
//! \} End of solar_panel_modules

/**
 * \defgroup magnetorquers
 * \ingroup OBDH_pins
 * \brief output pins from MCU to magnetorquers
 * \{
 */
#define DRIVER_CH0_CH1_SLEEP_DIR P3DIR
#define DRIVER_CH0_CH1_SLEEP_OUT P3OUT
#define DRIVER_CH0_CH1_SLEEP_PIN BIT0

#define DRIVER_CH2_SLEEP_DIR P3DIR
#define DRIVER_CH2_SLEEP_OUT P3OUT
#define DRIVER_CH2_SLEEP_PIN BIT1

#define DRIVER_CH0_0_DIR P3DIR
#define DRIVER_CH0_0_OUT P3OUT
#define DRIVER_CH0_0_PIN BIT2

#define DRIVER_CH0_1_DIR P3DIR
#define DRIVER_CH0_1_OUT P3OUT
#define DRIVER_CH0_1_PIN BIT3

#define DRIVER_CH1_0_DIR P3DIR
#define DRIVER_CH1_0_OUT P3OUT
#define DRIVER_CH1_0_PIN BIT4

#define DRIVER_CH1_1_DIR P3DIR
#define DRIVER_CH1_1_OUT P3OUT
#define DRIVER_CH1_1_PIN BIT5

#define DRIVER_CH2_0_DIR P3DIR
#define DRIVER_CH2_0_OUT P3OUT
#define DRIVER_CH2_0_PIN BIT6

#define DRIVER_CH2_1_DIR P3DIR
#define DRIVER_CH2_1_OUT P3OUT
#define DRIVER_CH2_1_PIN BIT7

#define DRIVER_CH0_CH1_FAULT_DIR P9DIR
#define DRIVER_CH0_CH1_FAULT_IN P9IN
#define DRIVER_CH0_CH1_FAULT_PIN BIT0

#define DRIVER_CH2_FAULT_DIR P9DIR
#define DRIVER_CH2_FAULT_IN P9IN
#define DRIVER_CH2_FAULT_PIN BIT1
//! \} End of magnetorquers

//! \} End of pins

#endif /* DRIVER_HAL_OBDH_H_ */


