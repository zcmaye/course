#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int main������洢�ַ���()
{
	printf("%d %d\n", sizeof('A'), sizeof("A"));

	int ages[5] = { 1,2,3,4 };				//��������
	char name[5] = { 'm','a','y','e' };		//�ַ����飬�洢�����ַ���
	char name1[5] = { 'm','a','y','e','w' };//�ַ����飬�洢�����ַ�����  ���ǣ���Ϊ��βû��\0
	printf("%s   |  %s\n", name, name1);

	char str[] = "My name is maye";		//str�洢�����ַ�������
	const char* pstr = "maye";			//pstrָ������ַ�������
	"hello";


	str[0] = 'm';
	//pstr[0] = 'M';   �����޸ĳ���

	puts(str);
	puts(pstr);


	return 0;
}

int main11()
{
	
	char name[10];
	/*
	//getchar()ѭ�������ַ�����
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
	//scanf�����ַ�����ʱ�������ո���Զ��ضϣ�ֻ�����ո�ǰ�������
	//scanf("%s", name);
	//scanf_s("%s", name,10);

	//gets_s ר��������ȡ�ַ�����
	gets_s(name, 10);


	puts(name);



	return 0;
}

int main�ַ�����������()
{
	//���ַ����ĳ���
	char name[] = "��ʯ 2 3 5";
	int len = strlen(name);
	printf("%d\n", len);

	//�ַ����Ƚ�,������ַ����бȽϣ�һ�������в�ͬ���ַ�����ô�����ֱ�ӿ����жϳ�����
	//str1>str2 ����1  str1<str2 ����-1 ��� ����0
	char str1[] = "Maye";
	char str2[] = "ma";
	int ret = strcmp(str1, str2);
	printf("%d\n", ret);

	//�ַ�������,��src������dest��ȥ�������Ǵ�dest�ĵ�һ��Ԫ�ؿ�ʼ
	//dest����Ҫ���㹻�Ŀռ䣬ȥ����src�е��ַ�
	//char dest[10] = "I'";
	char dest[10] = {0};
	//strcpy(dest, "you");
	strncpy(dest, "maye hello", 2);
	puts(dest);

	//�ַ���ƴ��
	char dest1[100] = "I'm ";
	//strcat(dest1, "teacher");
	strncat(dest1, "student",3);
	puts(dest1);

	//�ַ�����
	char words[] = "My name's maye,nice too me s you!";
	char * pres = strrchr(words, 's');
	puts(pres);
	//����strchr�ķ���ֵ����ò��ҵ��ַ����ڵ��±�
	int index = pres - words;
	printf("index:%d\n", index);

	//�����Ӵ�
	pres = strstr(words, "maye");
	puts(pres);




	return 0;
}

int main()
{
	int age1[5] = { 1,2,3,4,5 };
	int age2[5] = { 1,2,3,4,5 };
	//1,����,��������������׵�ַ����ͬ�������׵�ַ�϶���һ��
	if (age1 == age2)
	{
		printf("1:age1 == age2");
	}
	//2,ѭ��������Ƚ�ÿ��Ԫ��
	bool flag = true;		//�Ƿ���ȵ�״̬����Ĭ��Ϊ���
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

	//�ڴ�Ƚ� memcmp
	int res = memcmp(age1, age2, sizeof(int) * 5);
	printf("%d\n", res);

	int a = 3, b = 7;
	res = memcmp(&a,&b, sizeof(int));
	printf("%d\n", res);

	//�ڴ濽�� memcpy
	int arr1[] = { 4,5,6,7,8 };
	int arr[10];
	//arr = arr1; //��������֮�䲻��ֱ�Ӹ�ֵ
	memcpy(arr, arr1, sizeof(int) * 5);


	//��һƬ�ڴ棬���ֽ�ͳһ�趨һ��ֵ memset
	//�����ַ�������˵
	char names[10] = "";
	memset(names, 128, sizeof(char) * 9);
	puts(names);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", names[i]);
	}

	//�����������͵�����,����ͳһ��ʼ��Ϊ0��������
	int tel[11];
	memset(tel, 0, sizeof(int) * 11);
	//memset(tel, 1, sizeof(int) * 11);
	for (int i = 0; i < 11; i++)
	{
		printf("%d ", tel[i]);
	}


	return 0;
}