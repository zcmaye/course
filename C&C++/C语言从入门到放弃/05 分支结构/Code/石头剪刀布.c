#include<stdio.h>
#include<stdlib.h>	//Ϊ��ʹ���������	srand()��������  rand() �������һ������
#include<time.h>	//Ϊ��������������� time(NULL) ��ȡϵͳ��ǰʱ��
//��ȭ��Ϸ
//Rock Scissors Paper  ʯͷ ���� ��
/*
	1��ϵͳ�������ȭͷ��0 1 2��
	2����ʾ�û�ѡ���ȭ
	3���ж��û���ϵͳ˭Ӯ�ˣ�������

	����������û����������������ӣ���ôÿ�����ɵ���������һ����
			���������������õ�ֵ�ǹ̶��ģ���ôrandÿ������Ҳ�ǹ̶���
*/
#define Rock	0	//ʯͷ
#define Sci		1	//����
#define Paper	2	//��
int main()
{
	srand((unsigned)time(NULL));	//��Ҫһ�����Ϸ����仯������
	int sys = rand() % 3;			//ϵͳ�������ȭ
	printf("0��ʯͷ\n");
	printf("1������\n");
	printf("2����\n");

	printf("���ȭ>");
	int user = -1;
	scanf("%d", &user);
	if (user < 0 || user>2)
	{
		printf("������ѡ��>\n");
	}
	else
	{
		//��Ӯ��
		if ((user == Rock && sys == Sci) ||
			(user == Sci && sys == Paper) ||
			(user == Paper && sys  == Rock))
		{
			printf("���Ӯ��\n");
		}
		//������
		else if ((user == Rock && sys == Paper) ||
				 (user == Sci && sys == Rock) ||
				(user == Paper && sys == Sci))
		{
			printf("�������\n");
		}
		//ƽ��
		else
		{
			printf("ƽ��\n");
		}
	}
	//printf("user��%d  sys��%d\n", user, sys);
	//���������(��Ŀ�����)
	printf("user: %s ", user == 0 ? "ʯͷ" : (user == 1 ? "����" : "��"));
	printf("sys: %s ", sys == 0 ? "ʯͷ" : (sys == 1 ? "����" : "��"));

	/*
	if (user == Rock)
	{
		printf("��ң�ʯͷ");
	}
	else if (user == Sci)
	{
		printf("��ң�����");
	}
	else
	{
		printf("��ң���");
	}

	if (sys == Rock)
	{
		printf("sys��ʯͷ");
	}
	else if (sys == Sci)
	{
		printf("sys������");
	}
	else
	{
		printf("sys����");
	}*/



	return 0;
}