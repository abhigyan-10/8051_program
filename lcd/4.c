//display counter after a string
#include <REGX52.H>

#define LCD P2
unsigned int count;

sbit RS = P0^6;
sbit EN = P0^7;
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char ch);
void delay(unsigned char d);
void lcd_string(unsigned char *s);

void lcd_init(void){
	lcd_cmd(0x38);
	delay(2);
	lcd_cmd(0x0C);
	delay(2);
	lcd_cmd(0x01);
	delay(4);
	lcd_cmd(0x06);
	delay(2);
}

void lcd_cmd(unsigned char cmd)
{
	LCD = cmd;
	RS = 0;
	EN = 1;
	delay(1);
	EN = 0;
	delay(1);
}

void lcd_data(unsigned char ch)
{
	LCD = ch;
	RS = 1;
	EN = 1;
	delay(1);
	EN = 0;
	delay(1);
}

void lcd_string(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
		delay(1);
	}
}
void lcd_num(unsigned int s)
{
	unsigned char digit[5];
	signed char i=0;
	
	if(s==0){
		lcd_data('0');
		return;
	}
	
	while(s>0)
	{
		digit[i] = s%10;
		s=s/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
		lcd_data(digit[i]+'0');
	
}
void delay(unsigned char d)
{
	unsigned int i,j;
	for(i=0;i<=d; i++)
		for(j=0;j<=3500;j++);
}

void main()
{
	count = 0;
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Cristiano");
	EA = 1;
	EX0 = 1;
	IT0 = 1;
	//lcd_cmd(0xC0);
	//lcd_string("I AM BACK");
	while(1){
		lcd_cmd(0x8A);
		lcd_num(count);
		lcd_string("  ");
		delay(3);
		count++;
		if(count>7){
			count = 0;
			lcd_cmd(0xC0);
			lcd_string("Goooal!! Siuuu");
			delay(7);
			lcd_cmd(0xC0);
			lcd_string("              ");
		}
	}
}

