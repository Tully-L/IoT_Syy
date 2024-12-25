#ifndef __DHT11_H
#define __DHT11_H


void dht11_init(void); //初始化DHT11

int dht11_get_data(unsigned char *tem,  unsigned char *hum); //读取温湿度 

#endif

