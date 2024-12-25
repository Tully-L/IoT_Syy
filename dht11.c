#include "dht11.h"
#include "delay.h"
#include "stdio.h"

/*
 * Function: DHT11_GPIO_Init
 * Description: Initialize GPIO for DHT11
 * Parameters: None
 * Returns: None
 */
void DHT11_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable GPIO clock
    RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE);
    
    // Configure DHT11 pin as output
    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
    
    // Set default state to high
    DHT11_OUT_HIGH;
}

/*
 * Function: DHT11_Mode_OUT
 * Description: Configure DHT11 pin as output
 * Parameters: None
 * Returns: None
 */
void DHT11_Mode_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}

/*
 * Function: DHT11_Mode_IN
 * Description: Configure DHT11 pin as input
 * Parameters: None
 * Returns: None
 */
void DHT11_Mode_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}

/*
 * Function: DHT11_Init
 * Description: Initialize DHT11 sensor
 * Parameters: None
 * Returns: 0 - Success, 1 - Error
 */


uint8_t DHT11_Init(void)
{
    DHT11_GPIO_Init();
    
    // Send start signal with precise timing
    DHT11_Mode_OUT();
    DHT11_OUT_HIGH;
    delay_ms(250);         // Power-on stabilization time
    
    // Host start signal
    DHT11_OUT_LOW;
    delay_ms(30);         // Pull low for at least 18ms (using 30ms to be safe)
    
    DHT11_OUT_HIGH;
    delay_us(40);         // Pull high 20-40us (using 40us)
    
    DHT11_Mode_IN();      // Switch to input mode
    
    printf("Waiting for DHT11 response...\r\n");
    
    // Wait for DHT11 response (LOW) - 80us typical
    uint16_t timeout = 0;
    while(DHT11_IN == 1 && timeout < 100)
    {
        delay_us(1);
        timeout++;
    }
    
    if(timeout >= 100)
    {
        printf("Error: DHT11 no response (1), pin stuck HIGH\r\n");
        return 1;
    }
    
    // Wait for DHT11 to pull up - 80us typical
    timeout = 0;
    while(DHT11_IN == 0 && timeout < 100)
    {
        delay_us(1);
        timeout++;
    }
    
    if(timeout >= 100)
    {
        printf("Error: DHT11 no response (2), pin stuck LOW\r\n");
        return 1;
    }
    
    return 0;
}

static uint8_t DHT11_Read_Bit(void)
{
    uint16_t timeout = 0;
    uint8_t result;
    
    // Wait for start of bit (50us LOW)
    while(DHT11_IN == 1 && timeout < 100)
    {
        delay_us(1);
        timeout++;
    }
    if(timeout >= 100)
    {
        printf("Bit error: Timeout waiting for LOW\r\n");
        return 0xFF;
    }
    
    // Wait for bit value signal (HIGH)
    timeout = 0;
    while(DHT11_IN == 0 && timeout < 100)
    {
        delay_us(1);
        timeout++;
    }
    if(timeout >= 100)
    {
        printf("Bit error: Timeout waiting for HIGH\r\n");
        return 0xFF;
    }
    
    // Wait 35us and sample the bit
    // 26-28us for '0', 70us for '1'
    delay_us(35);  // Sample in the middle of the timing window
    result = DHT11_IN;
    
    // Wait for bit to finish
    timeout = 0;
    while(DHT11_IN == 1 && timeout < 100)
    {
        delay_us(1);
        timeout++;
    }
    
    return result;
}

uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5] = {0};
    uint8_t i;
    uint8_t retry = 0;
    
    while(retry < 3)  // Try up to 3 times
    {
        if(DHT11_Init() != 0)
        {
            retry++;
            delay_ms(1000);  // Wait before retry
            continue;
        }
        
        for(i = 0; i < 40; i++)
        {
            uint8_t bit = DHT11_Read_Bit();
            if(bit == 0xFF)
            {
                printf("Bit read error at bit %d\r\n", i);
                break;
            }
            buf[i/8] <<= 1;
            buf[i/8] |= bit;
        }
        
        if(i == 40)  // All bits read successfully
        {
            printf("Raw data: %02X %02X %02X %02X %02X\r\n",
                   buf[0], buf[1], buf[2], buf[3], buf[4]);
            
            // Verify checksum
            if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
            {
                *humi = buf[0];
                *temp = buf[2];
                return 0;  // Success
            }
            else
            {
                printf("Checksum error\r\n");
            }
        }
        
        retry++;
        delay_ms(1000);  // Wait before retry
    }
    
    return 1;  // Failed after all retries
}
