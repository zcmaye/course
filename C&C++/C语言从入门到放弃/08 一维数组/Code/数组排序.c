#include<stdio.h>

int main()
{
	int arr[5] = { 8,5,9,7,3 };
	int maxSize = 5;
	//����֮�� 3 5 7 8 9
	/*
	ð������bubbleSort
	src 8 5 9 7 3
	��һ�ˣ�5 8 7 3 9	->4 	���԰�����Ԫ�أ��ŵ������(ð��)��ÿһ�˶������ź�һ��Ԫ��
	�ڶ��ˣ�5 7 3 8 9    ->3
	������: 5 3 7 8 9    ->2
	�����ˣ�3 5 7 8 9     ->1
	����Ԫ����5����������4�˾Ϳ����������	
	*/

	for (int i = 0; i < maxSize-1; i++)	//��������
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