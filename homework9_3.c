#include "stc12c5a60s2.h"
#include "intrins.h"
void count_break(unsigned short int count);
void init(void);
void delay1ms(void);
void delay_nms(unsigned short int t);
sbit P3_2 = P3^2;
unsigned short int count = 0;
unsigned char num[3] = {0,0,0};
char code table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char i=0;
unsigned char j=0;
unsigned char test = 0x01;
unsigned char test0;
int main()
{
	
	init();
	while(1){
		count_break(count);
	}
		
	
	return 0;
}

void init(void)
{
	P2M1 = 0x00;
	P2M0 = 0xff;
	
	TMOD = 0x11;
	TH0 = 0xdc; //10ms
	TL0 = 0x00;
	
	TH1 = 0xf8; //2ms
	TL1 = 0xcc;
	
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	EX0 = 1;
	
	IT0 = 1;
	
	TR0 = 1;
	TR1 = 1;
	
	PX0 = 1;
	PT0 = 0;
	PT1 = 0;
	
	
	PT1 = 1;
	PX0 = 0; 
	return;
}

void count_break(unsigned short int count)
{
	unsigned char duan1,duan2,duan3;
	unsigned short int temp3,temp2;
	duan3 = count%10;
	temp3 = count/10;
	
	duan2 = temp3%10;
	temp2 = temp3/10;
	
	duan1 = temp2%10;
	
	num[0] = duan1;
	num[1] = duan2;
	num[2] = duan3;
	
	return;
	
	
}

void timer0() interrupt 1
{
	TH0 = 0xdc;
	TL0 = 0x00;
	count++;
	if(count == 1000)
		count = 0;
	
	
}

void timer1() interrupt 3
{
	TH1 = 0xf8; //2ms, segœ‘ æ
	TL1 = 0xcc;
	P4 = test;
	P2 = table[num[i]];
	test = test<<1;
	i++;
	if(test == 0x08){
		test = 0x01;
	}
	if(i>2){
		i = 0;
	}
	
}

void int0() interrupt 0
{
	EX0 = 0;
	
	TR0 = 0;
	
	while(P3_2 == 0);
	
	
	
	TR0 = 1;

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
