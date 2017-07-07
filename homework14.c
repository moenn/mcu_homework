#include "stc12c5a60s2.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
void mcu_initial(void);
void delay(uint j);

sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit ENA = P2^5;
sbit INA1 = P2^6;
sbit INA2 = P2^7;

uint pwm = 900;
int main()
{
	mcu_initial();
	ENA = 1;
	INA1 = 0;
	INA2 = 1;
	while(1){
		ENA = 1;
		delay(pwm);
		ENA = 0;
		delay(1000-pwm);
	}
}

//increase
void int0(void) interrupt 0
{
	if(pwm < 1000){
		pwm += 100;

	}
	else{
		pwm = 1000;
	}

}

//decrease
void int1(void) interrupt 2
{
	if(pwm > 0){
		pwm -= 100;

	}
	else{
		pwm = 0;
	}

}

void mcu_initial(void)
{
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;
}

void delay(uint j)
{
	for(;j>0;j--){
		_nop_();
	}
}

