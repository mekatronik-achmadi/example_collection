#ifndef _DATA_
#define _DATA_

/**
 * @brief   define data array movement direction.
 */
#define LEFT_TO_RIGHT FALSE

/**
 * @brief   define data scaling for display.
 */
#define DATA_SCALE 0.1

/**
 * @brief   define total data point for display.
 */
#define N_DATA 320

/**
 * @brief ADC to Volt conversion
 */
#define VOLT_CALIB 0.00081

/**
 * @brief Data Update with GUI or Auto
 */
#define UPDATE_DATA_AUTO FALSE

/**
 * @brief Initialization data
 */
void dataInit(void);

/**
 * @brief Updating data
 */
void dataUpdate(void);

#endif