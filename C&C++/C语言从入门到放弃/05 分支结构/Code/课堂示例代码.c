#include<stdio.h>
#include<math.h>
#include<stdbool.h>
void example_1();
void example_2();
void example_3();
void example_4();
void example_5();
void example_6();
void example_7();
void example_8();
void example_9();

int main()
{
	example_9();

	return 0;
}

//从键盘输入三个整数到变量a，b，c中，将这三个数由大到校进行排序，使a中存放最小的数，c中存档最大的数，然后输出。
void example_1()
{
	int a, b, c;
	printf("input a b c>");
	scanf("%d %d %d", &a, &b, &c);

	int tmp = 0;
	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}

	if (a > c)
	{
		tmp = a;
		a = c;
		c = tmp;
	}

	if (b > c)
	{
		tmp = b;
		b = c;
		c = tmp;
	}

	printf("%d %d %d\n", a, b, c);
}

//输入一个数，输入是偶数输出`even number`，奇数输出`odd number`。
void example_2()
{
	int number = 0;
	printf("input number>");
	scanf("%d", &number);
	if (number % 2 == 0)
	{
		printf("even number\n");
	}
	else
	{
		printf("odd number\n");
	}
}

//某公司工资按周发放，标准是每小时制20元，若员工周工作时间超过40小时，超出部分每小时30元。输入一名员工一周的工作小时数，输出他的周工资。
void example_3()
{
	int workingHours = 0;
	int salary = 0;
	printf("input workingHours>");
	scanf("%d", &workingHours);

	if (workingHours > 40)
	{
		int exceedHours = workingHours - 40;	//超出时长
		salary = exceedHours * 30 + 40 * 20;
	}
	else
	{
		salary = workingHours * 20;
	}

	printf("salary is %d\n", salary);
}

//编写程序，输入三角形的三条边，求其面积。注意：如果3条边构不成三角形，则要给出错误提示。
void example_4()
{
	int a, b, c;
	printf("input a b c>");
	scanf("%d %d %d", &a, &b, &c);

	if (a + b > c && a + c > b && b + c > a)
	{
		double p = (a + b + c) / 2.0;
		double area = sqrt(p * (p - a) * (p - b) * (p - c));
		printf("三角形ABC的面积为%lf\n", area);
	}
	else
	{
		printf("error:a b c不能构成三角形\n");
	}

}

//输入一个三位整数，判断它是否为水仙花数，当输入数据不正确的时候，要求给出错误提示。
//水仙花总数为153,370,371,407
void example_5()
{
	int number = 0;
	printf("input number>");
	scanf("%d", &number);

	bool isNarcissisticNumber = false;	//是否是水仙花数

	//求每个位的立方和
	int ge, shi, bai;
	ge = number % 10;
	shi = number / 10 % 10;
	bai = number / 100 % 10;

	isNarcissisticNumber = number == (int)(pow(ge, 3) + pow(shi, 3) + pow(bai, 3));

	if (isNarcissisticNumber)
	{
		printf("是水仙花数\n");
	}
	else
	{
		printf("不是水仙花数\n");
	}

}

//有一个函数如下，写一段程序，输入x，输出y
void example_6()
{
	int x = 0,y = 0;
	printf("input x>");
	scanf("%d", &x);

	if (x >= 10)
	{
		y = 3 * x - 11;
	}
	else if(1<=x && x<10)
	{
		y = 2 * x - 1;
	}
	else
	{
		y = x;
	}

	printf("%d", y);
}


//从键盘输入3个整数a，b，c的值，求一元二次方程 ax<sup>2</sup>+bx+c=0的跟，计算结果保留两位小数。
//1 4 3
void example_7()
{
	int a, b, c;
	printf("input a b c>");
	scanf("%d %d %d", &a, &b, &c);

	//判根
	int delta = pow(b, 2) - 4 * a * c;
	if (delta > 0)
	{
		double x1 = (-b + sqrt(delta)) / 2.0 * a;
		double x2 = (-b - sqrt(delta)) / 2.0 * a;

		printf("有两个不相等的实根(%lf %lf)\n",x1,x2);
	}
	else if (delta == 0)
	{
		printf("有两个相等的实根(%lf)\n", (-b - sqrt(delta)) / 2.0 * a);
	}
	else
	{
		printf("没有实根\n");
	}

}

//等级评定
void example_8()
{
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
}

//编写程序，实现学生管理系统的菜单选择功能。
void example_9()
{
	//菜单，让用户输入选择的功能
	printf("-------------------------\n");
	printf("|**     1,查看学生     **|\n");
	printf("|**     2,添加学生     **|\n");
	printf("|**     3,删除学生     **|\n");
	printf("|**     4,查找学生     **|\n");
	printf("-------------------------\n");


	int choose = 0;
	printf("select>");
	while (!scanf("%d", &choose))
	{
		while (getchar() != '\n');
		printf("reselect>");
	}


	switch (choose)
	{
	case 1:
		printf("查看学生\n");
		break;
	case 2:
		printf("添加学生\n");
		break;
	case 3:
		printf("删除学生\n");
		break;
	case 4:
		printf("查找学生\n");
		break;
	default:
		printf("输入有误，请查证后重试~\n");
		break;
	}
}
