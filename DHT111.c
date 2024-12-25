#include "stm32f10x.h"                  // Device header
#include "dht11.h"

/*********
单总线通信 -  GPIO   PB4

//main.c参考

int main()
{	
	unsigned char tem = 0, hum = 0;
	
	uart1_init(115200);
	dht11_init();
	
	while(1)
	{
		
		dht11_get_data(&tem, &hum);
		printf("tem: %d, hum: %d\r\n", tem, hum);
		my_delay_ms(1000) ;
	}
}
**********/

static void Delay10uS(void)
{
	int i = 100;
	while(i--);
}
static void Delay10mS(void)
{
	int n = 10, i = 0;
	while(n--)
		for(i=0; i<8050; i++);
}

//初始化DHT11的IO口   PB4
void dht11_init(void)
{     
	int i = 10;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	//关闭JATG，复用PB4为GPIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);  //PB4初始化 为推挽输出模式
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET);
	
	while(i--)
		Delay10mS();
}

static void DHT11_IO_IN(void)//DHT11输入
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
static void DHT11_IO_OUT(void)//DHT11输出
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


//等待DHT11的回应
static int DHT11_Check(void)    
{   
again:
	DHT11_IO_OUT(); //PB0管脚设置为输出管脚
	GPIO_WriteBit(GPIOB,GPIO_Pin_4,Bit_SET);
	Delay10mS();
	GPIO_WriteBit(GPIOB,GPIO_Pin_4,Bit_RESET);

	//拉低至少18ms
	Delay10mS();
	Delay10mS();

	GPIO_WriteBit(GPIOB,GPIO_Pin_4,Bit_SET); //DQ=1 

	DHT11_IO_IN(); //PB0管脚设置为输入管脚
	//主机拉高20~40us
	Delay10uS();
	Delay10uS();
	Delay10uS();

	if(RESET == GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))//DHT11会拉低80us
	{
		while (!(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) )) ;  //等待响应信号结束
			
		while ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) )) ;  //DHT11发送响应信号后，再把总线拉高80us
			
		return 0;
	}
	else
		goto again;
}


//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;-1,读取失败
int dht11_get_data(unsigned char *tem,  unsigned char *hum)    
{        
	int count = 0;
	u8 data[5] = {0};

	u8 i;

	if(0 == DHT11_Check())
	{
		
		for(i=0; i<40; i++)
		{
			while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4));//等待低电平结束 50us
			
			count = 0;
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4))//等待高电平结束并count计数,通过计数判断当前值为0还是1
			{
				Delay10uS();
				count++;
			}
			
			if(count > 5)//高电平  
			{
				data[i/8] |= 1 << (7 - i % 8); //将对应位置1 注意：数据传输时从高到低传输
			}
			
		}
		Delay10mS();
		
		//数据接收完成之后将PB0管脚模式设置为输出，并数据高电平
		DHT11_IO_OUT();//PB0管脚为输出管脚
		GPIO_WriteBit(GPIOB, GPIO_Pin_4,Bit_SET);//输出高电平
			
		if(data[4] != (data[0] + data[1] + data[2] + data[3]))//判断接收数据是否正确
			return -1;
		else
		{			
			*tem = data[2];
			*hum = data[0];
			
			return 0;
		}

	}
	 
	return -1;
}




