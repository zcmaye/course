#include<stdio.h>

//删除字符串中的指定字符
void removeChar(char* str, char ch)
{
	int i, j;
	for ( i=j = 0; str[i]; i++)
	{
		if (str[i] != ch)
		{
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

int main()
{
	char str[] = "aabbcc";
	removeChar(str, 'b');
	puts(str);


	return 0;
}