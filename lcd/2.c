//displaying nos one after another from 0 - 65535
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
void lcd_num(unsigned int s)
{
	unsigned char digit[5];
	unsigned char i=0;
	
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
	for(i=i-1;i>0;i--)
		lcd_data(digit[i]+'0');
	
}
void delay(unsigned char d)
{
	unsigned int i,j;
	for(i=0;i<=d; i++)
		for(j=0;j<=2000;j++);
}

void main()
{
	unsigned int count;
	count = 0;
	lcd_init();
	while(1){
		lcd_cmd(0x80);
		
		lcd_string("     "); //to remove the whole no and clr the screen.....using instead of lcd_cmd(0x01) to clr screen to reduce the delay

		delay(3);
		
		lcd_cmd(0x80); //to bring back the curson to 1st row, 1st col
		
		lcd_num(count);
		
		delay(1);
		
		count++;
	}
}

