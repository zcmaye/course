#include<iostream>
#include<functional>
using namespace std;
/*
namespace sp1
{
	template<typename T>
	T print(T t)
	{
		cout << t << endl;
		return t;
	}

	template<class ...Args>
	void unpack(Args ...args) {}

	template<typename ...Args>
	void foo(Args ...args)
	{
		//unpack(print(args)...);
		auto arr = {(print(args),0)...};
	}
}
namespace sp2
{
	template<typename ...Args>
	int baz(Args ...args)
	{
		return 0;
	}

	template<typename ...Args>
	void unpack(Args ...args) 
	
	{}

	template<typename ...Args>
	void foo(Args ...args)
	{
		unpack(baz(&args...) + args...);
	}

}
namespace sp3
{
	template<class T>
	T sum(T arg)
	{
		return arg;
	}

	template<typename T,typename ...Args>
	auto sum(T arg, Args ...args)
	{
		return arg + sum(args...);
	}
}
namespace sp4
{ 
//template<typename T, typename ...Args>
//void foo(T t, Args ...args)
//{
//	cout << t << endl;
//	foo(args...,0);
//}

	template<typename T>
	void foo(T t)
	{
		cout << t << endl;
	}

	template<typename T, typename ...Args>
	void foo(T t, Args ...args)
	{
		cout << t << endl;
		foo(args...);
	}
}
namespace sp5
{
	template<typename ...Args>
	auto sum(Args ...args)
	{
		return (args + ... +0);
	}
}
namespace sp6
{
	template<typename ...Args>
	void print(Args ...args)
	{
		(std::cout << ... << args)  << std::endl;
	}

	template<typename ...Args>
	auto andop(Args ...args)
	{
		return (args && ...);
	}
}

namespace sp7
{
	template<typename ...Args>
	class Derived : public Args...
	{
	public:
		Derived(const Args& ...args)
			:Args(args)...
		{}
	};

	class Base1
	{
	public:
		Base1() {}
		Base1(const Base1&)
		{
			std::cout << "copy ctor base1" << std::endl;
		}
	};

	class Base2
	{
	public:
		Base2() {}
		Base2(const Base2&)
		{
			std::cout << "copy ctor Base2" << std::endl;
		}
		void base2_show()
		{

		}
	};

}
namespace sp8
{
	template<template<typename ...> typename ...Args>
	class Bar : public Args<int, double>...
	{
	public:
		Bar(const Args<int, double>&...args)
			:Args<int, double>(args)...
		{}
	};

	template<typename ...Args>
	class Baz1 {};

	template<typename ...Args>
	class Baz2 {};

}
using namespace sp8;*/

int main()
{
	//创建tuple
	//1,使用构造函数
	//std::tuple<int, std::string> tp(100, "maye");
	//2,使用make_tuple
	auto tp = std::make_tuple(100, "maye");
	//3,右值引用版本
	//auto tp = std::forward_as_tuple(100, "maye");

	//修改数据
	get<0>(tp) = 10;
	//获取数据
	//1，根据位置获取
	cout << get<0>(tp) << " " << get<1>(tp) << endl;
	//2，tie
	//2.1 获取所有元素
	int number = -1;
	std::string name;
	tie(ignore, name) = tp;
	cout << number << "  " << name << endl;

	//2.2 从对象构建tuple
	auto tp1 = tie(number, name);

	//连接两个tuple
	auto ttp = tuple_cat(tp, tp1);
	
	std::pair<int, int> p;


	return 0;
}
