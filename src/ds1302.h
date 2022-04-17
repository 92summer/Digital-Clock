/*���Ź��ܶ���*/
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

#define DS1302_W_FIRSTADDR 0x80  //дʱ�������Ĵ�����ʼ��ַ
#define DS1302_R_FIRSTADDR 0x81	//��ʱ�������Ĵ�����ʼ��ַ

 
void DS1302WriteByte(unsigned char dat);
unsigned char DS1302ReadByte();

/************************************************ 
****˵��: ��д��ַ���������
****����: ��addr��Ӧ��ַ�ж�ȡһ���ֽڵ�����
�������: addr:Ҫд��ĵ�ַ
****���: ��ȡ������
*************************************************/
unsigned char DS1302ReadAddr(unsigned char addr);

/************************************************ 
****˵��:��д��ַ����д����
****����: �� addr ��Ӧ��ַ��дһ���ֽڵ�����
�������: addr: Ҫд��Ŀ�����,dat: Ҫд�������
*************************************************/ 
void DS1302WriteAddr(unsigned char addr, unsigned char dat);

unsigned char BCD_to_DEC(unsigned char BCD);
unsigned char DEC_to_BCD(unsigned char DEC);

void DS1302TimeInit();
void ReadTime();