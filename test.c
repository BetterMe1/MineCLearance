/*
date：2018/11/17
author:BetterMe1
program:Mine Clearance
compiler:Visual Studio 2013
拓展功能:1.设置游戏难度等级
2.保证玩家在第一把踩雷后不被炸死
3.若排雷的地方无雷，自动扩展到有雷的周围，并给出雷数
4.标记
5.取消标记
*/

/*测试部分*/
#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int COUNT = 0;

void menu(){
	printf("************  扫雷小游戏  ************\n");
	printf("******  1.进入游戏  2.退出游戏  ******\n");
	printf("**************************************\n");
}
void menu2(){
	printf("********  请选择要挑战的模式  ********\n");
	printf("********  1.简单模式（10个雷）********\n");
	printf("********  2.一般模式（20个雷）********\n");
	printf("********  3.困难模式（25个雷）********\n");
}
void game(){
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };//显示雷,给玩家看
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');//初始化棋盘
	Putmine(mine, ROW, COL,COUNT);//埋雷
	DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);//打印棋盘
	Findmine(mine,show, ROW, COL, COUNT);//扫雷
}
void test(){
	int input = 0;
	int input2 = 0;
	do{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input){
		case 1:
			while (1){
				menu2();
				printf("请选择:>");
				scanf("%d", &input2);
				switch (input2){
				case 1:
					COUNT = EASY_COUNT;
					break;
				case 2:
					COUNT = USUAL_COUNT;
					break;
				case 3:
					COUNT = HARD_COUNT;
					break;
				default:
					printf("输入有误，请重新选择！\n");
					break;
				}
				if (input2 >= 1 && input2 <= 3){
					break;
				}
			}
			game();
			break;
		case 2:
			printf("退出游戏！\n");
			break;
		default:
			printf("输入有误，请重新选择！\n");
			break;
		}
	} while ((input - 2));
}
void main(){
	test();
	system("pause");
}