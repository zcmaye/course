
#include<stdio.h>

/*************************字符串处理函数*************************/
//strlen
int my_strlen(char* str)
{
#if 0
	char* start = str;
	while (*str != '\0')
	{
		str++;
	}
	return str-start;
#else
	int cnt = 0;
	while (*str!='\0')
	{
		str++;
		cnt++;
	}
	return cnt;
#endif
}
//strcpy
char* MyStrcpy(char* dest, char* src)
{
	char* ptr = dest;
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return ptr;
}
//strcat
char* MyStrcat(char* dest, char* src)
{
	char* ptr = dest;
	while (*dest!='\0')
	{
		dest++;
	}
	while (*src!='\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return ptr;
}
//strcmp
int MyStrcmp(char* dest, char* src)
{
	while (*dest && *src && *dest==*src)
	{
		dest++;
		src++;
	}
	
	return *dest > *src ? 1 : *dest == *src ? 0 : -1;
}
//strstr
char* MyStrstr(char* str, char* subStr)
{
	while (*str!='\0')
	{
		char* pstr = str;
		char* psub = subStr;
		while (*pstr++ == *psub++)
		{
			if (*psub == '\0')
				return str;
		}
		str++;
	}
	return	NULL;
}
//strchr
char* MyStrchr(char* str, char c)
{
	while (*str)
	{
		if (*str == c)
		{
			return str;
		}
		str++;
	}
	return NULL;
}
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

void memset4(void* dst, int val, size_t size)
{
	int* pd = (int*)dst;
	for (size_t i = 0; i < size/4; i++)
	{
		pd[i] = val;
	}
}

int main()
{
	char str[] = "aabbcc";
	removeChar(str, 'b');
	puts(str);


	return 0;
}