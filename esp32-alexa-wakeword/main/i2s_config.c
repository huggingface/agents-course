/**
 * @file i2s_config.c
 * @brief I2S Configuration Implementation for INMP441
 */

#include "i2s_config.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "I2S_CONFIG";
static i2s_chan_handle_t rx_handle = NULL;

esp_err_t i2s_init(void)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGI(TAG, "Initializing I2S for INMP441 microphone");
    ESP_LOGI(TAG, "Pin Configuration - BCK: %d, WS: %d, DATA_IN: %d", 
             I2S_BCK_PIN, I2S_WS_PIN, I2S_DATA_IN_PIN);

    // I2S channel configuration
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true;
    chan_cfg.dma_desc_num = I2S_BUFFER_COUNT;
    chan_cfg.dma_frame_num = I2S_BUFFER_SIZE;

    ret = i2s_new_channel(&chan_cfg, NULL, &rx_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S channel: %s", esp_err_to_name(ret));
        return ret;
    }

    // I2S standard mode configuration
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_BCK_PIN,
            .ws = I2S_WS_PIN,
            .dout = I2S_GPIO_UNUSED,
            .din = I2S_DATA_IN_PIN,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ret = i2s_channel_init_std_mode(rx_handle, &std_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2S standard mode: %s", esp_err_to_name(ret));
        i2s_del_channel(rx_handle);
        return ret;
    }

    ret = i2s_channel_enable(rx_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable I2S channel: %s", esp_err_to_name(ret));
        i2s_del_channel(rx_handle);
        return ret;
    }

    ESP_LOGI(TAG, "I2S initialized successfully - Sample Rate: %d Hz, Bits: %d", 
             SAMPLE_RATE, BITS_PER_SAMPLE);

    return ESP_OK;
}

esp_err_t i2s_read_audio(void *buffer, size_t buffer_size, size_t *bytes_read)
{
    if (rx_handle == NULL) {
        ESP_LOGE(TAG, "I2S not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = i2s_channel_read(rx_handle, buffer, buffer_size, bytes_read, portMAX_DELAY);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2S read failed: %s", esp_err_to_name(ret));
    }

    return ret;
}

esp_err_t i2s_deinit(void)
{
    if (rx_handle != NULL) {
        i2s_channel_disable(rx_handle);
        i2s_del_channel(rx_handle);
        rx_handle = NULL;
        ESP_LOGI(TAG, "I2S deinitialized");
    }
    return ESP_OK;
}
