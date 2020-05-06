#ifndef __8X8LATTICE_H
#define __8X8LATTICE_H
#include <reg52.h>
#include <intrins.h>


//==== 引脚定义========
sbit A = P1^0;
sbit RB = P1^1;
sbit C = P1^2;
sbit D = P1^3;
sbit EN = P1^4;


void colWrite(unsigned char writeVal);
void rowWrite(unsigned char writeVal);
void drawPoint(unsigned char x, unsigned char y);
void scanDisplay(unsigned char *pbuff);


#endif
