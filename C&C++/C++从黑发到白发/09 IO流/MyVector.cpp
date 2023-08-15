#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
//ʵ��һ��������,ʵ�ֻ�������
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
			cerr << "���鳬����~,curSize="<<curSzie << endl;
		}
		Array[curSzie] = number;
		curSzie++;
	}
	int& operator[](int index)
	{
		if (index < 0 || index >= curSzie)
		{
			cerr << "����Խ��" << endl;
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
	//��������֮�丳ֵ  =
	void operator=(MyVector& other)
	{
		//�����㹻ֱ����һ����
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
	//��������
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
	//����������Ԫ�س���һ����
	void square(int num)
	{
		for (int i = 0; i < curSzie; i++)
		{
			Array[i] *= num;
		}
	}
	//���vector
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
	int* Array;		//����ָ��
	int curSzie;	//���鵱ǰ��С
	int capacity;	//�����������
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