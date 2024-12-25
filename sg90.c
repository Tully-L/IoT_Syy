#include "sg90.h"
#include "delay1.h"

// PWM related definitions
#define TIM_PERIOD      20000-1    // 20ms period (50Hz)
#define TIM_PRESCALER   72-1       // 72MHz/72=1MHz
#define SERVO_MIN       500        // 0.5ms - 0 degrees
#define SERVO_MAX       2500       // 2.5ms - 180 degrees

static uint8_t doorState = DOOR_CLOSED;

/**
 * @brief Initialize SG90 servo using Timer2 Channel1 (PA0)
 */
void SG90_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    // Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    // Configure PA0 as Timer2 Channel1 output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Time base configuration
    TIM_TimeBaseStructure.TIM_Period = TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    // PWM1 Mode configuration: Channel1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SERVO_MIN;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    
    // Enable Timer2
    TIM_Cmd(TIM2, ENABLE);
    
    // Move to initial position
    SG90_SetAngle(ANGLE_CLOSED);
    delay_ms(500);  // Wait for servo to reach position
}

/**
 * @brief Set servo angle
 * @param angle: 0-180 degrees
 */
void SG90_SetAngle(uint8_t angle)
{
    uint16_t pulse;
    
    // Limit angle to 0-180 degrees
    if(angle > 180)
        angle = 180;
    
    // Convert angle to pulse width
    // 500-2500 us mapped to 0-180 degrees
    pulse = SERVO_MIN + (uint16_t)((SERVO_MAX - SERVO_MIN) * angle / 180);
    
    // Set pulse width
    TIM_SetCompare1(TIM2, pulse);
    
    // Small delay for stability
    delay_ms(20);
}

///**
// * @brief Set door position using servo
// * @param state: DOOR_CLOSED (0) or DOOR_OPEN (1)
// */
//void setDoorState(uint8_t state)
//{
//    if(state == DOOR_CLOSED)
//    {
//        SG90_SetAngle(ANGLE_CLOSED);
//    }
//    else
//    {
//        SG90_SetAngle(ANGLE_OPEN);
//    }
//    doorState = state; 
//}

/**
 * @brief Get current door state
 * @return Current door state (DOOR_CLOSED or DOOR_OPEN)
 */
uint8_t getDoorState(void)
{
    return doorState;
}
