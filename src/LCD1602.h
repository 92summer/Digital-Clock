/*���Ź��ܶ���*/
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


void Busy_wait();//��д���
void WriteData(unsigned char Data);//������
void WriteCmd(unsigned char cmd); //������

/****************
����˵����
mode==3  ----��������0x0c����ʾ;	 
mode==2	 ----��������0x0e�����;
mode==1  ----��������0x0f�����˸ 
	
cmod==0  ----��������0x04���ָ��-1�����ƣ� 
cmod==1  ----��������0x06���ָ��+1�����ƣ� 	
*******************/
void LCDInit(unsigned char mode,bit cmod);

/****************
�������ܣ�
LCD���½�Ϊԭ��
��(x,y)λ����ʾ�ַ����ַ���
*****************/
void LCDWriteChar(unsigned char x, unsigned char y, char s);
void LCDWriteStr(unsigned char x, unsigned char y, char *str);

void display_date_and_time();