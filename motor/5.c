//motor interfacing using TImer
#include <REGX52.H>

sbit EN = P1^5;
sbit IN1 = P1^6;
sbit IN2 = P1^7;
unsigned int j;
void motor(void);
void timer0_delay(unsigned char i);

void motor(void){
	IN1 = 1;
	IN2 = 0;
}

void timer0_delay(unsigned char i)
{
	if(i == 0)
	{
		TH0 = 0xEA;
		TL0 = 0x67;
	}
	else
	{
		TH0 = 0xF1;
		TL0 = 0x9A;
	}
	TF0 = 0;
	TR0 = 1;
	while(TF0 == 0);
	TF0 = 0;
	TR0 = 0;
}

void main()
{
	P1 = 0;
	TMOD = 0x01;
	EN = 0;
	motor();
	while(1)
	{
		EN = 1;
		timer0_delay(0);
		//for(j=0;j<50000;j++);  this is used to check whether the timer is working or not
		EN = 0;
		timer0_delay(1);
		//for(j=0;j<50000;j++);
	}
}

		
