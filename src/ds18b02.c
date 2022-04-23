#include "ds18b02.h"
#include "delay.h"
#include "LCD1602.h"
#include <STC89C5xRC.H>
#include<intrins.h>

unsigned int temperature;//��ds18b02ת�����¶���ֵ
unsigned char L,M;

void ds18_init()
{
	bit i;
	ds18 = 1;
	_nop_();
	ds18 = 0;
	Delay_us(75); //��������499.45us �ҽ��������ϵ�18B20����ȫ������λ
	ds18 = 1; //�ͷ�����
	Delay_us(4); //��ʱ37.95us �ȴ�18B20���ش����ź�
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
		_nop_();//����Щʱ��
		ds18 = dat & 0x01;//�����λ��ʼ��
		Delay_us(10);//76.95us
		ds18 = 1; //�ͷ�����׼����һ������д��
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
		_nop_();//������ʱ��
		ds18 = 1;
		_nop_();//�ͷ�����
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
	ds18_write_byte(0xcc); //����ROM����
	ds18_write_byte(0x44); //�¶�ת��ָ��

	ds18_init();
	ds18_write_byte(0xcc);//����ROM����
	ds18_write_byte(0xbe);//��ʼ��ȡ�ݴ�����ֵ
	L = ds18_read_byte(); //��8λ
	M = ds18_read_byte(); //��8λ
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