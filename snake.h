#ifndef __SNAKE_H
#define __SNAKE_H

#define WIDTH 8
#define LENGTH 8
#define SNAKE_Max_Long 15	// 蛇最大长度

static void createFood();
static void Collision_Monitoring();
static void initSnake();
static void drawSnake();
static void runSnake();
static void changeDir(unsigned char key);
void startSnake();
unsigned int KeyCheck (void);
#endif
