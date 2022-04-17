/*引脚功能定义*/
#define _TESTDS_ 0
#if _TESTDS_
#define RST P12
#define SDA P11
#define SCLK P10
#else
#define RST P25
#define SDA P24
#define SCLK P23
#endif

#define DS1302_W_FIRSTADDR 0x80  //写时钟日历寄存器起始地址
#define DS1302_R_FIRSTADDR 0x81	//读时钟日历寄存器起始地址

 
void DS1302WriteByte(unsigned char dat);
unsigned char DS1302ReadByte();

/************************************************ 
****说明: 先写地址，后读数据
****功能: 从addr相应地址中读取一个字节的数据
输入参数: addr:要写入的地址
****输出: 读取的数据
*************************************************/
unsigned char DS1302ReadAddr(unsigned char addr);

/************************************************ 
****说明:先写地址，后写数据
****功能: 向 addr 相应地址中写一个字节的数据
输入参数: addr: 要写入的控制字,dat: 要写入的数据
*************************************************/ 
void DS1302WriteAddr(unsigned char addr, unsigned char dat);

unsigned char BCD_to_DEC(unsigned char BCD);
unsigned char DEC_to_BCD(unsigned char DEC);

void DS1302TimeInit();
void ReadTime();