#include<stdio.h>
#include<stdbool.h>
int main语句()
{
	;	//一个语句的结尾一定要加分号

	int maye = 30;
	printf("maye:%d\n", maye);
	//int maye = 55;	//error  重定义

	//作用域：变量在哪里能够被访问,作用范围从定义开始，到快语句结束
	{
		int maye = 20;			//开始
		printf("maye:%d\n", maye);
	}		//结束

	printf("end maye:%d\n",maye);


	return 0;
}
int main三种控制语句概念()
{
	//顺序结构 ，交换两个变量的值
	int a = 3, b = 5;
	printf("%d,%d\n", a, b);	//3 5

	int t = a;
	a = b;
	b = t;

	printf("%d,%d\n", a, b);	//5 3

	//分支结构
	printf(a > b ? "a>b" : "<b");

	//循环结构
	while (1)
	{
		printf("吃饭，睡觉\n");
	}

	return 0;
}

/*
	单分支语句：
	if(条件)
	{
		分支体(要执行的语句)
	}
	...
	执行流程：如果条件成立，执行分支体，否则不执行(执行分支语句后面的语句)

	双分支语句
	if(条件）
	{
		分支体1
	}
	else
	{
		分支体2
	}
	执行流程:如果条件成立执行分支体1，否则执行分支体2，两个分支提互斥
	if是可以单独存在的，但是else必须有一个if与之对应

	嵌套分支
	if(条件1)
	{
		分支1
	}
	else if(条件2)
	{
		分支2
	}
	...
	else if(条件n)
	{
		分支n
	}
	else	//可以选其他情况
	{

	}
	执行流程:首先判断条件1，成立执行分支1，否则继续判断条件2，成立执行分支2，否则继续判断....
	值得注意的是：一旦某个分支满足了条件，那么剩下的分支不在执行，直接跳过，执行if语句后面的语句去了

	switch(表达式)
	{
		case 常量表达式1:
			break;	//不是必须的，可以选
		case 常量表达式2:
			break;
		....
		default:	//默认 其他 else
			break;
	}
	执行流程：根据表达式的值，与每一个case 后面的数据进行判断，如果满足了某一个case，则执行
	如果该case后面没有break那么后面的将同样执行
*/
int mainswitch语句()
{
	//菜单，让用户输入选择的功能
	printf("/**1,查看学生**/\n");
	printf("/**2,添加学生**/\n");
	printf("/**3,删除学生**/\n");
	printf("/**4,查找学生**/\n");

	int choose = 0;
	printf("请选择操作>");
	scanf("%d", &choose);

	int test = 50;
	switch (choose)
	{
		//int test = 50;		//不要再switch语句里面定义任何变量 warning C4700: 使用了未初始化的局部变量“test”
		case 1:
			printf("你选择了查看学生 %d\n",test);
			break;
		case 2:
			printf("你选择了添加学生\n");
			break;
		case 3:
			printf("你选择了删除学生\n");
			break;
		case 4:
			printf("你选择了查找学生\n");
			break;
		default:
			printf("输入有误，请查证后重试~\n");
			break;
	}

	/*
	if (choose == 1)
	{
		printf("你选择了查看学生\n");
	}
	else if(choose ==2)
	{
		printf("你选择了添加学生\n");
	}
	else if (choose == 3)
	{
		printf("你选择了删除学生\n");
	}
	else if(choose == 4)
	{
		printf("你选择了查找学生\n");
	}
	else
	{
		printf("输入有误，请查证后重试~\n");
	}
	*/

	return 0;
}
int mainif语句()
{
	/*
	//输入一个整数，判断这个数是不是偶数？ num % 2 == 0
	int input = 0;
	printf("请输入一个整数>");
	scanf_s("%d", &input);

	if (input % 2 == 0)	
	{
		printf("%d是一个偶数\n", input);
	}
	else  
	{
		printf("%d是一个奇数\n", input);
	}
	*/


	//相亲   女   -> 漂亮  不漂亮  
	char sex = 0;	//0 女  1 男
	if (!sex)
	{
		printf("相亲开始...\n");
		bool 漂亮 = true;
		if (漂亮)
		{
			printf("我相中了\n");
		}
		else if (!漂亮)
		{
			printf("我没有相中\n");
		}
	}




	//根据用户输入的分数，进行等级判定，大于90分为A等，大于80为B，
	//大于70为C，大于60为D，小于60为E   如果等于59分，输出经典语录
	int score = 0;
	printf("请输入分数>");
	scanf_s("%d", &score);

	if (score >= 90)
	{
		printf("等级为A\n");
	}
	else if (score >= 80)
	{
		printf("等级为B\n");
	}
	else if (score >= 70)
	{
		printf("等级为C\n");
	}
	else if (score >= 60)
	{
		printf("等级为D\n");
	}
	else if (score == 59)
	{
		printf("你是开创者的希望，传统人士的悲哀。是勇敢奋起的动力，是懦弱徒放弃的理由！");
	}
	else
	{
		printf("等级为E\n");
	}






	printf("--end--");
	getchar();
	return 0;
}