# GM01-Light-Sensor-driver

A driver for GM01 Light Sensor

## 驱动使用说明

### 1. 硬件连接
- **光敏传感器输出**连接到默认为01引脚
- **光敏传感器VCC**连接到3.3V
- **光敏传感器GND**连接到GND

### 2. 编译配置
- 确保在`CMakeLists.txt`中添加了LS组件

### 3. 主要函数
- `LS_Init()`: 初始化光敏传感器
- `LS_Get_Status()`: 获取光线状态

### 4. 全局变量
- `ls_adc_value`: ADC原始值
- `ls_status`: 光线状态 (0=不足, 1=充足)

### 5. 暗光阈值调整
可以在`LS.h`中修改`LS_THRESHOLD_DARK`
根据实际光敏传感器特性调整这个值
