#include "stm32f10x.h"
#include "delay1.h"
#include "led.h"
#include "oled.h"
#include "usart1.h" 
#include "stdio.h"

// Pin definitions
#define SERVO_PIN      GPIO_Pin_11    // PB11 - Servo
#define SERVO_PORT     GPIOB
#define LIGHT_PIN      GPIO_Pin_1     // PA1 - Light sensor
#define LIGHT_PORT     GPIOA
#define BEEP_PIN      GPIO_Pin_6     // PA6 - Buzzer
#define BEEP_PORT     GPIOA

// System parameters
#define LIGHT_THRESHOLD  2000
#define PULSE_0_DEG    1000    // 1ms for 0 degrees
#define PULSE_90_DEG   2000    // 2ms for 90 degrees

// Buzzer control macros
#define BEEP_ON()   GPIO_SetBits(BEEP_PORT, BEEP_PIN)
#define BEEP_OFF()  GPIO_ResetBits(BEEP_PORT, BEEP_PIN)

// Global variables
static uint8_t doorState = 0;         // 0: closed, 1: open
static uint8_t lastLightState = 0;    // 0: bright, 1: dark
static uint8_t lastPosition = 0;      // Track servo position

// Function declarations
static void Servo_Init(void);
static void Servo_Pulse(uint16_t pulseWidth);
static void Servo_Move(uint16_t pulseWidth);
static void LightSensor_Init(void);
static void Buzzer_Init(void);
static void Beep_Open(void);
static void Beep_Close(void);
static uint16_t ReadLightSensor(void);
static void updateDisplay(void);
static void updateSystem(void);

/**
 * @brief Initialize GPIO for servo control
 */
static void Servo_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = SERVO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SERVO_PORT, &GPIO_InitStructure);
}

/**
 * @brief Generate servo pulse using delays
 */
static void Servo_Pulse(uint16_t pulseWidth)
{
    GPIO_SetBits(SERVO_PORT, SERVO_PIN);
    delay_us(pulseWidth);
    GPIO_ResetBits(SERVO_PORT, SERVO_PIN);
    delay_us(20000 - pulseWidth);  // Complete 20ms period
}

/**
 * @brief Move servo to specified position with multiple pulses
 */
static void Servo_Move(uint16_t pulseWidth)
{
    for(int i = 0; i < 50; i++)
    {
        Servo_Pulse(pulseWidth);
    }
}

/**
 * @brief Initialize buzzer GPIO
 */
static void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
    
    // Initially off
    BEEP_OFF();
}

/**
 * @brief Generate door open sound (single long beep)
 */
static void Beep_Open(void)
{
    BEEP_ON();
    delay_ms(500);    // Long beep
    BEEP_OFF();
}

/**
 * @brief Generate door close sound (two short beeps)
 */
static void Beep_Close(void)
{
    // First short beep
    BEEP_ON();
    delay_ms(100);
    BEEP_OFF();
    delay_ms(100);
    
    // Second short beep
    BEEP_ON();
    delay_ms(100);
    BEEP_OFF();
}

/**
 * @brief Initialize ADC for light sensor
 */
static void LightSensor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = LIGHT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(LIGHT_PORT, &GPIO_InitStructure);
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1, ENABLE);
    
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

/**
 * @brief Read light sensor value
 */
static uint16_t ReadLightSensor(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

/**
 * @brief Update OLED display
 */
static void updateDisplay(void)
{
    char buf[20];
    uint16_t lightValue = ReadLightSensor();
    
    OLED_Clear();
    
    // Display door status in one line
    sprintf(buf, "Door: %s", doorState ? "OPEN" : "CLOSED");
    OLED_ShowString(0, 0, buf);
    
    // Display light value in one line
    sprintf(buf, "Light: %d", lightValue);
    OLED_ShowString(0, 2, buf);
    
    // Display light status in one line
    sprintf(buf, "Status: %s", lightValue > LIGHT_THRESHOLD ? "DARK" : "BRIGHT");
    OLED_ShowString(0, 4, buf);
}

/**
 * @brief Update system state based on light level
 */
static void updateSystem(void)
{
    uint16_t lightValue = ReadLightSensor();
    uint8_t currentLightState = (lightValue > LIGHT_THRESHOLD) ? 1 : 0;
    
    if(currentLightState != lastLightState)
    {
        lastLightState = currentLightState;
        
        if(lightValue > LIGHT_THRESHOLD)  // Dark environment
        {
            red_led_on();                 // Turn on red LED
            green_led_off();              // Turn off green LED
            if(lastPosition != 0)
            {
                Servo_Move(PULSE_0_DEG);  // Close door (0 degrees)
                lastPosition = 0;
                doorState = 0;
                printf("\r\nDark Environment - Door Closed\r\n");
                Beep_Close();             // Double beep for door close
            }
        }
        else  // Bright environment
        {
            green_led_on();               // Turn on green LED
            red_led_off();                // Turn off red LED
            if(lastPosition != 90)
            {
                Servo_Move(PULSE_90_DEG); // Open door (90 degrees)
                lastPosition = 90;
                doorState = 1;
                printf("\r\nBright Environment - Door Open\r\n");
                Beep_Open();              // Single long beep for door open
            }
        }
        
        updateDisplay();  // Update OLED display
    }
    
    // Maintain servo position
    Servo_Pulse(lastPosition == 0 ? PULSE_0_DEG : PULSE_90_DEG);
}

/**
 * @brief Main function
 */
int main(void)
{
    // Initialize system
    SystemInit();
    delay_init();
    
    // Initialize peripherals
    usart1_init();
    OLED_Init();
    OLED_Clear();
    led_init();
    Servo_Init();
    LightSensor_Init();
    Buzzer_Init();
    
    printf("\r\nSystem Initialized\r\n");
    printf("Light Control Active\r\n");
    
    // Set initial position
    Servo_Move(PULSE_0_DEG);
    lastPosition = 0;
    doorState = 0;
    
    // Initial display update
    updateDisplay();
    
    // Main loop
    while(1)
    {
        updateSystem();      // Update system state
        delay_ms(20);       // Delay for stability
    }
}
