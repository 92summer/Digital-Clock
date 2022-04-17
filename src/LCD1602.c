#include "LCD1602.h"
#include <STC89C5xRC.H>
#include "delay.h"
#include "ds1302.h"

extern unsigned char DT[];

void Busy_wait()//读写检测
{
	bit ifbusy;
	/*读状态*/
	RS = command;
	RW = read;
	do
	{
		EN = 1;
		ifbusy = D7;
		EN = 0;
	}while(ifbusy);
}

void WriteData(unsigned char Data)
{
	Busy_wait();
	RS = DATA;
	RW = write;
	DB = Data;
	EN = 1;
	delay(5);
	EN = 0;		//产生高脉冲
}

void WriteCmd(unsigned char cmd)
{
 	Busy_wait();
	RS = command;
	RW = write;
	DB = cmd;
	EN = 1;
	delay(5);
	EN = 0;	
}



void LCDInit(unsigned char mode,bit cmod)
{
 	WriteCmd(0x3f);//设置16*2显示，5*7点阵，8位数据接口
	/*
	0x0c开显示;	 mode==3
	0x0e开光标;	 mode==2
	0x0f光标闪烁 mode==1
	*/
	switch(mode)
	{
	 	case 1: WriteCmd(0x0f);break;
		case 2: WriteCmd(0x0e);break;
		case 3: WriteCmd(0x0c);break;
	}
	WriteCmd(0x01);	//数据指针和显示清零
	/*
	0x04光标指针-1（左移），cmod==0
	0x06光标指针+1（右移），cmod==1
	*/
	if(cmod)
		WriteCmd(0x06);
	else
		WriteCmd(0x04);
}

void LCDWriteChar(unsigned char x, unsigned char y, char s)
{
 	if(y == 1)//第一行
	{
	 	WriteCmd(0x80 | x);	
	}
	else if(y == 0)//第二行
	{
	 	WriteCmd(0xc0 | x);
	}
	WriteData(s);
}

void LCDWriteStr(unsigned char x, unsigned char y, char *str)
{
	char *ps = str;

	if(y == 1)//第一行
	{
	 	WriteCmd(0x80 | x);	
	}
	else if(y == 0)//第二行
	{
	 	WriteCmd(0xc0 | x);
	}
	
 	while(*ps)
	{
	 	WriteData(*ps);
		ps++;
	}
}

void display_date_and_time()
{
	//年份--20XX年
	LCDWriteChar(7,1,DT[6]/10+48);
	LCDWriteChar(8,1,DT[6]%10+48);

	LCDWriteChar(9,1,'-');
	//月份--
	LCDWriteChar(10,1,DT[4]/10+48);
	LCDWriteChar(11,1,DT[4]%10+48);

	LCDWriteChar(12,1,'-');
	//日--
	LCDWriteChar(13,1,DT[3]/10+48);
	LCDWriteChar(14,1,DT[3]%10+48);

	//时--
	LCDWriteChar(6,0,DT[2]/10+48);
	LCDWriteChar(7,0,DT[2]%10+48);

	LCDWriteChar(8,0,':');
	//分--
	LCDWriteChar(9,0,DT[1]/10+48);
	LCDWriteChar(10,0,DT[1]%10+48);

	LCDWriteChar(11,0,':');
	//秒--
	LCDWriteChar(12,0,DT[0]/10+48);
	LCDWriteChar(13,0,DT[0]%10+48);
}