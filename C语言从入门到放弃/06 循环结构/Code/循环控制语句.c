#include<stdio.h>
#include<stdbool.h>

int main��ѭ��()
{
	//while (true)
	//{
	//	printf("ѧϰ\n");
	//}

	//do
	//{
	//	printf("�Է�\n");
	//} while (true);

	//for �������û��д����ôĬ��Ϊ�棬����Զִ�����ѭ����
	//��ѭ�����棬������Ҫ�޸�ѭ������
	//for (int i = 0;i<= 100;i++)
	//{
	//	printf("for %d\n",i);
	//	if (i > 50)
	//	{
	//		i = i - 20;
	//	}
	//}


	//��ʾ�û�����ɼ�������-1��������
	int score = 0;
	printf("����ɼ�>");
	while (score != -1)
	{		
		scanf("%d", &score);
		printf("%d ", score);
	}


	printf("\nmain");
	return 0;
}
int main11()
{
	//break ����ѭ��
	//�ҵ���һ����13�������� i%13 == 0
	//���� ����  ѭ��
	for (int i = 14;; i++)
	{
		if (i % 13 == 0)
		{
			printf("��һ����13����������:%d\n", i);
			//������Ӧ���������ѭ��������
			break;
		}
	}
	

	//continue ��������ѭ����ֱ�ӿ�ʼ��һ��ѭ��
	//while (true)
	//{
	//	printf("1\n");
	//	continue;
	//	printf("2\n");
	//	printf("3\n");
	//}
	
	for (int i = 0;; i++)
	{
		if (i > 100)
		{
			break;
		}
		if (i % 2 == 0)
		{
			continue;
		}

		//���������ż��
		printf("%d -> %d\n", i, i + 1);
	}
	int a = 2;
	printf("\nmain\n");


	return 0;
}
int main()
{
	bool flag = false;
	for (int i = 0; i < 5; i++)
	{	
		for (int k = 0; k < 5; k++)
		{
			printf("%d%d ", i,k);
			if (i == 2)
			{
				//goto endLoop;
				flag = true;
				break;
			}
		}
		if (flag)
		{
			break;
		}
		printf("\n");
	}
	//endLoop:

	return 0;
}