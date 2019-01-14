#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set){
	memset(board, set, rows*cols*sizeof(board[0][0]));
}
void DisplayBoard(char board[ROWS][COLS], int row, int col){
	int i, j = 0;
	if (row == ROW - 6){
		printf("------------------------------\n");
	}
	if (row == ROW - 2){
		printf("-----------------------------------------\n");
	}
	if (row == ROW){
		printf("----------------------------------------------\n");
	}
	for (i = 0; i <= row; i++){
		for (j = 0; j <= col; j++){
			if (i == 0 || j == 0){
				if (j == 0){
					if (i < 10){
						printf("%d  ", i);
					}
					else{
						printf("%d ", i);
					}
				}
				else{
					if (j < 10){
						printf("%d  ", j);
					}
					else{
						printf("%d ", j);
					}
				}
			}
			else{
				printf("%c  ", board[i][j]);
			}
		}
		printf("\n");
	}
	if (row == ROW - 6){
		printf("------------------------------\n");
	}
	if (row == ROW - 2){
		printf("-----------------------------------------\n");
	}
	if (row == ROW){
		printf("----------------------------------------------\n");
	}
}
void Putmine(char board[ROWS][COLS], int row, int col, int count){
	int c = 0;//��õ��׵ĸ���
	int i = 0;
	int j = 0;
	do{
		i = rand() % row + 1;
		j = rand() % col + 1;
		if (board[i][j] =='0'){//��֤�׵ĸ���Ϊ count��
			board[i][j] = '1';
			c++;
		}	
	} while (count-c);
}
/*ͳ���׵ĸ���*/
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
void ExpansionMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j, int row, int col){
	if (MineCount(mine, i, j) == 0){
		show[i][j] = ' ';
		//�ٴα�����Χ����
		if (i - 1 > 0 && show[i - 1][j] == '*'){
		//	printf("1\n");
			ExpansionMine(mine, show, i - 1, j, row, col);//�ݹ�
		}
		if (i - 1 > 0 && j + 1 <= col && show[i - 1][j + 1] == '*'){
			ExpansionMine(mine, show, i - 1, j + 1, row, col);
		}
		if (j + 1 <= col && show[i][j + 1] == '*'){
			ExpansionMine(mine, show, i, j + 1, row, col);
		}
		if (i + 1 <= row && j + 1 <= col && show[i + 1][j + 1] == '*'){
			ExpansionMine(mine, show, i + 1, j + 1, row, col);
		}
		if (i + 1 <= row && show[i + 1][j] == '*'){
			ExpansionMine(mine, show, i + 1, j, row, col);
		}
		if (i + 1 <= row && j - 1 >0 && show[i + 1][j - 1] == '*'){
			ExpansionMine(mine, show, i + 1, j - 1, row, col);
		}
		if (j - 1 > 0 && show[i][j - 1] == '*'){
			ExpansionMine(mine, show, i, j - 1, row, col);
		}
		if (i - 1 > 0 && j - 1 > 0 && show[i - 1][j + 1] == '*'){
			ExpansionMine(mine, show, i - 1, j + 1, row, col);
		}
	}
	else{//�ܱ�����
		show[i][j] = MineCount(mine, i, j) + '0';
	}
}
void menu3(){
	printf("********   1.���    2.�Ų�   ********\n");
	printf("��ѡ��:>");
}
void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int count){
	int i, j;//��������
	int playcount = 0;//������׵Ĵ���
	int remine = 0;//�ѱ�ǵĻ�û���Ų�����ꣻ
	while (remine!=count){
		//printf("%d", remine);
		int input = 0;
		printf("***** 1.���  2.ȡ�����  3.�Ų� *****\n");
		printf("��ѡ��:>");
		scanf("%d", &input);
		if (input == 1){
			printf("������Ҫ��ǵ����꣨�磺a b��:>");
			scanf("%d %d", &i, &j);
			if (i >= 1 && i <= row && j >= 1 && j <= col){
				if (show[i][j] == '*'){
					show[i][j] = 'P';
					system("cls");
					DisplayBoard(show, row, col);
				}
				else if (show[i][j] == 'P'){
					printf("�������ѱ���ǹ������������룡\n");
				}
				else{
					printf("�������ѱ��Ų�������������룡\n");
				}
			}

			else{
				printf("���������������������룡\n");
			}
		}
		else if (input == 2){
			printf("������Ҫȡ����ǵ����꣨�磺a b��:>");
			scanf("%d %d", &i, &j);
			if (i >= 1 && i <= row && j >= 1 && j <= col){
				if (show[i][j] == 'P'){
					show[i][j] = '*';
					system("cls");
					DisplayBoard(show, row, col);
				}
				else if (show[i][j] == '*'){
					printf("�����껹û�б���ǹ������������룡\n");
				}
				else{
					printf("�������ѱ��Ų�������������룡\n");
				}
			}

			else{
				printf("���������������������룡\n");
			}
		}
		else if (input == 3){
			//printf("%d", remine);
			printf("������Ҫ�Ų�����꣨�磺a b��:>");
			scanf("%d%d", &i, &j);
			if (i >= 1 && i <= row && j >= 1 && j <= col){
				if (show[i][j] == '*'){
					if (mine[i][j] == '1'){
						if (playcount == 0){//��ʱ˵������״������Ҳȵ�����
							mine[i][j] = '0';
							Putmine(mine, row, col, 1);//���·��ף���֤����ڵ�һ�Ѳ�����
							playcount = 1;
							ExpansionMine(mine, show, i, j, row, col);//��չ�ܱߵ���
							DisplayBoard(show, row, col);
						}
						else{
							printf("���ź����㱻ը���ˣ�\n");
							printf("���󲼾����£�\n");
							DisplayBoard(mine, row, col);
							break;
						}
					}
					else{
						ExpansionMine(mine, show, i, j, row, col);//��չ�ܱߵ���
						system("cls");
						//DisplayBoard(mine, row, col);
						DisplayBoard(show, row, col);
						playcount = 1;
					}
				}
				else if (show[i][j] == 'P'){
					printf("�������ѱ���ǹ������������룡\n");
				}
				else{
					printf("�������ѱ��Ų�������������룡\n");
				}
			}
			else{
				printf("���������������������룡\n");
			}
		}
		else{
			printf("�����������������룡\n");
		}
		remine = 0;//����ͳ�ƣ�
		for (int m = 1; m <= row; m++){
			for (int n = 1; n <= col; n++){
				if ((show[m][n] == '*' )||( show[m][n] == 'P')){
					remine++;
				}
			}
		}
	}
	//printf("%d", remine);
	if (remine == count){
		printf("��ϲ��,���׳ɹ���\n");
		printf("���󲼾����£�\n");
		DisplayBoard(mine, row, col);
	}

}