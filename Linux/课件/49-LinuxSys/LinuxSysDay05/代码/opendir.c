//目录操作测试: opendir readdir closedir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	//打开目录
	//DIR *opendir(const char *name);
	DIR *pDir = opendir(argv[1]);
	if(pDir==NULL)
	{
		perror("opendir error");
		return -1;
	}

	//循环读取目录项
	//struct dirent *readdir(DIR *dirp);
	struct dirent *pDent = NULL;
	while((pDent=readdir(pDir))!=NULL)
	{
		//过滤掉.和..文件
		if(strcmp(pDent->d_name, ".")==0 || strcmp(pDent->d_name, "..")==0)
		{
			continue;
		}

		printf("[%s]---->", pDent->d_name);

		//判断文件类型
		switch(pDent->d_type)
		{
			case DT_REG:
				printf("普通文件");
				break;

			case DT_DIR:
				printf("目录文件");
				break;

			case DT_LNK:
				printf("链接文件");
				break;

			default:
				printf("未知文件");
		}

		printf("\n");
	}

	//关闭目录
	closedir(pDir);

	return 0;
}
