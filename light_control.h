//#ifndef __LIGHT_CONTROL_H
//#define __LIGHT_CONTROL_H

//#include "stm32f10x.h"

//// Pin definitions
//#define LIGHT_DO_PIN     GPIO_Pin_0     // PA0 - Digital output
//#define LIGHT_AO_PIN     GPIO_Pin_1     // PA1 - Analog input
//#define RGB_RED_PIN      GPIO_Pin_8     // PA8
//#define RGB_GREEN_PIN    GPIO_Pin_15    // PB15
//#define RGB_BLUE_PIN     GPIO_Pin_14    // PB14

//// Light sensor thresholds
//#define LIGHT_THRESHOLD  2000    // Adjust based on your environment
//#define NO_MOTION_TIME   600     // 6 seconds (when counting in 10ms units)
//#define DAYLIGHT_THRESHOLD 1000  // Threshold for daylight detection

//// Global variables (extern declaration)
//extern uint32_t lastMotionTime;
//extern uint8_t lightingActive;
//extern uint16_t currentLightLevel;

//// Function prototypes
//void LightSensor_Init(void);
//void RGB_LED_Init(void);
//void RGB_LED_White(void);
//void RGB_LED_Off(void);
//uint16_t ReadLightSensor(void);
//uint8_t IsDarkEnvironment(void);
//void processLighting(void);
//void updateDisplayInfo(uint8_t doorState);

//#endif
