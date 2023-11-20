#include<stdio.h>
#include<stdlib.h>	//为了使用随机函数	srand()设置种子  rand() 随机生成一个整数
#include<time.h>	//为了设置随机数种子 time(NULL) 获取系统当前时间
//猜拳游戏
//Rock Scissors Paper  石头 剪刀 布
/*
	1，系统随机生成拳头（0 1 2）
	2，提示用户选择出拳
	3，判断用户和系统谁赢了，输出结果

	随机数：如果没有设置随机数字种子，那么每次生成的数，都是一样的
			如果随机数种子设置的值是固定的，那么rand每次生成也是固定的
*/
#define Rock	0	//石头
#define Sci		1	//剪刀
#define Paper	2	//布
int main()
{
	srand((unsigned)time(NULL));	//需要一个不断发生变化的数字
	int sys = rand() % 3;			//系统随机生成拳
	printf("0，石头\n");
	printf("1，剪刀\n");
	printf("2，布\n");

	printf("请出拳>");
	int user = -1;
	scanf("%d", &user);
	if (user < 0 || user>2)
	{
		printf("请重新选择>\n");
	}
	else
	{
		//我赢了
		if ((user == Rock && sys == Sci) ||
			(user == Sci && sys == Paper) ||
			(user == Paper && sys  == Rock))
		{
			printf("玩家赢了\n");
		}
		//我输了
		else if ((user == Rock && sys == Paper) ||
				 (user == Sci && sys == Rock) ||
				(user == Paper && sys == Sci))
		{
			printf("玩家输了\n");
		}
		//平局
		else
		{
			printf("平局\n");
		}
	}
	//printf("user：%d  sys：%d\n", user, sys);
	//条件运算符(三目运算符)
	printf("user: %s ", user == 0 ? "石头" : (user == 1 ? "剪刀" : "布"));
	printf("sys: %s ", sys == 0 ? "石头" : (sys == 1 ? "剪刀" : "布"));

	/*
	if (user == Rock)
	{
		printf("玩家：石头");
	}
	else if (user == Sci)
	{
		printf("玩家：剪刀");
	}
	else
	{
		printf("玩家：布");
	}

	if (sys == Rock)
	{
		printf("sys：石头");
	}
	else if (sys == Sci)
	{
		printf("sys：剪刀");
	}
	else
	{
		printf("sys：布");
	}*/



	return 0;
}