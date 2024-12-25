#include "beep.h"
#include "delay1.h"

// Initialize beeper on PB10
void beep_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // Initially off
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}

// Implement beep patterns
void beep_short(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_10);
    delay_ms(100);
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}

void beep_double(void)
{
    beep_short();
    delay_ms(100);
    beep_short();
}

void beep_error(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_10);
    delay_ms(500);
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}
