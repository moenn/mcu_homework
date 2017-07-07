#include "stc12c5a60s2.h"
#include "intrins.h"
sbit p1_4 = P1^4;

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

int main()
{
	char code table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	unsigned char count=0;
	P3M1 = 0X00;
	P3M0 = 0XFF;
	P3 = 0x01;
	P2 = table[count];
	while(1){
		if(p1_4 == 0){
			count++;
			if(count == 16)
				count = 0;
			P2 = table[count];
			do{;}while(p1_4 == 0);
		}
	}
	
	
	return 0;
}