#ifndef _GAME_H_
#define _GAME_H

#define EASY_COUNT 10 //简单级，10个雷
#define USUAL_COUNT 20 //普通级，20个雷
#define HARD_COUNT 25 //简单级，30个雷


#define ROW 9 //显示9行
#define COL 9 //显示9列

#define ROWS ROW+2
#define COLS COL+2

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);//初始化棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col);//打印棋盘
void Putmine(char board[ROWS][COLS], int row, int col, int count);//埋雷
void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col,int count);//扫雷

#endif

