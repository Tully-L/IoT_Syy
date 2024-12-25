#include "oled.h"
#include "oledfont.h"
#include "stdio.h"

// Helper function for calculations
uint32_t OLED_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while(n--)
        result *= m;
    return result;
}

// Delay function
static void OLED_Delay(void)
{
    uint16_t i = 500;
    while(i--);
}

// I2C communication functions
static void I2C_Start(void)
{
    GPIO_SetBits(OLED_GPIO, OLED_SDA_PIN);
    GPIO_SetBits(OLED_GPIO, OLED_SCL_PIN);
    OLED_Delay();
    GPIO_ResetBits(OLED_GPIO, OLED_SDA_PIN);
    OLED_Delay();
    GPIO_ResetBits(OLED_GPIO, OLED_SCL_PIN);
}

static void I2C_Stop(void)
{
    GPIO_ResetBits(OLED_GPIO, OLED_SDA_PIN);
    GPIO_SetBits(OLED_GPIO, OLED_SCL_PIN);
    OLED_Delay();
    GPIO_SetBits(OLED_GPIO, OLED_SDA_PIN);
}

static void I2C_SendByte(uint8_t data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        GPIO_ResetBits(OLED_GPIO, OLED_SCL_PIN);
        if(data & 0x80)
            GPIO_SetBits(OLED_GPIO, OLED_SDA_PIN);
        else
            GPIO_ResetBits(OLED_GPIO, OLED_SDA_PIN);
        OLED_Delay();
        GPIO_SetBits(OLED_GPIO, OLED_SCL_PIN);
        OLED_Delay();
        data <<= 1;
    }
    GPIO_ResetBits(OLED_GPIO, OLED_SCL_PIN);
    OLED_Delay();
    GPIO_SetBits(OLED_GPIO, OLED_SCL_PIN);
    OLED_Delay();
    GPIO_ResetBits(OLED_GPIO, OLED_SCL_PIN);
}

static void OLED_WriteCmd(uint8_t cmd)
{
    I2C_Start();
    I2C_SendByte(OLED_ADDR);
    I2C_SendByte(0x00);
    I2C_SendByte(cmd);
    I2C_Stop();
}

static void OLED_WriteData(uint8_t data)
{
    I2C_Start();
    I2C_SendByte(OLED_ADDR);
    I2C_SendByte(0x40);
    I2C_SendByte(data);
    I2C_Stop();
}

void OLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OLED_GPIO, &GPIO_InitStructure);
    
    GPIO_SetBits(OLED_GPIO, OLED_SCL_PIN | OLED_SDA_PIN);
    
    // Power-on delay
    for(uint32_t i = 0; i < 500000; i++);
    
    // OLED initialization sequence
    OLED_WriteCmd(0xAE);
    OLED_WriteCmd(0xD5);
    OLED_WriteCmd(0x80);
    OLED_WriteCmd(0xA8);
    OLED_WriteCmd(0x3F);
    OLED_WriteCmd(0xD3);
    OLED_WriteCmd(0x00);
    OLED_WriteCmd(0x40);
    OLED_WriteCmd(0x8D);
    OLED_WriteCmd(0x14);
    OLED_WriteCmd(0x20);
    OLED_WriteCmd(0x02);
    OLED_WriteCmd(0xA1);
    OLED_WriteCmd(0xC8);
    OLED_WriteCmd(0xDA);
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0x81);
    OLED_WriteCmd(0xCF);
    OLED_WriteCmd(0xD9);
    OLED_WriteCmd(0xF1);
    OLED_WriteCmd(0xDB);
    OLED_WriteCmd(0x30);
    OLED_WriteCmd(0xA4);
    OLED_WriteCmd(0xA6);
    OLED_WriteCmd(0xAF);
    
    OLED_Clear();
}

// ????????
void OLED_Clear(void)
{
    uint8_t i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd(0xB0 + i);
        OLED_WriteCmd(0x00);
        OLED_WriteCmd(0x10);
        for(n = 0; n < 128; n++)
            OLED_WriteData(0x00);
    }
}

void OLED_ShowChar(uint8_t x, uint8_t y, char chr)
{
    uint8_t c = chr - ' ';
    uint8_t i = 0;
    
    OLED_Set_Pos(x * 6, y);
    for(i = 0; i < 6; i++)
        OLED_WriteData(F6x8[c][i]);
}

void OLED_ShowString(uint8_t x, uint8_t y, char *str)
{
    while(*str != '\0')
    {
        OLED_ShowChar(x++, y, *str++);
        if(x > 21)
        {
            x = 0;
            y++;
        }
    }
}

void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for(t = 0; t < len; t++)
    {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1))
        {
            if(temp == 0)
            {
                OLED_ShowChar(x + t, y, '0');
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + t, y, temp + '0');
    }
}

void OLED_ShowSignedNum(uint8_t x, uint8_t y, int32_t num, uint8_t len)
{
    uint8_t i;
    uint32_t Number;
    if(num >= 0)
    {
        OLED_ShowChar(x, y, '+');
        Number = num;
    }
    else
    {
        OLED_ShowChar(x, y, '-');
        Number = -num;
    }
    for(i = 0; i < len; i++)
    {
        OLED_ShowChar(x + i + 1, y, Number / OLED_Pow(10, len - i - 1) % 10 + '0');
    }
}

void OLED_ShowHexNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len)
{
    uint8_t i, SingleNumber;
    for(i = 0; i < len; i++)
    {
        SingleNumber = num / OLED_Pow(16, len - i - 1) % 16;
        if(SingleNumber < 10)
        {
            OLED_ShowChar(x + i, y, SingleNumber + '0');
        }
        else
        {
            OLED_ShowChar(x + i, y, SingleNumber - 10 + 'A');
        }
    }
}

void OLED_ShowBinNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len)
{
    uint8_t i;
    for(i = 0; i < len; i++)
    {
        OLED_ShowChar(x + i, y, num / OLED_Pow(2, len - i - 1) % 2 + '0');
    }
}


void OLED_Set_Pos(uint8_t x, uint8_t y)
{
    OLED_WriteCmd(0xB0 + y);
    OLED_WriteCmd(((x & 0xF0) >> 4) | 0x10);
    OLED_WriteCmd(x & 0x0F);
}
