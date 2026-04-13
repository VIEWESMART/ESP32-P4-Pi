/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "esp_system.h"
#include "esp_check.h"
#include "es8311.h"

/***************************  I2C ↓ *******************************************/
#define BSP_I2C_SDA           (GPIO_NUM_7)   // SDA引脚
#define BSP_I2C_SCL           (GPIO_NUM_8)   // SCL引脚
#define ES8311_I2C_ADDR       (0x18)

#define BSP_I2C_NUM           (0)            // I2C外设
#define BSP_I2C_FREQ_HZ       100000         // 100kHz

esp_err_t bsp_i2c_init(void);   // 初始化I2C接口
/***************************  I2C ↑  *******************************************/
/*******************************************************************************/
/***************************   I2S  ↓    **************************************/

/* Example configurations */
#define EXAMPLE_RECV_BUF_SIZE   (2400)
#define EXAMPLE_SAMPLE_RATE     (16000)
#define EXAMPLE_MCLK_MULTIPLE   (384) // If not using 24-bit data width, 256 should be enough
#define EXAMPLE_MCLK_FREQ_HZ    (EXAMPLE_SAMPLE_RATE * EXAMPLE_MCLK_MULTIPLE)
#define EXAMPLE_VOICE_VOLUME    (100)

/* I2S port and GPIOs
 *
 * 与板子强相关：ESP32-P4-Pi 与 ESP32-P4-Function-EV 的 I2S/功放引脚不同。
 * 无声时请先确认板型，再设置 BOARD_ESP32_P4_PI（1=P4 Pi 常见接法，0=Function EV）。
 *
 * 参考：p4-pi 工程 viewe__esp32_p4_pi（DOUT=48, PA=11）；
 *       esp-idf P4_10_1 esp32_p4_function_ev_board（DOUT=9, PA=53, DSIN=11）。
 */
#define BOARD_ESP32_P4_PI   (1)

/*
 * ESP32-P4 各官方 BSP 默认使用 I2S1（见 CONFIG_BSP_I2S_NUM），不是 I2S0。
 * 与板载 ES8311 的接线/时钟树一致，否则易出现“日志正常但无声音”。
 */
#define I2S_NUM         (1)

#if BOARD_ESP32_P4_PI
#define I2S_MCK_IO      (GPIO_NUM_13)
#define I2S_BCK_IO      (GPIO_NUM_12)
#define I2S_WS_IO       (GPIO_NUM_10)
#define I2S_DO_IO       (GPIO_NUM_48)
#define I2S_DI_IO       (GPIO_NUM_9) /* 与 BSP 一致；全双工时接至 Codec DOUT */
#define GPIO_OUTPUT_PA  (GPIO_NUM_11)
#else
#define I2S_MCK_IO      (GPIO_NUM_13)
#define I2S_BCK_IO      (GPIO_NUM_12)
#define I2S_WS_IO       (GPIO_NUM_10)
#define I2S_DO_IO       (GPIO_NUM_9)
#define I2S_DI_IO       (GPIO_NUM_11)
#define GPIO_OUTPUT_PA  (GPIO_NUM_53)
#endif

/* 功放使能有效电平：若仍无声可改为 0（低有效）试一次 */
#define PA_GPIO_ON_LEVEL    (1)

static const char *TAG = "i2s_es8311";
static const char err_reason[][30] = {"input param is invalid",
                                      "operation timeout"
                                     };
static i2s_chan_handle_t tx_handle = NULL;
static i2s_chan_handle_t rx_handle = NULL;

/* Import music file as buffer */
extern const uint8_t music_pcm_start[] asm("_binary_canon_pcm_start");
extern const uint8_t music_pcm_end[]   asm("_binary_canon_pcm_end");

esp_err_t bsp_i2c_init(void)
{
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BSP_I2C_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = BSP_I2C_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_FREQ_HZ
    };
    i2c_param_config(BSP_I2C_NUM, &i2c_conf);

    return i2c_driver_install(BSP_I2C_NUM, i2c_conf.mode, 0, 0, 0);
}

// 初始化I2C接口 并初始化es8311芯片
static esp_err_t es8311_codec_init(void)
{
    /* 初始化I2C接口 */
    ESP_ERROR_CHECK(bsp_i2c_init());

    /* 初始化es8311芯片 */
    es8311_handle_t es_handle = es8311_create(BSP_I2C_NUM, ES8311_I2C_ADDR);
    ESP_RETURN_ON_FALSE(es_handle, ESP_FAIL, TAG, "es8311 create failed");
    const es8311_clock_config_t es_clk = {
        .mclk_inverted = false,
        .sclk_inverted = false,
        .mclk_from_mclk_pin = true,
        .mclk_frequency = EXAMPLE_MCLK_FREQ_HZ,
        .sample_frequency = EXAMPLE_SAMPLE_RATE
    };

    ESP_ERROR_CHECK(es8311_init(es_handle, &es_clk, ES8311_RESOLUTION_16, ES8311_RESOLUTION_16));
    ESP_RETURN_ON_ERROR(es8311_sample_frequency_config(es_handle, EXAMPLE_SAMPLE_RATE * EXAMPLE_MCLK_MULTIPLE, EXAMPLE_SAMPLE_RATE), TAG, "set es8311 sample frequency failed");
    ESP_RETURN_ON_ERROR(es8311_voice_volume_set(es_handle, EXAMPLE_VOICE_VOLUME, NULL), TAG, "set es8311 volume failed");
    ESP_RETURN_ON_ERROR(es8311_voice_mute(es_handle, false), TAG, "set es8311 unmute failed");
    ESP_RETURN_ON_ERROR(es8311_microphone_config(es_handle, false), TAG, "set es8311 microphone failed");

    return ESP_OK;
}

// 初始化I2S外设（与 P4 Pi / Function EV BSP 相同：I2S1 全双工，避免仅用 I2S0 单发时无输出）
static esp_err_t i2s_driver_init(void)
{
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true;
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle, &rx_handle));

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(EXAMPLE_SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = I2S_MCK_IO,
            .bclk = I2S_BCK_IO,
            .ws = I2S_WS_IO,
            .dout = I2S_DO_IO,
            .din = I2S_DI_IO,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    std_cfg.clk_cfg.mclk_multiple = EXAMPLE_MCLK_MULTIPLE;

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(tx_handle));
    ESP_ERROR_CHECK(i2s_channel_enable(rx_handle));

    return ESP_OK;
}

static void pa_gpio_init(void)
{
    /* 功放使能脚：P4 Pi 多为 GPIO11，Function EV 多为 GPIO53；高电平有效（与 BSP pa_reverted=false 一致） */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_OUTPUT_PA),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    gpio_set_level(GPIO_OUTPUT_PA, PA_GPIO_ON_LEVEL);
}

/* 打开 RX 后需周期性读走数据，否则 DMA 可能溢出 */
static void i2s_rx_discard_task(void *arg)
{
    uint8_t buf[512];
    for (;;) {
        size_t n = 0;
        (void)i2s_channel_read(rx_handle, buf, sizeof(buf), &n, pdMS_TO_TICKS(500));
    }
}


static void i2s_music(void *args)
{
    esp_err_t ret = ESP_OK;
    size_t bytes_write = 0;
    uint8_t *data_ptr = (uint8_t *)music_pcm_start;

    /* 全双工下勿对 TX 反复 disable/enable，以免与 RX 共用时钟异常 */
    while (1) {
        /* Write music to earphone */
        ret = i2s_channel_write(tx_handle, data_ptr, music_pcm_end - data_ptr, &bytes_write, portMAX_DELAY);
        if (ret != ESP_OK) {
            /* Since we set timeout to 'portMAX_DELAY' in 'i2s_channel_write'
               so you won't reach here unless you set other timeout value,
               if timeout detected, it means write operation failed. */
            ESP_LOGE(TAG, "[music] i2s write failed, %s", err_reason[ret == ESP_ERR_TIMEOUT]);
            abort();
        }
        if (bytes_write > 0) {
            ESP_LOGI(TAG, "[music] i2s music played, %d bytes are written.", bytes_write);
        } else {
            ESP_LOGE(TAG, "[music] i2s music play failed.");
            abort();
        }
        data_ptr = (uint8_t *)music_pcm_start;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}



void app_main(void)
{
    printf("i2s es8311 codec example start\n-----------------------------\n");
    /* 初始化I2S外设 */
    if (i2s_driver_init() != ESP_OK) {
        ESP_LOGE(TAG, "i2s driver init failed");
        abort();
    } else {
        ESP_LOGI(TAG, "i2s driver init success");
    }
    /* 初始化I2C 以及初始化es8311芯片 */
    if (es8311_codec_init() != ESP_OK) {
        ESP_LOGE(TAG, "es8311 codec init failed");
        abort();
    } else {
        ESP_LOGI(TAG, "es8311 codec init success");
    }

    pa_gpio_init();

    xTaskCreate(i2s_rx_discard_task, "i2s_rx_dump", 2048, NULL, 3, NULL);

    /* 创建播放音乐任务 */
    xTaskCreate(i2s_music, "i2s_music", 4096, NULL, 5, NULL);
}
