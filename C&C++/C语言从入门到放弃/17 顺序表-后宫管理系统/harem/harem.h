#pragma once
#include<stdio.h>
struct Size    //三围尺寸
{   
	int bust;	//胸围
	int hip;	//臀围
	int waist;	//腰围
};
//后宫里面有啥，妃子
typedef struct _Harem
{
	int id;				//妃子的排名
	int age;
	char name[20];		//姓名
	struct Size size;
}Harem;


//查看所有妃子
void show(Harem harem[],int num);
//添加妃子
void push_back(Harem harem[], int *num);
//删除妃子
void pop_back(Harem harem[], int* num);
//删除指定的编号的妃子
int earse(Harem harem[], int* num,int id);
//查找指定id的妃子
int search(Harem harem[], int* num, int id);
//修改指定id的妃子信息
void modify(Harem harem[], int* num, int id);
//按照id排序
void sort(Harem harem[], int* num);
//读取文件
int readFile(Harem harem[], int* num);
//写入文件
int saveFile(Harem harem[], int* num);
