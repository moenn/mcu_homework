#include "reg52.h"
#include "intrins.h"
void delay_nms(unsigned int t);
void delay1ms(void);

void east_west_on(void);

void south_north_on(void);
char code table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int main()
{
	while(1)
	{
		east_west_on();
		south_north_on();
		
	}
	

}







void east_west_on(void)
{
	P2 = 0x81;
	delay_nms(5000);
	//»ÆµÆ
	P2 = 0x41;
	delay_nms(3000);
	
}


void south_north_on(void)
{
	P2 = 0x24;
	delay_nms(5000);
	//»ÆµÆ
	P2 = 0x22;
	delay_nms(3000);
}






void delay_nms(unsigned  int t)
{
	int i;
	for(i=0;i<t;i++){
		delay1ms();
	}
}	
void delay1ms(void)   //?? -0.651041666667us
{
    unsigned char a,b;
    for(b=4;b>0;b--)
        for(a=113;a>0;a--);
}
