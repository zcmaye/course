#include<stdio.h>		//预处理指令，包含指定的头文件 stdio 标准输入输出头文件
#include<stdlib.h>

int main()	//这个是程序的入口函数，main函数，入口函数
{
	printf("hello world\n");	//printf是stdio里面的函数
	printf("   -----   \n");

	getchar();
	//while (1);
	//system("pause");	// warning C4013: “system”未定义
	return 0;	//返回值  0 正常退出   -1 异常退出
}
/*
	程序如何运行？
	1，Ctrl+F5  运行但不调试
	2，F5		直接调试			可能会闪退

	在运行之前，代码可能有各种问题，那么我们需要对代码进行语法检查
	1，Ctrl + Shift + B		先编译一下代码，(生成解决方案)
	2，Ctrl + F				编译代码


	程序闪退怎么办？
	1，getchar();		//等待输入一个字符，会把程序阻塞
	2，while(1);			//死循环，直接把程序卡死
	3，system("pause");	//需要头文件<stdlib.h>  让程序在这等待，直到用户按下任意键

	入口(main)函数
	野路子写法：
	1,不要这样写，这是不合法的
	main()
	{

	}
	2,不推荐这样写
	void main()
	{

	}

	正规军：
	1，一般使用这种写法
	int main()
	{
		return 0;
	}
	2，这种写法更完整
	argc命令行参数个数  argv命令行参数数组
	int main(int argc,char *argv[])
	{

		return  0;
	}






*/