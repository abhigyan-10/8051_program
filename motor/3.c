//checking the pwm of the motor
#include <REGX52.H>
sbit EN = P1^3;
sbit IN1 = P1^6;
sbit IN2 = P1^7;

void motor_pwm (void);
void delay(unsigned int val);

void motor_pwm (void){
		EN = 1;
		delay(30);
		EN = 0;
		delay(70);
}



void delay(unsigned int val)
{
	unsigned int i,j;
	for(i=0;i<val;i++)
	{
		for(j=0;j<1275;j++);
	}
}

void main()
{
	P1 = 0;
	
	IN1 = 1;
	IN2 = 0;
	EN = 0;
	while(1)
	{
		motor_pwm();
	}
}

