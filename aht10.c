#include "aht10.h"
#include "delay1.h"

// AHT10 Commands
#define AHT10_INIT_CMD     0xE1
#define AHT10_MEASURE_CMD  0xAC
#define AHT10_RESET_CMD    0xBA
#define AHT10_ADDR_WRITE   0x70
#define AHT10_ADDR_READ    0x71

// GPIO Definitions
#define AHT10_SCL_PIN     GPIO_Pin_12
#define AHT10_SDA_PIN     GPIO_Pin_15
#define AHT10_GPIO        GPIOA
#define AHT10_RCC         RCC_APB2Periph_GPIOA

// GPIO Operations
#define SCL_H   GPIO_SetBits(AHT10_GPIO, AHT10_SCL_PIN)
#define SCL_L   GPIO_ResetBits(AHT10_GPIO, AHT10_SCL_PIN)
#define SDA_H   GPIO_SetBits(AHT10_GPIO, AHT10_SDA_PIN)
#define SDA_L   GPIO_ResetBits(AHT10_GPIO, AHT10_SDA_PIN)
#define SDA_READ GPIO_ReadInputDataBit(AHT10_GPIO, AHT10_SDA_PIN)

// Function declarations
static void I2C_Delay(void);
static void SDA_OUT(void);
static void SDA_IN(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Ack(void);
static void I2C_NAck(void);
static uint8_t I2C_Wait_Ack(void);
static void I2C_Send_Byte(uint8_t txd);
static uint8_t I2C_Read_Byte(unsigned char ack);

// I2C Basic Functions
static void I2C_Delay(void)
{
    delay_us(4);
}

static void SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = AHT10_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(AHT10_GPIO, &GPIO_InitStructure);
}

static void SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = AHT10_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(AHT10_GPIO, &GPIO_InitStructure);
}

static void I2C_Start(void)
{
    SDA_OUT();
    SDA_H;
    SCL_H;
    I2C_Delay();
    SDA_L;
    I2C_Delay();
    SCL_L;
}

static void I2C_Stop(void)
{
    SDA_OUT();
    SCL_L;
    SDA_L;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SDA_H;
    I2C_Delay();
}

static void I2C_Ack(void)
{
    SCL_L;
    SDA_OUT();
    SDA_L;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SCL_L;
}

static void I2C_NAck(void)
{
    SCL_L;
    SDA_OUT();
    SDA_H;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SCL_L;
}

static uint8_t I2C_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    
    SDA_IN();
    SDA_H;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    
    while(SDA_READ)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            I2C_Stop();
            return 1;
        }
    }
    SCL_L;
    return 0;
}

static void I2C_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    SCL_L;
    
    for(t=0; t<8; t++)
    {
        if((txd&0x80)>>7)
            SDA_H;
        else
            SDA_L;
        txd <<= 1;
        I2C_Delay();
        SCL_H;
        I2C_Delay();
        SCL_L;
        I2C_Delay();
    }
}

static uint8_t I2C_Read_Byte(unsigned char ack)
{
    unsigned char i, receive=0;
    
    SDA_IN();
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay();
        SCL_H;
        receive <<= 1;
        if(SDA_READ) receive++;
        I2C_Delay();
    }
    
    if(!ack)
        I2C_NAck();
    else
        I2C_Ack();
    
    return receive;
}

// Public functions
void AHT10_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(AHT10_RCC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = AHT10_SCL_PIN | AHT10_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(AHT10_GPIO, &GPIO_InitStructure);
    
    SCL_H;
    SDA_H;
    
    delay_ms(40);
    
    I2C_Start();
    I2C_Send_Byte(AHT10_ADDR_WRITE);
    I2C_Wait_Ack();
    I2C_Send_Byte(AHT10_INIT_CMD);
    I2C_Wait_Ack();
    I2C_Send_Byte(0x08);
    I2C_Wait_Ack();
    I2C_Send_Byte(0x00);
    I2C_Wait_Ack();
    I2C_Stop();
    
    delay_ms(500);
}

uint8_t AHT10_Read_Data(float *temperature, float *humidity)
{
    uint32_t temp_raw, humi_raw;
    uint8_t buffer[6];
    uint8_t i;
    
    I2C_Start();
    I2C_Send_Byte(AHT10_ADDR_WRITE);
    if(I2C_Wait_Ack()) return 1;
    I2C_Send_Byte(AHT10_MEASURE_CMD);
    if(I2C_Wait_Ack()) return 1;
    I2C_Send_Byte(0x33);
    if(I2C_Wait_Ack()) return 1;
    I2C_Send_Byte(0x00);
    if(I2C_Wait_Ack()) return 1;
    I2C_Stop();
    
    delay_ms(80);
    
    I2C_Start();
    I2C_Send_Byte(AHT10_ADDR_READ);
    if(I2C_Wait_Ack()) return 1;
    
    for(i = 0; i < 6; i++)
    {
        buffer[i] = I2C_Read_Byte(i < 5);
    }
    
    I2C_Stop();
    
    if(buffer[0] & 0x80) return 1;
    
    humi_raw = ((uint32_t)buffer[1] << 12) | ((uint32_t)buffer[2] << 4) | (buffer[3] >> 4);
    temp_raw = ((uint32_t)(buffer[3] & 0x0F) << 16) | ((uint32_t)buffer[4] << 8) | buffer[5];
    
    *humidity = (float)humi_raw * 100 / 0x100000;
    *temperature = (float)temp_raw * 200 / 0x100000 - 50;
    
    return 0;
}
