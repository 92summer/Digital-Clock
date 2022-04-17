#include "ds1302.h"
#include "delay.h"
#include <STC89C5xRC.H>

/******��ֵ����
***************
6--�� 5--�� 4--�� 3--�� 2--ʱ 1--�� 0--��
**/
unsigned char DT[7]={30,6,23,17,4,7,22};

void DS1302WriteByte(unsigned char dat)
{
	unsigned char i;
	SCLK=0;//��ʼʱ������Ϊ 0
	delay(2);
	for(i=0;i<8;i++)//��ʼ���� 8 ���ֽڵ�����
	{
		SDA=dat&0x01;//ȡ���λ��ע��DS1302 �����ݺ͵�ַ���Ǵ����λ��ʼ�����
		delay(2);
		SCLK=1;//ʱ�������ߣ����������أ� SDA �����ݱ�����
		delay(2);
		SCLK=0;//ʱ�������ͣ�Ϊ��һ����������׼��
		dat>>=1;//��������һλ��׼��������һλ����
	}
}

unsigned char DS1302ReadByte()
{
	unsigned char i,dat;
	delay(2);
	for(i=0;i<8;i++)
	{
		dat>>=1;//Ҫ���ص���������һλ
		if(SDA==1)//��������Ϊ��ʱ��֤����λ����Ϊ 1
			dat|=0x80;///Ҫ�������ݵĵ�ǰֵ��Ϊ 1, ������,��Ϊ 0
		SCLK=1;//����ʱ����
		delay(2);
		SCLK=0;//�����½���
		delay(2);
	}
	return dat;//���ض�ȡ��������
}


unsigned char DS1302ReadAddr(unsigned char addr)
{
	unsigned char dat;
	RST=0;//��ʼ CE ����Ϊ 0
	SCLK=0;//��ʼʱ������Ϊ 0
	RST=1;//��ʼ CE ��Ϊ 1�����俪ʼ
	DS1302WriteByte(addr);//���������֣�Ҫ��ȡ��ʱ��/������ַ
	dat=DS1302ReadByte();//��ȡҪ�õ���ʱ��/����
	SCLK=1;//ʱ��������
	RST=0;//��ȡ������CE ��Ϊ 0���������ݵĴ���
	return dat;//���صõ���ʱ��/����
}

void DS1302WriteAddr(unsigned char addr, unsigned char dat)
{
	RST=0; //��ʼ CE ����Ϊ 0
	SCLK=0; //��ʼʱ������Ϊ 0
	RST=1; //��ʼ CE ��Ϊ 1�����俪ʼ
	DS1302WriteByte(addr); //���������֣�Ҫд���ʱ��/������ַ
	DS1302WriteByte(dat); //д��Ҫ�޸ĵ�ʱ��/����
	SCLK=1; //ʱ��������
	RST=0; //��ȡ������CE ��Ϊ 0���������ݵĴ���
}

unsigned char BCD_to_DEC(unsigned char BCD)
{
	unsigned char DEC;
	DEC = BCD&0x0f;
    BCD >>= 4;
    DEC += 10*(BCD&0x0f);
    return DEC;
}

unsigned char DEC_to_BCD(unsigned char DEC)
{
    unsigned char BCD;
    BCD = DEC % 10;//��λ
    DEC /= 10;
    DEC <<= 4;
    DEC &= 0xf0;
    BCD |= DEC;//ʮλ
    return BCD;
}


void DS1302TimeInit()
{
	unsigned char i;
	DS1302WriteAddr(0x8e,0x00);//��д����
	RST = 0;
	SDA = 0;
	RST = 1;//ʹ�ܶ����ߣ���ʼд����
	DS1302WriteByte(0xbe);//��дͻ��
	for ( i = 0; i < 7; i++)
	{
		DS1302WriteAddr(DS1302_W_FIRSTADDR+2*i, DEC_to_BCD(DT[i]));
	}	

	DS1302WriteAddr(0x8e,0x80);//��д����
}

void ReadTime()
{
	unsigned char i;
	unsigned char temp;
	DS1302WriteAddr(0x8e,0x00);//��д����
	RST = 0;
	SDA = 0;
	RST = 1;//ʹ�ܶ����ߣ���ʼд����
	DS1302WriteByte(0xbf);//��дͻ��

	for ( i = 0; i < 7; i++)
	{
		temp = DS1302ReadAddr(DS1302_R_FIRSTADDR+2*i);
		temp = BCD_to_DEC(temp);
		DT[i] = temp;
	}

	DS1302WriteAddr(0x8e,0x80);//��д����
}
