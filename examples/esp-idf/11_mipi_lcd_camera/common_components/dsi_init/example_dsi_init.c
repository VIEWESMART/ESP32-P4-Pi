/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_ili9881c.h"
#include "esp_lcd_ek79007.h"
#include "esp_lcd_jd9165.h"
#include "example_dsi_init.h"
#include "example_dsi_init_config.h"
#include "sdkconfig.h"

#if VIEWE_JD9165_7
static const jd9165_lcd_init_cmd_t lcd_init_cmds[] = { 
    //  {cmd, { data }, data_size, delay_ms}
    {0x30, (uint8_t []){0x00}, 1, 0},
    {0xF7, (uint8_t []){0x49, 0x61, 0x02, 0x00}, 4, 0},
    {0x30, (uint8_t []){0x01}, 1, 0},
    {0x04, (uint8_t []){0x0C}, 1, 0},
    {0x05, (uint8_t []){0x08}, 1, 0},
    {0x0B, (uint8_t []){0x11}, 1, 0}, //0x11(2lanes),0x12(3lanes),0x13(4lanes)
    {0x20, (uint8_t []){0x04}, 1, 0}, //r_lansel_sel_reg  //A2 add
    {0x1F, (uint8_t []){0x00}, 1, 0},  //mipi_hs_settle  //0x05->0x00 (P7_r01=04)
    {0x23, (uint8_t []){0x38}, 1, 0},
    {0x28, (uint8_t []){0x18}, 1, 0},
    {0x29, (uint8_t []){0x29}, 1, 0},
    {0x2A, (uint8_t []){0x01}, 1, 0},
    {0x2B, (uint8_t []){0x29}, 1, 0},
    {0x2C, (uint8_t []){0x01}, 1, 0},
    {0x30, (uint8_t []){0x02}, 1, 0},
    {0x00, (uint8_t []){0x05}, 1, 0},
    {0x01, (uint8_t []){0x22}, 1, 0},
    {0x02, (uint8_t []){0x08}, 1, 0},
    {0x03, (uint8_t []){0x12}, 1, 0},
    {0x04, (uint8_t []){0x16}, 1, 0},
    {0x05, (uint8_t []){0x64}, 1, 0},
    {0x06, (uint8_t []){0x00}, 1, 0},
    {0x07, (uint8_t []){0x00}, 1, 0},
    {0x08, (uint8_t []){0x78}, 1, 0},
    {0x09, (uint8_t []){0x00}, 1, 0},
    {0x0A, (uint8_t []){0x04}, 1, 0},
    {0x0B, (uint8_t []){0x16,0x17,0x0B,0x0D,0x0D,0x0D,0x11,0x10,0x07,0x07,0x09}, 11, 0},
    {0x0C, (uint8_t []){0x09,0x1E,0x1E,0x1C,0x1C,0x0D,0x0D,0x0D,0x0D,0x0D,0x0D}, 11, 0},
    {0x0D, (uint8_t []){0x0A,0x05,0x0B,0x0D,0x0D,0x0D,0x11,0x10,0x06,0x06,0x08}, 11, 0},
    {0x0E, (uint8_t []){0x08,0x1F,0x1F,0x1D,0x1D,0x0D,0x0D,0x0D,0x0D,0x0D,0x0D}, 11, 0},
    {0x0F, (uint8_t []){0x0A,0x05,0x0D,0x0B,0x0D,0x0D,0x11,0x10,0x1D,0x1D,0x1F}, 11, 0},
    {0x10, (uint8_t []){0x1F,0x08,0x08,0x06,0x06,0x0D,0x0D,0x0D,0x0D,0x0D,0x0D}, 11, 0},
    {0x11, (uint8_t []){0x16,0x17,0x0D,0x0B,0x0D,0x0D,0x11,0x10,0x1C,0x1C,0x1E}, 11, 0},
    {0x12, (uint8_t []){0x1E,0x09,0x09,0x07,0x07,0x0D,0x0D,0x0D,0x0D,0x0D,0x0D}, 11, 0},
    {0x13, (uint8_t []){0x00,0x00,0x00,0x00}, 4, 0},
    {0x14, (uint8_t []){0x00,0x00,0x41,0x41}, 4, 0},
    {0x15, (uint8_t []){0x00,0x00,0x00,0x00}, 4, 0},
    {0x17, (uint8_t []){0x00}, 1, 0},
    {0x18, (uint8_t []){0x85}, 1, 0},
    {0x19, (uint8_t []){0x06,0x09}, 2, 0},
    {0x1A, (uint8_t []){0x05,0x08}, 2, 0},
    {0x1B, (uint8_t []){0x0A,0x04}, 2, 0},
    {0x26, (uint8_t []){0x00}, 1, 0},
    {0x27, (uint8_t []){0x00}, 1, 0},
    {0x30, (uint8_t []){0x06}, 1, 0},
    {0x12, (uint8_t []){0x3F,0x26,0x27,0x35,0x2D,0x34,0x3F,0x3F,0x3F,0x35,0x2A,0x20,0x16,0x08}, 14, 0},
    {0x13, (uint8_t []){0x3F,0x26,0x28,0x35,0x27,0x29,0x29,0x2F,0x35,0x2F,0x26,0x20,0x16,0x08}, 14, 0},
    {0x30, (uint8_t []){0x0A}, 1, 0},
    {0x02, (uint8_t []){0x4F}, 1, 0},
    {0x0B, (uint8_t []){0x40}, 1, 0},
    {0x30, (uint8_t []){0x0D}, 1, 0},
    {0x0D, (uint8_t []){0x04}, 1, 0}, //mipi add  //0x0C, 0x04
    {0x10, (uint8_t []){0x0C}, 1, 0},
    {0x11, (uint8_t []){0x0C}, 1, 0},
    {0x12, (uint8_t []){0x0C}, 1, 0},
    {0x13, (uint8_t []){0x0C}, 1, 0},
    {0x30, (uint8_t []){0x00}, 1, 0},
    {0x11, (uint8_t []){0x00}, 0, 120},
    {0x29, (uint8_t []){0x00}, 0, 20},
};
#endif

void example_dsi_resource_alloc(esp_lcd_dsi_bus_handle_t *mipi_dsi_bus, esp_lcd_panel_io_handle_t *mipi_dbi_io, esp_lcd_panel_handle_t *mipi_dpi_panel, void **frame_buffer)
{
    //---------------DSI resource allocation------------------//
    esp_lcd_dsi_bus_config_t bus_config = {
        .bus_id = 0,
        .num_data_lanes = 2,
        .phy_clk_src = MIPI_DSI_PHY_CLK_SRC_DEFAULT,
        .lane_bit_rate_mbps = 1000, // 1000 Mbps
    };
    ESP_ERROR_CHECK(esp_lcd_new_dsi_bus(&bus_config, mipi_dsi_bus));

    esp_lcd_dbi_io_config_t dbi_config = {
        .virtual_channel = 0,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_dbi(*mipi_dsi_bus, &dbi_config, mipi_dbi_io));

    esp_lcd_dpi_panel_config_t dpi_config = {
        .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,
        .dpi_clock_freq_mhz = EXAMPLE_MIPI_DSI_DPI_CLK_MHZ,
        .virtual_channel = 0,
        .in_color_format = LCD_COLOR_FMT_RGB565,
        .video_timing = {
            .h_size = CONFIG_EXAMPLE_MIPI_DSI_DISP_HRES,
            .v_size = CONFIG_EXAMPLE_MIPI_DSI_DISP_VRES,
            .hsync_back_porch = EXAMPLE_MIPI_DSI_IMAGE_HBP,
            .hsync_pulse_width = EXAMPLE_MIPI_DSI_IMAGE_HSYNC,
            .hsync_front_porch = EXAMPLE_MIPI_DSI_IMAGE_HFP,
            .vsync_back_porch = EXAMPLE_MIPI_DSI_IMAGE_VBP,
            .vsync_pulse_width = EXAMPLE_MIPI_DSI_IMAGE_VSYNC,
            .vsync_front_porch = EXAMPLE_MIPI_DSI_IMAGE_VFP,
        },
#if CONFIG_EXAMPLE_MIPI_DSI_DISP_USE_DMA2D
        .flags.use_dma2d = true,
#endif
    };

#if CONFIG_EXAMPLE_LCD_PATTERN_ILI9881C
    ili9881c_vendor_config_t vendor_config = {
        .mipi_config = {
            .dsi_bus = *mipi_dsi_bus,
            .dpi_config = &dpi_config,
            .lane_num = 2,
        },
    };
    esp_lcd_panel_dev_config_t lcd_dev_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9881c(*mipi_dbi_io, &lcd_dev_config, mipi_dpi_panel));
#elif CONFIG_EXAMPLE_LCD_PATTERN_EK79007
#if VIEWE_JD9165_7
    jd9165_vendor_config_t vendor_config = {
        .init_cmds = lcd_init_cmds,
        .init_cmds_size = sizeof(lcd_init_cmds) / sizeof(jd9165_lcd_init_cmd_t),
        .mipi_config = {
            .dsi_bus = *mipi_dsi_bus,
            .dpi_config = &dpi_config,
        },
    };
    esp_lcd_panel_dev_config_t lcd_dev_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_jd9165(*mipi_dbi_io, &lcd_dev_config, mipi_dpi_panel));
#else
    ek79007_vendor_config_t vendor_config = {
        .mipi_config = {
            .dsi_bus = *mipi_dsi_bus,
            .dpi_config = &dpi_config,
        },
    };
    esp_lcd_panel_dev_config_t lcd_dev_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ek79007(*mipi_dbi_io, &lcd_dev_config, mipi_dpi_panel));
#endif
#endif

    ESP_ERROR_CHECK(esp_lcd_dpi_panel_get_frame_buffer(*mipi_dpi_panel, 1, frame_buffer));
}

void example_dpi_panel_reset(esp_lcd_panel_handle_t mipi_dpi_panel)
{
    //---------------DPI Panel Reset------------------//
    ESP_ERROR_CHECK(esp_lcd_panel_reset(mipi_dpi_panel));
}

void example_dpi_panel_init(esp_lcd_panel_handle_t mipi_dpi_panel)
{
    //---------------DPI Panel Init------------------//
    ESP_ERROR_CHECK(esp_lcd_panel_init(mipi_dpi_panel));
}

void example_dsi_resource_destroy(esp_lcd_dsi_bus_handle_t mipi_dsi_bus, esp_lcd_panel_io_handle_t mipi_dbi_io, esp_lcd_panel_handle_t mipi_dpi_panel)
{
    ESP_ERROR_CHECK(esp_lcd_panel_del(mipi_dpi_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_io_del(mipi_dbi_io));
    ESP_ERROR_CHECK(esp_lcd_del_dsi_bus(mipi_dsi_bus));
}
