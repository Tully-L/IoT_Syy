//#include "key.h"
//#include "delay1.h"

///**
// * @brief Initialize key S1 GPIO
// * @note  PA4 - Output (Row1), PA3 - Input with pull-up (Col1)
// */
//void KEY_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    
//    // Enable GPIOA clock
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    
//    // Configure PA4 as output
//    GPIO_InitStructure.GPIO_Pin = KEY_OUT_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
//    
//    // Configure PA3 as input with pull-up
//    GPIO_InitStructure.GPIO_Pin = KEY_IN_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
//    
//    // Set output pin to low level
//    GPIO_ResetBits(KEY_PORT, KEY_OUT_PIN);
//}

///**
// * @brief Scan key status with debounce
// * @return 1 if key pressed, 0 if not pressed
// */
//uint8_t KEY_Scan(void)
//{
//    if(GPIO_ReadInputDataBit(KEY_PORT, KEY_IN_PIN) == 0)
//    {
//        delay_ms(20);  // Debounce delay
//        if(GPIO_ReadInputDataBit(KEY_PORT, KEY_IN_PIN) == 0)
//        {
//            while(GPIO_ReadInputDataBit(KEY_PORT, KEY_IN_PIN) == 0);
//            delay_ms(20);  // Release debounce
//            return 1;
//        }
//    }
//    return 0;
//}
