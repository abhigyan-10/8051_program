//calculator using keypad and lcd
#include <REGX52.H>
#define LCD P2

sbit RS = P0^6;
sbit EN = P0^7;
unsigned char keypad[4][4] = {'0', '1', '2', '3',
															'4', '5', '6', '7',
															'8', '9', '=', '%',
															'+', '-', '*', '/'};
void init(void);
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char c);
void delay(unsigned char c);
unsigned char get_key(void);
void lcd_num(unsigned int n);
unsigned int string_to_num(unsigned char *s);

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

unsigned int string_to_num(unsigned char *s)
{
	unsigned int n = 0;
	while(*s != '\0')
	{
		n= n*10+(*s - '0');
		s++;
	}
	return n;
}

void lcd_num(unsigned int n)
{
    unsigned char digit[14];
    unsigned char i = 0;

    if(n == 0)
    {
        lcd_data('0');
        return;
    }

    while(n > 0)
    {
        digit[i] = n % 10;
        n = n / 10; 
        i++;
    }

    while(i > 0)
    {
        i--;
        lcd_data(digit[i] + '0');
    }
}
		
void main()
{
	unsigned char key,i=0,j=0,state = 0;
	unsigned char s1[7]='\0', s2[7] = '\0',operate;
	signed int s = 0;unsigned n1,n2;
	init();
	lcd_cmd(0x80); 
	while(1){
		key = get_key();
		lcd_data(key);
		
		if(key == '+' || key == '-' || key == '*' || key == '%' || key == '/'){
			operate = key;
			state = 1;
		}
		else if(key == '=')
		{
			lcd_cmd(0xC0);
			n1 = string_to_num(s1);
			n2 = string_to_num(s2);
			switch(operate)
			{
				case '+':
				{
					s= n1 + n2;
					break;
				}
				case '-':
				{
					s= n1 - n2;
					break;
				}
				case '*':
				{
					s= n1 * n2;
					break;
				}
				case '/':
				{
					if(n2 != 0)
						s= n1 / n2;
					else {
						s=9999;
					}
					break;
				}
				case '%':
				{
					if(n2 != 0)
						s= n1 / n2;
					else {
						s=9999;
					}
					break;
				}
			}
			lcd_num(s);
			i=0;
			j=0;
			state = 0;
			delay(150);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
		}
		else
		{
			if(state == 0)
				s1[i++] = key;
			if(state == 1)
				s2[j++] = key;
			s1[i]='\0';
			s2[j]='\0';
		}
		
	}
}

	
