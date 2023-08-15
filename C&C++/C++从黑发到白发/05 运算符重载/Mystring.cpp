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
	// const���������޸������ݳ�Ա, ������������ݵ�����
	int length()const
	{
		return size;
	}
	const char*data()
	{
		return c_str;
	}
	//���ظ�ֵ�������ʹ�ÿ���ʹ�ö�����"xxxxxx"����ֵ
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
		//���汾����ַ���
		char *temp = new char[size + 1];
		strcpy(temp, c_str);
		//�ͷű���ָ��,�����������ڴ�
		delete[] c_str;
		size = size + other.size;
		c_str = new char[size + 1];
		strcpy(c_str, temp);
		strcat(c_str, other.c_str);
		//�ͷ���ʱ������ڴ�
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
	//����[]
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
		cout << "������<=" << other.size << "���ַ����ַ���" << endl;
		in >> other.c_str;
		return in;
	}
	//�ַ�����ת
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
	int size;		//�ַ�����С
	char *c_str;	//�ַ���ָ��
};
int main()
{
	MyString str("maye");
	*str="ĪӰ";
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