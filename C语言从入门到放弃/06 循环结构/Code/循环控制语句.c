#include<stdio.h>
#include<stdbool.h>

int main死循环()
{
	//while (true)
	//{
	//	printf("学习\n");
	//}

	//do
	//{
	//	printf("吃饭\n");
	//} while (true);

	//for 如果条件没有写，那么默认为真，就永远执行这个循环了
	//在循环里面，尽量不要修改循环变量
	//for (int i = 0;i<= 100;i++)
	//{
	//	printf("for %d\n",i);
	//	if (i > 50)
	//	{
	//		i = i - 20;
	//	}
	//}


	//提示用户输入成绩，输入-1结束输入
	int score = 0;
	printf("输入成绩>");
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
	//break 跳出循环
	//找到第一个被13整除的数 i%13 == 0
	//遍历 迭代  循环
	for (int i = 14;; i++)
	{
		if (i % 13 == 0)
		{
			printf("第一个被13整除的数是:%d\n", i);
			//在这里应该跳出这个循环，结束
			break;
		}
	}
	

	//continue 结束本次循环，直接开始下一次循环
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

		//把奇数变成偶数
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