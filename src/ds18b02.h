#define TESTDS18 0
#if TESTDS18
#define ds18 P22
#else
#define ds18 P26
#endif

void ds18_init();

/*���е����ݺ�ָ��Ĵ��ݶ��Ǵ������Чλ��ʼͨ��������*/
void ds18_write_byte(unsigned char dat);
unsigned char ds18_read_byte();

void ReadTemperature();
void display_temperature();