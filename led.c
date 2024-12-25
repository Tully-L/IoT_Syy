#include "led.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void led_init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOA端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置PA0/PA1/PA2为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 初始状态设为低电平（LED熄灭）
    GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}

// 共阴极LED：高电平点亮，低电平熄灭
void red_led_on(void){
    GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 设置高电平点亮
}

void red_led_off(void){
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 设置低电平熄灭
}

void green_led_on(void){
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void green_led_off(void){
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void blue_led_on(void){
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void blue_led_off(void){
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}


