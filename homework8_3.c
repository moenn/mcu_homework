/*
使用电平触发方式的话，每次按键后count的值会增加几百！
*/

#include "stc12c5a60s2.h"
#include "intrins.h"
void count_break(unsigned short int count);
void delay1ms(void);
void delay_nms(unsigned short int t);

unsigned short int count = 0;
unsigned char num[4] = {0,0,0,0};
char code table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit P3_2 = P3^2;
unsigned char test0;
unsigned char j;

int main()
{
	
	unsigned char i;
	unsigned char test;
	
	
	P2M1 = 0x00;
	P2M0 = 0xff;
	
	EA = 1;
	EX0 = 1;
	IT0 = 0;
	
	while(1)
	{
		count_break(count);
		//显示定时数字
		test = 0x01;
		for(i=0;i<4;i++){
			P4 = test; 
			P2 = table[num[i]];
			delay_nms(1);
			test = test<<1;
		}		
	}
	return 0;
}



void int0() interrupt 0
{
	EX0 = 0;
	
	count++;
	if(count == 1000){
		count = 0;
	}
	while(P3_2 == 0){
		test0 = 0x01;
		for(j=0;j<4;j++){
			P4 = test0; 
			P2 = table[num[j]];
			delay_nms(1);
			test0 = test0<<1;
		}		
	}
	delay_nms(10);
	
	EX0 = 1;
	
}

void count_break(unsigned short int count)
{
	unsigned char duan0,duan1,duan2,duan3;
	unsigned short int temp3,temp2,temp1;
	duan3 = count%10;
	temp3 = count/10;
	
	duan2 = temp3%10;
	temp2 = temp3/10;
	
	duan1 = temp2%10;
	temp1 = temp2/10;
	
	duan0 = temp1%10;
	
	
	num[0] = duan0;
	num[1] = duan1;
	num[2] = duan2;
	num[3] = duan3;
	
	return;
	
	
}

void delay1ms(void)   //?? -0.018084490741us
{
    unsigned char a,b;
    for(b=21;b>0;b--)
        for(a=130;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void delay_nms(unsigned short int t)
{
	unsigned short int i;
	for(i=0;i<t;i++){
		delay1ms();
	}
}

