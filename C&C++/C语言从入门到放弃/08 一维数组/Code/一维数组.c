#include<stdio.h>
#include<stdbool.h>
/*
	���飺��ͬ�������͵ļ��ϣ�ÿ��Ԫ�صĵ�ַ���������ģ������±�(����)�Ǵ�0��ʼ�ģ����С��������Ĵ�С��1
	����Ķ��壺�������� ������[size]={��ʼֵ};	��ͨ��������������  ������ = ��ʼֵ��
			
*/
int main����Ķ���ͳ�ʼ��()
{
	//int ages[5];		//���û�г�ʼ��,ֵ��������ֵ
	//int ages[5] = 0;	//error C2075: ��ages��: ��ʼ����Ҫ�����ŵĳ�ʼֵ�趨���б�
	//int ages[5] = {2,3,4};	//�ۺϳ�ʼ����ʽ,���ָ����һ������Ԫ�أ�����δָ����Ԫ�أ��Զ���ʼ��Ϊ0
	//int ages[5] = { 0 };	//��ʼ��ֻ�ܴ��������γ�ʼ������������ĳ��Ԫ��
	//ages[4] = 6;			//���������±�Ϊ���������-1
	//int ages[5] = { 1,2,3,4,5,6 };	//error C2078: ��ʼֵ�趨��̫��

	int ages[] = { 1,2,3,4,5,6,7,8,9};
	//�������Ԫ�ظ���
	int len = sizeof(ages)/sizeof(ages[0]);	
	printf("%d\n", len);

	//�±�Խ�����ô����żȻ����ȷ���ȱ�Ȼ�Ĵ��������~
	//printf("%d %d\n", ages[-1],ages[1000000]);

	
	//������������Ԫ���أ�
	//printf("%d\n", ages[0]);	//���һ��Ԫ�ص�ֵ
	for (int i = 0; i < len; i++)
	{
		printf("%d ", ages[i]);
	}
	



	return 0;
}
int main()
{
	//����һ������
	int datas[10] = { 1,2,3 };
	int maxSize = sizeof(datas)/sizeof(datas[0]);	//�������Ԫ�ظ���
	int curSize = 3;								//���鵱ǰ��ЧԪ�ظ���

	int pos = -1;		//Ҫ�������ɾ����λ��(�±�)
	int data = -1;		//Ҫ�������ɾ����Ԫ��

	while (true)
	{
		printf("*****�˵�*******\n");
		printf("*****0,�鿴*******\n");
		printf("*****1,���*****\n");
		printf("*****2,ɾ��*****\n");

		int choose = -1;
		printf("��ѡ�����>");
		scanf_s("%d", &choose);

		switch (choose)
		{
		case 0:
			//���Ԫ��
			for (int i = 0; i < curSize; i++)
			{
				printf("%d ", datas[i]);
			}
			printf("\n");
			break;
		case 1:
			printf("������Ҫ�����pos��data:");
			scanf_s("%d %d", &pos, &data);

			//��datas�����ˣ���Ͳ��ܼ���������
			if (curSize == maxSize)
			{
				printf("datas�������޷���������~\n");
			}
			else
			{
				//�ݴ���������
				if (pos > curSize || pos < 0)
				{
					pos = curSize;
				}
				//��posλ�õ�Ԫ����������ƶ�һλ
				for (int i = curSize; i > pos; i--)
				{
					datas[i] = datas[i - 1];
				}

				//����Ԫ�أ����ı�curSize
				datas[pos] = data;
				curSize++;
			}
			break;
		case 2:
			printf("������Ҫɾ����pos>");
			scanf_s("%d", &pos);

			if (curSize == 0)
			{
				printf("datasΪ�գ�����ɾ��\n");
			}
			else
			{
				if (pos < 0 || pos >= curSize)
				{
					printf("pos���Ϸ����޷�ɾ��\n");
				}
				else
				{
					for (int i = pos; i < curSize-1; i++)
					{
						datas[i] = datas[i + 1];	//curSize = 10   i>9   i+1>10
					}
					curSize--;
				}
			}

			break;
		}

	}


	
	


	                   
	return 0;
}