#include<stdio.h>
#include<stdbool.h>
int main���������()
{
	int num = 3;
	printf("%d\n", num);
	printf("%d\n", -num);	//��Ŀ���Ų���ı�ԭ��������ֵ
	
	printf("%d\n", 3 + 2);
	printf("%d\n", 3 - 2);
	printf("%d\n", 3 * 2);
	//��C�����У��������������������һ��������ȡ��
	printf("%f\n", (float)3 / 2); // Ϊʲô������������ֵģ�С������ȥ���ˣ�

	printf("%d\n", 3 % -2);

	return 0;
}
int main��ֵ�����()
{
	// = ��ֵ�����
	int age = 18;
	printf("%d\n", age);
	// +=
	age += 2+5-3*4;				//-> age = age +(2+5-3*4);
	printf("%d\n", age);


	return 0;
}
int main��ϵ�����()
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

	//0Ϊ�٣���0Ϊ��    true   false

	if ((n1 > n2) == false) 
	{
		printf("true");
	}



	return 0;
}
int main�߼������()
{
	/*
	int a = 2, b = 3, c = 4;
	printf("%d\n", a > b > c);
	printf("%d\n", a < b < c);
	//printf("%d\n", a > c < b);	//a>c  c<b   
	printf("%d\n", a > c && c < b);	//0 && 0
	//&& �߼��룬ֻ�е����ߵı��ʽͬʱΪ���ʱ���������ʽ��Ϊ��
	//|| �߼���ֻҪ���ߵı��ʽ����һ��Ϊ�棬���������ʽΪ��
	//! �߼��ǣ���0Ϊ�棬����Ϊ��	       ���û�������Ҿͳ�ȥ    ������
	
	printf("%d\n", a > c || c < b);	//0 || 0
	printf("%d\n", c > a || c < b);	//1 || 0

	bool rain = true;	//������
	if (!rain)
	{
		printf("���Գ�ȥ��\n");
	}
	
	printf("%d  %d\n", !0,!20);
	*/

	//true  -> 1 ��
	//false -> 0 ��

	bool one = true && printf("1\n");		//1
	bool two = false && printf("2\n");		//0

	bool three = true || printf("3\n");		//1
	bool four = false || printf("4\n");		//1

	printf("one:%d  two:%d three:%d four:%d", one, two, three, four);


	return 0;
}
int main���������֮�������Լ�()
{
	int num = 0,num1 = 0;
	//��num���м�1����
	//num = num + 1;
	//num += 1;
	//num++;					//Ч�ʱȽϸ�
	printf("%d\n", num++);		//0
	printf("%d\n", ++num1);		//1
	printf("%d %d\n", num, num1);
	//++д�ڱ������棬�������ã����û��Ȱѱ�����������㣬Ȼ���Լ��ű仯
	//++ж�ر���ǰ�棬����ǰ�ã�ǰ�û����ñ����Լ��仯��Ȼ���ٲ���������

	int ret = num++;
	int ret1 = ++num1;
	printf("num:%d %d\n", num, num1);
	printf("ret:%d %d\n", ret, ret1);

	//ע�⣺
	/*int a = 2, b = 3;
	printf("ע�⣺%d %d %d\n", a++, b++, a + b);		//2 3 7    3+4




	printf("a,b %d %d\n", a, b);	//3 4
	printf("ע�⣺%d %d %d\n", a + b,a++, b++);		//error:7 3 4   right:9 3 4
	//һ�����ִ��˳����������йأ���ͬ�ı������в�ͬ�Ĵ���ʽ��MSVC �Ǵ���������м����
	*/

	int a = 2, b = 3;
	int res = a++ + ++b + a + b++;				//		2 + 5 + 2 + 3   
	printf("res=%d  %d %d\n",res, a, b);		//      a =3    b == 5




	return 0;
}
int main���������֮��������������������()
{
	//�ָ
	//int a = 0, b = 1;
	////printf("%d", a);

	//int num = (1, 2, 3, 4, 5);
	//printf("%d\n", num);

	//printf("%d\n", (++a, ++b));	//2

	// ����?���ʽ1:���ʽ2  �ж������Ƿ�����������������ִ�б��ʽ1������ִ�б��ʽ2
	int a = 5, b = 2;
	int ret = a > b ? a : b;
	printf("%d\n", ret);

	printf((5 > 2) == true ? ("true") : ("fale"));

	int c = 4;
	ret = a > b ? (a > c ? a : c) : b;
	printf("ret:%d\n", ret);



	return 0;
}
int mainλ�����()
{
	char bin = 0b0010'1010;
	//��λ�� &  ��0��0
	printf("%d\n",bin & 0);
	/*
	0010'1010
	0000'0000  &
	------------
	0000 0000	
	*/

	//��λ�� |  ��1��1
	printf("%d\n", bin & 5);
	/*
	0010'1010
	0000 0101 &
	------------
	0010 1111		->47
	*/
	 
	//��λȡ�� ~  0��1��1��0   ��Ŀ�����
	printf("%d\n", ~6);
	printf("%d %d\n", 0, ~0);		//int [-21�� ~ 21��]
	printf("%u %u\n", 0, ~0);
	/*
	~ 0000 0110  ->6
	  1111 1001  ->249

	~0	//�з���
	0000 0000
	1111 1111		//����  ����
	1000 0001		-1

	~0	//�޷���
	0000 0000
	1111 1111		//����  ����
	*/

	//��λ���  ^ ��ͬΪ0����ͬΪ1
	printf("%d\n", 3 ^ 5);
	/*
	0000 0011
	0000 0101 ^
	-----------
	0000 0110	
	*/

	//���� <<  �������������������ƶ�nλ
	//��û��1�����ʱ��ÿ����һλ�����൱��ԭ�������ݳ���2
	5 << 1;	// 5->10
	5 << 2;	// 5->20
	5 << 3;	// 5->40
	printf("%d\n", 5 << 5);
	5 << 6;	//64  �������λ��1����ˣ�����˵����Ͳ���ԭ�������ݳ���2��
	/*
	0000 0101 ->5	
	*/

	//���� >>   �ƶ�֮��ճ�����λ���Ϸ���λ������0 or 1
	//��û��1�����ʱ��ÿ����һλ�����൱��ԭ�������ݳ���2
	5 >> 1;	//5 -> 2		5/2 =2
	5 >> 2; //5 -> 1		5/2/2 =1
	//printf("125>> %d\n", 125 >> 32);	//warning C4293: ��>>��: Shift ����Ϊ�����������Ϊδ����


	printf("%d\n", -5 >> 1);
	printf("%d\n", -5 >> 2);
	printf("%d\n", -5 >> 3);
	printf("%d\n", -5 >> 4);

	return 0;
}
int main()
{
	//&ȡ��ַ   * ȡֵ
	int age = 18;
	printf("age��ַ��:%p age= %d\n", &age,*&age);

	//sizeof ���ڴ��С
	//1�������͵Ĵ�С
	printf("%d Byte\n", sizeof(int));
	printf("%d Byte\n", sizeof(double));
	printf("%d Byte\n", sizeof(long int));	//32λ��������4���ֽڣ�64λ��������8���ֽ� short<=int<=long int
	printf("%d Byte\n", sizeof(long long));
	//2,������Ĵ�С
	printf("%d Byte\n", sizeof(age));


	//(type)ǿ��ת�������
	printf("%d\n", (int)(3.15 * 2.1));

	//printf("%p\n", &printf);
	printf("hello");

	return 0;
}