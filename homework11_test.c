#include "stc12c5a60s2.h"

sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_3 = P3^3;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;
int main()
{
	while(1){
		if(P3_6 == 1){
			P2 = 0x00;
			
		}
		else if(P3_6 == 0){
			P2 = 0xff;
		}
		else;
	}
}
