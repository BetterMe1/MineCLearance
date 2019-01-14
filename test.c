/*
date��2018/11/17
author:BetterMe1
program:Mine Clearance
compiler:Visual Studio 2013
��չ����:
1.������Ϸ�Ѷȵȼ�
2.��֤����ڵ�һ�Ѳ��׺󲻱�ը��
3.�����׵ĵط����ף��Զ���չ�����׵���Χ������������
4.���(�൱��ɨ����Ϸ�еĲ����ӣ�
5.ȡ�����
*/

/*
������
1.�ö�ά�ַ�����mine[ROWS][COLS]���洢��,�����������ַ�1����ʾ���ף��ַ�0��ʾ���ס�
�ö�ά�ַ�����show[ROWS][COLS]�����е�Ԫ�س�ʼ��Ϊ*������ӡ��Ϊչ�ָ���ҵġ�
ͬʱ��show��������ʾ��Ӧ��mine��������Χ�׼��ַ�0�ĸ�����
���ڱ�Ե�ĸ����޷������׵ĸ����������������2��2�У���ֹ����Խ�硣
2.��Ϸ�Ѷȵȼ������ü������׵ĸ��������̴�С��ͬ��������Putmine�д���COUNT(��������ͬ��
���̴�С��ͬҲ�����ڳ�ʼ�������ס�ɨ�ס���ӡ���̵Ⱥ����д����С�������ͬ��
�����ǿ���̨����û�н�һ��ģʽ������ģʽ�����̴�ӡ�Ĺ�����Ϊ���Ҳ�����ۻ��������������ɨ�׵��м�ģʽ��40���ף�16*16��
�߼�ģʽ��99���ף�16*30��.
3.Ϊ�˱�֤������飬��֤����ڵ�һ�Ѳ��׺󲻱�ը������ʱֻ��Ҫ�ж���ҵ�һ���Ų�������Ƿ�����׵����꣬����ǣ������������ߣ����������������
4.�����׵ĵط����ף��Զ���չ�����׵���Χ����������������ʱ��Ҫ�õ��ݹ飬ֱ���ݹ鵽��Χ����ֹͣ����������������ʾ�������ϡ�
5.�����ȡ���������Ǻ�����ʵ�ֵģ������λ�ø�ΪP��Ҳ����Ϊ��������ȡ����ǸĻ�*���ɡ�
*/
/*���Բ���*/
#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include <stdio.h>
#include <stdlib.h>


void menu(){
	printf("************  ɨ��С��Ϸ  ************\n");
	printf("******  1.������Ϸ  2.�˳���Ϸ  ******\n");
	printf("**************************************\n");
}
void menu2(){
	printf("********  ��ѡ��Ҫ��ս��ģʽ  ********\n");
	printf("********  1.��ģʽ��10���ף�********\n");
	printf("********  2.һ��ģʽ��15���ף�********\n");
	printf("********  3.����ģʽ��20���ף�********\n");
}
void game(int COUNT ){
	if (COUNT == 10){
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//��ʾ��,����ҿ�
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//��ʼ������
		Putmine(mine, ROW-6, COL-6, COUNT);//����
		//DisplayBoard(mine, ROW - 6, COL - 6);
		DisplayBoard(show, ROW-6, COL-6);//��ӡ����
		Findmine(mine, show, ROW-6, COL-6, COUNT);//ɨ��
	}
	else if (COUNT == 15){
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//��ʾ��,����ҿ�
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//��ʼ������
		Putmine(mine, ROW - 2, COL - 2, COUNT);//����
		//DisplayBoard(mine, ROW - 2, COL - 2);
		DisplayBoard(show, ROW - 2, COL - 2);//��ӡ����
		Findmine(mine, show, ROW - 2, COL - 2, COUNT);//ɨ��
	}
	else{
		char mine[ROWS][COLS] = { 0 };
		char show[ROWS][COLS] = { 0 };//��ʾ��,����ҿ�
		InitBoard(mine, ROWS, COLS, '0');
		InitBoard(show, ROWS, COLS, '*');//��ʼ������
		Putmine(mine, ROW, COL, COUNT);//����
		//DisplayBoard(mine, ROW, COL);
		DisplayBoard(show, ROW, COL);//��ӡ����
		Findmine(mine, show, ROW , COL, COUNT);//ɨ��
	}
}
void test(){
	srand((unsigned int)time(0));//�������
	int input = 0;
	int input2 = 0;
	int COUNT = 0;
	do{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		system("cls");
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
			system("cls");
			game(COUNT);
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