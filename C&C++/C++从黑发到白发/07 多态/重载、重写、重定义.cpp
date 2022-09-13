#include<iostream>
using namespace std;
//类里面的同名函数是重载关系
class Parent
{
public:
	virtual void func()
	{
		cout << "Parent::func()" << endl;
	}
	virtual void func(int a,int b)
	{
		cout << "Parent::func(int a,int b) " <<a<<" "<<b<< endl;
	}
};
class Child:public Parent
{
public:
	virtual void func(int a, int b)
	{
		cout << "Child::func(int a, int b) " << a << " " << b << endl;
	}
	virtual void func(int a, int b, int c)
	{
		cout << "Child::func(int a, int b, int c) " << a << " " << b <<" "<<c<< endl;
	}
};
int main()
{
	//1,能访问func()吗？
	//Child c;
	//c.func();


	return 0;
}