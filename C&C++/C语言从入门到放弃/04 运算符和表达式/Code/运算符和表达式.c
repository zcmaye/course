#include<stdio.h>
#include<stdbool.h>
int main算术运算符()
{
	int num = 3;
	printf("%d\n", num);
	printf("%d\n", -num);	//单目负号不会改变原操作数的值
	
	printf("%d\n", 3 + 2);
	printf("%d\n", 3 - 2);
	printf("%d\n", 3 * 2);
	//在C语言中，如果两个整数相除，结果一定是向下取整
	printf("%f\n", (float)3 / 2); // 为什么结果是整数部分的，小数部分去哪了？

	printf("%d\n", 3 % -2);

	return 0;
}
int main赋值运算符()
{
	// = 赋值运算符
	int age = 18;
	printf("%d\n", age);
	// +=
	age += 2+5-3*4;				//-> age = age +(2+5-3*4);
	printf("%d\n", age);


	return 0;
}
int main关系运算符()
{
	int n1 = 5, n2 = 6;
	printf("%d\n", n1 > n2);		//0
	printf("%d\n", n1 < n2);		//1
	printf("%d\n", n1 >= n2);		//0
	printf("%d\n", n1 <= n2);		//1
	printf("%d\n", n1 == n2);		//0
	printf("%d\n", n1 != n2);		//1

	if (n1 > n2)
	{
		printf("n1>n2\n");
	}
	else if(n1 ==n2)
	{
		printf("n1==n2\n");
	}
	else
	{
		printf("n1<n2\n");
	}

	//0为假，非0为真    true   false

	if ((n1 > n2) == false) 
	{
		printf("true");
	}



	return 0;
}
int main逻辑运算符()
{
	/*
	int a = 2, b = 3, c = 4;
	printf("%d\n", a > b > c);
	printf("%d\n", a < b < c);
	//printf("%d\n", a > c < b);	//a>c  c<b   
	printf("%d\n", a > c && c < b);	//0 && 0
	//&& 逻辑与，只有当两边的表达式同时为真的时候，整个表达式才为真
	//|| 逻辑或，只要两边的表达式任意一个为真，则整个表达式为真
	//! 逻辑非，非0为真，非真为假	       如果没有下雨我就出去    在下雨
	
	printf("%d\n", a > c || c < b);	//0 || 0
	printf("%d\n", c > a || c < b);	//1 || 0

	bool rain = true;	//在下雨
	if (!rain)
	{
		printf("可以出去玩\n");
	}
	
	printf("%d  %d\n", !0,!20);
	*/

	//true  -> 1 真
	//false -> 0 假

	bool one = true && printf("1\n");		//1
	bool two = false && printf("2\n");		//0

	bool three = true || printf("3\n");		//1
	bool four = false || printf("4\n");		//1

	printf("one:%d  two:%d three:%d four:%d", one, two, three, four);


	return 0;
}
int main特殊运算符之自增和自减()
{
	int num = 0,num1 = 0;
	//对num进行加1操作
	//num = num + 1;
	//num += 1;
	//num++;					//效率比较高
	printf("%d\n", num++);		//0
	printf("%d\n", ++num1);		//1
	printf("%d %d\n", num, num1);
	//++写在变量后面，叫做后置，后置会先把变量做别的运算，然后自己才变化
	//++卸载变量前面，叫做前置，前置会先让变量自己变化，然后再参与别的运算

	int ret = num++;
	int ret1 = ++num1;
	printf("num:%d %d\n", num, num1);
	printf("ret:%d %d\n", ret, ret1);

	//注意：
	/*int a = 2, b = 3;
	printf("注意：%d %d %d\n", a++, b++, a + b);		//2 3 7    3+4




	printf("a,b %d %d\n", a, b);	//3 4
	printf("注意：%d %d %d\n", a + b,a++, b++);		//error:7 3 4   right:9 3 4
	//一个语句执行顺序，与编译器有关，不同的编译器有不同的处理方式，MSVC 是从右往左进行计算的
	*/

	int a = 2, b = 3;
	int res = a++ + ++b + a + b++;				//		2 + 5 + 2 + 3   
	printf("res=%d  %d %d\n",res, a, b);		//      a =3    b == 5




	return 0;
}
int main特殊运算符之逗号运算符和条件运算符()
{
	//分割：
	//int a = 0, b = 1;
	////printf("%d", a);

	//int num = (1, 2, 3, 4, 5);
	//printf("%d\n", num);

	//printf("%d\n", (++a, ++b));	//2

	// 条件?表达式1:表达式2  判断条件是否成立，如果条件成立执行表达式1，否则执行表达式2
	int a = 5, b = 2;
	int ret = a > b ? a : b;
	printf("%d\n", ret);

	printf((5 > 2) == true ? ("true") : ("fale"));

	int c = 4;
	ret = a > b ? (a > c ? a : c) : b;
	printf("ret:%d\n", ret);



	return 0;
}
int main位运算符()
{
	char bin = 0b0010'1010;
	//按位与 &  有0则0
	printf("%d\n",bin & 0);
	/*
	0010'1010
	0000'0000  &
	------------
	0000 0000	
	*/

	//按位或 |  有1则1
	printf("%d\n", bin & 5);
	/*
	0010'1010
	0000 0101 &
	------------
	0010 1111		->47
	*/
	 
	//按位取反 ~  0变1，1变0   单目运算符
	printf("%d\n", ~6);
	printf("%d %d\n", 0, ~0);		//int [-21亿 ~ 21亿]
	printf("%u %u\n", 0, ~0);
	/*
	~ 0000 0110  ->6
	  1111 1001  ->249

	~0	//有符号
	0000 0000
	1111 1111		//负数  补码
	1000 0001		-1

	~0	//无符号
	0000 0000
	1111 1111		//负数  补码
	*/

	//按位异或  ^ 相同为0，不同为1
	printf("%d\n", 3 ^ 5);
	/*
	0000 0011
	0000 0101 ^
	-----------
	0000 0110	
	*/

	//左移 <<  二进制数据整体向左移动n位
	//当没有1溢出的时候，每左移一位，就相当于原来的数据乘以2
	5 << 1;	// 5->10
	5 << 2;	// 5->20
	5 << 3;	// 5->40
	printf("%d\n", 5 << 5);
	5 << 6;	//64  这里最高位有1溢出了，所以说结果就不是原来的数据乘以2了
	/*
	0000 0101 ->5	
	*/

	//右移 >>   移动之后空出来的位补上符号位的数据0 or 1
	//当没有1溢出的时候，每右移一位，就相当于原来的数据除以2
	5 >> 1;	//5 -> 2		5/2 =2
	5 >> 2; //5 -> 1		5/2/2 =1
	//printf("125>> %d\n", 125 >> 32);	//warning C4293: “>>”: Shift 计数为负或过大，其行为未定义


	printf("%d\n", -5 >> 1);
	printf("%d\n", -5 >> 2);
	printf("%d\n", -5 >> 3);
	printf("%d\n", -5 >> 4);

	return 0;
}
int main()
{
	//&取地址   * 取值
	int age = 18;
	printf("age地址是:%p age= %d\n", &age,*&age);

	//sizeof 求内存大小
	//1，求类型的大小
	printf("%d Byte\n", sizeof(int));
	printf("%d Byte\n", sizeof(double));
	printf("%d Byte\n", sizeof(long int));	//32位机器上是4个字节，64位机器上是8个字节 short<=int<=long int
	printf("%d Byte\n", sizeof(long long));
	//2,求变量的大小
	printf("%d Byte\n", sizeof(age));


	//(type)强制转换运算符
	printf("%d\n", (int)(3.15 * 2.1));

	//printf("%p\n", &printf);
	printf("hello");

	return 0;
}