#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "head.h"

int main(int argc, char *argv[])
{
    printf("this is main!\n");
	int i = 0;
	for(i=0; i<argc; i++)
	{
		printf("[%d]:[%s]\n", i, argv[i]);
	}

    fun1();
    fun2();

	printf("sum(10)==[%d]\n", sum(10));

    return 0;
}
