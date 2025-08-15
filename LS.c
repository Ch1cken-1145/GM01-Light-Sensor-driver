/*
 * 光敏传感器ESP-IDF驱动代码
 * 基于STM32F103光敏传感器代码移植
 * 使用ESP32的ADC功能读取光敏传感器值
 * 
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-19     AI Assistant    first version
 */

#include "LS.h"
#include "esp_timer.h"

// 全局变量定义
uint16_t ls_adc_value = 0;
uint8_t ls_status = LS_INSUFFICIENT;
uint32_t ls_bright_time_sec = 0;       // 充足光线持续时间 (秒)

// 光敏传感器初始化
void LS_Init(void)
{
    // 配置ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(LS_ADC_CHANNEL, ADC_ATTEN_DB_11);
    
    // 初始化状态
    ls_status = LS_INSUFFICIENT;
    ls_adc_value = 0;
}

// 获取光敏传感器状态
uint8_t LS_Get_Status(void)
{
    static uint64_t bright_start_time = 0;  // 充足光线开始时间
    static uint8_t last_status = LS_INSUFFICIENT;   // 上次状态
    uint64_t current_time = esp_timer_get_time() / 1000000; // 转换为秒
    
    // 读取ADC值
    ls_adc_value = adc1_get_raw(LS_ADC_CHANNEL);
    
    // 根据阈值判断状态
    if (ls_adc_value < LS_THRESHOLD_DARK) {
        ls_status = LS_INSUFFICIENT;
        // 如果从充足变为不足，重置计时器
        if (last_status == LS_SUFFICIENT) {
            bright_start_time = 0;
        }
        ls_bright_time_sec = 0;
    } else {
        ls_status = LS_SUFFICIENT;
        // 如果从不足变为充足，开始计时
        if (last_status == LS_INSUFFICIENT) {
            bright_start_time = current_time;
        }
        // 计算充足光线持续时间
        if (bright_start_time > 0) {
            ls_bright_time_sec = current_time - bright_start_time;
        }
    }
    
    last_status = ls_status;
    return ls_status;
} 