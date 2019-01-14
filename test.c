/*
date：2018/11/17
author:BetterMe1
program:Mine Clearance
compiler:Visual Studio 2013
拓展功能:
1.设置游戏难度等级
2.保证玩家在第一把踩雷后不被炸死
3.若排雷的地方无雷，自动扩展到有雷的周围，并给出雷数
4.标记(相当于扫雷游戏中的插旗子）
5.取消标记
*/

/*
分析：
1.用二维字符数组mine[ROWS][COLS]来存储雷,现在我们用字符1来表示有雷，字符0表示无雷。
用二维字符数组show[ROWS][COLS]将所有的元素初始化为*，并打印作为展现给玩家的。
同时用show数组来表示对应的mine数组中周围雷即字符0的个数。
对于边缘的格子无法计算雷的个数，因此需再增加2行2列，防止数组越界。
2.游戏难度等级的设置即就是雷的个数和棋盘大小不同，即就是Putmine中传的COUNT(雷数）不同，
棋盘大小不同也就是在初始化、埋雷、扫雷、打印棋盘等函数中传的行、列数不同，
由于是控制台程序，没有将一般模式和困难模式的棋盘打印的过大（因为会丑，也容易眼花），正常情况下扫雷的中级模式是40个雷，16*16格，
高级模式是99个雷，16*30格.
3.为了保证玩家体验，保证玩家在第一把踩雷后不被炸死，此时只需要判断玩家第一次排查的坐标是否等于雷的坐标，如果是，将雷悄悄移走（重新生成随机数）
4.若排雷的地方无雷，自动扩展到有雷的周围，并给出雷数，此时需要用到递归，直至递归到周围有雷停止，并计算雷数，显示在棋盘上。
5.标记与取消标记这个是很容易实现的，将标记位置改为P（也可以为其他），取消标记改回*即可。
*/
/*测试部分*/
#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <stdio.h>
#include <stdlib.h>


void menu(){
	printf("************  扫雷小游戏  ************\n");
	printf("******  1.进入游戏  2.退出游戏  ******\n");
	printf("**************************************\n");
}
void menu2(){
	printf("********  请选择要挑战的模式  ********\n");
	printf("********  1.简单模式（10个雷）********\n");
	printf("********  2.一般模式（15个雷）********\n");
	printf("********  3.困难模式（20个雷）********\n");
}
void game(int COUNT ){
	if (COUNT == 10){
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//显示雷,给玩家看
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//初始化棋盘
		Putmine(mine, ROW-6, COL-6, COUNT);//埋雷
		//DisplayBoard(mine, ROW - 6, COL - 6);
		DisplayBoard(show, ROW-6, COL-6);//打印棋盘
		Findmine(mine, show, ROW-6, COL-6, COUNT);//扫雷
	}
	else if (COUNT == 15){
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//显示雷,给玩家看
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//初始化棋盘
		Putmine(mine, ROW - 2, COL - 2, COUNT);//埋雷
		//DisplayBoard(mine, ROW - 2, COL - 2);
		DisplayBoard(show, ROW - 2, COL - 2);//打印棋盘
		Findmine(mine, show, ROW - 2, COL - 2, COUNT);//扫雷
	}
	else{
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//显示雷,给玩家看
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//初始化棋盘
		Putmine(mine, ROW, COL, COUNT);//埋雷
		//DisplayBoard(mine, ROW, COL);
		DisplayBoard(show, ROW, COL);//打印棋盘
		Findmine(mine, show, ROW , COL, COUNT);//扫雷
	}
}
void test(){
	srand((unsigned int)time(0));//随机种子
	int input = 0;
	int input2 = 0;
	int COUNT = 0;
	do{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		system("cls");
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
			system("cls");
			game(COUNT);
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