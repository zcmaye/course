#include<stdio.h>
/*
	while(����)
	{
		ѭ���壻
	}
	��������
	���̣����ж������Ƿ����㣬�������ִ��ѭ���壬����ִ��ѭ������ĵ�һ�����

	do
	{
		ѭ���壻
	}while(����);
	���̣���ִ��һ��ѭ���壬Ȼ�����ж������Ƿ����㣬����������ִ�У������˳�ѭ��
	while���ж�������do...while����ִ��һ�Σ����ж�����

	for(��ʼ�����;����;���ʽ��
	{
		ѭ����;
	}
	����:1����ִ�г�ʼ����䣬Ȼ���ж������Ƿ���������������ִ��ѭ���壬�����˳�ѭ��
		2��ִ��ѭ����֮����ִ�б��ʽ��Ȼ�����ж�����
		3��ע�⣺��ʼ�����ֻ��ִ��һ��

*/
int mainWhile()
{
	int age = 0;	//80��
	while (age<80)
	{
		printf("һ����һ��:�Ժ�����˯~ age:%d\n",age);
		age++;
	}

	//��[1,100]�ĺ�
	int sum = 0;	//�����
	//sum = 1 + 2 + 3 + 4 + ... + 100;
	int n = 1;
	while (n <= 100)
	{
		sum += n++;	//1 2 3 4 5 6...100
		//printf("%d\n", n++);
	}
	printf("���Ϊ:%d", sum);


	return 0;
}
int mainDoWhile()
{
	int sum = 0;
	int n = 1;
	do
	{
		sum += n++;
	} while (n<=100);
	printf("%d", sum);

	//���ף�����

	char choose = ' ';	//����y��ʾ�����ˣ�����n��ʾû����
	//do
	//{
	//	printf("��������");
	//	scanf_s("%c", &choose, 1);
	//	getchar();	//����������е�\n
	//	//һֱ����
	//} while (choose == 'n');
	//printf("1��ϲ�㣬����Я���붴����~");

	printf("��������");
	scanf_s("%c", &choose, 1);
	getchar();
	while (choose == 'n')
	{
		printf("��������");
		scanf_s("%c", &choose, 1);

		getchar();	//����������е�\n
	}
	printf("2��ϲ�㣬����Я���붴����~");

}
int mainFor()
{
	//��1-100֮��ĺ�
	int sum = 0;
	for (int n = 0; n <= 100; n++)
	{
		sum += n;		
	}
	printf("sum:%d", sum);

	return 0;
}