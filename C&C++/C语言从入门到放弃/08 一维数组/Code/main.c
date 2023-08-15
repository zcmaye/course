/*!
* @file main.c
* @author maye
* @details order func
* #date 22-11-29
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*!
*
*/
/*!
* @brief 冒泡排序
* @detail 从左到右相邻元素进行比较，如果满足交换规则，则交换，重复这个步骤，直到排序完成
*
* @param arr 待排序的数组
* @param len 待排序的数组元素个数
*
*/
void bubbleSort(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		bool isSort = true;	//判断是否排序完成
		for (int k = 0; k < len - i - 1; k++)
		{
			if (arr[k] > arr[k + 1])
			{
				int t = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = t;
				isSort = false;
			}
		}
		if (isSort)
			break;
		printf("i:%d\n", i);
	}
}

/*!
* @brief 选择排序
* @detail 从左往右遍历，找到剩余的最小的元素与之交换
*
* @param arr 待排序的数组
* @param len 待排序的数组元素个数
*
*/
void selectSort(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int minIndex = i;
		for (int k = i + 1; k < len; k++)
		{
			if (arr[k] < arr[minIndex])
			{
				minIndex = k;
			}
		}
		//如果找到了比minIndex处元素还小的元素，就把最小的与i处的元素进行交换
		if (minIndex != i)
		{
			int t = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = t;
		}
	}
}

/*!
* @brief 插入排序
* @detail 如果只有一个元素，不需要排序；有多个元素默认第一个元素有序，判断是插入在该元素的左边还是右边
*		 如果有多个元素，则需要从右往左逐个遍历判断
*
* @param arr 待排序的数组
* @param len 待排序的数组元素个数
*
*/
void insertSort(int arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int insVal = arr[i];	//待插入的数据
		//接下来判断把后面的元素一个一个的与前面元素比较，直到满足插入条件
		int k;
		for (k = i - 1; k >= 0; k--)
		{
			if (arr[k] > insVal)
			{
				arr[k + 1] = arr[k];	//往后移动元素
			}
			else
			{
				break;
			}
		}
		arr[k + 1] = insVal;
		//如果想判断是直接插入到i处开始找到了合适的位置
		//if (i != k + 1)
		//{
		//	arr[k + 1] = insVal;
		//}
		//else
		//{
		//	arr[k + 1] = insVal;
		//}
	}
}

/*!
* @brief 二分查找
* @detail 二分查找必须得是对有序的集合进行，先确定最中间的元素(n/2),然后根据是升序还是降序，向左边或右边继续二分
*
* @param arr 待排序的数组
* @param len 待排序的数组元素个数
*
*/

int binaraySearch(int arr[], int len, int val)
{
	int left = 0;
	int right = len - 1;
	int mid = len / 2;
	while (left <= right)
	{		
		//如果等于中间元素
		if (val == arr[mid])
		{
			return mid;
		}
		else if (val == arr[left])
		{
			return left;
		}
		else if (val == arr[right])
		{
			return right;
		}
		//如果是升序
		if (val > arr[mid])
		{
			left = mid + 1;
			mid = left + (right - left) / 2;
		}
		else if (val < arr[mid])
		{
			right = mid - 1;
			mid = right / 2;
		}
	}

	return -1;
}


void printArr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
int main()
{
	int arr[] = { 9};
	//int arr[] = { 1,2,3,4,5,6,7,8,9 };
	//int arr[] = { 6 , 9,  8 , 1 , 0 };
	//int arr[] = { 1,2,3,4,6,5 };
	int len = sizeof(arr) / sizeof(arr[0]);
	printArr(arr, len);
	//bubbleSort(arr, len);
	//selectSort(arr, len);
	//insertSort(arr, len);
	printArr(arr, len);

	printf("index:%d\n", binaraySearch(arr, len, 9));

	return 0;
}