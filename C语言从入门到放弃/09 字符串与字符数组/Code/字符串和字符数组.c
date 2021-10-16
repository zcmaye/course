#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int main用数组存储字符串()
{
	printf("%d %d\n", sizeof('A'), sizeof("A"));

	int ages[5] = { 1,2,3,4 };				//整型数组
	char name[5] = { 'm','a','y','e' };		//字符数组，存储的是字符串
	char name1[5] = { 'm','a','y','e','w' };//字符数组，存储的是字符串吗？  不是，因为结尾没有\0
	printf("%s   |  %s\n", name, name1);

	char str[] = "My name is maye";		//str存储的是字符串变量
	const char* pstr = "maye";			//pstr指向的是字符串常量
	"hello";


	str[0] = 'm';
	//pstr[0] = 'M';   不能修改常量

	puts(str);
	puts(pstr);


	return 0;
}

int main11()
{
	
	char name[10];
	/*
	//getchar()循环输入字符数组
	for (int i = 0; i < 10; i++)
	{
		name[i] = getchar();
		if (name[i] == '\n')
		{
			name[i] = '\0';
			break;
		}
	}
	*/
	//scanf()
	//scanf输入字符串的时候，遇到空格会自动截断，只保留空格前面的内容
	//scanf("%s", name);
	//scanf_s("%s", name,10);

	//gets_s 专门用来获取字符串的
	gets_s(name, 10);


	puts(name);



	return 0;
}

int main字符串操作函数()
{
	//求字符串的长度
	char name[] = "顽石 2 3 5";
	int len = strlen(name);
	printf("%d\n", len);

	//字符串比较,是逐个字符进行比较，一旦发现有不同的字符，那么结果就直接可以判断出来了
	//str1>str2 返回1  str1<str2 返回-1 相等 返回0
	char str1[] = "Maye";
	char str2[] = "ma";
	int ret = strcmp(str1, str2);
	printf("%d\n", ret);

	//字符串拷贝,把src拷贝到dest中去，而且是从dest的第一个元素开始
	//dest必须要有足够的空间，去容纳src中的字符
	//char dest[10] = "I'";
	char dest[10] = {0};
	//strcpy(dest, "you");
	strncpy(dest, "maye hello", 2);
	puts(dest);

	//字符串拼接
	char dest1[100] = "I'm ";
	//strcat(dest1, "teacher");
	strncat(dest1, "student",3);
	puts(dest1);

	//字符查找
	char words[] = "My name's maye,nice too me s you!";
	char * pres = strrchr(words, 's');
	puts(pres);
	//根据strchr的返回值，获得查找的字符所在的下标
	int index = pres - words;
	printf("index:%d\n", index);

	//查找子串
	pres = strstr(words, "maye");
	puts(pres);




	return 0;
}

int main()
{
	int age1[5] = { 1,2,3,4,5 };
	int age2[5] = { 1,2,3,4,5 };
	//1,错误,数组名是数组的首地址，不同的数组首地址肯定不一样
	if (age1 == age2)
	{
		printf("1:age1 == age2");
	}
	//2,循环，逐个比较每个元素
	bool flag = true;		//是否相等的状态，先默认为相等
	for (int i = 0; i < 5; i++)
	{
		if (age1[i] > age2[i])
		{
			flag = false;
			printf("2:age1 > age2\n");
			break;
		}
		else if (age1[i] < age2[i])
		{
			flag = false;
			printf("2:age1 < age2\n");
			break;
		}
	}
	if (flag)
	{
		printf("2:age1 == age2\n");
	}

	//内存比较 memcmp
	int res = memcmp(age1, age2, sizeof(int) * 5);
	printf("%d\n", res);

	int a = 3, b = 7;
	res = memcmp(&a,&b, sizeof(int));
	printf("%d\n", res);

	//内存拷贝 memcpy
	int arr1[] = { 4,5,6,7,8 };
	int arr[10];
	//arr = arr1; //错误，数组之间不能直接赋值
	memcpy(arr, arr1, sizeof(int) * 5);


	//对一片内存，按字节统一设定一个值 memset
	//对于字符数组来说
	char names[10] = "";
	memset(names, 128, sizeof(char) * 9);
	puts(names);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", names[i]);
	}

	//对于其他类型的数组,用来统一初始化为0，是最方便的
	int tel[11];
	memset(tel, 0, sizeof(int) * 11);
	//memset(tel, 1, sizeof(int) * 11);
	for (int i = 0; i < 11; i++)
	{
		printf("%d ", tel[i]);
	}


	return 0;
}