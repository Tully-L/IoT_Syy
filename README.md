### 智能门锁系统 V1

**使用模块：**
1. 舵机（PB11 - 门控制）
2. 双色LED（状态指示）
3. OLED显示屏（状态显示）
4. 无源蜂鸣器（PA6 - 声音提示）
5. 光敏传感器（PA1 - 环境光检测）

**功能需求：**

1. 门控制功能：
```
// 基于光线的自动门控制
- 光敏传感器检测环境光线：
  * 光线明亮：舵机转到90°（开门）
  * 光线黑暗：舵机转到0°（关门）
```

2. 光线感应与状态指示：
```
// 自动状态控制
- 光敏传感器检测环境光线：
  * 检测到光线明亮：绿色LED亮起
  * 检测到光线黑暗：红色LED亮起
  * 阈值设定：2000（ADC值）
```

3. 状态显示系统：
```
// LED状态指示
- 双色LED状态：
  * 绿色：环境明亮，门开启
  * 红色：环境黑暗，门关闭

// OLED显示内容
- OLED实时显示：
  * Door: OPEN/CLOSED
  * Light: [ADC值]
  * Status: BRIGHT/DARK
```

4. 声音反馈系统：
```
// 蜂鸣器提示音
- 状态变化提示音：
  * 开门：单次长鸣（500ms）
  * 关门：两次短鸣（各100ms）
```

5. 串口通信：
```
// 状态报告
- 系统初始化提示
- 门状态变化提示：
  * "Bright Environment - Door Open"
  * "Dark Environment - Door Closed"
```

注：
- 系统启动默认为关门状态（0度）
- 系统通过20ms周期性检测实现稳定控制
- 所有状态变化都有相应的声光指示反馈

  
### 系统功能概述
这是一个基于STM32F10x的自动门控制系统，主要功能包括：
1. 根据环境光线自动控制门的开关（通过舵机实现）
2. LED指示当前状态（绿色表示明亮环境，红色表示黑暗环境）
3. 蜂鸣器提示门的开关状态（开门一声长鸣，关门两声短鸣）
4. OLED显示系统状态（包括门状态、光照值和光照状态）
5. 通过串口输出系统状态信息

### 详细模块解析

#### 1. 硬件定义
```c
// Pin definitions
#define SERVO_PIN      GPIO_Pin_11    // PB11 - 舵机控制引脚
#define SERVO_PORT     GPIOB
#define LIGHT_PIN      GPIO_Pin_1     // PA1 - 光敏传感器引脚
#define LIGHT_PORT     GPIOA
#define BEEP_PIN       GPIO_Pin_6     // PA6 - 蜂鸣器引脚
#define BEEP_PORT      GPIOA

// 系统参数
#define LIGHT_THRESHOLD  2000         // 光照阈值
#define PULSE_0_DEG     1000         // 0度对应的PWM脉冲宽度（1ms）
#define PULSE_90_DEG    2000         // 90度对应的PWM脉冲宽度（2ms）
```

#### 2. 舵机控制模块
```c
static void Servo_Init(void)
{
    // 初始化舵机GPIO为推挽输出模式
}

static void Servo_Pulse(uint16_t pulseWidth)
{
    // 生成单个PWM脉冲，周期20ms
    // pulseWidth决定舵机角度（1000-2000对应0-90度）
}

static void Servo_Move(uint16_t pulseWidth)
{
    // 连续发送50个脉冲确保舵机到达指定位置
}
```

#### 3. 光敏传感器模块
```c
static void LightSensor_Init(void)
{
    // 初始化ADC和GPIO配置
    // 配置PA1为模拟输入
    // 配置ADC1为独立模式，单次转换
}

static uint16_t ReadLightSensor(void)
{
    // 启动ADC转换并返回转换结果
}
```

#### 4. 蜂鸣器控制模块
```c
static void Buzzer_Init(void)
{
    // 初始化蜂鸣器GPIO为推挽输出
}

static void Beep_Open(void)
{
    // 开门提示音：一声长鸣（500ms）
}

static void Beep_Close(void)
{
    // 关门提示音：两声短鸣（各100ms）
}
```

#### 5. 显示控制模块
```c
static void updateDisplay(void)
{
    // 更新OLED显示内容
    // 显示门状态、光照值和光照状态
}
```

#### 6. 系统状态更新模块
```c
static void updateSystem(void)
{
    // 读取光照值并更新系统状态
    // 根据光照值控制：
    // - 舵机位置（门的开关）
    // - LED指示灯
    // - 蜂鸣器提示音
    // - 显示更新
    // - 串口输出
}
```

#### 7. 主函数
```c
int main(void)
{
    // 系统初始化
    // 外设初始化
    // 设置初始状态
    
    while(1)
    {
        updateSystem();      // 持续更新系统状态
        delay_ms(20);       // 延时保证稳定性
    }
}
```

### 工作流程
1. 系统上电后初始化所有外设，门处于关闭状态（0度）
2. 系统持续检测环境光照强度：
   - 光照值 > 阈值（2000）：表示环境黑暗
     - 关闭门（舵机转到0度）
     - 红色LED亮起
     - 发出两声短促蜂鸣
   - 光照值 ≤ 阈值：表示环境明亮
     - 打开门（舵机转到90度）
     - 绿色LED亮起
     - 发出一声长鸣
3. OLED实时显示系统状态
4. 串口输出状态变化信息

该系统实现了一个完整的自动门控制方案，通过光照感应实现自动控制，并提供了声光指示和状态显示功能。
