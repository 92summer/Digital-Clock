/*引脚功能定义*/
#define _TESTLCD_ 0
#if _TESTLCD_
#define EN P34
#define RS P35
#define RW P36
#define D7 P07
#define DB P0
#else
#define EN P20
#define RS P21
#define RW P22
#define D7 P17
#define DB P1
#endif

#define read 1
#define write 0
#define DATA 1
#define command 0


void Busy_wait();//读写检测
void WriteData(unsigned char Data);//发数据
void WriteCmd(unsigned char cmd); //发命令

/****************
参数说明：
mode==3  ----发送命令0x0c开显示;	 
mode==2	 ----发送命令0x0e开光标;
mode==1  ----发送命令0x0f光标闪烁 
	
cmod==0  ----发送命令0x04光标指针-1（左移） 
cmod==1  ----发送命令0x06光标指针+1（右移） 	
*******************/
void LCDInit(unsigned char mode,bit cmod);

/****************
函数功能：
LCD左下角为原点
在(x,y)位置显示字符或字符串
*****************/
void LCDWriteChar(unsigned char x, unsigned char y, char s);
void LCDWriteStr(unsigned char x, unsigned char y, char *str);

void display_date_and_time();