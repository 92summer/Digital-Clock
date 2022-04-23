#include "ds18b02.h"
#include "delay.h"
#include "LCD1602.h"
#include <STC89C5xRC.H>
#include<intrins.h>

unsigned int temperature;//存ds18b02转换的温度数值
unsigned char L,M;

void ds18_init()
{
	bit i;
	ds18 = 1;
	_nop_();
	ds18 = 0;
	Delay_us(75); //拉低总线499.45us 挂接在总线上的18B20将会全部被复位
	ds18 = 1; //释放总线
	Delay_us(4); //延时37.95us 等待18B20发回存在信号
	i = ds18;
	Delay_us(20); //141.95us
	ds18 = 1;
	_nop_();
	//return (i);
}

void ds18_write_byte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		ds18 = 0;
		_nop_();//产生些时序
		ds18 = dat & 0x01;//从最低位开始传
		Delay_us(10);//76.95us
		ds18 = 1; //释放总线准备下一次数据写入
		_nop_();
		dat >>= 1;
	}
}

unsigned char ds18_read_byte()
{
	unsigned char i, j, dat;
	for(i=0;i<8;i++)
	{
	    ds18 = 0;
		_nop_();//产生读时序
		ds18 = 1;
		_nop_();//释放总线
		j = ds18;
		Delay_us(10);//76.95us
		ds18 = 1;
		_nop_();
		dat = (j<<7)|(dat>>1);	
	}
	return (dat);
}

void ReadTemperature()
{
 	ds18_init();
	ds18_write_byte(0xcc); //忽略ROM操作
	ds18_write_byte(0x44); //温度转换指令

	ds18_init();
	ds18_write_byte(0xcc);//忽略ROM操作
	ds18_write_byte(0xbe);//开始读取暂存器的值
	L = ds18_read_byte(); //低8位
	M = ds18_read_byte(); //高8位
	temperature = M;
	temperature <<= 8;
	temperature |= L;
}

void display_temperature()
{
	unsigned char temp;
 	temp = temperature>>4;
	LCDWriteChar(0,0,'0'+temp/10);
	LCDWriteChar(1,0,'0'+temp%10);
	LCDWriteChar(2,0,'.');
	temp = temperature & 0x000f;
	temp = temp*0.0625*10+0.5;
	LCDWriteChar(3,0,'0'+temp%10);
	LCDWriteChar(4,0,0xdf);
	LCDWriteChar(5,0,'C');
}