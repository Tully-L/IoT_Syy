//#include "delay.h"

//static uint8_t fac_us = 0;
//static uint16_t fac_ms = 0;

///*
// * Function: delay_init
// * Description: Initialize delay function
// * Parameters: None
// * Returns: None
// */
//void delay_init(void)
//{
//    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
//    fac_us = SystemCoreClock / 8000000;
//    fac_ms = (uint16_t)fac_us * 1000;
//}

///*
// * Function: delay_us
// * Description: Microsecond delay
// * Parameters: us - delay time in microseconds
// * Returns: None
// */
//void delay_us(uint32_t us)
//{
//    uint32_t start = SysTick->VAL;
//    uint32_t cycles = us * (SystemCoreClock / 1000000);
//    uint32_t reload = SysTick->LOAD;
//    
//    while(1)
//    {
//        uint32_t current = SysTick->VAL;
//        uint32_t elapsed;
//        
//        if(current <= start)
//        {
//            elapsed = start - current;
//        }
//        else
//        {
//            elapsed = reload - current + start;
//        }
//        
//        if(elapsed >= cycles)
//        {
//            break;
//        }
//    }
//}

///*
// * Function: delay_ms
// * Description: Millisecond delay
// * Parameters: ms - delay time in milliseconds
// * Returns: None
// */
//void delay_ms(uint16_t ms)
//{
//    uint32_t temp;
//    SysTick->LOAD = (uint32_t)ms * fac_ms;
//    SysTick->VAL = 0x00;
//    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
//    do
//    {
//        temp = SysTick->CTRL;
//    }
//    while((temp & 0x01) && !(temp & (1<<16)));
//    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
//    SysTick->VAL = 0X00;
//}
