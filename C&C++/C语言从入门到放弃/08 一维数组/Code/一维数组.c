#include<stdio.h>
#include<stdbool.h>
/*
	数组：相同数据类型的集合，每个元素的地址都是连续的，并且下标(索引)是从0开始的，最大小标是数组的大小减1
	数组的定义：数据类型 数组名[size]={初始值};	普通变量：数据类型  变量名 = 初始值；
			
*/
int main数组的定义和初始化()
{
	//int ages[5];		//如果没有初始化,值就是辣鸡值
	//int ages[5] = 0;	//error C2075: “ages”: 初始化需要带括号的初始值设定项列表
	//int ages[5] = {2,3,4};	//聚合初始化方式,如果指定了一个或多个元素，其他未指定的元素，自动初始化为0
	//int ages[5] = { 0 };	//初始化只能从左到右依次初始化，不能跳过某个元素
	//ages[4] = 6;			//数组的最大下标为，最大数量-1
	//int ages[5] = { 1,2,3,4,5,6 };	//error C2078: 初始值设定项太多

	int ages[] = { 1,2,3,4,5,6,7,8,9};
	//求数组的元素个数
	int len = sizeof(ages)/sizeof(ages[0]);	
	printf("%d\n", len);

	//下标越界会怎么样？偶然的正确，比必然的错误更可怕~
	//printf("%d %d\n", ages[-1],ages[1000000]);

	
	//输出数组的所有元素呢？
	//printf("%d\n", ages[0]);	//输出一个元素的值
	for (int i = 0; i < len; i++)
	{
		printf("%d ", ages[i]);
	}
	



	return 0;
}
int main()
{
	//定义一个数组
	int datas[10] = { 1,2,3 };
	int maxSize = sizeof(datas)/sizeof(datas[0]);	//数组最大元素个数
	int curSize = 3;								//数组当前有效元素个数

	int pos = -1;		//要插入或者删除的位置(下标)
	int data = -1;		//要插入或者删除的元素

	while (true)
	{
		printf("*****菜单*******\n");
		printf("*****0,查看*******\n");
		printf("*****1,添加*****\n");
		printf("*****2,删除*****\n");

		int choose = -1;
		printf("请选择操作>");
		scanf_s("%d", &choose);

		switch (choose)
		{
		case 0:
			//输出元素
			for (int i = 0; i < curSize; i++)
			{
				printf("%d ", datas[i]);
			}
			printf("\n");
			break;
		case 1:
			printf("请输入要插入的pos和data:");
			scanf_s("%d %d", &pos, &data);

			//当datas存满了，你就不能继续插入了
			if (curSize == maxSize)
			{
				printf("datas以满，无法继续插入~\n");
			}
			else
			{
				//容错处理（矫正）
				if (pos > curSize || pos < 0)
				{
					pos = curSize;
				}
				//把pos位置的元素整体向后移动一位
				for (int i = curSize; i > pos; i--)
				{
					datas[i] = datas[i - 1];
				}

				//插入元素，并改变curSize
				datas[pos] = data;
				curSize++;
			}
			break;
		case 2:
			printf("请输入要删除的pos>");
			scanf_s("%d", &pos);

			if (curSize == 0)
			{
				printf("datas为空，无需删除\n");
			}
			else
			{
				if (pos < 0 || pos >= curSize)
				{
					printf("pos不合法，无法删除\n");
				}
				else
				{
					for (int i = pos; i < curSize-1; i++)
					{
						datas[i] = datas[i + 1];	//curSize = 10   i>9   i+1>10
					}
					curSize--;
				}
			}

			break;
		}

	}


	
	


	                   
	return 0;
}