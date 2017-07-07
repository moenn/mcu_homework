#include "stc12c5a60s2.h"
#define uchar unsigned char
#define uint unsigned int
void mcu_initial(void);
uint time = 0;
uchar num[3] = {0,0,0};
uchar temp;

uchar code table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//0-9
uchar seg_select = 0x10;
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
	TMOD = 0X11;
	TH1 = 0XDC;
	TL1 = 0X00;
	TH0 = 0XFC;
	TL0 = 0X66;

	EA = 1;
	ET0 = 1;
	ET1 = 1;
	TR0 = 1;
	TR1 = 1;
}


void timer0() interrupt 1
{
	TH0 = 0XFC;
	TL0 = 0X66;
	P1 = table[num[i]];
	P2 = seg_select;
	i = i + 1;
	seg_select = seg_select<<1;
	if(i == 3){
		i = 0;
		seg_select = 0x10;
	}
	

}

void timer1() interrupt 3
{
	TH0 = 0XDC;//10MS
	TL0 = 0X66;
	time++;
	if(time == 1000){
		time = 0;
	}
	num[0] = time/100;
	temp = time - num[0]*100;
	num[1] = temp/10;
	num[2] = temp%10;

}