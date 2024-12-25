//#include "stm32f10x.h"
//#include "led.h"
//#include "usart1.h"
//#include "stdio.h"
//#include "dht11.h"

//void my_delay(int ms){
//	while(ms--)
//		for(int i = 0; i < 8050;i++);
//}
//	
//int main(void){

//    DHT11_Data_TypeDef DHT11_Data;
//    
//    led_init();
//    usart1_init();
//    DHT11_Init();
//	
//		unsigned char data = 0;
//	
////*******************************************
////red/green/blue_Tri-color LED cycle lighting
//		while(1){
//		red_led_on();
//		my_delay(1000);
//		red_led_off();
//		
//		green_led_on();
//		my_delay(1000);
//		green_led_off();
//		
//		blue_led_on();
//		my_delay(1000);
//		blue_led_off();
//		
//		my_delay(1000);
//			 }

// }

//****************************************WHYYYYYYYYYYYYYY????!!!!
//#include "stm32f10x.h"
//#include "DHT111.h"
//#include "delay1.h"
//#include "usart1.h"
//#include <stdio.h>

//int main(void)
//{
//    uint8_t temperature;
//    uint8_t humidity;
//    uint8_t init_status;
//    
//    // Initialize system
//    SystemInit();
//    delay_init();
//    usart1_init();
//    
//    printf("DHT11 Test Starting...\r\n");
//    
//    // Wait for DHT11 to stabilize
//    delay_ms(1000);
//    
//    // Initialize DHT11
//    init_status = DHT11_Init();
//    if(init_status != 0)
//    {
//        printf("DHT11 Initialization Failed!\r\n");
//        while(1);
//    }
//    
//    printf("DHT11 Initialized Successfully!\r\n");
//    
//    while(1)
//{
//    if(DHT11_Read_Data(&temperature, &humidity) == 0)
//    {
//        printf("Temperature: %d dgree, Humidity: %d%%\r\n", temperature, humidity);
//    }
//    else
//    {
//        printf("DHT11 Read Error!\r\n");
//    }
//    
//    delay_ms(3000);  // Increased to 3 seconds
//}
//}

////aht11              WHYYYYYYYYYYYYYYYYYYYYYYYYYY???????????!!!!!!!!
//#include "stm32f10x.h"
//#include "aht10.h"
//#include "delay1.h"
//#include "usart1.h"
//#include "stdio.h"

//int main(void)
//{
//    float temperature, humidity;
//    char buffer[50];
//    
//    // Initialize system
//    SystemInit();
//    delay_init();
//    usart1_init();
//    
//    delay_ms(100);  // Wait for system stabilization
//    
//    printf("AHT10 Test Starting...\r\n");
//    delay_ms(10);
//    
//    AHT10_Init();
//    printf("AHT10 Initialized\r\n");
//    delay_ms(10);
//    
//    while(1)
//    {
//        if(AHT10_Read_Data(&temperature, &humidity) == 0)
//        {
//            sprintf(buffer, "Temperature: %.1f C, Humidity: %.1f%%\r\n", 
//                    temperature, humidity);
//            printf("%s", buffer);
//        }
//        else
//        {
//            printf("AHT10 Read Error!\r\n");
//        }
//        
//        delay_ms(2000);  // Read every 2 seconds
//    }
//}

//// Redirect printf to USART1
//int fputc(int ch, FILE *f)
//{
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//    USART_SendData(USART1, (uint8_t)ch);
//    return ch;
//}


//****************************************
//#include "stm32f10x.h"
//#include "oled.h"
//#include "stdio.h"
//#include "led.h"
//#include "usart1.h"

//int main(void)
//{
//    OLED_Init();  // Initialize OLED
//    
//    // Test OLED basic display functions
//    OLED_ShowChar(1, 1, 'A');  // Display single character
//    OLED_ShowString(1, 3, "HelloWorld!");  // Display string
//    
//    // Test number display
//    OLED_ShowNum(2, 1, 123, 4);  // Display 4-digit number
//    OLED_ShowNum(2, 6, 123, 2);  // Display 2-digit number
//    OLED_ShowSignedNum(2, 9, -66, 2);  // Display signed number (negative)
//    OLED_ShowSignedNum(2, 13, 66, 2);  // Display signed number (positive)
//    
//    // Test hex and binary display
//    OLED_ShowHexNum(3, 1, 0xAA55, 4);  // Display hexadecimal
//    OLED_ShowBinNum(4, 1, 0xAA55, 16);  // Display binary
//    
//    while(1);  // Infinite loop
//}

//****************************************
//#include "stm32f10x.h"
//#include "light.h"
//#include "oled.h"
//#include "stdio.h"

//// Simple delay function
//void Delay(uint32_t count)
//{
//    while(count--);
//}

//int main(void)
//{
//    // Variables for storing sensor readings
//    uint8_t digital_value;    // Digital output (0: bright, 1: dark)
//    uint16_t analog_value;    // Analog output (0-4095, lower value = darker)
//    char str[16];            // Buffer for string formatting
//    
//    // Init OLED display and light sensor
//    OLED_Init();
//    Light_Init();
//    
//    while(1)
//    {
//        // Get sensor readings
//        digital_value = Light_GetDO();  // Read digital state
//        analog_value = Light_GetAO();   // Read analog value
//        
//        // Display title
//        OLED_ShowString(0, 0, "Light Sensor:");
//        
//        // Show digital output (0/1)
//        sprintf(str, "DO: %d", digital_value);
//        OLED_ShowString(0, 2, str);
//        
//        // Show analog output (0-4095)
//        sprintf(str, "AO: %d", analog_value);
//        OLED_ShowString(0, 4, str);
//        
//        Delay(500000);  // Wait 0.5s before next update
//    }
//}

//****************************************
//#include "stm32f10x.h"
//#include "ds1302.h"
//#include "usart1.h"
//#include "stdio.h"

//void Delay(uint32_t count)
//{
//    while(count--);
//}

//int main(void)
//{
//    int tt = 0;
//    
//    // Initialize system
//    SystemInit();
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    
//    // Set initial time (23/12/31 23:59:50)
//    uchar Settime[6] = {0x23, 0x12, 0x31, 0x23, 0x59, 0x50};
//    DS1302_init(Settime);
//    DS1302_SetTime(Settime);
//    
//    while(1)
//    {
//        tt++;
//        if(tt >= 3200000)
//        {
//            tt = 0;
//            DS1302_Readtime();
//            printf("20%d%d/%d%d/%d%d %d%d:%d%d:%d%d\r\n",
//                   label2[0], label2[1],    // Year
//                   label2[3], label2[4],    // Month
//                   label2[6], label2[7],    // Day
//                   label2[8], label2[9],    // Hour
//                   label2[11], label2[12],  // Minute
//                   label2[14], label2[15]); // Second
//        }
//        Delay(100);
//    }
//}


//***************************************************
//#include "stm32f10x.h"
//#include "delay1.h"
//#include "usart1.h"
//#include "beep.h"
//#include "stdio.h"

//int main(void)
//{
//    uint16_t light_value;
//    
//    // Initialize system
//    SystemInit();
//    delay_init();
//    usart1_init();
//    
//    // Initialize light sensor and beeper
//    Light_Init();
//    Beep_Init();
//    
//    printf("\r\nLight Sensor Test Starting...\r\n");
//    
//    while(1)
//    {
//        // Get light sensor value
//        light_value = Light_Get_Value();
//        
//        // Print light value
//        printf("Light Value: %d\r\n", light_value);
//        
//        // Control beeper based on light value
//        if(light_value > LIGHT_THRESHOLD)
//        {
//            Beep_OFF();  // Light detected, turn off beeper
//            printf("Light detected, Beeper ON\r\n");
//        }
//        else
//        {
//            Beep_ON();   // Dark detected, turn on beeper
//            printf("Dark detected, Beeper OFF\r\n");
//        }
//        
//        delay_ms(500);  // Check every 500ms
//    }
//}


//************************************************88
//#include "stm32f10x.h"
//#include "delay1.h"
//#include "usart1.h"
//#include "sg90.h"
//#include "stdio.h"

//// Function declarations
//void Mode_1(void);  // Touch key control mode
//void Mode_2(void);  // Auto sweep mode

//int main(void)
//{
//    // Initialize system
//    SystemInit();
//    delay_init();
//    usart1_init();
//    
//    // Initialize servo and touch key
//    SG90_Init();
//    Touch_Init();
//    
//    printf("\r\nServo Test Starting...\r\n");
//    printf("1. Press key to switch between 0 and 180 degrees\r\n");
//    printf("2. Long press key (>3s) to enter sweep mode\r\n");
//    
//    while(1)
//    {
//        if(Touch_Scan())  // Key pressed
//        {
//            delay_ms(3000);  // Wait to check if it's a long press
//            
//            if(!TOUCH_READ())  // Still pressed after 3s
//            {
//                Mode_2();  // Enter sweep mode
//            }
//            else
//            {
//                Mode_1();  // Enter touch control mode
//            }
//        }
//        delay_ms(10);
//    }
//}

///**
// * @brief Touch key control mode
// * @param None
// * @retval None
// */
//void Mode_1(void)
//{
//    static uint8_t angle = 0;
//    
//    angle = (angle == 0) ? 180 : 0;  // Toggle between 0 and 180
//    SG90_SetAngle(angle);
//    printf("Angle: %d\r\n", angle);
//}

///**
// * @brief Auto sweep mode (0-180-0 degrees)
// * @param None
// * @retval None
// */
//void Mode_2(void)
//{
//    uint8_t angle;
//    
//    printf("Entering sweep mode...\r\n");
//    
//    while(1)
//    {
//        // Sweep from 0 to 180
//        for(angle = 0; angle <= 180; angle += 1)
//        {
//            SG90_SetAngle(angle);
//            printf("Angle: %d\r\n", angle);
//            delay_ms(20);
//            
//            if(Touch_Scan())  // Exit if key pressed
//                return;
//        }
//        
//        // Sweep from 180 to 0
//        for(angle = 180; angle > 0; angle -= 1)
//        {
//            SG90_SetAngle(angle);
//            printf("Angle: %d\r\n", angle);
//            delay_ms(20);
//            
//            if(Touch_Scan())  // Exit if key pressed
//                return;
//        }
//    }
//}

//#include "stm32f10x.h"
//#include "delay1.h"
//#include "usart1.h"
//#include "beep.h"
//#include "stdio.h"

////乐谱：生日快乐歌C调简谱C语言表示方法(M5,50)为(音调，音长)100表示为一个音长(节拍)，50位半个音长(节拍)，25位四分之一音长(节拍)
//int music[]=  
//{  
//        M5,50,M5,25,M5,25, 

//        M6,100,M5,100,H1,100,

//        M7,100,M7,100,M5,50,M5,25,M5,25,

//        M6,100,M5,100,H2,100,

//        H1,100,H1,100,M5,50,M5,25,M5,25,

//        H5,100,H3,100,H1,100,

//        M7,100,M6,100,H4,50,H4,25,H4,25,

//        H3,100,H1,100,H2,100,H1,100,H1,100

//};


//int main()
//{
//	int i = 2000;
//	int length = sizeof(music)/sizeof(music[0]);//计算数组长度

//	beep_init();
//	
//	while(1)
//	{
//		for(i=0; i<(length/2); i++)//取数组数据
//		{  
//			beep_set(music[2*i], music[2*i]);//PWM波周期

//			my_music_delay( 5 * music[2*i+1] );//音长的时间都乘以5即一拍为500微秒，此值"5"可调整，只是播放的整个快慢而已，有点类似于视频快进和后退
//		}
//		
//		my_music_delay(2000); //2S延时
//	}
//};

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
