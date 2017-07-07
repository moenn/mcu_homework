#include "stc12c5a60s2.h"
#include "intrins.h"
void delay1ms(void);
void delay_nms(unsigned short int t);
sbit P3_2 = P3^2;
unsigned char count=0;
int main()
{
	char code table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	P4 = 0x01;
	P2M1 = 0X00;
	P2M0 = 0XFF;
	
	EA = 1;
	EX0 = 1;
	IT0 = 0;

	while(1){
		P2 = table[count];
	}
	return 0;
}

void int0() interrupt 0
{
	EX0 = 0;
	
	count++;
	if(count==16){
		count = 0;
	}
	while(P3_2 == 0);
	delay_nms(10);
	
	EX0 = 1;
	
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


