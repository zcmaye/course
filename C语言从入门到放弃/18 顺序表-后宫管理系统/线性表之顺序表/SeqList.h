#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<stdbool.h>
#define INC_SIZE 3	//ÿ�����ݴ�С
#define INIT_SEQLIST_SIZE 8	//˳���ĳ�ʼ��С
/*********�Զ�����������**********/
typedef struct _Harem
{
	int id;
	char name[50];
}Harem;
//typedef Harem Data;
/********************************/
typedef int Data;	//�������������
typedef struct
{
	Data* base;		//ָ���׵�ַ��ָ��
	int capacity;	//������������
	int size;		//��ǰԪ������
}SeqList;

bool inc(SeqList* list);	//����
void initList(SeqList* list);
void push_back(SeqList* list, Data data);
void push_front(SeqList* list, Data data);
void insert(SeqList* list, int index, Data data);
void show_list(SeqList* list);
//void show_harem(SeqList* list);

void pop_back(SeqList* list);
void pop_front(SeqList* list);
void erase_pos(SeqList* list, int pos);
void erase_val(SeqList* list, Data val);

int size(SeqList* list);
bool empty(SeqList* list);
int find(SeqList* list, Data val);
void sort(SeqList* list);
void reverse(SeqList* list);
void clear(SeqList* list);


#endif // !_SEQLIST_H_
