#include "stc12c5a60s2.h"
#include "intrins.h"
void delay1ms(void);
void delay_nms(unsigned short int t);
sbit p3_0 = P3^0;
int main()
{
	unsigned char count=0;
	unsigned char m;
	
	m = p3_0;
	P2 = 0x00;
	while(1){
		if(p3_0 != m){
			delay_nms(10);
			if(p3_0 != m){
				count++;
				P2 = count;
				if(count == 0xff)
					count = 0;
				delay_nms(300);
				m = p3_0;
			}
		}
	}
	return 0 ;
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
