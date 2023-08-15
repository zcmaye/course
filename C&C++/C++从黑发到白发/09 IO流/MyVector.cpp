#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
//实现一个数组类,实现基本操作
class MyVector
{
public:
	MyVector()
	{
		Array = nullptr;
		curSzie = 0;
		capacity = 0;
	}
	MyVector(int size)
	{
		curSzie = 0;
		capacity = size;
		Array = new int[capacity];
	}
	void push_back(int number)
	{
		if (curSzie == capacity)
		{
			cerr << "数组超载了~,curSize="<<curSzie << endl;
		}
		Array[curSzie] = number;
		curSzie++;
	}
	int& operator[](int index)
	{
		if (index < 0 || index >= curSzie)
		{
			cerr << "访问越界" << endl;
		}
		return Array[index];
	}
	void showData()
	{
		for (int i = 0; i < curSzie; i++)
		{
			cout << setw(5) << setiosflags(ios::left) << Array[i];
		}
		cout << endl;
	}
	//两个数组之间赋值  =
	void operator=(MyVector& other)
	{
		//容量足够直接逐一复制
		if (this->capacity < other.curSzie)
		{
			clear();
			capacity = other.curSzie;
			Array = new int[capacity];	
		}
		for (int i = 0; i < other.curSzie; i++)
		{
			this->Array[i] = other.Array[i];
		}
		curSzie = other.curSzie;
	}
	//拷贝构造
	MyVector(MyVector& other)
	{
		capacity = other.curSzie;
		Array = new int[capacity];
		for (int i = 0; i < other.curSzie; i++)
		{
			this->Array[i] = other.Array[i];
		}
		curSzie = other.curSzie;
	}
	//对数组所有元素乘以一个数
	void square(int num)
	{
		for (int i = 0; i < curSzie; i++)
		{
			Array[i] *= num;
		}
	}
	//清除vector
	void clear()
	{
		if (Array != nullptr)
		{
			delete[] Array;
			Array = nullptr;
			curSzie = 0;
			capacity = 0;
		}	
	}
	~MyVector()
	{
		delete[] Array;
	}
private:
	int* Array;		//数组指针
	int curSzie;	//数组当前大小
	int capacity;	//数组最大容量
};
int main()
{
	MyVector arr(10);
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(i);
	}	
	arr.showData();

	MyVector vec=arr;
	vec.showData();

	MyVector vec1;
	vec1 = vec;
	vec1.showData();





	return 0;
}