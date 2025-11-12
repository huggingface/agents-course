/**
 * @file i2s_config.h
 * @brief I2S Configuration for INMP441 Microphone
 * 
 * Pin Configuration:
 * - SCK (BCLK): GPIO18
 * - WS (LRCLK): GPIO5
 * - SD (DATA):  GPIO4
 */

#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "driver/i2s_std.h"
#include "esp_err.h"

// I2S Pin Configuration
#define I2S_BCK_PIN     18
#define I2S_WS_PIN      5
#define I2S_DATA_IN_PIN 4

// Audio Configuration
#define SAMPLE_RATE     16000
#define BITS_PER_SAMPLE 16
#define CHANNEL_NUM     1  // Mono

// Buffer Configuration
#define I2S_READ_LEN    (1024)
#define I2S_BUFFER_COUNT 8
#define I2S_BUFFER_SIZE  1024

/**
 * @brief Initialize I2S for INMP441 microphone
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t i2s_init(void);

/**
 * @brief Read audio data from I2S
 * @param buffer Buffer to store audio data
 * @param buffer_size Size of buffer
 * @param bytes_read Pointer to store number of bytes read
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t i2s_read_audio(void *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * @brief Deinitialize I2S
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t i2s_deinit(void);

#endif // I2S_CONFIG_H
