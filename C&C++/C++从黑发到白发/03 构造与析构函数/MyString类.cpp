#include<iostream>
using namespace std;
class MyString
{
public:
	MyString();
	MyString(const char *str);
	MyString(const MyString&other);
	const char* mycat(MyString other);
	int mycmp(MyString other);
	const char* inverted();//逆序
	const char* getData();
	~MyString();
	int length();

private:
	char* data;
	int size;
};

MyString::MyString()
{
	size = 0;
	data = NULL;
}
MyString::MyString(const char* str)
{
	size = strlen(str);
	data = (char*)malloc(sizeof(char) * size+1);
	strcpy(data, str);
}
MyString::MyString(const MyString& other)
{
	size = strlen(other.data);
	data = (char*)malloc(sizeof(char) * size+1);
	strcpy(data, other.data);
}
int MyString::length()
{
	return size;
}
const char* MyString::mycat(MyString other)
{
	if (!other.data)//如果other为空，则直接返回本对象的data
	{
		return data;
	}
	else
	{
		char* temp = (char*)malloc(sizeof(char) * size + 1);
		strcpy(temp, data);

		size = size + other.size;
		data= (char*)malloc(sizeof(char) * size + 1);
		strcpy(data,temp);
		strcat(data, other.data);

		free(temp);

		//cout <<"?? "<< *temp << endl;
	}
	return data;
}
int MyString::mycmp(MyString other)
{
	return strcmp(data, other.data);
}
const char* MyString::inverted()
{
	char* front = data;
	char* tail = data;
	while (*tail)
	{
		tail++;
	}
	tail--;//让尾指针指向最后一个字符
	
	while (front != data+size/2 )//判断指针是否移到了指定位置
	{
		char tch=*front;
		*front = *tail;
		*tail = tch;
		front++;
		tail--;
	}

	return data;
}
const char* MyString::getData()
{
	return data;
}
MyString::~MyString()
{
	free(data);
}
int main()
{
	MyString str="maye";
	MyString str1 = "Nice 12356";
	str.mycat(str1);
	cout << str.length() <<"  "<<str.getData()<< endl;
	
	cout << str.inverted() << endl;
	cout << str.mycmp(str1) << endl;
	'm','N';
	system("pause");
	return 0;
}