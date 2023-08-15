/*
	课程内容：后宫管理系统
	知识点：结构体数组，函数
*/
#include"harem.h"
#include<stdlib.h>
#define MAXSIZE 20  //最多能有多少个妃子
enum Select   //用户的选择判断
{
	EXIT,
	SEE,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	CLS,
	SORT,
	SAVE
};
void menu()
{
	printf("************后宫管理系统*****************\n");
	printf("          0,退出系统\n");
	printf("          1,查看所有的妃子\n");
	printf("          2,添加妃子\n");
	printf("          3,删除妃子\n");
	printf("          4,查找妃子\n");
	printf("          5,修改妃子\n");
	printf("          6,清屏\n");
	printf("          7,排序\n");	//按照id排序
	printf("          8,保存文件\n");	//按照id排序
	
	
}
int main()
{
	Harem harem[MAXSIZE] = { 1001,18,"七仙女",{56,55,40} };
	int curSize = 1;	//当前有多少个妃子
	menu();
	readFile(harem, &curSize);
	while (1)
	{
		printf("请选择>");
		int select = -1, id = -1, res = -1;
		scanf_s("%d", &select);
		switch (select)
		{
		case EXIT:
			exit(66);			//66是随便写的
			break;
		case SEE:
			show(harem, curSize);
			break;
		case ADD:
			push_back(harem, &curSize);
			break;
		case DEL:
			//pop_back(harem, &curSize);
			printf("请输入要删除的id>");
			scanf_s("%d", &id);
			res = earse(harem, &curSize, id);
			if (res != -1)
			{
				printf("删除id：%d成功\n", id);
			}
			break;
		case SEARCH:
			printf("请输入要查找的id>");			
			scanf_s("%d", &id);
			res = search(harem, &curSize,id);
			if (res != -1)
			{
				//printf("找到了id为%d的妃子,下标为%d\n", id,res);
				printf("%d %d %s [%d %d %d]\n", harem[res].id, harem[res].age, harem[res].name, harem[res].size.bust,
					harem[res].size.hip, harem[res].size.waist);
			}
			else
			{
				printf("没有id为%d的妃子\n", id);
			}
			break;
		case MODIFY:
			printf("请输入要修改的id>");
			scanf_s("%d", &id);
			modify(harem, &curSize, id);
			break;
		case CLS:
			system("cls");
			menu();
			break;
		case SORT:
			
			sort(harem, &curSize);
			break;
		case SAVE:
			saveFile(harem, &curSize);
			break;
			
		}
	}
	return 0;
}