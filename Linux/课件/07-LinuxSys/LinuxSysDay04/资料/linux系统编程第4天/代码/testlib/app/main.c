#include <stdio.h>
#include "head.h"
int main()
{
	int a=20;
	int b=10;

	printf("a+b==[%d]\n", add(a, b));
	printf("a-b==[%d]\n", sub(a, b));
	printf("a*b==[%d]\n", mul(a, b));
	printf("a/b==[%d]\n", divd(a, b));

	return 0;
}
