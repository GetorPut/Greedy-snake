#include "8x8lattice.h"

 void colWrite(unsigned char writeVal)		 //列显示
{
	unsigned char i;
	for(i=0; i<30; i++)
	{
		  P0 = writeVal;
	}
}
void rowWrite(unsigned char writeVal)	   //行
{
	D = 0;
	EN=0;
	switch(writeVal)
	{
		case 0: A=0;RB=0;C=0;break;
		case 1: A=1;RB=0;C=0;break;
		case 2: A=0;RB=1;C=0;break;
		case 3: A=1;RB=1;C=0;break;
		case 4: A=0;RB=0;C=1;break;
		case 5: A=1;RB=0;C=1;break;
		case 6: A=0;RB=1;C=1;break;
		case 7: A=1;RB=1;C=1;break;
		default:  break;	
	}
}
void drawPoint(unsigned char x, unsigned char y)
{
	rowWrite(y);
	colWrite(0xFF);
	colWrite(~(1<<x));
}
void scanDisplay(unsigned char *pbuff)
{
	unsigned char i=0;
	colWrite(0xFF);
	for(i=0; i<8; i++)
	{	
		rowWrite(i);
		colWrite(~pbuff[i]);		
		colWrite(0xFF);
	}
}


