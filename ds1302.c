#include "ds1302.h"

uchar label2[16];  // Time display buffer

/*
 * Function: DS1302_GPIOInit
 * Description: Initialize GPIO pins for DS1302
 * Parameters: None
 * Returns: None
 */
void DS1302_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // Configure PA4(CLK), PA6(IO), PA7(CS) as output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

/*
 * Function: DS1302_IO_GPIO
 * Description: Configure IO pin direction
 * Parameters: FLAG - IN(0x00) or OUT(0x01)
 * Returns: None
 */
void DS1302_IO_GPIO(uchar FLAG)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    if(FLAG == OUT)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }
    GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

/*
 * Function: DS1302_delay
 * Description: Simple delay function
 * Parameters: dd - delay count
 * Returns: None
 */
void DS1302_delay(u8 dd)
{
    u8 i;
    for(; dd > 0; dd--)
        for(i = 110; i > 0; i--);
}

/*
 * Function: DS1302_Write
 * Description: Write data to DS1302
 * Parameters: add - register address, dat - data to write
 * Returns: None
 */
void DS1302_Write(uchar add, uchar dat)
{
    uchar i;
    CS_Set_1;
    
    // Write address
    for(i = 0; i < 8; i++)
    {
        if(add & 0x01)
            IO_Set_1;
        else
            IO_Reset_0;
        add >>= 1;
        CLK_Set_1;
        DS1302_delay(2);
        CLK_Reset_0;
    }
    
    // Write data
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x01)
            IO_Set_1;
        else
            IO_Reset_0;
        dat >>= 1;
        CLK_Set_1;
        DS1302_delay(2);
        CLK_Reset_0;
    }
    
    CS_Reset_0;
}

/*
 * Function: DS1302_Read
 * Description: Read data from DS1302
 * Parameters: add - register address
 * Returns: value - read data in decimal format
 */
uchar DS1302_Read(uchar add)
{
    uchar i, temp, value;
    uchar suf = 0;
    
    CS_Set_1;
    
    // Write address
    for(i = 0; i < 8; i++)
    {
        if(add & 0x01)
            IO_Set_1;
        else
            IO_Reset_0;
        add >>= 1;
        CLK_Set_1;
        DS1302_delay(2);
        CLK_Reset_0;
    }
    
    DS1302_IO_GPIO(IN);
    
    // Read data
    for(i = 0; i < 8; i++)
    {
        suf >>= 1;
        if(IO_Read)
            suf |= 0x80;
        CLK_Set_1;
        DS1302_delay(2);
        CLK_Reset_0;
    }
    
    CS_Reset_0;
    DS1302_IO_GPIO(OUT);
    
    // Convert BCD to decimal
    temp = suf;
    value = ((temp >> 4) * 10) + (temp & 0x0F);
    return value;
}

/*
 * Function: DS1302_SetTime
 * Description: Set time to DS1302
 * Parameters: ad - pointer to time array [year,month,day,hour,min,sec]
 * Returns: None
 */
void DS1302_SetTime(uchar *ad)
{
    DS1302_Write(0x8E, 0x00);    // Disable write protection
    
    DS1302_Write(ds1302_sec_addr, ad[5]);     // Second
    DS1302_Write(ds1302_min_addr, ad[4]);     // Minute
    DS1302_Write(ds1302_hour_addr, ad[3]);    // Hour
    DS1302_Write(ds1302_day_addr, ad[2]);     // Day
    DS1302_Write(ds1302_month_addr, ad[1]);   // Month
    DS1302_Write(ds1302_year_addr, ad[0]);    // Year
    
    DS1302_Write(0x8E, 0x80);    // Enable write protection
}

/*
 * Function: DS1302_init
 * Description: Initialize DS1302
 * Parameters: time - initial time array
 * Returns: None
 */
void DS1302_init(uchar *time)
{
    DS1302_GPIOInit();
    DS1302_delay(2);
    
    CS_Reset_0;
    CLK_Reset_0;
    
    // Initialize DS1302 settings
    DS1302_Write(0x8E, 0x00);    // Disable write protection
    DS1302_Write(0x90, 0xA7);    // Charge control
    DS1302_Write(0x8E, 0x80);    // Enable write protection
    
    if(DS1302_Read(0x81) & 0x80)
    {
        DS1302_SetTime(time);
    }
}

/*
 * Function: DS1302_Readtime
 * Description: Read current time from DS1302
 * Parameters: None
 * Returns: None
 */
void DS1302_Readtime(void)
{
    label2[0] = DS1302_Read(0x8D) / 10;     // Year tens
    label2[1] = DS1302_Read(0x8D) % 10;     // Year ones
    label2[2] = '/';
    label2[3] = DS1302_Read(0x89) / 10;     // Month tens
    label2[4] = DS1302_Read(0x89) % 10;     // Month ones
    label2[5] = '/';
    label2[6] = DS1302_Read(0x87) / 10;     // Day tens
    label2[7] = DS1302_Read(0x87) % 10;     // Day ones
    label2[8] = DS1302_Read(0x85) / 10;     // Hour tens
    label2[9] = DS1302_Read(0x85) % 10;     // Hour ones
    label2[10] = ':';
    label2[11] = DS1302_Read(0x83) / 10;    // Minute tens
    label2[12] = DS1302_Read(0x83) % 10;    // Minute ones
    label2[13] = ':';
    label2[14] = DS1302_Read(0x81) / 10;    // Second tens
    label2[15] = DS1302_Read(0x81) % 10;    // Second ones
}
