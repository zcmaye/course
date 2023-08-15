#include<stdio.h>
#include<stdbool.h>
//1,
void intersect()
{
	int arr1[20] = { 0 }, arr2[20] = {0};
	int curSize1 = 0, curSize2 = 0;
	for (int i = 0; i < 20; i++)
	{
		scanf_s("%d", &arr1[i]);
		if (arr1[i] == -1)
		{
			curSize1 = i;
			break;
		}
			
	}
	for (int i = 0; i < 20; i++)
	{
		scanf_s("%d", &arr2[i]);
		if (arr2[i] == -1)
		{
			curSize2 = i;
			break;
		}
			
	}
	//判断是否有相同的
	//for (int i = 0; i < curSize1; i++)
	//{
	//	for (int k = 0; k < curSize2; k++)
	//	{
	//		if (arr1[i] == arr2[k])
	//		{
	//			printf("%d ", arr1[i]);
	//		}
	//	}
	//}

	for (int i = 0; i < curSize1; i++)
	{
		for (int k = 0; k < curSize2; k++)
		{
			if (arr1[i] == arr2[k])
			{
				printf("%d ", arr1[i]);
				int t = arr2[k];
				arr2[k] = arr2[curSize2 - 1];
				arr2[curSize2 - 1] = t;
				--curSize2;

				t = arr1[i];
				arr1[i] = arr1[curSize1 - 1];
				arr1[curSize1 - 1] = t;
				--curSize1;

			}
		}
	}

}

void showArr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//2,
void adjust1()
{
	int arr[10] = { 12, 31, 17, 45, 68, 40, 57, 43, 25, 78 };
	showArr(arr, 10);
	int left = 0;
	int right = 10 - 1;
	while (left<right)
	{
		if (arr[left] % 2 != 0)	//奇数
		{
			if (arr[right] % 2 == 0)
			{
				int t = arr[left];
				arr[left] = arr[right];
				arr[right] = t;
				left++;
				right--;
			}
			else
			{
				right--;
			}
		}
		else
		{
			left++;
		}
	}
	showArr(arr, 10);
}
void adjust()
{
	int arr[10] = { 12, 31, 17, 45, 68, 40, 57, 43, 25, 78 };
	showArr(arr, 10);
	int left = 0;
	int right = 10 - 1;
	while (left <= right)
	{
		if (arr[left] % 2 == 0)
		{
			left++;
		}
		else
		{
			//找到一个偶数
			while (arr[right] % 2 != 0)
			{
				right--;
			}
			//与前面的奇数交换
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			//跳过当前位置
			right--;		
		}
	}
	showArr(arr, 10);
}
int main(int argc,char*argv[])
{
	//intersect();
	adjust();

	return 0;
}