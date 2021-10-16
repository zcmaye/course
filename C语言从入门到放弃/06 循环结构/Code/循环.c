#include<stdio.h>
/*
	while(条件)
	{
		循环体；
	}
	。。。。
	流程：先判断条件是否满足，如果满足执行循环体，否则执行循环后面的第一个语句

	do
	{
		循环体；
	}while(条件);
	流程：先执行一次循环体，然后再判断条件是否满足，如果满足继续执行，否则退出循环
	while先判断条件，do...while是先执行一次，再判断条件

	for(初始化语句;条件;表达式）
	{
		循环体;
	}
	流程:1，先执行初始化语句，然后判断条件是否成立，如果成立则执行循环体，否则退出循环
		2，执行循环体之后，再执行表达式，然后再判断条件
		3，注意：初始化语句只会执行一次

*/
int mainWhile()
{
	int age = 0;	//80岁
	while (age<80)
	{
		printf("一年又一年:吃喝拉撒睡~ age:%d\n",age);
		age++;
	}

	//求[1,100]的和
	int sum = 0;	//保存和
	//sum = 1 + 2 + 3 + 4 + ... + 100;
	int n = 1;
	while (n <= 100)
	{
		sum += n++;	//1 2 3 4 5 6...100
		//printf("%d\n", n++);
	}
	printf("结果为:%d", sum);


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

	//相亲，见面

	char choose = ' ';	//输入y表示看中了，输入n表示没看中
	//do
	//{
	//	printf("相中了吗？");
	//	scanf_s("%c", &choose, 1);
	//	getchar();	//清楚缓冲区中的\n
	//	//一直相亲
	//} while (choose == 'n');
	//printf("1恭喜你，可以携手入洞房了~");

	printf("相中了吗？");
	scanf_s("%c", &choose, 1);
	getchar();
	while (choose == 'n')
	{
		printf("相中了吗？");
		scanf_s("%c", &choose, 1);

		getchar();	//清楚缓冲区中的\n
	}
	printf("2恭喜你，可以携手入洞房了~");

}
int mainFor()
{
	//求1-100之间的和
	int sum = 0;
	for (int n = 0; n <= 100; n++)
	{
		sum += n;		
	}
	printf("sum:%d", sum);

	return 0;
}