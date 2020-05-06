#include "KEY.H"

void delay1Ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void delayMs(unsigned int i)
{
	while(i--)
	{
		delay1Ms();
	}
}
