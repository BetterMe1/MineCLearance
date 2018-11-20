#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set){
	memset(board, set, rows*cols*sizeof(board[0][0]));
}
void DisplayBoard(char board[ROWS][COLS], int row, int col){
	int i, j = 0;
	printf("------------------------\n");
	for (i = 0; i <= row; i++){
		for (j = 0; j <= col; j++){
			if (i == 0 || j == 0){
				if (j == 0){
						printf("%d ", i);
					}
				else{
					printf("%d ", j);
				}
			}
			else{
				printf("%c ", board[i][j]);
			}
		}
		printf("\n");
	}
	printf("------------------------\n");
}
void Putmine(char board[ROWS][COLS], int row, int col, int count){
	int c = 0;//埋好的雷的个数
	int i = 0;
	int j = 0;
	do{
		i = rand() % row + 1;
		j = rand() % col + 1;
		if (board[i][j] =='0'){//保证雷的个数为 count个
			board[i][j] = '1';
			c++;
		}	
	} while (count-c);
}
/*统计雷的个数*/
int MineCount(char mine[ROWS][COLS], int i, int j){
	return (mine[i - 1][j] +
		mine[i - 1][j + 1] +
		mine[i][j + 1] +
		mine[i + 1][j + 1] +
		mine[i + 1][j] +
		mine[i + 1][j - 1] +
		mine[i][j - 1] +
		mine[i - 1][j - 1]) - 8 * '0';
}
void ExpansionMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j){
	if (MineCount(mine, i, j) == 0){
		show[i][j] = ' ';
		//再次遍历周围的雷
		if ((i - 1) > 0 && show[i - 1][j] == '*'){
		//	printf("1\n");
			ExpansionMine(mine, show, i-1,j);//递归
		}
		if (i - 1 > 0 && j + 1 <= COL && show[i - 1][j + 1] == '*'){
			ExpansionMine(mine, show, i - 1, j+1);
		}
		if (j + 1 <= 9 && show[i][j + 1] == '*'){
			ExpansionMine(mine, show, i, j + 1);
		}
		if (i + 1 <= 9 && j + 1 <= 9 && show[i + 1][j + 1] == '*'){
			ExpansionMine(mine, show, i + 1, j + 1);
		}
		if (i + 1 <= 9 && show[i + 1][j] == '*'){
			ExpansionMine(mine, show, i + 1, j);
		}
		if (i + 1 <= 9 && j - 1 >0 && show[i + 1][j - 1] == '*'){
			ExpansionMine(mine, show, i + 1, j - 1);
		}
		if (j - 1 > 0 && show[i][j - 1] == '*'){
			ExpansionMine(mine, show, i, j - 1);
		}
		if (i - 1 > 0 && j - 1 > 0 && show[i - 1][j + 1] == '*'){
			ExpansionMine(mine, show, i - 1, j + 1);
		}
	}
	else{//周边有雷
		show[i][j] = MineCount(mine, i, j) + '0';
	}
}
void menu3(){
	printf("********   1.标记    2.排查   ********\n");
	printf("请选择:>");
}
void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int count){
	int i, j;//行列坐标
	int playcount = 0;//玩家排雷的次数
	int remine = 0;//已标记的或没有排查的坐标；
	while (remine!=EASY_COUNT){
		//printf("%d", remine);
		int input = 0;
		printf("***** 1.标记  2.取消标记  3.排查 *****\n");
		printf("请选择:>");
		scanf("%d", &input);
		if (input == 1){
			printf("请输入要标记的坐标（如：a,b）:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == '*'){
					show[i][j] = 'P';
					DisplayBoard(show, ROW, COL);
				}
				else if (show[i][j] == 'P'){
					printf("此坐标已被标记过，请重新输入！\n");
				}
				else{
					printf("此坐标已被排查过，请重新输入！\n");
				}
			}

			else{
				printf("坐标输入有误，请重新输入！\n");
			}
		}
		else if (input == 2){
			printf("请输入要取消标记的坐标（如：a,b）:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == 'P'){
					show[i][j] = '*';
					DisplayBoard(show, ROW, COL);
				}
				else if (show[i][j] == '*'){
					printf("此坐标还没有被标记过，请重新输入！\n");
				}
				else{
					printf("此坐标已被排查过，请重新输入！\n");
				}
			}

			else{
				printf("坐标输入有误，请重新输入！\n");
			}
		}
		else if (input == 3){
			//printf("%d", remine);
			printf("请输入要排查的坐标（如：a,b）:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == '*'){
					if (mine[i][j] == '1'){
						if (playcount == 0){//此时说明玩家首次排雷且踩到雷了
							mine[i][j] = '0';
							Putmine(mine, ROW, COL, 1);//重新放雷，保证玩家在第一把不踩雷
							playcount = 1;
							ExpansionMine(mine, show, i, j);//扩展周边的雷
							DisplayBoard(show, ROW, COL);
						}
						else{
							printf("很遗憾，你被炸死了！\n");
							printf("雷阵布局如下：\n");
							DisplayBoard(mine, ROW, COL);
							break;
						}
					}
					else{
						ExpansionMine(mine, show, i, j);//扩展周边的雷
						//DisplayBoard(mine, ROW, COL);
						DisplayBoard(show, ROW, COL);
						playcount = 1;
					}
				}
				else if (show[i][j] == 'P'){
					printf("此坐标已被标记过，请重新输入！\n");
				}
				else{
					printf("此坐标已被排查过，请重新输入！\n");
				}
			}
			else{
				printf("坐标输入有误，请重新输入！\n");
			}
		}
		else{
			printf("输入有误，请重新输入！\n");
		}
		remine = 0;//重新统计；
		for (int m = 1; m <= row; m++){
			for (int n = 1; n <= col; n++){
				if ((show[m][n] == '*' )||( show[m][n] == 'P')){
					remine++;
				}
			}
		}
	}
	//printf("%d", remine);
	if (remine == EASY_COUNT){
		printf("恭喜您,排雷成功！\n");
		printf("雷阵布局如下：\n");
		DisplayBoard(mine, ROW, COL);
	}

}