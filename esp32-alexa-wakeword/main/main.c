/**
 * @file main.c
 * @brief ESP32-S3 Alexa Wake Word Detection Main Application
 * 
 * Hardware Setup:
 * - ESP32-S3 Development Board
 * - INMP441 I2S MEMS Microphone
 * 
 * Connections:
 * INMP441 VCC  -> ESP32-S3 3.3V
 * INMP441 GND  -> ESP32-S3 GND
 * INMP441 SCK  -> GPIO18 (I2S_BCK)
 * INMP441 L/R  -> GPIO5  (I2S_WS)
 * INMP441 SD   -> GPIO4  (I2S_DATA_IN)
 * 
 * LED (optional) -> GPIO2
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "i2s_config.h"
#include "wake_word_detector.h"

static const char *TAG = "MAIN";

// Audio buffer for I2S reading
#define AUDIO_BUFFER_SIZE (I2S_READ_LEN)
static int16_t audio_buffer[AUDIO_BUFFER_SIZE / sizeof(int16_t)];

/**
 * @brief Main audio processing task
 */
static void audio_processing_task(void *arg)
{
    size_t bytes_read = 0;
    uint32_t loop_count = 0;

    ESP_LOGI(TAG, "Audio processing task started");
    ESP_LOGI(TAG, "Listening for wake word 'Alexa'...");

    while (1) {
        // Read audio data from I2S
        esp_err_t ret = i2s_read_audio(audio_buffer, AUDIO_BUFFER_SIZE, &bytes_read);
        
        if (ret == ESP_OK && bytes_read > 0) {
            // Process audio for wake word detection
            bool wake_word_detected = wake_word_detect(audio_buffer, bytes_read);
            
            if (wake_word_detected) {
                // Trigger LED and log detection
                wake_word_trigger_led();
                ESP_LOGI(TAG, "═══════════════════════════════════════");
                ESP_LOGI(TAG, "🎤 WAKE WORD 'ALEXA' DETECTED!");
                ESP_LOGI(TAG, "═══════════════════════════════════════");
            }

            // Log status every 5 seconds
            if (++loop_count % 500 == 0) {
                ESP_LOGI(TAG, "System running... Listening for 'Alexa'");
            }
        } else {
            ESP_LOGW(TAG, "I2S read error or no data: %s", esp_err_to_name(ret));
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Small delay to prevent watchdog issues
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

/**
 * @brief Print system information
 */
static void print_system_info(void)
{
    ESP_LOGI(TAG, "═══════════════════════════════════════");
    ESP_LOGI(TAG, "  ESP32-S3 Alexa Wake Word Detector");
    ESP_LOGI(TAG, "═══════════════════════════════════════");
    ESP_LOGI(TAG, "Chip: %s", CONFIG_IDF_TARGET);
    ESP_LOGI(TAG, "Free heap: %lu bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "Hardware Configuration:");
    ESP_LOGI(TAG, "  Microphone: INMP441 (I2S)");
    ESP_LOGI(TAG, "  Sample Rate: %d Hz", SAMPLE_RATE);
    ESP_LOGI(TAG, "  Bits per Sample: %d", BITS_PER_SAMPLE);
    ESP_LOGI(TAG, "  Channels: Mono");
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "Pin Configuration:");
    ESP_LOGI(TAG, "  I2S_BCK  (SCK): GPIO%d", I2S_BCK_PIN);
    ESP_LOGI(TAG, "  I2S_WS   (L/R): GPIO%d", I2S_WS_PIN);
    ESP_LOGI(TAG, "  I2S_DATA (SD):  GPIO%d", I2S_DATA_IN_PIN);
    ESP_LOGI(TAG, "  LED:            GPIO%d", LED_PIN);
    ESP_LOGI(TAG, "═══════════════════════════════════════");
}

void app_main(void)
{
    esp_err_t ret;

    // Print system information
    print_system_info();

    // Initialize NVS (required for some ESP-IDF components)
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS partition was truncated, erasing...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "✓ NVS initialized");

    // Initialize I2S for INMP441 microphone
    ret = i2s_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "✗ Failed to initialize I2S: %s", esp_err_to_name(ret));
        ESP_LOGE(TAG, "Check your wiring and pin configuration!");
        return;
    }
    ESP_LOGI(TAG, "✓ I2S initialized");

    // Initialize wake word detector
    ret = wake_word_detector_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "✗ Failed to initialize wake word detector: %s", esp_err_to_name(ret));
        i2s_deinit();
        return;
    }
    ESP_LOGI(TAG, "✓ Wake word detector initialized");

    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "🎤 System ready! Say 'Alexa' to test...");
    ESP_LOGI(TAG, "");

    // Create audio processing task
    xTaskCreate(audio_processing_task, "audio_task", 4096, NULL, 5, NULL);

    // Main loop - monitor system health
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGI(TAG, "System health: Free heap = %lu bytes", esp_get_free_heap_size());
    }
}
