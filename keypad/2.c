//write in both rows of led and after in ends go to the first position again
#include <REGX52.H>
#define LCD P2

sbit RS = P0^6;
sbit EN = P0^7;
unsigned char keypad[4][4] = {'0', '1', '2', '3',
															'4', '5', '6', '7',
															'8', '9', 'A', 'B',
															'C', 'D', 'E', 'F'};
void init(void);
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char c);
void delay(unsigned char c);
unsigned char get_key(void);

void init(void){
	lcd_cmd(0x38);
	delay(2);
	lcd_cmd(0x0C);
	delay(2);
	lcd_cmd(0x01);
	delay(2);
	lcd_cmd(0x06);
	delay(2);
}

void lcd_cmd(unsigned char c)
{
	LCD = c;
	RS = 0;
	EN = 1;
	delay(2);
	EN = 0;
	delay(1);
}

void lcd_data(unsigned char c)
{
	LCD = c;
	RS = 1;
	EN = 1;
	delay(2);
	EN = 0;
	delay(1);
}

void delay(unsigned char c){
	unsigned int i,j;
	for(i = 0;i<c;i++)
	{
		for(j=0;j<2000;j++);
	}
}

unsigned char get_key(void)
{
	unsigned char i,j;
	while(1)
	{	
		for(i=0;i<4;i++)
		{
			P1 = ~(1<<i);
			if(P1_4 == 0)
				j=0;
			else if(P1_5 == 0)
				j=1;
			else if(P1_6 == 0)
				j=2;
			else if(P1_7 == 0)
				j=3;
			else
				continue;
			delay(8);
			while((P1 & 0xF0)!= 0xF0);
			return keypad[i][j];
		}
	}
}
		
		
void main()
{
	unsigned char key, pos =0;
	init();
	lcd_cmd(0x80); 
	while(1){
		key = get_key();
		lcd_data(key);
		pos++;
		if(pos == 16)
			lcd_cmd(0xC0);
	  if(pos == 32){
			delay(1);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			pos=0;
		}
	
	}
}

	
