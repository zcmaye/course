//stat函数测试: 获取文件类型和权限
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//int stat(const char *pathname, struct stat *buf);
	//获取文件属性
	struct stat sb;
	stat(argv[1], &sb);

	//获取文件类型
	if ((sb.st_mode & S_IFMT) == S_IFREG) 
 	{
		printf("普通文件\n");
	}	
	else if((sb.st_mode & S_IFMT) ==S_IFDIR)
	{
		printf("目录文件\n");
	}
	else if((sb.st_mode & S_IFMT) ==S_IFLNK)
	{
		printf("连接文件\n");
	}
	

	if (S_ISREG(sb.st_mode)) 
	{
	 	printf("普通文件\n");
	}
	else if(S_ISDIR(sb.st_mode))
	{
		printf("目录文件\n");
	}
	else if(S_ISLNK(sb.st_mode))
	{
		printf("连接文件\n");
	}

	//判断文件权限
	if(sb.st_mode & S_IROTH)
	{
		printf("---R----");
	}

	if(sb.st_mode & S_IWOTH)
	{
		printf("---W----");
	}
	
	if(sb.st_mode & S_IXOTH)
	{
		printf("---X----");
	}

	printf("\n");

	return 0;
}
