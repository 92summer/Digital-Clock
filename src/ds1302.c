#include "ds1302.h"
#include "delay.h"
#include <STC89C5xRC.H>

/******初值数组
***************
6--年 5--周 4--月 3--日 2--时 1--分 0--秒
**/
unsigned char DT[7]={30,6,23,17,4,7,22};

void DS1302WriteByte(unsigned char dat)
{
	unsigned char i;
	SCLK=0;//初始时钟线置为 0
	delay(2);
	for(i=0;i<8;i++)//开始传输 8 个字节的数据
	{
		SDA=dat&0x01;//取最低位，注意DS1302 的数据和地址都是从最低位开始传输的
		delay(2);
		SCLK=1;//时钟线拉高，制造上升沿， SDA 的数据被传输
		delay(2);
		SCLK=0;//时钟线拉低，为下一个上升沿做准备
		dat>>=1;//数据右移一位，准备传输下一位数据
	}
}

unsigned char DS1302ReadByte()
{
	unsigned char i,dat;
	delay(2);
	for(i=0;i<8;i++)
	{
		dat>>=1;//要返回的数据左移一位
		if(SDA==1)//当数据线为高时，证明该位数据为 1
			dat|=0x80;///要传输数据的当前值置为 1, 若不是,则为 0
		SCLK=1;//拉高时钟线
		delay(2);
		SCLK=0;//制造下降沿
		delay(2);
	}
	return dat;//返回读取出的数据
}


unsigned char DS1302ReadAddr(unsigned char addr)
{
	unsigned char dat;
	RST=0;//初始 CE 线置为 0
	SCLK=0;//初始时钟线置为 0
	RST=1;//初始 CE 置为 1，传输开始
	DS1302WriteByte(addr);//传输命令字，要读取的时间/日历地址
	dat=DS1302ReadByte();//读取要得到的时间/日期
	SCLK=1;//时钟线拉高
	RST=0;//读取结束，CE 置为 0，结束数据的传输
	return dat;//返回得到的时间/日期
}

void DS1302WriteAddr(unsigned char addr, unsigned char dat)
{
	RST=0; //初始 CE 线置为 0
	SCLK=0; //初始时钟线置为 0
	RST=1; //初始 CE 置为 1，传输开始
	DS1302WriteByte(addr); //传输命令字，要写入的时间/日历地址
	DS1302WriteByte(dat); //写入要修改的时间/日期
	SCLK=1; //时钟线拉高
	RST=0; //读取结束，CE 置为 0，结束数据的传输
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
    BCD = DEC % 10;//个位
    DEC /= 10;
    DEC <<= 4;
    DEC &= 0xf0;
    BCD |= DEC;//十位
    return BCD;
}


void DS1302TimeInit()
{
	unsigned char i;
	DS1302WriteAddr(0x8e,0x00);//关写保护
	RST = 0;
	SDA = 0;
	RST = 1;//使能端拉高，开始写数据
	DS1302WriteByte(0xbe);//开写突发
	for ( i = 0; i < 7; i++)
	{
		DS1302WriteAddr(DS1302_W_FIRSTADDR+2*i, DEC_to_BCD(DT[i]));
	}	

	DS1302WriteAddr(0x8e,0x80);//开写保护
}

void ReadTime()
{
	unsigned char i;
	unsigned char temp;
	DS1302WriteAddr(0x8e,0x00);//关写保护
	RST = 0;
	SDA = 0;
	RST = 1;//使能端拉高，开始写数据
	DS1302WriteByte(0xbf);//开写突读

	for ( i = 0; i < 7; i++)
	{
		temp = DS1302ReadAddr(DS1302_R_FIRSTADDR+2*i);
		temp = BCD_to_DEC(temp);
		DT[i] = temp;
	}

	DS1302WriteAddr(0x8e,0x80);//开写保护
}
