#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include<string>
using namespace std;

template<typename Data>
class Vector
{
public:
	Vector() :_Array(nullptr), _curSize(0), _capacity(0) {}
	Vector(int size) :_curSize(0), _capacity(size)
	{
		_Array = new Data[size];
	}
	Vector(Vector& arr) :_curSize(arr._curSize), _capacity(arr._capacity)
	{
		_Array = new Data[_capacity];
		for (int i = 0; i < arr._curSize; i++)
		{
			this->_Array[i] = arr._Array[i];
		}
	}
	//构造聚合初始化
	Vector(initializer_list<Data> ls)
	{
		_capacity = ls.size();
		_curSize = 0;
		_Array = new Data[_capacity];
		for (const Data& temp : ls)
		{
			this->push_back(temp);
		}
	}
	void push_back(Data data)
	{
		if (_curSize < _capacity)
		{
			_Array[_curSize] = data;
			_curSize++;
			return;
		}
		cout << "数组越界" << endl;
	}
	void arrMul(int mulNum)
	{
		for (int i = 0; i < _curSize; i++)
		{
			_Array[i] *= mulNum;
			//要确保存的数据类型，能够相乘
		}
	}
	void operator=(Vector& arr)
	{
		//判断当前对象和arr的关系
		if (_capacity < arr._curSize)
		{
			delete[] _Array;
			_capacity = arr._capacity;
			_curSize = arr._curSize;
			_Array = new Data[_capacity];
		}
		for (int i = 0; i < arr._curSize; i++)
		{
			this->_Array[i] = arr[i];
			//要确保，存的类型能够相互赋值
		}
		_curSize = arr._curSize;
	}
	Data& operator[](int index)
	{
		if (index >= 0 && index < _capacity)
		{
			return _Array[index];
		}
		cout << "数组访问越界" << endl;
	}
	int size()
	{
		return _curSize;
	}
	friend ostream& operator<<(ostream& out, Vector<Data>& _Array)
	{
		for (int i = 0; i < _Array._curSize; i++)
		{
			out << setw(5) << setiosflags(ios::left) << _Array[i];
		}
		return out;
	}
	~Vector()
	{
		delete[] _Array;
	}

public://自己实迭代器
	class iterator;
	//返回数组首地址
	iterator begin()
	{
		iterator t(_Array);
		return t;
	}
	//返回数组，最后一个元素的一下一个位置的地址
	iterator end()
	{
		iterator t(&_Array[_curSize]);
		return t;
	}
	class iterator
	{
	public:
		iterator() :pmove(nullptr) {}
		iterator(Data* t) :pmove(t) {}
		iterator(const iterator& it)
		{
			this->pmove = it.pmove;
		}
		~iterator() {}
		iterator operator=(iterator it)
		{
			this->pmove = it.pmove;
			return *this;
		}
		bool operator!=(iterator it)
		{
			return pmove != it.pmove;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			pmove++;
			return temp;
		}
		Data& operator*()
		{
			return *pmove;
		}
		Data* operator->()
		{
			return pmove;
		}
	private:
		Data* pmove;
	};

protected:
	Data* _Array;		//数组指针
	int _curSize;		//数组当前元素大小
	int _capacity;		//数组最大容量
};
class teacher
{
public:
	teacher(int age = 0, const char* name = "NULL") :age(age)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void operator=(teacher& t)
	{
		delete[] this->name;
		this->name = new char[strlen(t.name) + 1];
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

void Test1()
{
	Vector<int> vec(10);
	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
	}
	//能通过迭代器访问嘛？不能，要自己实现迭代器之后才能使用
	for (Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void Test2()
{
	Vector<int> v{ 1,2,3,4,5,6,7,8,954,454,51,54,5678,697,1,6 };
	for (Vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		*it += 1;
		cout << *it << " ";

	}
}
//聚合初始化方式，当做函数参数
void show(initializer_list<int> ls)
{
	for (int i : ls)
	{
		cout << i << " ";
	}
	cout << endl;
}
int main()
{
	//Test1();
	//Test2();
	//show({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });


	return 0;
}