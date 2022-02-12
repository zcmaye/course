/*��������˳���*/
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
			printf("������Ҫ�����Ԫ��:");
			while (scanf_s("%d", &item),item != -1)
			{
				push_back(&list, item);
			};
			break;
		case 2:
			printf("������Ҫ�����Ԫ��:");
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
			printf("�����������±������:");
			scanf_s("%d %d",&index, &item);
			insert(&list,index , item);
			break;
		case 5:
			pop_back(&list);
			printf("β��ɾ���ɹ�...\n");
			break;
		case 6:
			pop_front(&list);
			printf("ͷ��ɾ���ɹ�...\n");
			break;
		case 7:
			printf("������Ҫɾ�����±�:");
			scanf_s("%d", &index);
			erase_pos(&list,index);
			printf("ָ���±�ɾ���ɹ�...\n");
			break;
		case 8:
			printf("������Ҫɾ����Ԫ��:");
			scanf_s("%d", &item);
			erase_val(&list,item);
			printf("ͷ��ɾ���ɹ�...\n");
			break;
		case 9:
			printf("������Ҫ���ҵ�Ԫ��:");
			scanf_s("%d", &item);
			int ret = find(&list, item);
			if (ret == -1)
			{
				printf("û���ҵ�%d\n", item);
			}
			else
			{
				printf("�ҵ���%d���±�Ϊ%d\n", item,ret);
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