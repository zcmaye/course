#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char *p = "hello world";

	p[0] = "H";
	printf("%s\n", p);

	return 0;
}

