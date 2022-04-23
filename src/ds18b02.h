#define TESTDS18 0
#if TESTDS18
#define ds18 P22
#else
#define ds18 P26
#endif

void ds18_init();

/*所有的数据和指令的传递都是从最低有效位开始通过单总线*/
void ds18_write_byte(unsigned char dat);
unsigned char ds18_read_byte();

void ReadTemperature();
void display_temperature();