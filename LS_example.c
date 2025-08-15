#include "LS.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LS_TAG "LS_EXAMPLE"

// 光敏传感器任务示例
void ls_task_example(void *pvParameters)
{
    // 初始化光敏传感器
    LS_Init();

    ESP_LOGI(LS_TAG, "光敏传感器初始化完成");

    while (1)
    {
        // 获取光敏传感器状态
        uint8_t status = LS_Get_Status();

        // 输出状态信息
        if (status == LS_INSUFFICIENT)
        {
            ESP_LOGI(LS_TAG, "光线状态: 不足 (ADC值: %d)", ls_adc_value);
        }
        else
        {
            ESP_LOGI(LS_TAG, "光线状态: 充足 (ADC值: %d, 持续时间: %lu秒)",
                     ls_adc_value, ls_bright_time_sec);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// 主函数示例
void app_main(void)
{
    // 创建光敏传感器任务
    xTaskCreate(ls_task_example, "ls_task", 4096, NULL, 5, NULL);
}