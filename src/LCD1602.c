#include "LCD1602.h"
#include <STC89C5xRC.H>
#include "delay.h"
#include "ds1302.h"

extern unsigned char DT[];

void Busy_wait()//��д���
{
	bit ifbusy;
	/*��״̬*/
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
	EN = 0;		//����������
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
 	WriteCmd(0x3f);//����16*2��ʾ��5*7����8λ���ݽӿ�
	/*
	0x0c����ʾ;	 mode==3
	0x0e�����;	 mode==2
	0x0f�����˸ mode==1
	*/
	switch(mode)
	{
	 	case 1: WriteCmd(0x0f);break;
		case 2: WriteCmd(0x0e);break;
		case 3: WriteCmd(0x0c);break;
	}
	WriteCmd(0x01);	//����ָ�����ʾ����
	/*
	0x04���ָ��-1�����ƣ���cmod==0
	0x06���ָ��+1�����ƣ���cmod==1
	*/
	if(cmod)
		WriteCmd(0x06);
	else
		WriteCmd(0x04);
}

void LCDWriteChar(unsigned char x, unsigned char y, char s)
{
 	if(y == 1)//��һ��
	{
	 	WriteCmd(0x80 | x);	
	}
	else if(y == 0)//�ڶ���
	{
	 	WriteCmd(0xc0 | x);
	}
	WriteData(s);
}

void LCDWriteStr(unsigned char x, unsigned char y, char *str)
{
	char *ps = str;

	if(y == 1)//��һ��
	{
	 	WriteCmd(0x80 | x);	
	}
	else if(y == 0)//�ڶ���
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
	//���--20XX��
	LCDWriteChar(7,1,DT[6]/10+48);
	LCDWriteChar(8,1,DT[6]%10+48);

	LCDWriteChar(9,1,'-');
	//�·�--
	LCDWriteChar(10,1,DT[4]/10+48);
	LCDWriteChar(11,1,DT[4]%10+48);

	LCDWriteChar(12,1,'-');
	//��--
	LCDWriteChar(13,1,DT[3]/10+48);
	LCDWriteChar(14,1,DT[3]%10+48);

	//ʱ--
	LCDWriteChar(6,0,DT[2]/10+48);
	LCDWriteChar(7,0,DT[2]%10+48);

	LCDWriteChar(8,0,':');
	//��--
	LCDWriteChar(9,0,DT[1]/10+48);
	LCDWriteChar(10,0,DT[1]%10+48);

	LCDWriteChar(11,0,':');
	//��--
	LCDWriteChar(12,0,DT[0]/10+48);
	LCDWriteChar(13,0,DT[0]%10+48);
}