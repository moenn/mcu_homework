#include "stc12c5a60s2.h"

int main()
{
	unsigned char data *p20=0x20;
  char data *p40=0x40;
	char xdata *p8000=0x8000;
	
	char i;
	unsigned char count=0;
	
	char test = 0x80; 
		//将[-8,7]共16个数存入0x40
	
	
	for(i=-8;i<8;i++){
		*p40 = i;
		if(!(*p40&test)){
			*p8000 = *p40;
			count++;
			p40++;
			p8000++;
		}
		else{
			p40++;
		}
	}

	*p20 = count;
	return 0;
}