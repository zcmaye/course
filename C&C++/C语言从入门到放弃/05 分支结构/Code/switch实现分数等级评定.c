#include<stdio.h>
//根据用户输入的分数，进行等级判定，大于90分为A等，大于80为B，
//大于70为C，大于60为D，小于60为E   如果等于59分，输出经典语录
/*
	[0,59)  E
	[60,70) D
	[70,80) C
	[80,90) B
	[90,100] A   

	[0,59)  E	->0 1 2 3 4 5  其他
	[6,7) D		->6
	[7,8) C		->7
	[8,9) B		->8
	[9,10] A	->9 10

*/
int main()
{
	int score = 0;
	printf("请输入分数>");
	scanf("%d", &score);

	int grade = score / 10; //让分数取整，获得等级的阶段
	printf("grade:%d\n", grade);
	if (score == 59)
	{
		printf("你是开创者的希望....\n");
	}
	else
	{
		switch (grade)
		{
		case 9:
		case 10:
			printf("A\n");
			break;
		case 8:
			printf("B\n");
			break;
		case 7:
			printf("C\n");
			break;
		case 6:
			printf("D\n");
			break;
		default:
			printf("E\n");
			break;
		}
	}
	


	return 0;
}