#include<stdio.h>
#include<stdbool.h>
#include<math.h>
//дһ���žų˷���
int main�žų˷���()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int k = 1; k <= i; k++)
		{
			printf("%d*%d=%2d ", k, i, i * k);
		}
		printf("\n");
	}

	return 0;
}
//��100���ڵ�����
int main����()
{
	//int m = 0;

	//printf("������һ������>");
	//scanf("%d", &m);
	for (int m = 3; m <= 100; m++)
	{
		//2~m-1 
		bool isok = true;
		//���ⷽ��1
		for (int i = 2; i < m; i++)
		{
			if (m % i == 0)
			{
				isok = false;
				break;
			}
		}
		//���ⷽ��2
		/*for (int i = 2; i <= sqrt(m); i++)
		{
			if (m % i == 0)
			{
				isok = false;
				break;
			}
		}*/
		if (isok)
		{
			printf("%d������\n", m);
		}
	}
	


	return 0;
}
//������еġ�ˮ�ɻ���������ν�ġ�ˮ�ɻ�������ָһ����λ�����λ���ֵ������͵��ڸ�������
//����153�ǡ�ˮ�ɻ���������Ϊ��153 = 1^3 + 5^3 + 3^3��
int mainˮ�ɻ���()
{
	for (int n = 100; n <= 999; n++)
	{
		int ge = n % 10;
		int shi = n / 10 % 10;
		int bai = n / 100;
		if (n == ge * ge * ge + shi * shi * shi + bai * bai * bai)
		{
			printf("%d��ˮ�ɻ���\n", n);
		}
	}

	return 0;
}
//��С������
int main��С������()
{
	//������ 5 3
	//n%5 ==0  && n%3==0  15/5 =3  15/3 =5  30 
	int m = 5,n = 3;
	int max = m > n ? m : n;
	for (int i = max; ; i++)
	{
		if (i % m == 0 && i % n == 0)
		{
			printf("m:%d n:%d����С��������%d\n", m, n, i);
			break;
		}
	}

	return 0;
}
//쳲��������� 1 1 2 3 5 8 13 ...  f(n) = f(n-1)+f(n-2)
int mainFibonacci()
{
	int a0 = 1;
	int a1 = 1;

	int n = 7;	//��������ֵ
	int res = 0;
	for (int i = 0; i < n-2; i++)
	{
		res = a0 + a1;
		int t = a1;
		a1 = res;
		a0 = t;
	}
	printf("��%d���ֵ��:%d\n", n, res);
	


	return 0;
}
//��Ǯ��ټ�
/*
һֻ����cockֵ��Ǯ��һֻĸ��henֵ��Ǯ����ֻС��(chick)ֵһǮ
100Ǯ����100ֻ�������ʹ�����ĸ����С��������ֻ��
	ȫ�򹫼���20ֻ
	ȫ��ĸ����33ֻ
	ȫ��С��: 100ֻ
5*cock+3*hen+chick/3 = 100Ǯ
cock+hen+chick =100ֻ
*/
int main��Ǯ��ټ�()
{
	for (int cock = 0; cock <= 20; cock++)	//�������ܵ�ֻ��
	{
		for (int hen = 0; hen <= 33; hen++)	//ĸ�����ܵ�ֻ��
		{
			for (int chick = 0; chick <= 100; chick++)
			{
				if (5 * cock + 3 * hen + chick / 3.0 == 100 && cock + hen + chick == 100)
				{
					printf("cock:%d hen:%d chick:%d\n", cock, hen, chick);
				}
			}
		}
	}

	return 0;
}