#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>

void summation();
void haskell();
void  primeNumber();
void example_1();
void example_2();
void example_3();
void example_4();

int main()
{
	//example_1();
	//example_2();
	//example_3();
	example_4();

	return 0;
}

//一、求[1,100]的和。
void summation()
{
	int sum = 0;
	for (int i = 0; i <= 100; i++)
	{
		sum += i;
	}
	printf("[1,100]的和为:%d\n", sum);
}

//二、写一个九九乘法表。
void haskell()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int k = 1; k <= i; k++)
		{
			printf("%d*%d=%2d ", k, i, i * k);
		}
		printf("\n");
	}
}

//三、求100以内的素数
void  primeNumber()
{
	for (int i = 2; i <= 100; i++)
	{
		bool flag = true;
		for (int k = 2; k < i; k++)
		{
			if (i % k == 0)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			printf("i%d是素数\n", i);
			flag = true;
		}
	}
}

//四、用while循环求编写求s=1+(1+2)+(1+2+3)+....+(1+2+3+....+n)值的小程序。用这道题进入循环的世界叭！
void example_1()
{
	int sum = 0,n = 3;
	int result = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += i;		//累加，保存每个序列的和
		result += sum;	//让结果加上每个序列的和

		//result +=  i * (i + 1) / 2;	//等差数列求和公式
	}
	printf("%d\n", result);
}

//五、编写程序输入n，用for循环求 s=1！+ 2！+ 3！+ …+n！的值并输出。
void example_2()
{
	//product 乘积
	int product = 1, n = 3;
	int result = 0;
	for (int i = 1; i <= n; i++)
	{
		product *= i;
		result += product;
	}
	printf("result:%d\n", result);
}

//六、输入正整数a和n，计算s=a+aa+aaa+aaaa+aa...a（n个a）的值。
void example_3()
{
	uint32_t a, n;
	printf("input a n>");
	scanf_s("%u %u", &a, &n);

	uint32_t tmp = a;
	uint32_t result = 0;
	for (int i = 1; i <= n; i++)
	{
		result += tmp;
		tmp = pow(10, i) * a + tmp;
	}
	printf("result:%u\n", result);
}

//七、用for循环求分数序列：2/1，3/2，5/3，8/5，13/8，21/13，…，前n项之和。
//1，分子每一项等于前两项分子之和，分母同样如此
//2，进一步分析发现，每一项的分母，都等于分子减去前一项的分母
void example_4()
{
	int a = 1, b = 1;
	int n = 2;
	float result = 0;

	for (int i = 1; i <= n; i++)
	{
		a = a + b;
		b = a - b;
		result += (float)a / b;
	}
	printf("result:%.2f\n", result);
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