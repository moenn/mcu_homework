#include "stc12c5a60s2.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int


sbit RS = P2 ^ 5;  //Êý¾Ý/ÃüÁîÑ¡Ôñ¶Ë£¬1ÊÇÊý¾Ý£¬0ÊÇÃüÁî£¨×´Ì¬£©
sbit RW = P2 ^ 6;	//¶ÁÐ´¿ØÖÆ£¬1ÊÇ¶Á£¬0ÊÇÐ´
sbit E = P2 ^ 7;	//Ê¹ÄÜ¶Ë£¬¸ßµçÆ½ÔÊÐí

void mcu_initial(void);
void lcd_initial(void);
void check_busy(void);
void write_command(uchar command);
void write_data(uchar _data);
void string(uchar ad,uchar *s);
void lcd_test(void);
void delay1ms(void);
void delay_nms(unsigned short int t);
uchar code table[11] = {0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a};
uchar _1sec_flag = 0;
uchar time[8] = {0,0,10,0,0,10,0,0};
uchar sec = 0;
uchar min = 0;
uchar hour = 0;
int main(void)
{

	
	lcd_initial();
	mcu_initial();
	while(1){
		string(0x80,time);


	}
}

void mcu_initial(void)
{
	TMOD = 0X01;
	TH0 = 0xdc; //10ms
	TL0 = 0x00;

	EA = 1;
	ET0 = 1;
	//EX0 = 1;

	TR0 = 1;
}

void timer0(void) interrupt 1  //change time
{
	TH0 = 0xdc; //10ms
	TL0 = 0x00;
	_1sec_flag ++;
	if(_1sec_flag == 100){
		sec++;
		if(sec == 60){
			min++;
			sec = 0;
			if(min == 60){
				hour++;
				min = 0;
				if(hour == 24){
					hour = 0;
				}
			}
		}
		_1sec_flag = 0;
		time[6] = sec/10;
		time[7] = sec%10;

		time[3] = min/10;
		time[4] = min%10;

		time[0] = hour/10;
		time[1] = hour%10;

	}	
}
void lcd_initial(void)
{ 
	write_command(0x38); //work
	write_command(0x0c); //display 
	write_command(0x06); //mode set
	write_command(0x01); //clear display
	delay1ms();   // without this line, display will overlap
}
void string(uchar address,uchar *time)
{
	uchar i=0;
	write_command(address);
	while(i<8){
		write_data(table[*time]);
		time++;
		i++;
	}
	

}
void write_command(uchar command)
{
	check_busy();
	E = 0;
	RS = 0;
	RW = 0;
	P1 = command;
	E = 1;
	_nop_();
	E = 0;
	delay1ms();
}

void write_data(uchar _data)
{
	check_busy();
	E = 0;
	RS = 1;
	RW = 0;
	P1 = _data;
	E = 1;
	_nop_();
	E = 0;
	delay1ms();
}




void check_busy(void)
{
	uchar dt;
	do{
		dt = 0xff;
		E = 0;
		RS = 0;
		RW = 1;
		E = 1;
		dt = P1;
	}while(dt&0x80);

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

