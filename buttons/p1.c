//press a switch to toggle all the leds

#include <REGX52.H>

sbit SW1 = P0^1;
sbit LED1 = P1^0;
void delay()
{
	volatile unsigned long i;
	for(i=0;i<=1000;i++);
}
void main()
{
		P1 = 0;
    while(1)
    {
        if(SW1 == 0)
				{
					delay();
					if(SW1 == 0)
					{
            P1 = ~P1;
						while(SW1 == 0);
					}
				}
    }
}
