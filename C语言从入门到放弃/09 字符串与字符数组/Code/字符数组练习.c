#include<stdio.h>
#include<conio.h>		//_getch()
#include<string.h>
/*�û���¼���������빦��*/
int main1()
{
	//���س��������� 10 -> '\n'    13 -> '\r'
	//int key = _getch();
	//printf("%d ", key);

	const char* defaultPasswd = "qwer123";

	char userName[20] = "";
	char userPasswd[20] = "";

	printf("�������û���>");
	gets_s(userName, 20);
	printf("����������>");
	//gets_s(userPasswd, 20);

	for (int i = 0; i < 19; )
	{
		userPasswd[i] = _getch();
		if (userPasswd[i] == '\r')	//���س���������
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
		printf("��ϲ�㣬��¼�ɹ�~\n");
	}	
	return 0;
}

//����һ���ַ����飬Ȼ�����������Ԫ������  maye  eyam
int main2()
{
	char str[10] = "123456789";
	//int len = sizeof(str) / sizeof(str[0]);	//�����鳤��
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

//abbcadd  ɾ���ַ������м���ظ���Ԫ��   abcd
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
				len--;	//���鳤�ȼ�һ
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