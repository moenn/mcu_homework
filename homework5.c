#include "stc12c5a60s2.h"
#include "intrins.h"
unsigned char code keytable[16] = {0xee,0xed,0xeb,0xe7,0xde,0xdd,0xdb,0xd7,0xbe,0xbd,0xbb,0xb7,0x7e,0x7d,0x7b,0x77};

unsigned char key_scan(void);
void delay_nms(unsigned short int t);
void delay1ms(void);
	
int main()
{
	
	unsigned char key;
		
	while(1)
	{
		key = key_scan();
		if(key != 16){
			P2 = ~key;
		}
		else;
	}
}


unsigned char key_scan()
{
	unsigned char i,scan1,scan2,keycode;
	unsigned char key;
	P1 = 0xf0;
	scan1 = P1;
	if((scan1&0xf0) != 0xf0){
		delay_nms(2);
		scan1 = P1;
		if((scan1&0xf0) != 0xf0){
			P1 = 0x0f;
			scan2 = P1;
			keycode = scan1|scan2;
			
			for(i=0;i<16;i++){
				if(keycode == keytable[i]){
					return i;
				}
			
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
