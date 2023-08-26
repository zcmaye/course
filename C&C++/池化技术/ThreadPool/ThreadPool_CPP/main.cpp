#include"ThreadPool.h"
#include<stdio.h>
#include<stdint.h>
struct Number
{
	Number() :num(0) {}
	Number(int i) :num(i) {}
	~Number() { printf("release Number %d  \n",num); }
	void show(int a, double b) 
	{ 
		printf("Number(num %d) %d %lf\n", num, a, b);
		usleep(10000);
	}
	int num = 0;
	operator const int& ()const { return num; }
	operator  int& () { return num; }
};

void foo(int a,double b)
{
	printf("%s %d %lf\n", __FUNCTION__,a,b);
	sleep(1);
}
int main()
{
	{
		Number n;
		ThreadPool pool(2, 10);
		for (int i = 0; i < 100; i++)
		{
			Task task(&Number::show,n, i, i * 0.1 + 0.5);
			n.num++;
			pool.addTask(task);
		}


		printf("sleep 30 start~\n");
		sleep(40);
	}
	printf("sleep 30 end~\n");
	return 0;
}

