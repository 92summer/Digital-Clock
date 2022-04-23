# 日历时钟(By STC89C52RC)

![image](https://github.com/92summer/Digital-Clock/blob/main/VID_20220417_232555_x264.gif)

## 程序开发

Keil4

## 主要物料表

| 序号 |        模块        | 数量 |
| :--: | :----------------: | :--: |
|  1   |      LCD1602       |  1   |
|  2   |     DS1302模块     |  1   |
|  3   |   DC-DC降压模块    |  1   |
|  4   | STC89C52RC最小系统 |  1   |
|  5   |      ds18b02      |  1   |

## 实物引脚分布

```c
/*LCD1602*/
#define EN P20
#define RS P21
#define RW P22
#define D7 P17
#define DB P1

/*DS1302*/
#define RST P25
#define SDA P24
#define SCLK P23
```  

```c
/*ds18b02*/
#define ds18 P26
```

## 时间初始化

```c
/*在ds1302.c中修改*/
//6--年 5--周 4--月 3--日 2--时 1--分 0--秒
unsigned char DT[7]={30,6,23,17,4,7,22};
```

## 2022.4.23更新：添加温度显示  
![image]()  
ds18b02  
