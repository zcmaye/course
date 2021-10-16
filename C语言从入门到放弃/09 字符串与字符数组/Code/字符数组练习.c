#include<stdio.h>
#include<conio.h>		//_getch()
#include<string.h>
/*用户登录，密码掩码功能*/
int main1()
{
	//按回车结束输入 10 -> '\n'    13 -> '\r'
	//int key = _getch();
	//printf("%d ", key);

	const char* defaultPasswd = "qwer123";

	char userName[20] = "";
	char userPasswd[20] = "";

	printf("请输入用户名>");
	gets_s(userName, 20);
	printf("请输入密码>");
	//gets_s(userPasswd, 20);

	for (int i = 0; i < 19; )
	{
		userPasswd[i] = _getch();
		if (userPasswd[i] == '\r')	//按回车结束输入
		{
			userPasswd[i] = '\0';
			break;
		}
		else if (userPasswd[i] == '\b' && i>0)
		{
			i--;
			printf("\b \b");
		}
		else
		{
			i++;
			printf("*");
		}
	}

	printf("\n");
	printf("userNmae:%s\n", userName);
	printf("userPasswd:%s\n", userPasswd);

	if (strcmp(defaultPasswd, userPasswd) == 0)
	{
		printf("恭喜你，登录成功~\n");
	}	
	return 0;
}

//定义一个字符数组，然后把这个数组的元素逆序  maye  eyam
int main2()
{
	char str[10] = "123456789";
	//int len = sizeof(str) / sizeof(str[0]);	//求数组长度
	int len = strlen(str);
	for (int i = 0; i < len/2; i++)
	{
		char t = str[i];
		str[i] = str[len -1 -i];
		str[len - 1 - i] = t;
	}
	puts(str);

	return 0;
}

//abbcadd  删除字符数组中间的重复的元素   abcd
int main()
{
	//char words[] = "abbcadd";
	char words[] = "abbbbbbbbbaaaasdfsdfsafdd";
	int len = sizeof(words) / sizeof(words[0]);

	for (int i = 0; i < len-1; i++)
	{
		for (int k = i + 1; k < len-1;)
		{
			if (words[i] == words[k])
			{
				for (int t = k; t < len - 1; t++)
				{
					words[t] = words[t + 1];
				}
				len--;	//数组长度减一
			}
			else
			{
				k++;
			}
		}
	}
	puts(words);



	return 0;
}