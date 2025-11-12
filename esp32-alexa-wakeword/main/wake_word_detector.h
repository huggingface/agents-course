/**
 * @file wake_word_detector.h
 * @brief Wake Word Detection using ESP-SR
 */

#ifndef WAKE_WORD_DETECTOR_H
#define WAKE_WORD_DETECTOR_H

#include "esp_err.h"
#include <stdbool.h>

// LED Pin for visual feedback
#define LED_PIN 2

/**
 * @brief Initialize wake word detector
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t wake_word_detector_init(void);

/**
 * @brief Process audio buffer for wake word detection
 * @param audio_buffer Audio data buffer (16-bit PCM)
 * @param buffer_len Length of buffer in bytes
 * @return true if wake word detected, false otherwise
 */
bool wake_word_detect(int16_t *audio_buffer, size_t buffer_len);

/**
 * @brief Deinitialize wake word detector
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t wake_word_detector_deinit(void);

/**
 * @brief Trigger LED when wake word is detected
 */
void wake_word_trigger_led(void);

#endif // WAKE_WORD_DETECTOR_H
