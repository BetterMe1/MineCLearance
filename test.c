/*
date��2018/11/17
author:BetterMe1
program:Mine Clearance
compiler:Visual Studio 2013
��չ����:1.������Ϸ�Ѷȵȼ�
2.��֤����ڵ�һ�Ѳ��׺󲻱�ը��
3.�����׵ĵط����ף��Զ���չ�����׵���Χ������������
4.���
5.ȡ�����
*/

/*���Բ���*/
#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int COUNT = 0;

void menu(){
	printf("************  ɨ��С��Ϸ  ************\n");
	printf("******  1.������Ϸ  2.�˳���Ϸ  ******\n");
	printf("**************************************\n");
}
void menu2(){
	printf("********  ��ѡ��Ҫ��ս��ģʽ  ********\n");
	printf("********  1.��ģʽ��10���ף�********\n");
	printf("********  2.һ��ģʽ��20���ף�********\n");
	printf("********  3.����ģʽ��25���ף�********\n");
}
void game(){
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };//��ʾ��,����ҿ�
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');//��ʼ������
	Putmine(mine, ROW, COL,COUNT);//����
	DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);//��ӡ����
	Findmine(mine,show, ROW, COL, COUNT);//ɨ��
}
void test(){
	int input = 0;
	int input2 = 0;
	do{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input){
		case 1:
			while (1){
				menu2();
				printf("��ѡ��:>");
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
					printf("��������������ѡ��\n");
					break;
				}
				if (input2 >= 1 && input2 <= 3){
					break;
				}
			}
			game();
			break;
		case 2:
			printf("�˳���Ϸ��\n");
			break;
		default:
			printf("��������������ѡ��\n");
			break;
		}
	} while ((input - 2));
}
void main(){
	test();
	system("pause");
}