#include<stdio.h>
int main()
{
	int i, j, k, n = 0; //n用于统计个数
	for (i = 1; i < 5; i++) {			//1 2 3 4
		for (j = 1; j < 5; j++) {		//1 2 3 4
			for (k = 1; k < 5; k++) {	//1 2 3 4
				//保证三位数不重复
				if (i != j && i != k && j != k)
				{
					n++;
					printf("%d%d%d ", i, j, k);
					if (n % 4 == 0)
						printf("\n");
				}
			}
		}
	}
	printf("\n一共:%d\n", n);
	return 0;
}
