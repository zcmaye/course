#include"ThreadPool.h"

int main()
{
	ThreadPool pool(2, 10);
	for (int i = 0; i < 100; i++)
	{
		Task task([](int a) {printf("Number is %d\n", a); }, i);
		pool.addTask(task);
	}

	
	printf("sleep 30 start~\n");
	sleep(40);
	printf("sleep 30 end~\n");
	return 0;
}
