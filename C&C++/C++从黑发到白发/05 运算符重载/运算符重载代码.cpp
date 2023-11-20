#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Int
{
public:
	Int(int number = 0):_num(number) {};
	int& Data()
	{
		return _num;
	}
	int toInt()
	{
		return _num;
	}
	string toString()
	{
		return std::to_string(_num);
	}
	int	operator()()
	{
		return _num;
	}
private:
	int _num;
public:
	//���������
	Int operator+(const Int& right)
	{
		return Int(this->_num+right._num);
	}
	friend Int operator+(const int left,const Int& right)
	{
		return Int(left + right._num);
	}
	Int operator-(const Int& right)
	{
		return Int(this->_num - right._num);
	}
	Int operator*(const Int& right)
	{
		return Int(this->_num * right._num);
	}
	Int operator/(const Int& right)
	{
		return Int(this->_num / right._num);
	}
	Int operator%(const Int& right)
	{
		return Int(this->_num % right._num);
	}
	//���������
	Int& operator++()
	{
		this->_num++;
		return *this;
	}
	Int operator++(int)
	{
		Int t = *this;
		this->_num++;
		return t;
	}
	Int& operator--()
	{
		this->_num--;
		return *this;
	}
	Int operator--(int)
	{
		Int t = *this;
		this->_num--;
		return t;
	}
	//λ����� |     &     ~     ^     <<     >>    
	Int operator|(const Int&right)
	{
		return Int(this->_num | right._num);
	}
	Int operator&(const Int& right)
	{
		return Int(this->_num | right._num);
	}
	Int operator~()
	{
		return Int(~this->_num);
	}
	Int operator^(const Int& right)
	{
		return Int(this->_num ^ right._num);
	}
	Int operator<<(const Int& right)
	{
		return Int(this->_num << right._num);
	}
	Int operator>>(const Int& right)
	{
		return Int(this->_num >> right._num);
	}
	//�߼������ || && ��
	bool operator==(const Int& right)
	{
		return this->_num == right._num;
	}
	bool operator&&(const Int& right)
	{
		return this->_num && right._num;
	}
	bool operator!()
	{
		return !this->_num;
	}
	//��ֵ�����
	Int& operator=(const Int& right)
	{
		*this = right;
		return *this;
	}
	Int& operator+=(const Int& right)
	{
		this->_num += right._num;
		return *this;
	}
	Int& operator-=(const Int& right)
	{
		this->_num -= right._num;
		return *this;
	}
	Int& operator*=(const Int& right)
	{
		this->_num *= right._num;
		return *this;
	}
	Int& operator/=(const Int& right)
	{
		this->_num /= right._num;
		return *this;
	}
	Int& operator%=(const Int& right)
	{
		this->_num %= right._num;
		return *this;
	}
	Int& operator&=(const Int& right)
	{
		this->_num &= right._num;
		return *this;
	}
	//��Ŀ�����
	Int operator+()
	{
		return Int(+this->_num);
	}
	Int operator-()
	{
		return Int(-this->_num);
	}
	Int* operator&()
	{
		return this;
	}
	Int operator*()
	{
		return *this;
	}

	Int& operator,(Int& right)
	{
		return right;
	}
	
	//������������������<< >> 
	friend ostream& operator<<(ostream& out,const Int& num)
	{
		out << num._num;
		return out;
	}
	friend istream& operator>>(istream& in, Int& num)
	{
		in >> num._num;
		return in;
	}
};

//����()
class Fun
{
	typedef void (*PFUN)();
public:
	Fun(PFUN fun) :_pfun(fun) {}
	void operator()()
	{
		_pfun();
		std::cout << "operator()" << std::endl;
	}
private:
	
	PFUN _pfun;
};
void show()
{
	cout << "show" << endl;
}

//����ָ�� ����->  *
class Auto_ptr
{
public:
	Auto_ptr(Int* ptr) :_ptr(ptr) {}
	~Auto_ptr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
private:
	Int* _ptr;
public:
	Int* operator->()
	{
		return this->_ptr;
	}
	Int& operator*()
	{
		return  *_ptr;
	}
};

//MyVector ����[]
class MyVector
{
public:
	MyVector(int capacity) :_capacity(capacity)
	{
		_capacity = capacity;
		_size = 0;
		_base = new int[_capacity] {0};

	}
	void push_back(int number)
	{
		_base[_size++] = number;
	}
	int  operator[](int index)
	{
		return _base[index];
	}
	~MyVector()
	{
		if (_base)
		{
			delete[] _base;
			_base = nullptr;
		}
	}
private:
	int* _base;
	int _capacity;
	int _size;
};

int main()
{
	Int a(1);
	cin >> a;
	a *= 4;
	cout << a;


	return 0;
}
