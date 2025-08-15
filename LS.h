#ifndef __LS_H
#define __LS_H

#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

// 光敏传感器引脚定义
#define LS_PIN 1                      // 光敏传感器引脚 (VP)
#define LS_ADC_CHANNEL ADC1_CHANNEL_0 // ADC通道

// 光敏传感器状态定义
#define LS_INSUFFICIENT 0 // 光线不足
#define LS_SUFFICIENT 1   // 光线充足

// 光敏传感器阈值定义
#define LS_THRESHOLD_DARK 2000 // 暗光阈值

// 函数声明
void LS_Init(void);          // 光敏传感器初始化
uint8_t LS_Get_Status(void); // 获取光敏传感器状态

// 全局变量声明
extern uint16_t ls_adc_value;       // ADC原始值
extern uint8_t ls_status;           // 光敏传感器状态
extern uint32_t ls_bright_time_sec; // 亮光持续时间 (秒)

#endif