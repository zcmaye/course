#include<stdio.h>
//�����û�����ķ��������еȼ��ж�������90��ΪA�ȣ�����80ΪB��
//����70ΪC������60ΪD��С��60ΪE   �������59�֣����������¼
/*
	[0,59)  E
	[60,70) D
	[70,80) C
	[80,90) B
	[90,100] A   

	[0,59)  E	->0 1 2 3 4 5  ����
	[6,7) D		->6
	[7,8) C		->7
	[8,9) B		->8
	[9,10] A	->9 10

*/
int main()
{
	int score = 0;
	printf("���������>");
	scanf("%d", &score);

	int grade = score / 10; //�÷���ȡ������õȼ��Ľ׶�
	printf("grade:%d\n", grade);
	if (score == 59)
	{
		printf("���ǿ����ߵ�ϣ��....\n");
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