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
void ExpansionMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j){
	if (MineCount(mine, i, j) == 0){
		show[i][j] = ' ';
		//�ٴα�����Χ����
		if ((i - 1) > 0 && show[i - 1][j] == '*'){
		//	printf("1\n");
			ExpansionMine(mine, show, i-1,j);//�ݹ�
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
	while (remine!=EASY_COUNT){
		//printf("%d", remine);
		int input = 0;
		printf("***** 1.���  2.ȡ�����  3.�Ų� *****\n");
		printf("��ѡ��:>");
		scanf("%d", &input);
		if (input == 1){
			printf("������Ҫ��ǵ����꣨�磺a,b��:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == '*'){
					show[i][j] = 'P';
					DisplayBoard(show, ROW, COL);
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
			printf("������Ҫȡ����ǵ����꣨�磺a,b��:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == 'P'){
					show[i][j] = '*';
					DisplayBoard(show, ROW, COL);
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
			printf("������Ҫ�Ų�����꣨�磺a,b��:>");
			scanf("%d,%d", &i, &j);
			if (i >= 1 && i <= 9 && j >= 1 && j <= 9){
				if (show[i][j] == '*'){
					if (mine[i][j] == '1'){
						if (playcount == 0){//��ʱ˵������״������Ҳȵ�����
							mine[i][j] = '0';
							Putmine(mine, ROW, COL, 1);//���·��ף���֤����ڵ�һ�Ѳ�����
							playcount = 1;
							ExpansionMine(mine, show, i, j);//��չ�ܱߵ���
							DisplayBoard(show, ROW, COL);
						}
						else{
							printf("���ź����㱻ը���ˣ�\n");
							printf("���󲼾����£�\n");
							DisplayBoard(mine, ROW, COL);
							break;
						}
					}
					else{
						ExpansionMine(mine, show, i, j);//��չ�ܱߵ���
						//DisplayBoard(mine, ROW, COL);
						DisplayBoard(show, ROW, COL);
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
	if (remine == EASY_COUNT){
		printf("��ϲ��,���׳ɹ���\n");
		printf("���󲼾����£�\n");
		DisplayBoard(mine, ROW, COL);
	}

}