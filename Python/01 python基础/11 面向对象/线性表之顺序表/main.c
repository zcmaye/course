/*用来测试顺序表*/
#define _CRT_SECURE_NO_WARNINGS
#include"SeqList.h"
void menu()
{
	printf("*********************************\n");
	printf("* [1]push_back   [2]push_front  *\n");
	printf("* [3]show_list   [4]insert      *\n");
	printf("* [5]pop_back    [6]pop_front   *\n");
	printf("* [7]erase_pos   [8]erase_val   *\n");
	printf("* [9]find        [10]size       *\n");
	printf("* [11]sort       [12]reverse    *\n");
	printf("* [13]clear      [14]quit       *\n");
	printf("* [15]cls                       *\n");
	printf("*********************************\n");
}
int main()
{
	SeqList list;
	initList(&list);
	menu();
	int select = -1,item=-1;
	int index = -1;
	while (1)
	{
		printf("select>");
		scanf_s("%d", &select);
		switch (select)
		{
		case 1:
			printf("请输入要插入的元素:");
			while (scanf_s("%d", &item),item != -1)
			{
				push_back(&list, item);
			};
			break;
		case 2:
			printf("请输入要插入的元素:");
			while (scanf_s("%d", &item), item != -1)
			{
				push_front(&list, item);
			};
			break;
		case 3:
			printf("DATA:");
			show_list(&list);
			break;
		case 4:
			printf("请输入插入的下标和数据:");
			scanf_s("%d %d",&index, &item);
			insert(&list,index , item);
			break;
		case 5:
			pop_back(&list);
			printf("尾部删除成功...\n");
			break;
		case 6:
			pop_front(&list);
			printf("头部删除成功...\n");
			break;
		case 7:
			printf("请输入要删除的下标:");
			scanf_s("%d", &index);
			erase_pos(&list,index);
			printf("指定下标删除成功...\n");
			break;
		case 8:
			printf("请输入要删除的元素:");
			scanf_s("%d", &item);
			erase_val(&list,item);
			printf("头部删除成功...\n");
			break;
		case 9:
			printf("请输入要查找的元素:");
			scanf_s("%d", &item);
			int ret = find(&list, item);
			if (ret == -1)
			{
				printf("没有找到%d\n", item);
			}
			else
			{
				printf("找到了%d，下标为%d\n", item,ret);
			}
			break;
		case 10:
			printf("size:%d", size(&list));
			break;
		case 11:
			sort(&list);
			break;
		case 12:
			reverse(&list);
			break;
		case 13:
			clear(&list);
			break;
		case 14:
			exit(0);
		case 15:
			system("cls");
			menu();
			break;
		}
	}

	return 0;
}