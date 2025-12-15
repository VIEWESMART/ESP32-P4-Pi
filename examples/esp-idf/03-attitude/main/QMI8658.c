#include "QMI8658.h"

static const char *TAG = "QMI8658";

/******************************************************************************/
/***************************  I2C ↓ *******************************************/
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

// I2C扫描功能，检测总线上有哪些设备
void bsp_i2c_scan(void)
{
    ESP_LOGI(TAG, "Scanning I2C bus...");
    ESP_LOGI(TAG, "I2C SDA: GPIO%d, SCL: GPIO%d", BSP_I2C_SDA, BSP_I2C_SCL);
    
    int devices_found = 0;
    for (uint8_t addr = 0x08; addr < 0x78; addr++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        
        esp_err_t ret = i2c_master_cmd_begin(BSP_I2C_NUM, cmd, pdMS_TO_TICKS(50));
        i2c_cmd_link_delete(cmd);
        
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "I2C device found at address: 0x%02X", addr);
            devices_found++;
        }
    }
    
    if (devices_found == 0) {
        ESP_LOGW(TAG, "No I2C devices found on the bus!");
        ESP_LOGW(TAG, "Please check:");
        ESP_LOGW(TAG, "  1. I2C wiring (SDA/SCL connections)");
        ESP_LOGW(TAG, "  2. Power supply to sensor");
        ESP_LOGW(TAG, "  3. Pull-up resistors (4.7kΩ recommended)");
    } else {
        ESP_LOGI(TAG, "Total I2C devices found: %d", devices_found);
    }
}
/***************************  I2C ↑  *******************************************/
/*******************************************************************************/


/*******************************************************************************/
/***************************  姿态传感器 QMI8658 ↓   ****************************/

// 存储实际检测到的QMI8658 I2C地址
static uint8_t qmi8658_actual_addr = QMI8658_SENSOR_ADDR;

// 读取QMI8658寄存器的值
esp_err_t qmi8658_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(BSP_I2C_NUM, qmi8658_actual_addr, &reg_addr, 1, data, len, 1000 / portTICK_PERIOD_MS);
}

// 给QMI8658的寄存器写值
esp_err_t qmi8658_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};

    return i2c_master_write_to_device(BSP_I2C_NUM, qmi8658_actual_addr, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
}

// 尝试读取指定地址的QMI8658 WHO_AM_I寄存器
static esp_err_t qmi8658_try_read_id(uint8_t addr, uint8_t *id)
{
    uint8_t reg = QMI8658_WHO_AM_I;
    return i2c_master_write_read_device(BSP_I2C_NUM, addr, &reg, 1, id, 1, pdMS_TO_TICKS(100));
}

// 初始化qmi8658
void qmi8658_init(void)
{
    uint8_t id = 0; // 芯片的ID号
    esp_err_t ret;
    uint8_t sensor_addr = QMI8658_SENSOR_ADDR; // 默认地址0x6A

    ESP_LOGI(TAG, "Starting QMI8658 initialization...");
    ESP_LOGI(TAG, "Trying I2C address: 0x%02X", sensor_addr);
    
    // 先尝试默认地址0x6A
    ret = qmi8658_try_read_id(sensor_addr, &id);
    if (ret != ESP_OK || id != 0x05) {
        ESP_LOGW(TAG, "Failed at address 0x%02X (ret=%s, id=0x%02X), trying alternative address 0x6B...", 
                 sensor_addr, esp_err_to_name(ret), id);
        // 尝试备用地址0x6B
        sensor_addr = 0x6B;
        ret = qmi8658_try_read_id(sensor_addr, &id);
        if (ret == ESP_OK && id == 0x05) {
            ESP_LOGI(TAG, "QMI8658 found at alternative address: 0x%02X", sensor_addr);
            qmi8658_actual_addr = sensor_addr; // 更新实际使用的地址
        } else {
            ESP_LOGE(TAG, "QMI8658 not found at 0x6A or 0x6B!");
            ESP_LOGE(TAG, "At 0x6B: ret=%s, id=0x%02X", esp_err_to_name(ret), id);
            ESP_LOGE(TAG, "Please check I2C connections and run I2C scan to verify.");
            return;
        }
    } else {
        // 在默认地址找到了
        qmi8658_actual_addr = sensor_addr;
        ESP_LOGI(TAG, "QMI8658 found at default address: 0x%02X, ID: 0x%02X", sensor_addr, id);
    }
    
    // ID已经验证成功，继续配置传感器
    ESP_LOGI(TAG, "QMI8658 ID verified successfully! Address: 0x%02X, ID: 0x%02X", qmi8658_actual_addr, id);

    // 复位
    ret = qmi8658_register_write_byte(QMI8658_RESET, 0xb0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to reset QMI8658, error: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "QMI8658 reset command sent");
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时10ms
    
    // CTRL1 设置地址自动增加
    ret = qmi8658_register_write_byte(QMI8658_CTRL1, 0x40);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write CTRL1, error: %s", esp_err_to_name(ret));
    }
    
    // CTRL7 允许加速度和陀螺仪
    ret = qmi8658_register_write_byte(QMI8658_CTRL7, 0x03);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write CTRL7, error: %s", esp_err_to_name(ret));
    }
    
    // CTRL2 设置ACC 4g 250Hz
    ret = qmi8658_register_write_byte(QMI8658_CTRL2, 0x95);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write CTRL2, error: %s", esp_err_to_name(ret));
    }
    
    // CTRL3 设置GRY 512dps 250Hz
    ret = qmi8658_register_write_byte(QMI8658_CTRL3, 0xd5);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write CTRL3, error: %s", esp_err_to_name(ret));
    }
    
    ESP_LOGI(TAG, "QMI8658 initialization completed successfully!");
}

// 读取加速度和陀螺仪寄存器值
void qmi8658_Read_AccAndGry(t_sQMI8658 *p)
{
    uint8_t status, data_ready=0;
    int16_t buf[6];

    qmi8658_register_read(QMI8658_STATUS0, &status, 1); // 读状态寄存器 
    if (status & 0x03) // 判断加速度和陀螺仪数据是否可读
        data_ready = 1;
    if (data_ready == 1){  // 如果数据可读
        data_ready = 0;
        qmi8658_register_read(QMI8658_AX_L, (uint8_t *)buf, 12); // 读加速度和陀螺仪值
        p->acc_x = buf[0];
        p->acc_y = buf[1];
        p->acc_z = buf[2];
        p->gyr_x = buf[3];
        p->gyr_y = buf[4];
        p->gyr_z = buf[5];
    }
}

// 获取XYZ轴的倾角值
void qmi8658_fetch_angleFromAcc(t_sQMI8658 *p)
{
    float temp;

    qmi8658_Read_AccAndGry(p); // 读取加速度和陀螺仪的寄存器值
    // 根据寄存器值 计算倾角值 并把弧度转换成角度
    temp = (float)p->acc_x / sqrt( ((float)p->acc_y * (float)p->acc_y + (float)p->acc_z * (float)p->acc_z) );
    p->AngleX = atan(temp)*57.29578f; // 180/π=57.29578
    temp = (float)p->acc_y / sqrt( ((float)p->acc_x * (float)p->acc_x + (float)p->acc_z * (float)p->acc_z) );
    p->AngleY = atan(temp)*57.29578f; // 180/π=57.29578
    temp = sqrt( ((float)p->acc_x * (float)p->acc_x + (float)p->acc_y * (float)p->acc_y) ) / (float)p->acc_z;
    p->AngleZ = atan(temp)*57.29578f; // 180/π=57.29578
}
/***************************  姿态传感器 QMI8658 ↑  ****************************/
/*******************************************************************************/
