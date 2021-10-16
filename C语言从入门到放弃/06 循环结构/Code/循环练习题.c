#include<stdio.h>
#include<stdbool.h>
#include<math.h>
//写一个九九乘法表
int main九九乘法表()
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
//求100以内的素数
int main素数()
{
	//int m = 0;

	//printf("请输入一个整数>");
	//scanf("%d", &m);
	for (int m = 3; m <= 100; m++)
	{
		//2~m-1 
		bool isok = true;
		//解题方法1
		for (int i = 2; i < m; i++)
		{
			if (m % i == 0)
			{
				isok = false;
				break;
			}
		}
		//解题方法2
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
			printf("%d是素数\n", m);
		}
	}
	


	return 0;
}
//输出所有的“水仙花数”，所谓的“水仙花数”是指一个三位数其各位数字的立方和等于该数本身，
//例如153是“水仙花数”，因为：153 = 1^3 + 5^3 + 3^3。
int main水仙花数()
{
	for (int n = 100; n <= 999; n++)
	{
		int ge = n % 10;
		int shi = n / 10 % 10;
		int bai = n / 100;
		if (n == ge * ge * ge + shi * shi * shi + bai * bai * bai)
		{
			printf("%d是水仙花数\n", n);
		}
	}

	return 0;
}
//最小公倍数
int main最小公倍数()
{
	//公倍数 5 3
	//n%5 ==0  && n%3==0  15/5 =3  15/3 =5  30 
	int m = 5,n = 3;
	int max = m > n ? m : n;
	for (int i = max; ; i++)
	{
		if (i % m == 0 && i % n == 0)
		{
			printf("m:%d n:%d的最小公倍数是%d\n", m, n, i);
			break;
		}
	}

	return 0;
}
//斐波拉契数列 1 1 2 3 5 8 13 ...  f(n) = f(n-1)+f(n-2)
int mainFibonacci()
{
	int a0 = 1;
	int a1 = 1;

	int n = 7;	//求第五项的值
	int res = 0;
	for (int i = 0; i < n-2; i++)
	{
		res = a0 + a1;
		int t = a1;
		a1 = res;
		a0 = t;
	}
	printf("第%d项的值是:%d\n", n, res);
	


	return 0;
}
//百钱买百鸡
/*
一只公鸡cock值五钱，一只母鸡hen值三钱，三只小鸡(chick)值一钱
100钱，买100只鸡，请问公鸡，母鸡，小鸡各多少只？
	全买公鸡：20只
	全买母鸡：33只
	全买小鸡: 100只
5*cock+3*hen+chick/3 = 100钱
cock+hen+chick =100只
*/
int main百钱买百鸡()
{
	for (int cock = 0; cock <= 20; cock++)	//公鸡可能的只数
	{
		for (int hen = 0; hen <= 33; hen++)	//母鸡可能的只数
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