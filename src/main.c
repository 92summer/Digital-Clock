#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "ds1302.h"
#include "delay.h"
#include "ds18b02.h"

unsigned char temp;//中间转换变量


int main()
{
 	
	LCDInit(3,1);
	//LCDWriteStr(0,1,"Date:20");
	LCDWriteStr(3,1,"20");
	//LCDWriteStr(0,0,"Now~");

	DS1302WriteAddr(0x90,0x00);//关 DS1302 充电
	temp = DS1302ReadAddr(0x91);
	if (temp == 0x00)
	DS1302TimeInit();	
	while(1)
	{
		display_date_and_time();
		ReadTime();
		
		display_temperature();
		ReadTemperature();

	 	Delay200ms();	
	}
	
}
