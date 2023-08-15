#include<stdio.h>

int main()
{
	int arr[5] = { 8,5,9,7,3 };
	int maxSize = 5;
	//排序之后 3 5 7 8 9
	/*
	冒泡排序：bubbleSort
	src 8 5 9 7 3
	第一趟：5 8 7 3 9	->4 	可以把最大的元素，放到最后面(冒泡)，每一趟都可以排好一个元素
	第二趟：5 7 3 8 9    ->3
	第三趟: 5 3 7 8 9    ->2
	第四趟：3 5 7 8 9     ->1
	数组元素有5个，经过了4趟就可以排序完成	
	*/

	for (int i = 0; i < maxSize-1; i++)	//控制趟数
	{
		//4 3 2  1
		for (int k = 0; k < maxSize -i -1; k++)	//0 1 2 3     0 1 2  0 1   0
		{
			if (arr[k] > arr[k + 1])
			{
				int t = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = t;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}