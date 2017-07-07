#include "stc12c5a60s2.h"
#include "intrins.h"
void delay1ms(void);
void delay_nms(unsigned  int t);
unsigned char flag=1;
void led_Down(void);
void led_Up(void);
void user_Defined(void);
sbit P3_3 = P3^3;

int main()
{
	EA = 1;
	EX1 = 1;
	IT1 = 1;
	
	while(1){
	switch(flag){
		case 1:
			led_Down();
			break;
		case 2:
			led_Up();
			break;
		case 3:
			user_Defined();
			break;
	}
	
	}
}

void int1() interrupt 3
{
	EX1 = 0;
	delay_nms(10);
	if(P3_3 == 0){
		flag++;
		if(flag == 4)
			flag = 1;
	}
	EX1 = 1;
}

void led_Down(void)
{
	unsigned char i;
	unsigned char test = 0xfe;
	
	for(i=0;i<8;i++){
		P2 = test;
		test = (test<<1)+1;
		delay_nms(70);
	}
}	
	

void led_Up(void)
{
	unsigned char i;
	unsigned char test = 0x7f;
	unsigned char temp;
	for(i=0;i<8;i++){
		P2 = test;
		temp = (~test)>>1;
		test = ~temp;
		delay_nms(70);
	}
}

void user_Defined(void)
{
	unsigned char Shift1[8] = {0x7f,0x3f,0x1f,0x8f,0xc7,0xe3,0xf1,0xf8};
	unsigned char i;
	for(i=0;i<8;i++){
				P2 = Shift1[i];
				delay_nms(70);
			}
	
}




















void delay1ms(void)   //?? -0.018084490741us
{
    unsigned char a,b;
    for(b=21;b>0;b--)
        for(a=130;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void delay_nms(unsigned  int t)
{
	unsigned  int i;
	for(i=0;i<t;i++){
		delay1ms();
	}
}

