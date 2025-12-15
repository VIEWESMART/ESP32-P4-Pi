#include "QMI8658.h"

static const char *TAG = "main"; // 在终端看到main 表示这条信息是从main.c文件中输出的

t_sQMI8658 QMI8658; // 定义QMI8658结构体变量

void app_main(void)
{
    ESP_ERROR_CHECK(bsp_i2c_init());  // 初始化I2C总线
    ESP_LOGI(TAG, "I2C initialized successfully"); // 输出I2C初始化成功的信息
    
    // 给I2C总线一些时间稳定
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    // 扫描I2C总线，查找所有设备
    bsp_i2c_scan();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    ESP_LOGI(TAG, "Starting QMI8658 initialization...");
    qmi8658_init(); // 初始化qmi8658芯片
    ESP_LOGI(TAG, "QMI8658 initialization function returned");
    
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延时1000ms
        qmi8658_fetch_angleFromAcc(&QMI8658);   // 获取XYZ轴的倾角
        // 输出XYZ轴的倾角
        ESP_LOGI(TAG, "angle_x = %.1f  angle_y = %.1f angle_z = %.1f",QMI8658.AngleX, QMI8658.AngleY, QMI8658.AngleZ);
    }
}


