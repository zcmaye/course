#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
class MyString
{
public:
	MyString(int size=0):size(size)
	{
		c_str = new char[size+1];
		strcpy(c_str, "");
	}
	MyString(const char *str)
	{
		size = strlen(str);
		c_str = new char[size + 1];
		strcpy(c_str, str);
	}
	MyString(const MyString& other)
	{
		size = other.size;
		c_str = new char[size + 1];
		strcpy(c_str, other.c_str);
	}
	~MyString()
	{
		if (c_str)
		{
			delete[] c_str;
			c_str = NULL;
		}
	}
	// const函数不能修改其数据成员, 仅仅起到输出数据的作用
	int length()const
	{
		return size;
	}
	const char*data()
	{
		return c_str;
	}
	//重载赋值运算符，使得可以使用对象与"xxxxxx"来赋值
	MyString& operator=(const MyString& other)
	{
		this->size = other.size;
		delete this->c_str;
		c_str = new char[this->size+1];
		strcpy(c_str, other.c_str);		
		return *this;
	}
	MyString& operator=(const char* str)
	{
		delete[] c_str;
		size = strlen(str);
		c_str = new char[size + 1];
		strcpy(c_str, str);
		return *this;
	}
	MyString& operator+=(const MyString&other)
	{
		//保存本类的字符串
		char *temp = new char[size + 1];
		strcpy(temp, c_str);
		//释放本类指针,并重新申请内存
		delete[] c_str;
		size = size + other.size;
		c_str = new char[size + 1];
		strcpy(c_str, temp);
		strcat(c_str, other.c_str);
		//释放临时申请的内存
		delete[] temp;
		return *this;
	}
	bool operator>(const MyString&other)
	{
		return strcmp(c_str, other.c_str)==1;
	}
	bool operator>=(const MyString&other)
	{
		return  strcmp(c_str, other.c_str)>=0;
	}
	bool operator<(const MyString&other)
	{
		return strcmp(c_str, other.c_str) == -1;
	}
	bool operator<=(const MyString&other)
	{
		return strcmp(c_str, other.c_str) <= 0;
	}
	bool operator==(const MyString&other)
	{
		return strcmp(c_str, other.c_str) == 0;
	}
	MyString& operator*()
	{
		return *this;
	}
	MyString* operator->()
	{
		return this;
	}
	//重载[]
	char& operator[](int index)
	{
		return c_str[index];
	}
	void operator()(const char * str)
	{
		delete[] c_str;
		size = strlen(str);
		c_str = new char[size + 1];
		strcpy(c_str, str);

		cout << c_str << endl;
	}
	friend ostream & operator<<(ostream &out,MyString&other)
	{
		out << other.c_str;
		return out;
	}
	friend istream&operator>>(istream&in, MyString&other)
	{
		cout << "请输入<=" << other.size << "个字符的字符串" << endl;
		in >> other.c_str;
		return in;
	}
	//字符串翻转
	void reverse()
	{
		char ch;
		for (int i = 0; i < size / 2; i++)
		{
			ch = c_str[i];
			c_str[i] = c_str[size - 1 - i];
			c_str[size - 1 - i] = ch;
		}
	}


private:
	int size;		//字符串大小
	char *c_str;	//字符串指针
};
int main()
{
	MyString str("maye");
	*str="莫影";
	str("visual studio~");
	cout << str << endl;
	cout << str->length() << endl;
	//cout << str.data() << endl;
	//MyString zc("Nice");
	//cout << zc << endl;
	//zc.reverse();
	//cout << zc << endl;
	//for (int i = 0; i < zc.length(); i++)
	//{
	//cout << zc[i] << " ";
	//}
	//str += zc;
	//str();

	//MyString temp(20);
	//cin >> temp;
	//cout << temp << endl;


	cout << "------------------"<<endl;
	while (1);
	getchar();
	return 0;
}