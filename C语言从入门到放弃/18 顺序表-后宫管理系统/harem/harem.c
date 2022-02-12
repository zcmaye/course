#include "harem.h"
void show(Harem harem[],int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%d %d %s [%d %d %d]\n", harem[i].id, harem[i].age, harem[i].name, harem[i].size.bust,
			harem[i].size.hip, harem[i].size.waist);
	}
}

void push_back(Harem harem[], int *num)
{
	Harem newH;
	printf("���������룺��� ���� ���� [��Χ]��");
	do {
		scanf_s("%d %d %s %d %d %d", &newH.id, &newH.age, newH.name,20, &newH.size.bust, &newH.size.hip, &newH.size.waist);
		harem[*num] = newH;	//���뵽��ǰcurSizeλ��
		(*num)++;			//����������1
	} while (newH.id != -1);


}

void pop_back(Harem harem[], int* num)
{
	(*num)--;
}

int earse(Harem harem[], int* num, int id)
{
	int index = search(harem, num, id);
	if (index == -1)
	{
		return -1;
	}
	//�ҵ���   *num -1��Ϊ�˷�ֹԽ��
	for (int i = index; i < *num -1; i++)	
	{
		harem[i] = harem[i + 1];	//�Ѻ����������ǰ�ƶ�
	}
	(*num)--;
	return index;
}

int search(Harem harem[], int* num, int id)
{
	for (int i = 0; i < *num; i++)
	{
		if (harem[i].id == id)
		{
			return i;
		}
	}
	return -1;
}

void modify(Harem harem[], int* num, int id)
{
	//�ж�id�Ƿ���ڣ����ھ��޸ģ������������
	int index = search(harem, num, id);
	if (index == -1)
	{
		//����
		harem[*num] = (Harem){ id };
		(*num)++;
	}
	else
	{
		//�޸�
		printf("0,�޸�������Ϣ\n");
		printf("1,id\n");
		printf("2,age\n");
		printf("3,name\n");
		printf("4,��Χ\n");
		printf("��ѡ��Ҫ�޸ĵ���Ϣ:");
		int select = -1;
		scanf_s("%d", &select);
		switch (select)
		{
		case 0:
			printf("���������룺��� ���� ���� [��Χ]��");
			scanf_s("%d %d %s %d %d %d", &harem[index].id, &harem[index].age, harem[index].name, 
				20, &harem[index].size.bust, &harem[index].size.hip, &harem[index].size.waist);
			break;
		case 1:
			printf("�������µ�ID>");
			scanf_s("%d", &harem[index].id);
			break;
		case 2:
			printf("�������µ�Age>");
			scanf_s("%d", &harem[index].age);
			break;
		case 3:
			printf("�������µ�Name>");
			scanf_s("%s", harem[index].name,20);
			break;
		case 4:
			printf("�������µ���Χ>");
			scanf_s("%d %d %d", &harem[index].size.bust, &harem[index].size.hip, &harem[index].size.waist);
			break;
		}

	}
}

void sort(Harem harem[], int* num)
{
	if (*num <= 1)	//û�л���ֻ��һ�����ݲ���Ҫ��
	{
		return;
	}
	for (int i = 0; i < *num-1; i++)
	{
		for (int k = 0; k < k-i-1; k++)
		{
			if (harem[k].id > harem[k+1].id)
			{
				Harem t = harem[k];
				harem[k] = harem[k + 1];
				harem[k + 1] = harem[k];
			}
		}
	}

}

int readFile(Harem harem[], int* num)
{
#if 1
	FILE* fp = fopen("harem.data", "rb");
	while (!feof(fp))
	{
		fread(harem+*num, sizeof(Harem), 1, fp);
		(*num)++;
	}
#else
	FILE* fp = fopen("harem.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%d\t%d\t%s\t%d\t%d\t%d\n", &harem[*num].id, &harem[*num].age, harem[*num].name,
					&harem[*num].size.bust, &harem[*num].size.hip, &harem[*num].size.waist);
		(*num)++;
	}
#endif
	fclose(fp);
	return 0;
}

int saveFile(Harem harem[], int* num)
{
#if 1
	FILE* fp = fopen("harem.data", "wb");
	fwrite(harem, sizeof(Harem), *num, fp);
#else
	FILE* fp = fopen("harem.txt", "w");
	for (int i = 0; i < *num; i++)
	{
		fprintf(fp, "%d\t%d\t%s\t%d\t%d\t%d\n", harem[i].id, harem[i].age, harem[i].name,
			harem[i].size.bust, harem[i].size.hip, harem[i].size.waist);
	}
#endif
	fclose(fp);
	return 0;
}
