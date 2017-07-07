#include "stc12c5a60s2.h"
#include "intrins.h"
#include "string.h"
void delay1ms(void);
void delay_nms(unsigned short int t);
void init(void);

sbit P3_2 = P3^2 ;
sbit P3_5 = P3^5 ;
sbit P3_6 = P3^6 ;
sbit P3_7 = P3^7;
unsigned char display = 0;
unsigned char record_display_index=0;


unsigned char time_i=0;
unsigned char time_select = 0x01;

unsigned char record_i=0;
unsigned char record_select = 0x01;

char code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
unsigned char code record_origin[10][8] = {
															{0,0,0,0,0,0,16,1},
															{0,0,0,0,0,0,16,2},
															{0,0,0,0,0,0,16,3},
															{0,0,0,0,0,0,16,4},
															{0,0,0,0,0,0,16,5},
															{0,0,0,0,0,0,16,6},
															{0,0,0,0,0,0,16,7},
															{0,0,0,0,0,0,16,8},
															{0,0,0,0,0,0,16,9},
															{0,0,0,0,0,0,16,10},

														};
unsigned int ms=0;
unsigned char sec=0;
unsigned char min=0;
unsigned char time[6] = {0,0,0,0,0,0}; 

unsigned char record_index = 0;
unsigned char record[10][8] = {
															{0,0,0,0,0,0,16,1},
															{0,0,0,0,0,0,16,2},
															{0,0,0,0,0,0,16,3},
															{0,0,0,0,0,0,16,4},
															{0,0,0,0,0,0,16,5},
															{0,0,0,0,0,0,16,6},
															{0,0,0,0,0,0,16,7},
															{0,0,0,0,0,0,16,8},
															{0,0,0,0,0,0,16,9},
															{0,0,0,0,0,0,16,10},

														};

int main()
{
	init();
	while(1){
		//record display
		if(P3_6 == 1){
			EX0 = 1;
			display = 1;
			do{
				;
			}while(P3_6 == 1);
			
			EX0 = 0;
			display = 0;
			record_display_index = 0;
		}
		
		if(P3_7 == 0){
			TR0 = 0;
			ET0 = 0;
		}
		if(P3_7 == 1){
			TR0 = 1;
			ET0 = 1;
		}
		
		if(P3_5 == 0){
			delay_nms(1000);
			if(P3_5 == 0){
				ms = 0;
				sec = 0;
				min = 0;
				time[0] = 0;
				time[1] = 0;
				time[2] = 0;
				time[3] = 0;
				time[4] = 0;
				time[5] = 0;
				
				record_display_index = 0;
				record_index = 0;
				memcpy(record,record_origin,sizeof(record_origin));
				
					}
				}
				

			}
}
		
	



void init(void)
{
	P0M1 = 0x00;
	P0M0 = 0xff;
	TMOD = 0x11;
	
	TH0 = 0Xdc;//10MS
	TL0 = 0X00;
	
	TH1 = 0Xfc;//1ms
	TL1 = 0X66;
	
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	EX0 = 0;
	EX1 = 1;
	
	IT0 = 1;
	IT1 = 1;
	
	TR0 = 1;
	TR1 = 1;
}

void timer0(void) interrupt 1
{
	TH0 = 0Xdc;//10MS
	TL0 = 0X00;
	
	ms++;
	if(ms == 100){
		ms = 0;
		sec++;
		if(sec == 60){
			sec = 0;
			min++;
			if(min == 60){
				min = 0;
		
			}
		}
	}
	
	time[0] = min/10;
	time[1] = min%10; 
	time[2] = sec/10;
	time[3] = sec%10;
	

	time[4] = ms/10;
	time[5] = ms%10;
	
	
}

void timer1(void) interrupt 3
{
	TH1 = 0Xfc;//1ms
	TL1 = 0X66;
	
	// display time
	if(display == 0){
		P0 = table[time[time_i]];
		P1 = time_select;
		time_i++;
		time_select = time_select<<1;
		if(time_i == 6){
			time_i = 0;
		}
		if(time_select == 0X40){
			time_select = 0x01;
		}
	}
	// display record
	else if(display == 1){
		P0 = table[record[record_display_index][record_i]];
		P1 = record_select;
		record_i++;
		record_select = record_select<<1;
		if(record_i == 8){
			record_i = 0;
		}
		if(record_select == 0X00){
			record_select = 0x01;
		}
	}
	else;
}

//record_display_index 
void int0(void) interrupt 0
{
	delay_nms(2);
	if(P3_2 == 0){
		record_display_index++;
			if(record_display_index == 10){
				record_display_index = 0;
			}
	}
	while(P3_2 == 0);
}

//record time of now
void int1(void) interrupt 2
{
	if(record_index < 10){
		memcpy(record[record_index],time,sizeof(time));
		record_index++;
	}
	
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



