/*
	�γ����ݣ��󹬹���ϵͳ
	֪ʶ�㣺�ṹ�����飬����
*/
#include"harem.h"
#include<stdlib.h>
#define MAXSIZE 20  //������ж��ٸ�����
enum Select   //�û���ѡ���ж�
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
	printf("************�󹬹���ϵͳ*****************\n");
	printf("          0,�˳�ϵͳ\n");
	printf("          1,�鿴���е�����\n");
	printf("          2,�������\n");
	printf("          3,ɾ������\n");
	printf("          4,��������\n");
	printf("          5,�޸�����\n");
	printf("          6,����\n");
	printf("          7,����\n");	//����id����
	printf("          8,�����ļ�\n");	//����id����
	
	
}
int main()
{
	Harem harem[MAXSIZE] = { 1001,18,"����Ů",{56,55,40} };
	int curSize = 1;	//��ǰ�ж��ٸ�����
	menu();
	readFile(harem, &curSize);
	while (1)
	{
		printf("��ѡ��>");
		int select = -1, id = -1, res = -1;
		scanf_s("%d", &select);
		switch (select)
		{
		case EXIT:
			exit(66);			//66�����д��
			break;
		case SEE:
			show(harem, curSize);
			break;
		case ADD:
			push_back(harem, &curSize);
			break;
		case DEL:
			//pop_back(harem, &curSize);
			printf("������Ҫɾ����id>");
			scanf_s("%d", &id);
			res = earse(harem, &curSize, id);
			if (res != -1)
			{
				printf("ɾ��id��%d�ɹ�\n", id);
			}
			break;
		case SEARCH:
			printf("������Ҫ���ҵ�id>");			
			scanf_s("%d", &id);
			res = search(harem, &curSize,id);
			if (res != -1)
			{
				//printf("�ҵ���idΪ%d������,�±�Ϊ%d\n", id,res);
				printf("%d %d %s [%d %d %d]\n", harem[res].id, harem[res].age, harem[res].name, harem[res].size.bust,
					harem[res].size.hip, harem[res].size.waist);
			}
			else
			{
				printf("û��idΪ%d������\n", id);
			}
			break;
		case MODIFY:
			printf("������Ҫ�޸ĵ�id>");
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