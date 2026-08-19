//using timer interrupt
#include <REGX52.H>

sbit EN = P1^5;
sbit IN1 = P1^6;
sbit IN2 = P1^7;
unsigned char mode = 1;
void motor(void);
void timer0_delay(void);

void motor(void){
	IN1 = 1;
	IN2 = 0;
}

void timer0_delay(void) interrupt 1
{
	if(mode == 1)
	{
		EN = 0;
		TH0 = 0xF1;  //4ms
		TL0 = 0x9A;
		mode = 0;
		
	}
	else
	{
		EN = 1;
		TH0 = 0xEA;  //6ms....1st time will be initialised in main and then here
		TL0 = 0x67;
		mode = 1;
	}
}

void main()
{
	P1 = 0;
	EA = 1;
	ET0 = 1;
	TMOD = 0x01; 
	TR0 = 1;
	EN = 0;
	motor();
	TH0 = 0xEA;
	TL0 = 0x67;
	while(1)
	{
	}
}

		
