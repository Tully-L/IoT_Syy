//#include "light_control.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_adc.h"
//#include "delay1.h"
//#include "stdio.h"
//#include "sg90.h"
//#include "oled.h"

//// Global variables definition
//uint32_t lastMotionTime = 0;
//uint8_t lightingActive = 0;
//static uint32_t systemTicks = 0;
//uint16_t currentLightLevel = 0;

///**
// * @brief Initialize light sensor (PA0, PA1)
// */
//void LightSensor_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    ADC_InitTypeDef ADC_InitStructure;

//    // Enable GPIOA and ADC1 clocks
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

//    // Configure PA0 as digital input (DO pin)
//    GPIO_InitStructure.GPIO_Pin = LIGHT_DO_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // Configure PA1 as analog input (AO pin)
//    GPIO_InitStructure.GPIO_Pin = LIGHT_AO_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // ADC1 configuration for analog reading
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//    ADC_InitStructure.ADC_NbrOfChannel = 1;
//    ADC_Init(ADC1, &ADC_InitStructure);

//    // Configure ADC channel for light sensor
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
//    
//    // Enable ADC
//    ADC_Cmd(ADC1, ENABLE);
//    
//    // ADC calibration
//    ADC_ResetCalibration(ADC1);
//    while(ADC_GetResetCalibrationStatus(ADC1));
//    ADC_StartCalibration(ADC1);
//    while(ADC_GetCalibrationStatus(ADC1));
//}

///**
// * @brief Initialize RGB LED (PA8, PB15, PB14)
// */
//void RGB_LED_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;

//    // Enable GPIOA and GPIOB clocks
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

//    // Configure PA8 (Red)
//    GPIO_InitStructure.GPIO_Pin = RGB_RED_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // Configure PB15 (Green) and PB14 (Blue)
//    GPIO_InitStructure.GPIO_Pin = RGB_GREEN_PIN | RGB_BLUE_PIN;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);

//    // Turn off all LEDs initially
//    RGB_LED_Off();
//}

///**
// * @brief Turn on RGB LED (white light)
// */
//void RGB_LED_White(void)
//{
//    GPIO_SetBits(GPIOA, RGB_RED_PIN);     // Red on
//    GPIO_SetBits(GPIOB, RGB_GREEN_PIN);   // Green on
//    GPIO_SetBits(GPIOB, RGB_BLUE_PIN);    // Blue on
//}

///**
// * @brief Turn off RGB LED
// */
//void RGB_LED_Off(void)
//{
//    GPIO_ResetBits(GPIOA, RGB_RED_PIN);     // Red off
//    GPIO_ResetBits(GPIOB, RGB_GREEN_PIN);   // Green off
//    GPIO_ResetBits(GPIOB, RGB_BLUE_PIN);    // Blue off
//}

///**
// * @brief Read analog light sensor value
// * @return ADC value (0-4095)
// */
//uint16_t ReadLightSensor(void)
//{
//    // Start ADC conversion
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    
//    // Wait for conversion complete
//    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
//    
//    // Get and store current light level
//    currentLightLevel = ADC_GetConversionValue(ADC1);
//    
//    return currentLightLevel;
//}

///**
// * @brief Check if current environment is dark
// * @return 1 if dark, 0 if bright
// */
//uint8_t IsDarkEnvironment(void)
//{
//    uint16_t lightLevel = ReadLightSensor();
//    return (lightLevel > DAYLIGHT_THRESHOLD);
//}

///**
// * @brief Update OLED display with current status
// * @param doorState: Current door state (0: Closed, 1: Open)
// */
//void updateDisplayInfo(uint8_t doorState)
//{
//    char buf[32];
//    
//    OLED_Clear();
//    
//    // Display title
//    OLED_ShowString(0, 0, "System Status:");
//    
//    // Display light level
//    sprintf(buf, "Light: %d", currentLightLevel);
//    OLED_ShowString(0, 2, buf);
//    
//    // Display environment status
//    if(IsDarkEnvironment())
//    {
//        OLED_ShowString(0, 4, "Env: Dark");
//    }
//    else
//    {
//        OLED_ShowString(0, 4, "Env: Bright");
//    }
//    
//    // Display door status
//    sprintf(buf, "Door: %s", doorState ? "Open" : "Closed");
//    OLED_ShowString(0, 6, buf);
//}

///**
// * @brief Process lighting control based on light sensor and motion
// */
//void processLighting(void)
//{
//    static uint32_t currentTime = 0;
//    systemTicks++;
//    currentTime = systemTicks;

//    // Only process if environment is dark
//    if(IsDarkEnvironment())
//    {
//        // Check for motion (using touch sensor as motion detector)
//        if(Touch_Scan())
//        {
//            lastMotionTime = currentTime;
//            if(!lightingActive)
//            {
//                RGB_LED_White();
//                lightingActive = 1;
//                printf("\r\nDark environment detected (Light: %d) - Lighting activated\r\n", 
//                       currentLightLevel);
//            }
//        }

//        // Turn off light if no motion for 6 seconds
//        if(lightingActive && (currentTime - lastMotionTime > NO_MOTION_TIME))
//        {
//            RGB_LED_Off();
//            lightingActive = 0;
//            printf("\r\nNo motion detected - Lighting deactivated\r\n");
//        }
//    }
//    else if(lightingActive)  // If it becomes bright and light is on
//    {
//        RGB_LED_Off();
//        lightingActive = 0;
//        printf("\r\nDaylight detected (Light: %d) - Lighting deactivated\r\n", 
//               currentLightLevel);
//    }
//}
