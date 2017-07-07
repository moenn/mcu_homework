#include "stc12c5a60s2.h"
#include "intrins.h"
void delay1ms(void);
void delay_nms(unsigned  int t);

int main()
{
		unsigned char code L_Shift[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//左移
		unsigned char code R_Shift[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//右移
		unsigned char code Middle_2_Edge[4] = {0xe7,0xc3,0x81,0x00};//中间向两边
		unsigned char code Edge_2_Middle[4] = {0x7e,0x3c,0x18,0x00};//两边向中间
		unsigned char code Shift0[6] = {0xf8,0xf1,0xe3,0xc7,0x8f,0x1f};//漂移
		unsigned char code Shift1[8] = {0x7f,0x3f,0x1f,0x8f,0xc7,0xe3,0xf1,0xf8};
 		unsigned char code Twinkle[5] = {0xff,0x00,0xff,0x00};//闪烁
		
		unsigned char test = 0x1f;
		unsigned char i;
		while(1){
			
			
			
			for(i=0;i<8;i++){	
				P2 = L_Shift[i];
				delay_nms(70);
			}
			
			for(i=0;i<8;i++){
				P2 = Shift1[i];
				delay_nms(70);
			}
			
			for(i=0;i<6;i++){
				P2 = Shift0[i];
				delay_nms(100);
			}
			
			for(i=0;i<8;i++){
				P2 = R_Shift[i];
				delay_nms(70);
			}
			
			for(i=0;i<4;i++){
				P2 = Edge_2_Middle[i];
				delay_nms(120);
			}
			for(i=0;i<4;i++){
				P2 = Middle_2_Edge[i];
				delay_nms(120);
			}
			
			P2 = 0xff;
			for(i=0;i<4;i++){
				P2 = Twinkle[i];
				delay_nms(100);
			}
			
		
			
			P2 = 0xff;
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

