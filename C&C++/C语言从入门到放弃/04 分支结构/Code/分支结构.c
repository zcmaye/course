#include<stdio.h>
#include<stdbool.h>
int main���()
{
	;	//һ�����Ľ�βһ��Ҫ�ӷֺ�

	int maye = 30;
	printf("maye:%d\n", maye);
	//int maye = 55;	//error  �ض���

	//�����򣺱����������ܹ�������,���÷�Χ�Ӷ��忪ʼ������������
	{
		int maye = 20;			//��ʼ
		printf("maye:%d\n", maye);
	}		//����

	printf("end maye:%d\n",maye);


	return 0;
}
int main���ֿ���������()
{
	//˳��ṹ ����������������ֵ
	int a = 3, b = 5;
	printf("%d,%d\n", a, b);	//3 5

	int t = a;
	a = b;
	b = t;

	printf("%d,%d\n", a, b);	//5 3

	//��֧�ṹ
	printf(a > b ? "a>b" : "<b");

	//ѭ���ṹ
	while (1)
	{
		printf("�Է���˯��\n");
	}

	return 0;
}

/*
	����֧��䣺
	if(����)
	{
		��֧��(Ҫִ�е����)
	}
	...
	ִ�����̣��������������ִ�з�֧�壬����ִ��(ִ�з�֧����������)

	˫��֧���
	if(������
	{
		��֧��1
	}
	else
	{
		��֧��2
	}
	ִ������:�����������ִ�з�֧��1������ִ�з�֧��2��������֧�ụ��
	if�ǿ��Ե������ڵģ�����else������һ��if��֮��Ӧ

	Ƕ�׷�֧
	if(����1)
	{
		��֧1
	}
	else if(����2)
	{
		��֧2
	}
	...
	else if(����n)
	{
		��֧n
	}
	else	//����ѡ�������
	{

	}
	ִ������:�����ж�����1������ִ�з�֧1����������ж�����2������ִ�з�֧2����������ж�....
	ֵ��ע����ǣ�һ��ĳ����֧��������������ôʣ�µķ�֧����ִ�У�ֱ��������ִ��if����������ȥ��

	switch(���ʽ)
	{
		case �������ʽ1:
			break;	//���Ǳ���ģ�����ѡ
		case �������ʽ2:
			break;
		....
		default:	//Ĭ�� ���� else
			break;
	}
	ִ�����̣����ݱ��ʽ��ֵ����ÿһ��case ��������ݽ����жϣ����������ĳһ��case����ִ��
	�����case����û��break��ô����Ľ�ͬ��ִ��
*/
int mainswitch���()
{
	//�˵������û�����ѡ��Ĺ���
	printf("/**1,�鿴ѧ��**/\n");
	printf("/**2,���ѧ��**/\n");
	printf("/**3,ɾ��ѧ��**/\n");
	printf("/**4,����ѧ��**/\n");

	int choose = 0;
	printf("��ѡ�����>");
	scanf("%d", &choose);

	int test = 50;
	switch (choose)
	{
		//int test = 50;		//��Ҫ��switch������涨���κα��� warning C4700: ʹ����δ��ʼ���ľֲ�������test��
		case 1:
			printf("��ѡ���˲鿴ѧ�� %d\n",test);
			break;
		case 2:
			printf("��ѡ�������ѧ��\n");
			break;
		case 3:
			printf("��ѡ����ɾ��ѧ��\n");
			break;
		case 4:
			printf("��ѡ���˲���ѧ��\n");
			break;
		default:
			printf("�����������֤������~\n");
			break;
	}

	/*
	if (choose == 1)
	{
		printf("��ѡ���˲鿴ѧ��\n");
	}
	else if(choose ==2)
	{
		printf("��ѡ�������ѧ��\n");
	}
	else if (choose == 3)
	{
		printf("��ѡ����ɾ��ѧ��\n");
	}
	else if(choose == 4)
	{
		printf("��ѡ���˲���ѧ��\n");
	}
	else
	{
		printf("�����������֤������~\n");
	}
	*/

	return 0;
}
int mainif���()
{
	/*
	//����һ���������ж�������ǲ���ż���� num % 2 == 0
	int input = 0;
	printf("������һ������>");
	scanf_s("%d", &input);

	if (input % 2 == 0)	
	{
		printf("%d��һ��ż��\n", input);
	}
	else  
	{
		printf("%d��һ������\n", input);
	}
	*/


	//����   Ů   -> Ư��  ��Ư��  
	char sex = 0;	//0 Ů  1 ��
	if (!sex)
	{
		printf("���׿�ʼ...\n");
		bool Ư�� = true;
		if (Ư��)
		{
			printf("��������\n");
		}
		else if (!Ư��)
		{
			printf("��û������\n");
		}
	}




	//�����û�����ķ��������еȼ��ж�������90��ΪA�ȣ�����80ΪB��
	//����70ΪC������60ΪD��С��60ΪE   �������59�֣����������¼
	int score = 0;
	printf("���������>");
	scanf_s("%d", &score);

	if (score >= 90)
	{
		printf("�ȼ�ΪA\n");
	}
	else if (score >= 80)
	{
		printf("�ȼ�ΪB\n");
	}
	else if (score >= 70)
	{
		printf("�ȼ�ΪC\n");
	}
	else if (score >= 60)
	{
		printf("�ȼ�ΪD\n");
	}
	else if (score == 59)
	{
		printf("���ǿ����ߵ�ϣ������ͳ��ʿ�ı��������¸ҷ���Ķ�������ų��ͽ���������ɣ�");
	}
	else
	{
		printf("�ȼ�ΪE\n");
	}






	printf("--end--");
	getchar();
	return 0;
}