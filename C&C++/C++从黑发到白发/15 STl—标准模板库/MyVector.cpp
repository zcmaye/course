#include <iostream>
#include <iomanip>
#include<string>
using namespace std;

template<typename Data>
class Vector
{
public:
	Vector() :Array(nullptr), curSize(0), capacity(0) {}
	Vector(int size) :curSize(0), capacity(size)
	{
		Array = new Data[size];
	}
	Vector(Vector& arr) :curSize(arr.curSize), capacity(arr.capacity)
	{
		Array = new Data[capacity];
		for (int i = 0; i < arr.curSize; i++)
		{
			this->Array[i] = arr.Array[i];
		}
	}
	void push(Data data)
	{
		if (curSize < capacity)
		{
			Array[curSize] = data;
			curSize++;
			return;
		}
		cout << "数组越界" << endl;
	}
	void arrMul(int mulNum)		
	{
		for (int i = 0; i < curSize; i++)
		{
			Array[i] *= mulNum;
			//要确保存的数据类型，能够相乘
		}
	}
	void operator=(Vector& arr)		
	{
		//判断当前对象和arr的关系
		if (capacity < arr.curSize)
		{
			delete[] Array;
			capacity = arr.capacity;
			curSize = arr.curSize;
			Array = new Data[capacity];
		}
		for (int i = 0; i < arr.curSize; i++)
		{
			this->Array[i] = arr[i];
			//要确保，存的类型能够相互赋值
		}
		curSize = arr.curSize;
	}
	Data& operator[](int index)
	{
		if (index >= 0 && index < capacity)
		{
			return Array[index];
		}
		cout << "数组访问越界" << endl;
	}
	friend ostream& operator<<<Data>(ostream& out, Vector& Array);
	~Vector()
	{
		delete[] Array;
	}
protected:
	Data* Array;		//Êý×éÖ¸Õë
	int curSize;	//Êý×éÊý×éµ±Ç°´óÐ¡
	int capacity;	//×î´óÈÝÁ¿
};
template<typename Data>
ostream& operator<<(ostream& out, Vector<Data>& Array)
{
	for (int i = 0; i < Array.curSize; i++)
	{
		out << setw(5) << setiosflags(ios::left) << Array[i];
	}
	return out;
}
class teacher
{
public:
	teacher(int age = 0, const char* name = "NULL") :age(age) 
	{ 
		this->name = new char[strlen(name) + 1];
		strcpy ( this->name, name);
	}
	void operator=(teacher& t)
	{
		delete[] this->name;
		this->name = new char[strlen(t.name)+1];
		strcpy(this->name, t.name);
		this->age = t.age;
	}
	~teacher()
	{
		if (name != nullptr)
		{
			delete[] name;
		}
	}
	friend ostream& operator<<(ostream& out, teacher& t)
	{
		out << t.age << " " << t.name << endl;
		return out;
	}
private:
	//string name;
	char* name;
	int age;

};



int main()
{
	//写的容器，如果存的是自定义的类型，一定要，能被赋值
	teacher t[3] = { teacher(18,"maye"),teacher(35,"qingge"),teacher(28,"momo") };
	Vector<teacher> arr(10);
	for (int i = 0; i < 3; i++)
	{
		arr.push(t[i]);
	}
	cout << arr << endl;

	Vector<teacher> arr1=arr;

	cout << arr1 << endl;

	/*
	//一次偶然的成功，比必然的失败更可怕
	Vector<int> arr(10);
	for (int i = 0; i < 10; i++)
	{
		arr.push(i);
	}
	cout << arr << endl;


	Vector<char> arr1(10);
	for (int i = 0; i < 10; i++)
	{
		arr1.push(i+'A');
	}
	cout << arr1 << endl;



	Vector<string> arr2(10);
	string name[5] = { string("maye"),string("zc"),string("cc"),string("ptian"),string("jason") };
	for (int i = 0; i < 5; i++)
	{
		arr2.push(name[i]);
	}
	cout << arr2 << endl;
	*/

	return 0;
}