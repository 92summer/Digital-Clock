#include "delay.h"

void delay(unsigned int z)
{
 	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}

void Delay200ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 103;
	k = 147;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/*
*输入：ms：要延时的毫秒
=================================================*/
void Delay_Ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}

void Delay_us(unsigned char us)
{
	while(us--);	
}
