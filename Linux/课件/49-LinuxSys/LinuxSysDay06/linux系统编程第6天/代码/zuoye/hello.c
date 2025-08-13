#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("[%d]:[%s]\n", i, argv[i]);
	}

	while(1)
	{
		printf("hello wolrd\n");
		sleep(1);
	}
	return 0;
}

