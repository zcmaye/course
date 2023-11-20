#include<stdio.h>

int main定义()
{
	//如何定义指针变量？ 类型*  变量名;
	//ptr是一个指针，指向(指针变量存储谁的地址，咱们就说指针指向了谁)的是一个int类型的空间
	//int* ptr;	//error C4700: 使用了未初始化的局部变量“ptr”
	int age = 18;
	int* ptr = &age;
	printf("%p %p\n", ptr,&age);

	char ch = 'A';
	//double* ptrd = &ch;	//warning C4133: “初始化”: 从“char *”到“double *”的类型不兼容
	char* ptrc = &ch;

	//注意：定义指针的时候，指针的类型和指针所指向的类型尽量保持一直
	//指针的类型      char型的指针  char就是指针的类型
	//指针指向的类型  指针存储的地址所表示的类型 char

	return 0;
}
/*
	& 取地址符号，获得变量的地址
	* 根据指针获取指向的内存空间的数据
	ptr == &money
	->  &money    *&moeny == money  一把钥匙解一把锁
	->  ptr       *ptr == money  
*/
int main取值()
{
	int money = 100000;

	//定义一个指针指向money呢？
	int* ptr = &money;
	printf("%p %p\n", &money, ptr);	//输出地址
	printf("%d %d\n", money, *ptr);	//输出数据

	printf("%d %d\n", *&money,money);




	return 0;
}

int main指针()
{
	char* pc;			//没有指向的指针叫做野指针
	//printf("%p\n", pc);	//error C4700: 使用了未初始化的局部变量“pc”
	//printf("%p\n", &pc);	//ok    获取指针自己的地址
	//printf("%d\n", *pc);	//error 获取指针指向的内存空间的值
	//绝对不允许出现野指针

	//空指针，可以判断指针有没有指向
	double* pd = NULL;
	printf("%p\n", pd);		//0x00000
	if (pd != NULL)
	{
		printf("%lf\n", *pd);
	}
	else
	{
		printf("pd指向了NULL\n");
	}
	

	//万能指针(void*)
	int score = 98;

	//万能指针可以指向任意类型的地址
	void* ps = &score;		
	printf("%d\n", *(int*)ps);	//error C2100: 非法的间接寻址

	//void*指针可以自动隐式的转化为其他类型的指针
	int* pi = ps;		//void* -> int*
	printf("%d\n", *pi);



	return 0;
}

int mainConst与指针()
{
	const double PI = 3.1415926;
	//PI = 3.14;						//error 禁止修改只读变量
	printf("%lf\n", PI);				//可以随便访问
	double* pt =  (double*)&PI;			//warning C4090: “初始化”: 不同的“const”限定符
	*pt = 6.24;
	printf("%lf\n", PI);				//可以随便访问

	&PI; //const double* ->double*




	int age = 18;
	//普通指针
	int* page = &age;
	*page = 19;
	printf("%d %d\n", *page,age);

	//常量指针(指向常量的指针) 指针指向的内存空间，通过指针是不可以修改的
	const int* readAge = page;	//page == &age
	//*readAge = 100;
	printf("*readAge:%d\n", *readAge);

	//指针常量(指针是常量) 指针不能改变指向（指针存的地址不能改变）
	int* const cp = page;
	*cp = 20;
	printf("*cp:%d\n", *cp);

	int maye = 666;

	//cp = &maye;
	printf("*cp:%d\n", *cp);


	/*
	 const int* ptr;		cosnt修饰的是int*,代表的是指针指向的内存空间不可以修改
	 int const * ptr;
	
	int* const ptr;			const修饰的是ptr，代表指针变量的指向不可以改变
	*/

	return 0;
}

int main指针运算()
{
	char* pc = NULL;	//char型指针，指向的是char变量 
	int* pi = NULL;	//int型指针，指向的是int变量
	double* pd = NULL;	//double型指针，指向的是double变量

	printf("%p %p\n", pc, pc + 1);	//1		//char		1Byte
	printf("%p %p\n", pi, pi + 1);	//4		//int		4Byte
	printf("%p %p\n", pd, pd + 1);	//8		//double	8Byte

	//指针的++ --并不是简单的数字加1，而是根据指针变量所指向的类型所决定的
	//步长，不同类型的指针的步长是不一样的，大人，小孩，老人，每走一步所走的距离不一样

	//不管什么类型的指针，所占的内存空间都是一样大的(32位 4个字节，64位 8个字节)
	printf("%d\n", sizeof(char*));
	printf("%d\n", sizeof(int*));
	printf("%d\n", sizeof(double*));
	printf("%d\n", sizeof(void*));

	printf("\n\n\n");

	int number = 0x12345678;
	int* pnum = &number;
	printf("%x\n", *pnum);

	short* psnum = (short*)&number;
	printf("%x\n", *psnum);		//0x12345678
	printf("%x\n", *(psnum + 1));

	//大端和小端存储



	return 0;
}

int main()
{
	int litte = 0x12345678;

	return 0;
}