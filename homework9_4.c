#include "stc12c5a60s2.h"
#define uchar unsigned char
#define uint unsigned int
void mcu_initial(void);
uint count = 0;
uchar num[4] = {0,0,0,0};
uchar temp;

uchar code table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//0-9
uchar seg_select = 0x01;
uchar i = 0; 
int main()
{
	mcu_initial();
	while(1);
}

void mcu_initial(void)
{
	P1M1 = 0X00;
	P1M0 = 0XFF;
	TMOD = 0X01;
	TH0 = 0XFC;
	TL0 = 0X66;

	EA = 1;
	ET0 = 1;
	EX0 = 1;
	TR0 = 1;

	IT0 = 1;
}


void int0() interrupt 0
{
	count++;
	num[0] = count/1000;
	temp = count - num[0]*1000;
	num[1] = temp/100;
	temp = temp - num[1]*100;
	num[2] = temp/10;
	num[3] = temp%10;
}

void timer0() interrupt 1
{
	TH0 = 0XFC;
	TL0 = 0X66;
	P1 = table[num[i]];
	P2 = seg_select;
	i = i + 1;
	seg_select = seg_select<<1;
	if(i == 4){
		i = 0;
		seg_select = 0x01;
	}
	

}

