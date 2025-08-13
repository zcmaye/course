#include <stdio.h>

int sum(int len)
{
	int i = 0;
	int sum = 0;
	for(i=0; i<len; i++)
	{
		sum += i;
	}

	return sum;
}
