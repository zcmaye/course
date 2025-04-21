#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>
typedef struct String
{
	size_t capacity;	//容量
	size_t len;			//当前长度
	char* str;			//字符串指针
}String;

String str_new(const char* initStr);
void str_free(String* str);
size_t str_length(String* str);
String str_copy(String* str1, String* str2);

int main()
{

	String str = str_new("hello wrold");
	String str2 = str_new("顽石老师");
	printf("%zu",str_length(&str));

	
	printf("%s\n",str_copy(&str, &str2).str);
	printf("begin\n");
	str_free(&str);
	printf("end\n");
	return 0;
}

String str_new(const char* initStr)
{
	String str;
	str.len = strlen(initStr);
	str.capacity = str.len + 1;
	str.str = malloc(sizeof(char) * str.capacity);
	assert(str.str != NULL);
	strncpy(str.str, initStr, str.len);
	str.str[str.len] = '\0';
	return str;
}
void str_free(String* str)
{
	free(str->str);
}
size_t str_length(String* str)
{
	return str->len;
}
String str_copy(String* str1, String* str2)
{
	char* p1 = str1->str;
	char* p2 = str2->str;
	while (*++p1);
	while (*p1++ = *p2++);
	*p1 = '\0';
	return *str1;
}
