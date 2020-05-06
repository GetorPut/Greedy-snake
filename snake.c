#include <reg52.h>
#include <stdlib.h>
#include "key.h"
#include "8x8lattice.h"
#include "snake.h"

sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;
sbit KeyOut1 = P2^3;
sbit KeyOut2 = P2^2;
sbit KeyOut3 = P2^1;
sbit KeyOut4 = P2^0;

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//******与蛇相关的结构体定义*************//
static struct Food
{
	unsigned char x;	// 食物的横坐标
	unsigned char y;	// 食物的纵坐标
}food;	// 食物结构体

struct Snake
{
	char x[SNAKE_Max_Long];
	char y[SNAKE_Max_Long];
	unsigned char Long;		// 蛇的长度
	unsigned char Life;		// 蛇的生命
	unsigned char Dir;		// 蛇移动方向
}snake;	// 蛇结构体
//****************************************//

enum Dir{up, down, left, right}; //方向枚举

//***********变量声明***************//
unsigned char DispRAM[8]={0}; // 蛇坐标缓存
unsigned char tCount=0;
unsigned char speedLevel=80;

//**********************************//
//启动贪吃蛇游戏（主函数）
void startSnake()
{	
	initSnake();
	while(snake.Life)
	{	
		//更新显示
	    drawSnake();
		//人机交互
		changeDir(KeyCheck());
		// 蛇运行的速度，由speedLevel决定
		if(tCount >= speedLevel)
		{
			tCount=0;
			//蛇run 
			runSnake();
		}
		//碰撞检测
		Collision_Monitoring();	
		tCount++;
	}
}

//初始化蛇的位置等
static void initSnake()
{
	//清除内存数据
	unsigned char i;
	for(i=0; i<SNAKE_Max_Long; i++)
	{
		snake.x[i]=-1;
		snake.y[i]=-1;
	}
	
	//初始化蛇参数
	snake.Long=2;	// 初始化蛇的长度为两节
	snake.Life=1;	//初始化蛇活着
	snake.Dir=right;
	snake.x[1]=0;
	snake.y[1]=2;
	snake.x[0]=1;
	snake.y[0]=2;
	createFood();
}
// 用此函数来产生食物
static void createFood()
{
	unsigned char i;
	food.x = rand()%WIDTH;
	food.y = rand()%LENGTH;
	for(i=0; i<snake.Long; i++)
	{
		if(food.x==snake.x[i] && food.y==snake.y[i])
		createFood();	
	}
}
//更新显示
static void drawSnake()
{
	unsigned char i=0;
	for(i=0; i<8; i++) DispRAM[i]=0;
	for(i=0; i<snake.Long; i++)
		DispRAM[snake.y[i]] |= 1<<snake.x[i];
	drawPoint(food.x, food.y);
	scanDisplay(DispRAM);

}
//方向按键处理
static void changeDir(unsigned int key)
{  	
	// 方向按键的规则
	switch(key)
	{
		case 4:	 if(snake.Dir != down)	snake.Dir=up; 		break;
		case 12: if(snake.Dir != up)	snake.Dir=down; 	break;
		case 8:  if(snake.Dir != right) snake.Dir=left; 	break;
		case 16: if(snake.Dir != left) 	snake.Dir=right;	break;
		default: break;
	}

}
//蛇运动坐标刷新
static void runSnake()
{
	unsigned char i;
	
	// 蛇身体坐标移动，蛇头方向坐标逐渐向蛇尾方向移动
	for(i=snake.Long; i>0; i--)
	{	
		snake.y[i]=snake.y[i-1];
		snake.x[i]=snake.x[i-1];
	}
	
	// 重新获得蛇的头部位置
	switch(snake.Dir)
	{	
		case up:	snake.y[0]-=1; break;
		case down:	snake.y[0]+=1; break;
		case left:	snake.x[0]-=1; break;
		case right: snake.x[0]+=1; break;
		default: break;
	}
}
//碰撞检测
static void Collision_Monitoring()
{
		uchar i=0;
		// 限定蛇活动范围，超范围就dead
		if((snake.x[0]>(WIDTH-1)) || (snake.x[0]<0) || (snake.y[0]>(LENGTH-1)) || (snake.y[0]<0))
		{
			snake.Life=0;			
			snake.Dir=right;	
		}
		// 蛇自杀检测
		for(i=4; i<=snake.Long; i++)
		{
			if(snake.x[i-1]==snake.x[0] && snake.y[i-1]==snake.y[0])
			{
				snake.Life=0;	
				snake.Dir=right;	
			}
		}
	// 蛇吃到食物
	if(snake.x[0]==food.x && snake.y[0]==food.y)
	{
		snake.Long++;
		createFood();
	}
}

//获取按键值
uint prev_key=16;  //记录上一次按键值
unsigned int KeyCheck (void)
{
		uint k;
		KeyOut1 = 0;
		KeyOut2 = 1;
		KeyOut3 = 1;
		KeyOut4 = 1;
		if(KeyIn1 == 0) 
		{
			delayMs(100);
			if(KeyIn1 == 0)
			   k=1;
		}
		if(KeyIn2 == 0)
		{
				delayMs(100);
			if(KeyIn2 == 0)
			   k=2;
		}
		if(KeyIn3 == 0)
		{
				delayMs(100);
			if(KeyIn3 == 0)
			   k=3;
		}	
		if(KeyIn4 == 0)
		{
				delayMs(100);
			if(KeyIn4 == 0)
			   k=4;
		}
		while((KeyIn1 == 0)||(KeyIn2 == 0)||
		      (KeyIn3 == 0)||(KeyIn4 == 0));
		
		KeyOut1 = 1;
		KeyOut2 = 0;
		KeyOut3 = 1;
		KeyOut4 = 1;
		if(KeyIn1 == 0) 
		{
				delayMs(100);
			if(KeyIn1 == 0)
			   k=5;
		}
		if(KeyIn2 == 0)
		{
				delayMs(100);
			if(KeyIn2 == 0)
			   k=6;
		}
		if(KeyIn3 == 0)
		{
				delayMs(100);
			if(KeyIn3 == 0)
			   k=7;
		}	
		if(KeyIn4 == 0)
		{
			delayMs(100);
			if(KeyIn4 == 0)
			   k=8;
		}
		while((KeyIn1 == 0)||(KeyIn2 == 0)||
		      (KeyIn3 == 0)||(KeyIn4 == 0));

		KeyOut1 = 1;
		KeyOut2 = 1;
		KeyOut3 = 0;
		KeyOut4 = 1;
		if(KeyIn1 == 0) 
		{
				delayMs(100);
			if(KeyIn1 == 0)
			   k=9;
		}
		if(KeyIn2 == 0)
		{
			delayMs(100);
			if(KeyIn2 == 0)
			   k=10;
		}
		if(KeyIn3 == 0)
		{
				delayMs(100);
			if(KeyIn3 == 0)
			   k=11;
		}	
		if(KeyIn4 == 0)
		{
				delayMs(100);
			if(KeyIn4 == 0)
			   k=12;
		}
		while((KeyIn1 == 0)||(KeyIn2 == 0)||
		      (KeyIn3 == 0)||(KeyIn4 == 0));

		KeyOut1 = 1;
		KeyOut2 = 1;
		KeyOut3 = 1;
		KeyOut4 = 0;
		if(KeyIn1 == 0) 
		{
				delayMs(100);
			if(KeyIn1 == 0)
			   k=13;
		}
		if(KeyIn2 == 0)
		{
				delayMs(100);
			if(KeyIn2 == 0)
			   k=14;
		}
		if(KeyIn3 == 0)
		{
				delayMs(100);
			if(KeyIn3 == 0)
			   k=15;
		}	
		if(KeyIn4 == 0)
		{
				delayMs(100);
			if(KeyIn4 == 0)
			   k=16;
		}
		
	   while((KeyIn1 == 0)||(KeyIn2 == 0)||
		      (KeyIn3 == 0)||(KeyIn4 == 0));

	   if(prev_key == k)
	   		return prev_key;
		else{
			prev_key = k;
			return k;
		}		
}


