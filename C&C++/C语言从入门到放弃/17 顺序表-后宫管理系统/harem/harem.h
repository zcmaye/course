#pragma once
#include<stdio.h>
struct Size    //��Χ�ߴ�
{   
	int bust;	//��Χ
	int hip;	//��Χ
	int waist;	//��Χ
};
//��������ɶ������
typedef struct _Harem
{
	int id;				//���ӵ�����
	int age;
	char name[20];		//����
	struct Size size;
}Harem;


//�鿴��������
void show(Harem harem[],int num);
//�������
void push_back(Harem harem[], int *num);
//ɾ������
void pop_back(Harem harem[], int* num);
//ɾ��ָ���ı�ŵ�����
int earse(Harem harem[], int* num,int id);
//����ָ��id������
int search(Harem harem[], int* num, int id);
//�޸�ָ��id��������Ϣ
void modify(Harem harem[], int* num, int id);
//����id����
void sort(Harem harem[], int* num);
//��ȡ�ļ�
int readFile(Harem harem[], int* num);
//д���ļ�
int saveFile(Harem harem[], int* num);
