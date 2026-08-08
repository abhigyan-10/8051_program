//display in both rows
#include <REGX52.H>

#define LCD P2

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
void delay(unsigned char d)
{
	unsigned int i,j;
	for(i=0;i<=d; i++)
		for(j=0;j<=3500;j++);
}

void main()
{
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Cristianoo");
	lcd_cmd(0xC0);
	lcd_string("I AM BACK");
	while(1){
	}
}

