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

