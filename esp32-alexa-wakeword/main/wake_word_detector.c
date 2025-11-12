/**
 * @file wake_word_detector.c
 * @brief Wake Word Detection Implementation
 */

#include "wake_word_detector.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ESP-SR includes (uncomment when ESP-SR is available)
// #include "esp_wn_iface.h"
// #include "esp_wn_models.h"
// #include "esp_afe_sr_iface.h"
// #include "esp_afe_sr_models.h"

static const char *TAG = "WAKE_WORD";

// Wake word model handle (uncomment when ESP-SR is available)
// static const esp_wn_iface_t *wakenet = NULL;
// static model_iface_data_t *model_data = NULL;

esp_err_t wake_word_detector_init(void)
{
    ESP_LOGI(TAG, "Initializing Wake Word Detector");

    // Initialize LED GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(LED_PIN, 0);

    ESP_LOGI(TAG, "LED configured on GPIO %d", LED_PIN);

    /* 
     * ESP-SR Initialization (uncomment when library is available)
     * 
     * // Get WakeNet model
     * wakenet = esp_sr_wakenet_quantized_init();
     * if (wakenet == NULL) {
     *     ESP_LOGE(TAG, "Failed to initialize WakeNet");
     *     return ESP_FAIL;
     * }
     * 
     * // Load model data
     * model_data = wakenet->create(DET_MODE_90);
     * if (model_data == NULL) {
     *     ESP_LOGE(TAG, "Failed to create model data");
     *     return ESP_FAIL;
     * }
     * 
     * ESP_LOGI(TAG, "WakeNet initialized successfully");
     * ESP_LOGI(TAG, "Wake word: Alexa");
     */

    ESP_LOGI(TAG, "Wake Word Detector initialized (ESP-SR integration pending)");
    return ESP_OK;
}

bool wake_word_detect(int16_t *audio_buffer, size_t buffer_len)
{
    if (audio_buffer == NULL || buffer_len == 0) {
        return false;
    }

    /*
     * ESP-SR Detection Logic (uncomment when library is available)
     * 
     * if (wakenet == NULL || model_data == NULL) {
     *     return false;
     * }
     * 
     * int detection_result = wakenet->detect(model_data, audio_buffer);
     * 
     * if (detection_result > 0) {
     *     ESP_LOGI(TAG, "Wake word detected! ID: %d", detection_result);
     *     return true;
     * }
     */

    // Placeholder: Simple energy-based detection for testing
    // This is NOT a real wake word detector - just for testing audio input
    static int sample_count = 0;
    int64_t energy = 0;
    size_t samples = buffer_len / sizeof(int16_t);

    for (size_t i = 0; i < samples; i++) {
        int32_t sample = audio_buffer[i];
        energy += (sample * sample);
    }

    energy /= samples;

    // Log audio level every 100 samples
    if (++sample_count % 100 == 0) {
        ESP_LOGI(TAG, "Audio energy level: %lld", energy);
    }

    // Simulate wake word detection when audio energy exceeds threshold
    // This is just for testing - replace with real ESP-SR detection
    if (energy > 1000000) {  // Adjust threshold based on your environment
        static uint32_t last_detection = 0;
        uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
        
        // Debounce: only trigger once every 3 seconds
        if (now - last_detection > 3000) {
            last_detection = now;
            ESP_LOGW(TAG, "⚠️  SIMULATED WAKE WORD DETECTED (high audio energy)");
            ESP_LOGW(TAG, "Replace this with real ESP-SR detection!");
            return true;
        }
    }

    return false;
}

void wake_word_trigger_led(void)
{
    ESP_LOGI(TAG, "🎤 ALEXA WAKE WORD TRIGGERED!");
    
    // Blink LED 3 times
    for (int i = 0; i < 3; i++) {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(200));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

esp_err_t wake_word_detector_deinit(void)
{
    /*
     * ESP-SR Cleanup (uncomment when library is available)
     * 
     * if (wakenet != NULL && model_data != NULL) {
     *     wakenet->destroy(model_data);
     *     model_data = NULL;
     * }
     */

    gpio_set_level(LED_PIN, 0);
    ESP_LOGI(TAG, "Wake Word Detector deinitialized");
    return ESP_OK;
}
