#include "stc12c5a60s2.h"

int main()
{
	char data *p30 = 0x30;
	char xdata *p1000 = 0x1000;
	char i;
	for(i=0;i<20;i++){
		*p30 = i;
		p30++;
	}
	p30 = 0x30;
	for(i=0;i<20;i++){ 
		ACC = *p30<<1;
		if(P){
			*p1000 = *p30&0x7f; //奇数个1，D7置为0
		}
		else{
			*p1000 = *p30|0x80;//偶数个1，D7置为1
		}
		p30++;
		p1000++;
	}
	
	return 0;
}


























/*#include "stc12c5a60s2.h"
#include<absacc.h>
char data *p30,*pD7;
char xdata *p1000;
char  data i,j,n;
void main( ) 
{
  p30=0x30;
  pD7=0xD0;
  p1000=0x1000;
n=0;
for(i=0;i<20;i++) 
{
*p1000=*p30;
for(j=0;j<7;j++)//将p30指针指向的数进行二进制转换
{
  *pD7=*p30/2;
  if(*pD7==1)
     n++;
  pD7++;
}
if(n/2!=0)
*pD7=0;
else 
*pD7=1;
 pD7=0xD0;
 p1000++;
 p30++;
}
}*/