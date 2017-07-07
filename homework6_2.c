#include "stc12c5a60s2.h"
#include "intrins.h"
unsigned char code keytable[16] = {0xee,0xed,0xeb,0xe7,0xde,0xdd,0xdb,0xd7,0xbe,0xbd,0xbb,0xb7,0x7e,0x7d,0x7b,0x77};
char code table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char key_scan(void);
void delay_nms(unsigned short int t);
void delay1ms(void);
	
int main()
{
	
	unsigned char key;
	P2M1 = 0X00;
	P2M0 = 0XFF;
	P3 = 0x01;
	while(1)
	{
		key = key_scan();
		if(key != 16){
			P2 = table[key];
		}
		else;
	}
}


unsigned char key_scan()
{
	unsigned char i,scan1,scan2,keycode;
	
	P1 = 0xf0;
	scan1 = P1;
	if((scan1&0xf0) != 0xf0){
		delay_nms(3);
		scan1 = P1;
		if((scan1&0xf0) != 0xf0){
			P1 = 0x0f;
			scan2 = P1;
			keycode = scan1|scan2;
			
			for(i=0;i<16;i++){
				if(keycode == keytable[i])
					return i;
				
			
			}
		}
	}
	else 
		return 16;
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
