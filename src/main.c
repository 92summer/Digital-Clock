#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "ds1302.h"
#include "delay.h"

unsigned char temp;

int main()
{
 	
	LCDInit(3,1);
	//LCDWriteStr(0,1,"Date:20");
	LCDWriteStr(5,1,"20");
	LCDWriteStr(0,0,"Now~");

	DS1302WriteAddr(0x90,0x00);//¹Ø DS1302 ³äµç
	temp = DS1302ReadAddr(0x91);
	if (temp == 0x00)
	DS1302TimeInit();	
	while(1)
	{
		display_date_and_time();
		ReadTime();
	 	Delay200ms();	
	}
	
}