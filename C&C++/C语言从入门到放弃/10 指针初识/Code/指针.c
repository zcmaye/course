#include<stdio.h>

int main����()
{
	//��ζ���ָ������� ����*  ������;
	//ptr��һ��ָ�룬ָ��(ָ������洢˭�ĵ�ַ�����Ǿ�˵ָ��ָ����˭)����һ��int���͵Ŀռ�
	//int* ptr;	//error C4700: ʹ����δ��ʼ���ľֲ�������ptr��
	int age = 18;
	int* ptr = &age;
	printf("%p %p\n", ptr,&age);

	char ch = 'A';
	//double* ptrd = &ch;	//warning C4133: ����ʼ����: �ӡ�char *������double *�������Ͳ�����
	char* ptrc = &ch;

	//ע�⣺����ָ���ʱ��ָ������ͺ�ָ����ָ������;�������һֱ
	//ָ�������      char�͵�ָ��  char����ָ�������
	//ָ��ָ�������  ָ��洢�ĵ�ַ����ʾ������ char

	return 0;
}
/*
	& ȡ��ַ���ţ���ñ����ĵ�ַ
	* ����ָ���ȡָ����ڴ�ռ������
	ptr == &money
	->  &money    *&moeny == money  һ��Կ�׽�һ����
	->  ptr       *ptr == money  
*/
int mainȡֵ()
{
	int money = 100000;

	//����һ��ָ��ָ��money�أ�
	int* ptr = &money;
	printf("%p %p\n", &money, ptr);	//�����ַ
	printf("%d %d\n", money, *ptr);	//�������

	printf("%d %d\n", *&money,money);




	return 0;
}

int mainָ��()
{
	char* pc;			//û��ָ���ָ�����Ұָ��
	//printf("%p\n", pc);	//error C4700: ʹ����δ��ʼ���ľֲ�������pc��
	//printf("%p\n", &pc);	//ok    ��ȡָ���Լ��ĵ�ַ
	//printf("%d\n", *pc);	//error ��ȡָ��ָ����ڴ�ռ��ֵ
	//���Բ��������Ұָ��

	//��ָ�룬�����ж�ָ����û��ָ��
	double* pd = NULL;
	printf("%p\n", pd);		//0x00000
	if (pd != NULL)
	{
		printf("%lf\n", *pd);
	}
	else
	{
		printf("pdָ����NULL\n");
	}
	

	//����ָ��(void*)
	int score = 98;

	//����ָ�����ָ���������͵ĵ�ַ
	void* ps = &score;		
	printf("%d\n", *(int*)ps);	//error C2100: �Ƿ��ļ��Ѱַ

	//void*ָ������Զ���ʽ��ת��Ϊ�������͵�ָ��
	int* pi = ps;		//void* -> int*
	printf("%d\n", *pi);



	return 0;
}

int mainConst��ָ��()
{
	const double PI = 3.1415926;
	//PI = 3.14;						//error ��ֹ�޸�ֻ������
	printf("%lf\n", PI);				//����������
	double* pt =  (double*)&PI;			//warning C4090: ����ʼ����: ��ͬ�ġ�const���޶���
	*pt = 6.24;
	printf("%lf\n", PI);				//����������

	&PI; //const double* ->double*




	int age = 18;
	//��ָͨ��
	int* page = &age;
	*page = 19;
	printf("%d %d\n", *page,age);

	//����ָ��(ָ������ָ��) ָ��ָ����ڴ�ռ䣬ͨ��ָ���ǲ������޸ĵ�
	const int* readAge = page;	//page == &age
	//*readAge = 100;
	printf("*readAge:%d\n", *readAge);

	//ָ�볣��(ָ���ǳ���) ָ�벻�ܸı�ָ��ָ���ĵ�ַ���ܸı䣩
	int* const cp = page;
	*cp = 20;
	printf("*cp:%d\n", *cp);

	int maye = 666;

	//cp = &maye;
	printf("*cp:%d\n", *cp);


	/*
	 const int* ptr;		cosnt���ε���int*,�������ָ��ָ����ڴ�ռ䲻�����޸�
	 int const * ptr;
	
	int* const ptr;			const���ε���ptr������ָ�������ָ�򲻿��Ըı�
	*/

	return 0;
}

int mainָ������()
{
	char* pc = NULL;	//char��ָ�룬ָ�����char���� 
	int* pi = NULL;	//int��ָ�룬ָ�����int����
	double* pd = NULL;	//double��ָ�룬ָ�����double����

	printf("%p %p\n", pc, pc + 1);	//1		//char		1Byte
	printf("%p %p\n", pi, pi + 1);	//4		//int		4Byte
	printf("%p %p\n", pd, pd + 1);	//8		//double	8Byte

	//ָ���++ --�����Ǽ򵥵����ּ�1�����Ǹ���ָ�������ָ���������������
	//��������ͬ���͵�ָ��Ĳ����ǲ�һ���ģ����ˣ�С�������ˣ�ÿ��һ�����ߵľ��벻һ��

	//����ʲô���͵�ָ�룬��ռ���ڴ�ռ䶼��һ�����(32λ 4���ֽڣ�64λ 8���ֽ�)
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

	//��˺�С�˴洢



	return 0;
}

int main()
{
	int litte = 0x12345678;

	return 0;
}