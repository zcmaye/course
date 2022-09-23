#  STL基本概念

STL，英文全称 standard template library，中文可译为标准模板库或者泛型库，其包含有大量的模板类和模板函数，是 C++ 提供的一个基础模板的集合，用于完成诸如输入/输出、数学计算等功能。

STL 最初由惠普实验室开发，于 1998 年被定为国际标准，正式成为 C++ 程序库的重要组成部分。

STL的从广义上讲分为三类：algorithm（算法）、container（容器）和iteraotr（迭代器），容器和算法通过迭代器可以进行无缝地连接。几乎所有的代码都采 用了模板类和模板函数的方式，这相比于传统的由函数和类组成的库来说提供了更好的代码重用机会。

*STL细说六大件：*

​						*– 容器（Container）*

​						*– 算法（Algorithm）*

​						*– 迭代器（iterator）*

​						*– 仿函数（Function object）*

​						*– 适配器（Adaptor）*

​						*– 空间配制器（allocator）*

在C++标准中，STL被组织为下面的13个头文 件：\<algorithm>、\<deque>、\<functional>、\<iter>、\<vector>、\<list>、\<map>、\<memory>、\<numeric>、\<queue>、\<set>、\<stack> 和\<utility>。

#### 说了这么多，使用STL有什么好处呢？

1）STL是C++的一部分，因此不用额外安装什么，它被内建在你的编译器之内。

2）STL的一个重要特点是数据结构和算法的分离。尽管这是个简单的概念，但是这种分离确实使得STL变得非常通用。

3） 程序员可以不用思考STL具体的实现过程，只要能够熟练使用STL就OK了。这样他们就可以把精力放在程序开发的别的方面。

4） STL具有高可重用性，高性能，高移植性，跨平台的优点。

高可重用性：STL中几乎所有的代码都采用了模板类和模版函数的方式实现，这相比于传统的由函数和类组成的库来说提供了更好的代码重用机会。关于模板的知识，已经给大家介绍了。

高性能：如map可以高效地从十万条记录里面查找出指定的记录，因为map是采用红黑树的变体实现的。(红黑树是平横二叉树的一种)

高移植性：如在项目A上用STL编写的模块，可以直接移植到项目B上。

跨平台：如用windows的Visual Studio编写的代码可以在Mac OS的XCode上直接编译。

5） 了解到STL的这些好处，我们知道STL无疑是最值得C++程序员骄傲的一部分。每一个C＋＋程序员都应该好好学习STL。只有能够熟练使用STL的程序员，才是好的C++程序员。

6） 总之：招聘工作中，经常遇到C++程序员对STL不是非常了解。大多是有一个大致的映像，而对于在什么情况下应该使用哪个容器和算法都感到比较茫然。***STL是C++程序员的一项不可或缺的基本技能***，掌握它对提升C++编程大有裨益。

![img](assets/Alexander Stepanov.jpg)

<div align="center">Alexander Stepanov</div>

#### 容器

容器，置物之所也。

研究数据的特定排列方式，以利于搜索或排序或其他特殊目的，这一门学科我们称为数据结构。几乎可以说，任何特定的数据结构都是为了实现某种特定的算法。STL容器就是将运用最广泛的一些数据结构实现出来。

常用的数据结构：数组(array),链表(list),树(tree)，栈(stack),队列(queue),集合(set),映射表(map),根据数据在容器中的排列特性，这些数据分为***序列式容器***和***关联式容器***两种。

<font style="color:red">序列式容器：</font>即以线性排列（类似普通数组的存储方式）来存储某一指定类型（例如 int、double 等）的数据，需要特殊说明的是，该类容器并不会自动对存储的元素按照值的大小进行排序。。

<font style="color:red">关联式容器：</font>非线性排列(二叉树)，在存储元素时会为每个元素在配备一个键，整体以键值对的方式存储到容器中，可以通过键值直接找到对应的元素，而无需遍历整个容器。另外，关联式容器在存储元素，默认会根据各元素键值的大小做升序排序。

#### 算法

算法，问题之解法也。

以有限的步骤，解决逻辑或数学上的问题，这一门学科我们叫做算法(Algorithms).

广义而言，我们所编写的每个程序都是一个算法，其中的每个函数也都是一个算法，毕竟它们都是用来解决或大或小的逻辑问题或数学问题。STL收录的算法经过了数学上的效能分析与证明，是极具复用价值的，包括常用的排序，查找等等。特定的算法往往搭配特定的数据结构，算法与数据结构相辅相成。

算法分为:***质变算法***和***非质变算法***。

质变算法：是指运算过程中会更改区间内的元素的内容。例如拷贝，替换，删除等等

非质变算法：是指运算过程中不会更改区间内的元素内容，例如查找、计数、遍历、寻找极值等等

#### 迭代器

迭代器(iterator)是一种抽象的设计概念，现实程序语言中并没有直接对应于这个概念的实物。

iterator模式定义如下：提供一种方法，使之能够依序寻访某个容器所含的各个元素，而又无需暴露该容器的内部表示方式。(实际上是封装了指针的类中类)

迭代器的设计思维-STL的关键所在，STL的中心思想在于将容器(container)和算法(algorithms)分开，彼此独立设计，最后再一贴胶着剂将他们撮合在一起。从技术角度来看，容器和算法的泛型化并不困难，c++的class template和function template可分别达到目标，如果设计出两这个之间的良好的胶着剂，才是大难题。

迭代器的种类:

|      种类      |                             功能                             |                  操作                   |
| :------------: | :----------------------------------------------------------: | :-------------------------------------: |
|   输入迭代器   |                     提供对数据的只读访问                     |          只读，支持++、==、!=           |
|   输出迭代器   |                     提供对数据的只写访问                     |              只写，支持++               |
|   前向迭代器   |               提供读写操作，并能向前推进迭代器               |          读写，支持++、==、!=           |
|   双向迭代器   |               提供读写操作，并能向前和向后操作               |           读写，支持++、--，            |
| 随机访问迭代器 | 提供读写操作，并能以跳跃的方式访问容器的任意数据，是功能最强的迭代器 | 读写，支持++、--、[n]、-n、<、<=、>、>= |

#### 容器、迭代器、算法分离案例

```cpp
#include<iostream>
using namespace std;

template<typename Ty>
class Vector
{
public:
	using iterator = Ty*;
public:
	Vector(int size) :_base(nullptr), _capacity(size), _size(0)
	{
		_base = new Ty[_capacity];
	}
	Ty& operator[](int index)
	{
		return _base[index];
	}
	void push_back(Ty val)
	{
		if (_size >= _capacity && !_inc())
		{
			throw std::out_of_range("run out of memory^V^");
		}
		_base[_size++] = val;
	}
	size_t size()
	{
		return _size;
	}
	size_t capacity()
	{
		return _capacity;
	}
public:
	iterator begin()
	{
		return _base;
	}
	iterator end()
	{
		return _base+_size;
	}
private:
	bool _inc(void)
	{
		Ty* ptr = _base;				//保存原数据

		try
		{
			_base = new Ty[_capacity + 8];	//分配新空间
		}
		catch (std::bad_alloc&)
		{
			return false;					//分配失败返回false
		}
	
		memcpy(_base, ptr, _capacity*sizeof(Ty));	//拷贝数据
		_capacity = _capacity + 8;		//更新容量
		delete[]ptr;					//释放旧内存
		return true;
	}
private:
	Ty* _base;
	int _capacity;
	int _size;
};

int main()
{
	/*
	//容器
	int arr[5] = { 1,2,3,4,5 };
	//方式1
	for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	//方式2
	int* iter = arr;
	for (iter = arr; iter != arr + 5; iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//方式3
	using  iterator = int*;
	iterator begin = arr;
	iterator end = arr + 5;
	for (iterator it = begin; it != end; it++)
	{
		cout << *it << " ";
	}*/
	Vector<int> vec(5);
	for (size_t i = 0; i < vec.capacity(); i++)
	{
		vec.push_back(i);
	}

	//方式1
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	//方式2
	int* iter = &vec[0];
	for (iter; iter != &vec[vec.size()]; iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	//方式3
	using  iterator = int*;
	iterator begin = &vec[0];
	iterator end = &vec[vec.size()];
	for (iterator it = begin; it != end; it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//方式4
	Vector<int>::iterator it = vec.begin();
	for (it; it != vec.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
```

如果是链表，通过using定义别名的方式是不行的,链表的指针不能直接++，为了让iterator支持++操作，必须封装一个类，一下是完整版

```cpp
#include<iostream>
using namespace std;

template<typename Ty>
class Vector
{
public:
	//using iterator = Ty*;
public:
	Vector(int size) :_base(nullptr), _capacity(size), _size(0)
	{
		_base = new Ty[_capacity];
	}
	Ty& operator[](int index)
	{
		return _base[index];
	}
	void push_back(Ty val)
	{
		if (_size >= _capacity && !_inc())
		{
			throw std::out_of_range("run out of memory^V^");
		}
		_base[_size++] = val;
	}
	size_t size()
	{
		return _size;
	}
	size_t capacity()
	{
		return _capacity;
	}
public:
	class iterator
	{
	public:
		iterator(Ty* ptr = nullptr):_ptr(ptr){}
		~iterator() {}
		iterator operator++()
		{
			//curNode = curNode->next;
			_ptr++;
			return *this;
		}
		iterator operator++(int)
		{
			//curNode = curNode->next;
			return iterator(_ptr++);
		}
		bool operator!=(const iterator& right)
		{
			return this->_ptr != right._ptr;
		}
		Ty& operator*()
		{
			return *_ptr;
		}
		Ty* operator->()
		{
			return _ptr;
		}
	private:
		Ty* _ptr;
	};
	iterator begin()
	{
		return iterator(_base);
	}
	iterator end()
	{
		return iterator(_base+_size);
	}

private:
	bool _inc(void)
	{
		Ty* ptr = _base;				//保存原数据

		try
		{
			_base = new Ty[_capacity + 8];	//分配新空间
		}
		catch (std::bad_alloc&)
		{
			return false;					//分配失败返回false
		}
	
		memcpy(_base, ptr, _capacity*sizeof(Ty));	//拷贝数据
		_capacity = _capacity + 8;		//更新容量
		delete[]ptr;					//释放旧内存
		return true;
	}
private:
	Ty* _base;
	int _capacity;
	int _size;
};

int main()
{
	/*
	//容器
	int arr[5] = { 1,2,3,4,5 };
	//方式1
	for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	//方式2
	int* iter = arr;
	for (iter = arr; iter != arr + 5; iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
	//方式3
	using  iterator = int*;
	iterator begin = arr;
	iterator end = arr + 5;
	for (iterator it = begin; it != end; it++)
	{
		cout << *it << " ";
	}
	//方式4
	for (auto& val : arr)
	{
		cout << val << endl;
	}
	*/
	Vector<int> vec(5);
	for (size_t i = 0; i < vec.capacity(); i++)
	{
		vec.push_back(i);
	}

	//方式1
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	//方式2
	int* iter = &vec[0];
	for (iter; iter != &vec[vec.size()]; iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	//方式3
	using  iterator = int*;
	iterator begin = &vec[0];
	iterator end = &vec[vec.size()];
	for (iterator it = begin; it != end; it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//方式4  没有写迭代器类是使用不了的
	for (auto& val : vec)
	{
		cout << val << endl;
	}

	//方式5
	Vector<int>::iterator it = vec.begin();
	
	for (it; /*it.operator!=(vec.end()) */it != vec.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
```

#### initializer_list聚合初始化

数组可以用聚合的方式初始化，int arr[]={1,3,1,4,5,2,0};那么咱们自己写的vector能用聚合初始化吗？

答案是否定的，那么怎么做才能使用聚合形式进行初始化呢？

C++11提供的新模板类型initializer_list<T>,有了它之后咱们就可以使用聚合进行初始化啦！

用法：

```cpp
void show(initializer_list<int> ls)
{
	for (int i : ls)
	{
		cout << i << " ";
	}
}

show({ 1,3,1,4,5,2,0 });//输出
```

同理，在类中我们可以提供一个initializer_list类型的构造函数

```cpp
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
```

# 仿函数

#### 可调用对象(Callable object)

函数调用需要使用"()"，这个“()”叫做`函数调用用运算符`。在面向对象编程世界里，一切皆为对象，对象是程序的基本单元。那么这个可调用的函数名，被称为可调用对象。

在C++中除了函数可以调用之外，重载了operator()的类，也是可以调用的，也可成为可调用对象

*C++中的可调用对象有以下几种：*

​						*– 函数（function）*

​						*– 函数指针（function pointer）*

​						*– 仿函数（Functor）*

​						*– lambda表达式*

​						*– bind 函数封装的函数对象*

函数和函数指针不用多说，从仿函数开始把~

#### 仿函数

仿函数（Functor）又称为函数对象（Function Object）是一个能行使函数功能的类，仿函数是定义了一个含有operator()成员函数的对象，可以视为一个一般的函数，只不过这个函数功能是在一个类中的运算符operator()中实现，是一个函数对象，它将函数作为参数传递的方式来使用。

写一个简单类，除了维护类的基本成员函数外，只需要重载 operator() 运算符 。这样既可以免去对一些公共变量的维护，也可以使重复使用的代码独立出来，以便下次复用。

STL 中也大量涉及到仿函数，有时仿函数的使用是为了函数拥有类的性质，以达到安全传递函数指针、依据函数生成对象、甚至是让函数之间有继承关系、对函数进行运算和操作的效果。比如 STL 中的容器 set 就使用了仿函数 less ，而 less 继承的 binary_function，就可以看作是对于一类函数的总体声明，这是函数做不到的。



#### 为什么要有仿函数？

1，假如客户有一个需求摆在我们的面前,编写一个函数：函数可以获得斐波拉契数列每项的值；每调用一次便返回一个值；函数可根据需要重复使用。

​    我们之前在 C 语言中也讲过斐波拉契数列，相信这个很好实现了。那么我们就编写的程序如下

```cpp
int fibonacci()
{
	static int a0 = 0;	//第一项
	static int a1 = 1;	//第二项

	int ret = a1;		//保存
	a1 = a0 + a1;
	a0 = ret;

	return ret;
}
int main()
{
	for (size_t i = 0; i < 5; i++)
	{
		cout << fibonacci() << " ";		//1 1 2 3 5
	}
	cout << endl;
	for (size_t i = 0; i < 5; i++)
	{
		cout << fibonacci() << " ";		//8 13 21 34 55
	}
	return 0;
}
```

我们就开心的完成任务了，于是交给客户了。过两天，客户又给打回来了。说是存在几个问题：函数一但调用就无法重来，静态局部变量处于函数内部，外界无法改变。函数为全局函数，是唯一的，无法多次独立使用。无法指定某个具体的数列项作为初始值。

​    于是我们想着将静态局部变量改为去全局变量，再次重新调用时，便将全局变量重新初始化，重新如下

```cpp
int a0 = 0;	//第一项
int a1 = 1;	//第二项
int fibonacci()
{
	int ret = a1;
	a1 = a0 + a1;
	a0 = ret;

	return ret;
}

int main()
{
	for (size_t i = 0; i < 5; i++)
	{
		cout << fibonacci() << " ";		//1 1 2 3 5 8
	}
	cout << endl;

	a0 = 0;
	a1 = 1;
	for (size_t i = 0; i < 5; i++)
	{
		cout << fibonacci() << " ";		//1 1 2 3 5 8
	}
	return 0;
}
```

 是满足这个需求了，但是要在使用时需要重新初始化全局变量，客户肯定不干啊。所以这个解决方案不可行。于是乎，我们在 C++ 中一个吊炸天的技术来了：函数对象。

先来说说函数对象：

a> 使用具体的类对象取代函数；

b> 该类的对象具备函数调用的行为；

c> 构造函数指定具体数列项的起始位置；

d> 多个对象相互独立的求解数列项。

​    同样函数对象也是通过函数调用操作符()，便是重载操作符了。它只能通过类的成员函数重载，可以定义不同参数的多个重载函数。

​    下来我们来看看最终的解决方案

```cpp
class Fibonacci
{
public:
	Fibonacci() :_a0(0), _a1(1) {}
	Fibonacci(int n) :_a0(0), _a1(1) 
	{
		for (int i = 0; i < n; i++)
		{
			int ret = _a1;
			_a1 = _a0 + _a1;
			_a0 = ret;
		}
	}
	int operator()()
	{
		int ret = _a1;
		_a1 = _a0 + _a1;
		_a0 = ret;
		return ret;
	}
private:
	int _a0;
	int _a1;
};


int main()
{
	Fibonacci fib;
	for (size_t i = 0; i < 5; i++)
	{
		cout << fib() << " ";		//1 1 2 3 5 8
	}
	cout << endl;

	Fibonacci fib1(9);
	for (size_t i = 0; i < 5; i++)
	{
		cout << fib1() << " ";		//55 89 144 233 377
	}
	return 0;
}
```

我们看到已经实现了所有需求，并且随时想从哪个数开始都行。



2，比如，有一个简单需求：统计一个`vector<int>`中，元素等于3的数量。解决方法可能会是：

```cpp
int equal_count(const vector<int>::iterator& first,const vector<int>::iterator& last,const int& val)
{
	int size = 0;
	for (auto it = first; it != last; it++)
	{
		if (*it == val)
		{
			size++;
		}
	}
	return size;
}
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
	//统计v中元素等于3的元素个数
	size_t size = equal_count(v.begin(), v.end(), 3);
	cout << size << endl;	//output:3

	return 0;
}
```

其实，统计容器中某个元素的数量，C++中有一个函数count

```cpp
size_t count(const Iter First, const Iter Last, const Ty& Val);
```

对于上面的统计元素个数没有拓展性。比如：统计v中元素大于于3的元素个数呢？为此我们必须再设计一个greater_count函数：

```cpp
int great_count(const vector<int>::iterator& first, const vector<int>::iterator& last, const int& val)
{
	int size = 0;
	for (auto it = first; it != last; it++)
	{
		if (*it > val)
		{
			size++;
		}
	}
	return size;
}
```

这样写就很麻烦，我只需要改变一下规则，就需要多一个函数，咱们可以把里面的比较规则，写成一个函数(可调用的对象),通过传参实现比较。

```cpp
//using FunType = bool (*)(int, int);
template<typename FunType>
int count_if(const vector<int>::iterator& first, const vector<int>::iterator& last,FunType cmp,const vector<int>::value_type& val)
{
	int size = 0;
	for (auto it = first; it != last; it++)
	{
		if (cmp(*it,val))
		{
			size++;
		}
	}
	return size;
}
bool equal(int a, int b)
{
	return a == b;
}
bool great(int a, int b)
{
	return a > b;
}
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
	//统计v中元素等于3的元素个数
	size_t size;
	size = count_if(v.begin(), v.end(), equal,3);
	cout << size << endl;
	//统计v中元素大于3的元素个数
	size = count_if(v.begin(), v.end(), great,3);
	cout << size << endl;
	
	return 0;
}
```

这样是不是就轻松很多了，但是这里的统计元素3，我们要通过count_if传到比较函数里面去，非常的丑陋对不对。有一种写法，可以不通过参数传进去。

首先，删掉count_if中的最后一个参数val。

然后，把equal和great稍加修改一下。

```cpp
template<typename FunType>	
int count_if(const vector<int>::iterator& first, const vector<int>::iterator& last, FunType cmp)
{
	int size = 0;
	for (auto it = first; it != last; it++)
	{
		if (cmp(*it))
		{
			size++;
		}
	}
	return size;
}
bool equal(int a)
{
	return a == 3;
}
bool great(int a)
{
	return a > 3;
}
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
	//统计v中元素等于3的元素个数
	size_t size;
	size = count_if(v.begin(), v.end(), equal);
	cout << size << endl;
	//统计v中元素大于3的元素个数
	size = count_if(v.begin(), v.end(), great);
	cout << size << endl;
	
	return 0;
}
```

或者使用lambda表达式

```cpp
vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
//统计v中元素等于3的元素个数
size_t size;
//size = equal_count(v.begin(), v.end(), 3);
size = count_if(v.begin(), v.end(), [](auto val) 
	{
			return val == 3; 
	});
cout << size << endl;
//统计v中元素大于3的元素个数
size = count_if(v.begin(), v.end(), [](auto val)
	{
		return val > 3;
	});
cout << size << endl;
```

其实lamda表达式出现之后(C++11)，仿函数(C++98)的作用已经被削弱了，使用lamda会让我们使用STL方便许多。

> 对于count_if  <algorithm>里有和我们写的一模一样的函数，以后直接使用即可

那么使用仿函数，怎么实现上述功能呢？

```cpp
struct Equal
{
	bool operator()(int val)
	{
		return val == 3;
	}
};
struct Great
{
	bool operator()(int val)
	{
		return val > 3;
	}
};
int count_if(const vector<int>::iterator& first, const vector<int>::iterator& last, FunType cmp);
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
	//统计v中元素等于3的元素个数
	size_t size;
	size = count_if(v.begin(), v.end(), Equal());
	cout << size << endl;
	//统计v中元素大于3的元素个数
	size = count_if(v.begin(), v.end(), Great());
	cout << size << endl;
	
	return 0;
}
```

可以继续升级~

```cpp
struct Equal
{
	Equal(int usrVal) :_usrVal(usrVal) {}
	bool operator()(int val)
	{
		return val == _usrVal;
	}
	int _usrVal;
};
struct Great
{
	Great(int usrVal) :_usrVal(usrVal) {}
	bool operator()(int val)
	{
		return val > _usrVal;
	}
	int _usrVal;
};
int count_if(const vector<int>::iterator& first, const vector<int>::iterator& last, FunType cmp);
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,1,3,1,4,3,2,1 };
	//统计v中元素等于3的元素个数
	size_t size;
	size = count_if(v.begin(), v.end(), Equal(2));
	cout << size << endl;
    
	//统计v中元素大于3的元素个数
	size = count_if(v.begin(), v.end(), Great(5));
	cout << size << endl;
	
	return 0;
}
```

这就是仿函数的妙用，怎么样，你学废了嘛？



#### 仿函数优点

如果可以用仿函数实现，那么你应该用仿函数，而不要用CallBack。原因在于：

+ 仿函数可以不带痕迹地传递上下文参数。而CallBack技术通常使用一个额外的void*参数传递。这也是多数人认为CallBack技术丑陋的原因。

+ 仿函数技术可以获得更好的性能，这点直观来讲比较难以理解。

#### 仿函数作用

仿函数通常有下面四个作用：

+ 作为排序规则，在一些特殊情况下排序是不能直接使用运算符<或者>时，可以使用仿函数。
+ 作为判别式使用，即返回值为bool类型。
+ 同时拥有多种内部状态，比如返回一个值得同时并累加。
+ 作为算法for_each的返回值使用。

## 函数对象

> 头文件<functional>

*函数对象*是专门设计用于使用类似于函数的语法的对象。在 C++ 中，这是通过`operator()`在其类中定义成员函数来实现的。

它们通常用作函数的参数，例如传递给标准算法的谓词或比较函数。

### 函数

这些函数根据其参数创建包装类的对象

#### bind

用来绑定函数调用的某些参数，可以将bind函数看作一个通用的函数包装器，它接受一个可调用对象，并返回函数对象。

返回的函数对象参数从前往后，可以依次编号，从1开始；然后可以把传入的参数对原来的参数进行绑定。

**1. 绑定普通函数**

```cpp
void show(int number, const std::string& str)
{
	cout << number << " " << str << endl;
}
```

+ 顺序绑定参数

  ```cpp
  auto bind_show = std::bind(show, placeholders::_1, placeholders::_2);
  bind_show(2,"world");
  ```

+ 交换参数位置

  ```cpp
  auto bind_show1 = std::bind(show, placeholders::_2, placeholders::_1);
  bind_show1("world",1314520);
  ```

+ 绑定固定参数

  ```cpp
  auto bind_show3 = std::bind(show, 888,placeholders::_1);
  bind_show3("玩蛇老师");
  ```

**2. 绑定成员函数**

```cpp
struct Plus
{
	int plus(int a, int b)
	{
		return a * b;
	}
};	
{
	Plus plus;
	auto func1 = std::bind(&Plus::plus, &plus, placeholders::_1, placeholders::_2);	//绑定对象指针
    auto func2 = std::bind(&Plus::plus, plus, placeholders::_1, placeholders::_2);	//绑定对象或引用
	cout << func1(2, 4) << endl;
}
```

**3. 绑定函数对象**

```cpp
struct Sub
{
	int operator()(int a, int b)
	{
		return a * b;
	}
};
{
	auto func2 = std::bind(Sub(), placeholders::_1, placeholders::_2);
	cout << func2(3, 4) << endl;
}
```

**4. 绑定lambda表达式**

```cpp
{	
	auto func3 = std::bind([](int a, int b) {return a / b; }, placeholders::_1, placeholders::_2);
	cout << func3(6 ,2) << endl;
}
```



#### not1

返回一元函数对象的否定，只能对仿函数进行否定，普通函数不行。

> ##### 一元函数又叫一元谓词
>
> 谓词( *predicate* )是指普通函数或重载的operator()返回值是bool类型的函数对象(仿函数)。如果operator()接受一个参数，那么叫做一元谓词,如果接受两个参数，那么叫做二元谓词，谓词可作为一个判断式。

```cpp
struct Greater5 
	:public unary_function<int, bool>		//必须继承自一元函数类
{
	bool operator()(int val) const			//必须加上const
	{
		return val > 5;
	}
};

int main()
{
	cout << boolalpha << Greater5()(10) << endl;
	auto _less5 = not1(Greater5());
	cout << boolalpha << _less5(10) << endl;
    return 0;
}
```





#### not2

返回二元函数对象的否定，只能对仿函数进行否定，普通函数不行。

```cpp
struct Greater
    :public binary_function<int,int,bool>	//必须继承自二元函数类
{
	bool operator()(int a, int b) const		//必须加上const
	{
		return a > b;
	}
};

int main()
{
	cout << boolalpha << Greater()(3, 1) << endl;;

	auto _less = not2(Greater());
	cout << boolalpha << _less(3,1) << endl;;

	return 0;
}
```



#### ref、cref

构造一个适当的reference_wrapper类型的对象来保存对elem的引用。

+ ref 普通引用

+ cref 常引用

```cpp
struct Inc
{
	mutable int number = 0;
	void operator()()const
	{
		cout << number << endl;
		number++;
	}
};

int main()
{
	Inc inc;
	auto func = bind(std::cref(inc));
	func();
	inc();
    return 0;
}
```

#### mem_fun

把成员函数转为函数对象，使用对象指针或对象(引用)进行绑定

```cpp
class Foo
{
public:
	int a{ 100 };
	void print()
	{
		cout << a << endl;
	}
	void print2(int val)
	{
		cout << a << " val:" << val << endl;
	}
};

int main()
{
	Foo f;
	//把成员函数转为函数对象，使用对象指针或对象(引用)进行绑定
	auto func = mem_fn(&Foo::print);
	func(f);		//把对象传进去
	func(&f);		//对象指针也行
	func(Foo());	//临时对象也行

	//把成员函数转为函数对象，使用对象指针进行绑定
	auto func1 = mem_fun(&Foo::print2);
	func1(&f,666);

	//把成员函数转为函数对象，使用对象(引用)进行绑定
	auto func2 = mem_fun_ref(&Foo::print);
	func2(f);

	return 0;
}
```

##### 示例

```cpp
struct Foo
{
	int v;
	Foo(int val = -1)
		:v(val) {}
	void print()
	{
		cout <<v << endl;
	}
};

int main()
{
	//让每个对象都调用指定的成员函数
	std::vector<Foo> vec(5);	//存对象
	for_each(vec.begin(), vec.end(), mem_fn(&Foo::print));
	
	cout << endl;

	//让每个对象都调用指定的成员函数
	std::vector<Foo*> vec_ptr;	//存指针
	for (int i = 0; i < 5; i++)
	{
		vec_ptr.push_back(new Foo(i*3));
	}	
	for_each(vec_ptr.begin(), vec_ptr.end(), mem_fn(&Foo::print));

	return 0;
}
```



##### 总结

| **函数**      | **作用**                                                 |
| :------------ | :------------------------------------------------------- |
| `mem_fun`     | 把成员函数转为函数对象，使用对象指针进行绑定             |
| `mem_fun_ref` | 把成员函数转为函数对象，使用对象(引用)进行绑定           |
| `mem_fn`      | 把成员函数转为函数对象，使用对象指针或对象(引用)进行绑定 |
| `bind`        | 包括但不限于mem_fn的功能，更为通用的解决方案             |

### 包装类

包装类是包含一个对象并具有与该对象类似的接口的类，但添加或更改了它的一些特性：

#### funtion

> 函数包装器

该函数包装器模板能包装任何类型的可调用实体，如普通函数、函数对象(仿函数)、lambda表达式以及bind创建的对象。

通过function类型可以将多个不同类型的可调用对象，整合到一个类型中。

1. 包装普通函数

   ```cpp
   int add(int a, int b)
   {
   	return a + b;
   }
   
   {
   	std::function<int(int, int)> fun_add(add);
   	cout<<fun_add(2, 3);
   }
   ```

2. 包装成员函数(通过bind绑定)

   ```cpp
   class Maye
   {
   public:
   	int add(int a, int b)
   	{
   		return a + b;
   	}
   };
   
   {
   	Maye maye;
   	std::function<int(int, int)> fun_maye_add(std::bind(&Maye::add, &maye,placeholders::_1,placeholders::_2));
   	cout << fun_maye_add(3, 5);
   }
   ```

3. 包装lambda表达式

   ```cpp
   {
       std::function<int(int, int)> fun_lambda_add([](int a, int b)->int 
                                                       {
                                                           return a + b; 
                                                       });
   	cout << fun_lambda_add(7, 8) << endl;
   }
   ```

4. 包装函数对象

   ```cpp
   class Maye
   {
   public:
   	int operator()(int a, int b)
   	{
   		return a * b;
   	}
   };
   
   {		
   	Maye obj;
   	std::function<int(int, int)> fun_functor(obj);
   	cout << fun_functor(2,4);
   }
   ```

#### reference_wrapper

引用包装器，std::ref函数返回的对象。

#### unary_negate

否定一元函数(谓词)对象类，std::not1函数返回的对象

#### binary_negate

否定二元函数(谓词)对象类，std::not2返回的对象

# 序列式容器

## string

#### string概念

+ string是STL的字符串类型，通常用来表示字符串。而在使用string之前，字符串通常是用char*表示的。string与char*都可以用来表示字符串，那么二者有什么区别呢。

**string和char*的比较**

+ string是一个类, char*是一个指向字符的指针。

  ​     *string封装了char\*，管理这个字符串，是一个char\*型的容器*

+ string不用考虑内存释放和越界。

  ​     *string管理char*所分配的内存。每一次string的复制，取值都由string类负责维护，不用担心复制越界和取值越界等。

+ string提供了一系列的字符串操作函数（这个等下会详讲）

  	*查找find，拷贝copy，删除erase，替换replace，插入insert*

#### string的构造函数

```cpp
string();									//默认构造
string(const char* ptr);					//char*指向的字符串
string(const string& right);				//拷贝构造
string(string&& right);						//移动构造
string(iter first,iter last);				//以相同顺序复制[first，last)范围内的字符
string(const size_t count,const char c);	//生成count个由字符c组成的序列
string(const char *ptr,size_t count);		//char*指向的字符串，前count个字符
```

#### string的存取字符操作

```cpp
ostream& operator<<(ostream& out,string& right);	//直接输出string
char& operator[](size_t off);						//获取off下标的字符(相对于首地址的偏移)
char& at(size_t off);								//同上  但是越界会抛异常
char& front();										//获取头部元素
char& back();										//获取尾部元素
```

#### string容量相关

```cpp
size_t size();								//获取字符串长度
size_t length();							//同上
size_t max_size();							//字符串可以存储的最大长度
size_t capacity();							//获取string内部存储字符串的内存大小，自动扩容
void   reserve(size_t n);					//请求更改容量，如果n大于当前字符串的容量，则使容器将其容量增加到n个字符（或更大）,小于可能不予理会(与实现有关)	
void   resize(size_t n,char c = '\0');		//调整字符串大小, 如果n小于当前字符串长度，则当前值将缩短为它的前n个字符，并删除第n个字符之外的字符。 如果n大于当前字符串的长度,则以c进行填充多余空间。
void   clear();								//清空字符串，长度变为0
bool   empty();								//判断是否为空串，即size == 0
void   shrink_to_fit();						//请求sting减小其容量到合适大小(可能不予理会)
```

#### string修改

```cpp
string& operator+=(string& right);
string& operator+=(char * str);
string& operator+=(char c);
//append
string& append(string& right);
string& append(string& right,size_t pos,size_t sublen = npos);	//从right pos位置开始，复制sublen长度到this
string& append(char *str);
string& append(char *str,size_t n);		//把str的前n个追加到当前string
string& append(size_t n,char c);		//追加n个字符c
string& append(iter first,iter last);	//以相同顺序追加[first，last)范围内的字符

void push_back(char c);					//追加字符c
//和构造函数差不多
string& assign(...);					//为字符串分配一个新值，替换其当前内容
//和append差不多，只是多了个插入位置
string& insert(size_t pos,string& str);	//将str插入到pos所指示的字符之前

string& erase(size_t pos = 0,size_t len = npos);	//删除从pos开始跨越len个字符的部分
iterator erase(iter p);						//删除p指向的字符		
iterator erase(iter first,iterator last);	//删除[first,last)范围内的字符


string& replace(size_t pos,size_t len,string &str);
string& replace(iter i1, iter i2, const string& str);	
string& replace(size_t pos,  size_t len,  const string& str,
                size_t subpos, size_t sublen);
string& replace(size_t pos,  size_t len,  const char* s);
string& replace(size_t pos,  size_t len,  const char* s, size_t n);
string& replace(iter i1, iter i2, const char* s, size_t n);
string& replace(size_t pos,  size_t len,  size_t n, char c);
string& replace(iter i1, iter i2, size_t n, char c);

template <class Inputiter>
string& replace (iter i1, iter i2,Inputiter first, Inputiter last);


void swap(string& str);					//交换两个string的内容
void swap(string& left,string& right);	//全局重载

void pop_back();						//删除最后一个字符
```

#### string操作

```cpp
const char* c_str();			//获取c风格字符串
const char* data();				//同上
size_t copy(char* s,size_t len,size_t pos = 0);//把当前串中以pos开始的len个字符拷贝到以s为起始位置的字符数组中，返回实际拷贝的数目。注意要保证s所指向的空间足够大以容纳当前字符串，不然会越界。

//find:返回查找到的起始下标，找不到返回string::npos
size_t find(const string& str, size_t pos = 0);	//从pos位置开始查找str
size_t find(const char* s, size_t pos = 0);	//从pos位置开始查找s
size_t find(const char* s, size_t pos, size_t n);//把s中的前n个字符，在string中的pos位置开始查找
size_t find(char c, size_t pos = 0);	//从pos位置开始查找字符c
size_t rfind(...);						//同上，只不过是反向查找
size_t find_first_of(...);				//查找与参数中字符串任意一个字符匹配的第一个字符
size_t find_last_of(...);				//同上，反向查找
size_t find_first_of(...);				//查找与参数中字符串任意一个字符都不匹配的第一个字符
size_t find_last_of(...);				//同上，反向查找
string substr(size_t pos=0,size_t len=npos);//返回一个新构造的string对象，其值初始化为该对象的子字符串的副本。
```

#### string静态成员

+ npos是一个静态成员常量值，被定义为-1，但是size_t是unsigned int，值是最大值(4294967295)
+ 用作字符串成员函数中*len*（或*sublen*）参数的值时，此值表示*“直到字符串结尾”*。 
+ 作为返回值，通常用于表示没有匹配项。



## array

#### array概念

array是一个容器，封装了固定大小的数组。

该容器是聚合类型，其语义与C风格数组的结构相同， T [ N ]作为其唯一的非静态数据成员。与c风格数组不同的是，它不会自动衰减为T*。(数组名不会自动转为数组首地址)

该容器将C风格数组的``性能``和``可访问性``与标准容器的优点相结合，比如知道自己的大小、支持赋值、随机访问迭代器等。

#### array初始化

array没有构造函数，也没有私有或保护成员，这就意味着它不会自动初始化。如果不对其初始化而直接获取其中的值，读出来的是野值。

可以使用聚合表达式（花括号）对其初始化。

```cpp
array<int,5> arr = {1,2,3,4,5};
```

如果花括号内元素个数小于数组容量，则会为剩余元素自动赋默认值。

也可以用`fill`函数对其填充。

```cpp
array<int,10> arr;
arr.fill(3);
```

对于元素类型和数组大小相同的array，可以直接进行赋值

```cpp
array<int,5> a1;
array<int,5> a2 = a1;
```



#### array元素访问

```cpp
Ty& operator[](size_t i);
Ty& at(size_t i);
Ty& front();
Ty& back();
Ty* data();						//返回指向数组中第一个元素的指针
```

#### array容量相关

```cpp
size_t size();					//返回数组大小
size_t max_size();				//返回数组大小
size_t empty();					//返回数组是否为空
```

#### array修改

```cpp
void fill(const Ty& val);		//把所有元素都设置为val
void swap(array<Ty,?>& other);	//交换两个array的数据，类型和大小必须一致
```



## vector

#### Vector概念

vector 容器是 STL 中最常用的容器之一，它和 array 容器非常类似，都可以看做是对 C++普通数组的“升级版”。不同之处在于，array 实现的是静态数组（容量固定的数组），而 vector 实现的是一个动态数组，即可以进行元素的插入和删除，在此过程中，vector 会动态调整所占用的内存空间，整个过程无需人工干预。

vector尾部添加或移除元素非常快速。但是在中部或头部插入元素或移除元素比较费时

#### vector的构造函数

```cpp
vector();
vector(initializer_list<_Ty> list);			//可以用聚合{}的方式初始化
vector(size_t size);						//指定vector初始大小
vector(size_t size, const Ty& val);			//指定大小，并把每个数据都设置为val
vector(Iter first, Iter last);				//以相同顺序复制[first,last)范围内的元素
vector(const vector& _Right);				//拷贝构造
vector(vector&& _Right);					//移动构造
```

#### vector元素访问

 ```cpp
Ty& operator[](size_t i);
Ty& at(size_t i);
Ty& front();
Ty& back();
Ty* data();						//返回指向数组中第一个元素的指针
 ```

#### vector容量相关

```cpp
size_t size();								//获取vector有效元素个数
size_t max_size();							//可以存储的最大元素数量
size_t capacity();							//获取当前容量，自动扩容
void   reserve(size_t n);					//请求更改容量，如果n大于当前字符串的容量，则使容器将其容量增加到n个字符（或更大）,小于可能不予理会(与实现有关)	
void   resize(size_t n);					//调整vector大小为n,n小于当前size，多余的数据会被丢掉
void   resize(size_t n,const Ty& val);		//如果n>size,剩下的用val填充
void   clear();								//清空数据，长度变为0
bool   empty();								//判断是否为空串，即size == 0
void   shrink_to_fit();						//请求vector减小其容量到合适大小
```



#### vector修改

```cpp
void push_back(const Ty& val);			//在尾部插入元素
void push_back(Ty&& val);				//同上
void emplace(Iter where,_Valty&& val);	//效率比较高
void emplace_back(_Valty&& val)
void pop_back();						//删除尾部元素

 void assign(const size_t size, const Ty& val);//设置新的大小，并用val设置所有值
 void assign(Iter First, Iter Last);		  //以相同顺序复制[first,last)范围内的元素
 void assign(initializer_list<_Ty> Ilist);	  //同时赋值多个元素
     
iter insert(iter _Where, const Ty& Val);	  //指定位置插入元素		
iter insert(iter _Where, const size_t Count, const Ty& val);//指定位置插入，并且可以指定插入数量
iter insert(iter _Where, Iter First, Iter Last);//指定位置插入[first,last)之间的元素
iter insert(iter _Where, initializer_list<_Ty> Ilist);

iterator erase(iter pos);						//删除pos指向的元素		
iterator erase(iter first,iterator last);		//删除[first,last)范围内的字符

void swap(vector& str);					//交换两个vector的内容
```



## deque

#### Deque概念

deque是“double-ended queue”的缩写，和vector一样都是STL的容器，deque是双端队列，而vector是单端的。

deque在接口上和vector非常相似，在许多操作的地方可以直接替换。

- deque 容器也擅长在序列尾部添加或删除元素（时间复杂度为`O(1)`），而不擅长在序列中间添加或删除元素。
- deque 容器也可以根据需要修改自身的容量和大小。

和 vector 不同的是，deque 还擅长在序列头部添加或删除元素，所耗费的时间复杂度也为常数阶`O(1)`。并且更重要的一点是，deque 容器中存储元素并不能保证所有元素都存储到连续的内存空间中。

#### deque构造函数

```cpp
deque();									//默认构造
deque(size_t count);						//指定size
deque(size_t count, Ty& val);				//批量构造
deque(const deque& right);					//拷贝构造
deque(deque&& right);						//移动构造
deque(Iter first,Iter last);				//区间构造
```

#### deque元素访问

```cpp
Ty& operator[](size_t i);
Ty& at(size_t i);
Ty& front();
Ty& back();
```



#### deque容量相关

```cpp
size_t size();								//获取有效元素个数
size_t max_size();							//可以存储的最大元素数量
void   resize(size_t n);					//调整大小为n,n小于当前size，多余的数据会被丢掉
void   resize(size_t n,const Ty& val);		//如果n>size,剩下的用val填充
void   clear();								//清空数据，长度变为0
bool   empty();								//判断是否为空串，即size == 0
void   shrink_to_fit();						//请求减小其容量到合适大小
```



#### deque的修改

```cpp
void push_back(const Ty& val);			//在尾部插入元素
void push_back(Ty&& val);				//同上
void push_front(const Ty& val);			//在头部插入元素
void push_front(Ty&& val);				//同上

void emplace(Iter where,_Valty&& val);	//效率比较高
void emplace_back(_Valty&& val);
void emplace_front(_Valty&& val)
void pop_back();						//删除尾部元素

 void assign(const size_t size, const Ty& val);//设置新的大小，并用val设置所有值
 void assign(Iter First, Iter Last);		  //以相同顺序复制[first,last)范围内的元素
 void assign(initializer_list<_Ty> Ilist);	  //同时赋值多个元素
     
iter insert(iter _Where, const Ty& Val);	  //指定位置插入元素		
iter insert(iter _Where, const size_t Count, const Ty& val);//指定位置插入，并且可以指定插入数量
iter insert(iter _Where, Iter First, Iter Last);//指定位置插入[first,last)之间的元素
iter insert(iter _Where, initializer_list<_Ty> Ilist);

iterator erase(iter pos);						//删除pos指向的元素		
iterator erase(iter first,iterator last);		//删除[first,last)范围内的字符

void swap(vector& str);					//交换两个vector的内容
```



## list

#### list简介

list 容器，又称双向链表容器，即该容器的底层是以双向链表的形式实现的。这意味着，list 容器中的元素可以分散存储在内存空间里，而不是必须存储在一整块连续的内存空间中。

 

#### list对象的默认构造

```cpp
list();
list(size_t count);
list(size_t count,const Ty& val);
list(const list& right);
list(list&& right);
list(Iter first,Iter last);
```

#### list元素访问

```cpp
Ty& front();
Ty& back();
```

#### list容量相关

```cpp
bool empty();
size_t size();
size_t max_size();
void   resize(size_t n);					//调整大小为n,n小于当前size，多余的数据会被丢掉
void   resize(size_t n,const Ty& val);		//如果n>size,剩下的用val填充
```

#### list添加元素

```cpp
void push_back(Ty& val);
void push_front(Ty& val);
void emplace_back(Args&&... args);
void emplace_front(Args&&... args);
Iter emplace(Iter pos,Args&&...args);

void assign(const size_t size, const Ty& val);//设置新的大小，并用val设置所有值
void assign(Iter First, Iter Last);		  //以相同顺序复制[first,last)范围内的元素
void assign(initializer_list<_Ty> Ilist);	  //同时赋值多个元素

iter insert(iter _Where, const Ty& Val);	  //指定位置插入元素
iter insert(iter _Where, Ty&& Val);	  		  //指定位置插入元素	
iter insert(iter _Where, const size_t Count, const Ty& val);//指定位置插入，并且可以指定插入数量
iter insert(iter _Where, Iter First, Iter Last);//指定位置插入[first,last)之间的元素
iter insert(iter _Where, initializer_list<_Ty> Ilist);
```

#### list删除元素

```cpp
iterator erase(iter pos);						//删除pos指向的元素		
iterator erase(iter first,iterator last);		//删除[first,last)范围内的字符

void pop_front();
void pop_back();

void clear();
```



 ***当使用一个容器的insert或者erase函数通过迭代器插入或删除元素"可能"会导致迭代器失效，因此我们为了避免危险，应该获取insert或者erase返回的迭代器，以便用重新获取的新的有效的迭代器进行正确的操作***

```cpp
lis<int> ls;
for (int i = 0; i < 10; i++)
{
	ls.push_back(i);
}
list<int>::iter it;
for (it = ls.begin(); it != ls.end(); )
{
	if (*it == 5)
	{
		it=ls.erase(it);
	}
    else
    {
        it++;
    }
	cout << *it << " ";
}
```



#### list的其他操作

```cpp
//list拼接，x中的元素会被直接转移到当前list中，不会涉及元素的构造
void splice (Iter where, list& x);		//把x插入到where位置,x会被清空
void splice (Iter where, list& x, Iter first);//把x的first位置的元素，插入到list的where位置
void splice (Iter where, list& x,Iter first, Iter last);//把x的[first,last)位置的元素，插入到list的where位置

void remove(const Ty& val);	//删除所有等于val的元素。这将调用这些对象的析构函数，并通过删除元素的数量来减少容器的大小。erase按元素的位置(使用迭代器)删除元素
template<typename Predicate>
void remove_if(Predicate pred);	//从容器中删除所有谓词pred返回true的元素。
void unique();	//从容器中每个相等元素的连续组中除去除第一个元素外的所有元素。
template <class Predicate>
void unique(Predicate _Pred);//以确定元素“唯一性”的特定比较函数作为参数。实际上，可以实现任何行为（并且不仅可以进行相等比较），从第二个开始）并删除如果谓词返回true，则从列表中返回i。
list<Stu> ls;
for (size_t i = 0; i < 10; i++)
{
	ls.push_back(Stu(rand()%5));
}
ls.unique([](const Stu& left, const Stu& right) 
          {//如果left大于right 那么把right删掉
              return left > right; 
          });

void merge(list& right);	//合并两个链表，如果两个链表都有序，合并之后同样也是有序的，否则合并失败，程序中断
void sort();				//对list元素进行排序，默认是升序
void sort(Predicate _Pred);	//可以自己修改排序规则
void reverse();				//反转list
```

通过remove删除元素时，自定义类型需要重载==运算符，而且需要加上const修饰

```cpp
//需要用const修饰this指针，否则如下代码所示，会有报错
bool operator==(const Stu& right) const
{
	return (this->_id == right._id);
}
// error C2678: 二进制“==”: 没有找到接受“const Stu”类型的左操作数的运算符(或没有可接受的转换)
//这是由于，test函数的两个参数都是const对象，如果不把this修饰为const，那么operator==函数，将不能把this转为const this
bool test(const Stu& val, const Stu& val2) 
{
	return val2 == val; 
}
```



## forward_list

#### forward_list构造函数

```cpp
forward_list();
forward_list(size_t count);
forward_list(size_t count,const Ty& val);
forward_list(const list& right);
forward_list(list&& right);
forward_list(Iter first,Iter last);
```

#### forward_list迭代器

```cpp
Iter before_begin();		//返回第一个元素的前一个位置，禁止解引用
```

#### forward_list元素访问

```cpp
Ty& front();
```

#### forward_list容量相关

```cpp
bool empty();
size_t max_size();
```

#### forward_list添加元素

```cpp
void push_front(Ty& val);
void emplace_front(Args&&... args);
Iter emplace_after(Iter where,Args&&...args);	//在where的下一个位置处插入新元素

void assign(const size_t size, const Ty& val);//设置新的大小，并用val设置所有值
void assign(Iter First, Iter Last);		  //以相同顺序复制[first,last)范围内的元素
void assign(initializer_list<_Ty> Ilist);	  //同时赋值多个元素

iter insert_after(iter _Where, const Ty& Val);	  //where下一个位置插入元素
iter insert_after(iter _Where, const size_t Count, const Ty& val);//where下一个位置插入，并且可以指定插入数量
iter insert_after(iter _Where, Iter First, Iter Last);//where下一个位置插入[first,last)之间的元素
iter insert_after(iter _Where, initializer_list<_Ty> Ilist);
```

####  forward_list删除元素

```cpp
iterator erase_after(iter where);		//删除where下一个位置的元素
iterator erase_after(iter first,iterator last);		//删除(first,last)范围内的字符

void pop_front();				//删除头部元素

void clear();					//清空链表
```



#### forward_list的其他操作

```cpp
//list拼接，x中的元素会被直接转移到当前list中，不会涉及元素的构造
void splice (Iter where, list& x);		//把x插入到where下一个位置
void splice (Iter where, list& x, Iter first);//把x的first的下一个位置的元素，插入到list的where下一个位置
void splice (Iter where, list& x,Iter first, Iter last);//把x的(first,last)位置的元素，插入到list的where位置

void remove(const Ty& val);	//删除所有等于val的元素。
template<typename Predicate>
void remove_if(Predicate pred);	//从容器中删除所有谓词pred返回true的元素。
void unique();	//从容器中每个相等元素的连续组中除去除第一个元素外的所有元素。
template <class Predicate>
void unique(Predicate _Pred);//以确定元素“唯一性”的特定比较函数作为参数。实际上，可以实现任何行为（并且不仅可以进行相等比较），从第二个开始）并删除如果谓词返回true，则从列表中返回i。


void merge(list& right);	//合并两个链表，如果两个链表都有序，合并之后同样也是有序的，否则合并失败，程序中断
void sort();				//对list元素进行排序，默认是升序
void sort(Predicate _Pred);	//可以自己修改排序规则
void reverse();				//反转list
```



# 容器适配器

> 容器适配器都不支持迭代器

## stack

#### Stack概念

stack是一种容器适配器，专门设计用于在LIFO上下文（后进先出）中操作，在LIFO上下文中，仅从容器的一端插入和提取元素。

**stack**作为*容器适配器*实现，它们是使用特定容器类的封装对象作为其*基础容器的*类，提供了一组特定的成员函数来访问其元素。元素从特定容器的尾部被推入*/*弹出*，这被称为堆栈的*顶部。

容器应支持以下操作：

- empty
- size
- back
- push_back
- pop_back

标准容器类vector，deque 和list满足这些要求。默认情况下，使用标准容器 deque来作为底层容器。

#### stack对象的默认构造



```cpp
stack() = default;
explicit stack (const container_type& _Cont);
explicit stack (container_type&& ctnr = container_type());

stack<int> s = { 1,2,3,4,5 };	//error 不能直接初始化
//如下，可以使用stack底层容器进行初始化
deque<int> dq = { 1,2,3,4,5 };
stack<int> s(dq);
```



#### stack其他

```cpp
Ty& top();						//获取顶部元素
void pop();						//删除顶部元素
void push(const Ty& val);		//入栈
void swap(stack& sk);			//交换两个stack
size_t size();					//获取元素个数
bool empty();					//判空

template <class... _Valty>
void emplace(_Valty&&... _Val);	//就地构造，提升效率
```



## queue

#### queue概念

FIFO队列

queue是一种容器适配器，专门设计用于在FIFO上下文中（先进先出）进行操作，在FIFO上下文中，将元素插入到容器的一端，并从另一端提取元素。

queue被实现为*容器适配器*，它们是使用特定容器类的封装对象作为其*基础容器的*类，提供了一组特定的成员函数来访问其元素。元素*被推*入特定容器的*“后部”*，并从其*“前部”弹出*。

基础容器可以是标准容器类模板之一，也可以是其他一些专门设计的容器类。此基础容器应至少支持以下操作：

- empty
- size
- front
- back
- push_back
- pop_front


标准容器类 deque和list满足这些要求。默认情况下，如果未为特定容器指定容器类队列

 类实例化，默认用标准容器 deque。

#### queue对象的默认构造

```cpp
queue() = default;
explicit queue(const _Container& _Cont);
explicit queue(_Container&& _Cont);
```



#### queue其他

```cpp
Ty& back();						//获取头部元素
Ty& front();					//获取尾部元素
void pop();						//删除头部元素
void push(const Ty& val);		//入队(从尾部)
void swap(stack& sk);			//交换两个queue
size_t size();					//获取元素个数
bool empty();					//判空

template <class... _Valty>
void emplace(_Valty&&... _Val);	//就地构造，提升效率
```



## priority_queue

#### priority_que概念

priority_que(优先级队列)是一种容器适配器，经过专门设计，以使其按照某些*严格的弱排序（strict weak ordering）*标准，其第一个元素始终是其中包含的最大元素。

> 严格是说在判断的时候会用"<"，而不是"<="，弱排序是因为，一旦"<"成立便认为存在"<"关系，返回ture，而忽略了"="关系和">"区别，把它们归结为false。

此上下文类似于*堆*，可以在任何时候插入元素，并且只能检索*最大堆*元素（*优先级队列*顶部的元素）。

优先级队列被实现为*容器适配器*，它们是使用特定容器类的封装对象作为其*基础容器的*类，提供了一组特定的成员函数来访问其元素。元素被*弹出*从特定容器的*“后退”*，称为优先级队列的*顶部*。

基础容器可以是任何标准容器类模板或某些其他专门设计的容器类。该容器应可通过随机访问迭代器访问并支持以下操作：

- `empty()`
- `size()`
- `front()`
- `push_back()`
- `pop_back()`


标准容器类 vector和 deque满足这些要求。默认情况下，如果未为特定容器指定容器类

priority_queue 类实例化，默认使用vector作为底层容器。

需要支持随机访问迭代器，以始终在内部保持堆结构。容器适配器通过自动调用算法函数(make_heap， push_heap，pop_heap )维持堆结构。

#### priority_que构造函数

```cpp
priority_queue() = default;
explicit priority_queue(const _Pr& _Pred);

priority_queue (const _Pr& Pred, const Container& Cont);

priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred, const _Container& _Cont);
    
priority_queue(_InIt _First, _InIt _Last);
    
priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred);
```



#### priority_que其他

```cpp
Ty& top();
void pop();
void push(Ty& val);
void swap();
size_t size();
bool empty();

template <class... _Valty>
    void emplace(_Valty&&... _Val)
```





# 关联式容器

## set/multiset容器

#### set/multiset的简介

set是一个***集合***容器，其中所包含的元素是***唯一***的，***集合中的元素按一定的顺序排列***。元素插入过程是按排序规则插入，所以不能指定插入位置。

set采用***红黑树***变体的数据结构实现，红黑树属于平衡二叉树。在插入操作和删除操作上比vector快。

<p style="color:red;">multiset与set的区别：set支持唯一键值，每个元素值只能出现一次；而multiset中同一值可以出现多次。</p>

<font style="color:blue">不可以直接修改set或multiset容器中的元素值</font>，因为该类容器是自动排序的。如果希望修改一个元素值，必须先删除原有的元素，再插入新的元素。

#### set/multiset对象的默认构造

```cpp
set();
set(const set& _Right);
explicit set(const key_compare& _Pred);
set(_Iter _First, _Iter _Last);
set(_Iter _First, _Iter _Last, const key_compare& _Pred);
```



#### set/multiset存取

```cpp
 pair<iterator, bool> insert(const value_type& _Val);
iterator insert(const value_type& _Val);
void insert(_Iter _First, _Iter _Last);
void insert(initializer_list<value_type> _Ilist);

iterator  erase (const_iterator where);		//返回下一个元素的位置
size_type erase (const value_type& val);	//返回删除元素的个数，对于set来说，永远是1(set的值不能重复)
iterator  erase (const_iterator first, const_iterator last);	//区间删除

void swap(const &right);	//交换set
void clear();				//清空所有元素
template <class... _Valtys>
    pair<iterator, bool> emplace(_Valtys&&... _Vals);

//提示从whrere开始找，不是插入到where的位置，如果vals满足排在where指向的值的后面，那么将提高速度，否则无影响
template <class... _Valtys>
    iterator emplace_hint(const_iterator _Where, _Valtys&&... _Vals)
```

#### set/multiset容量相关

```cpp
bool empty();
size_t size();
size_t max_size();
```

#### set/multiset获取比较规则

```cpp
//两个返回的都是一样的
key_compare key_comp（）const;
value_compare value_comp（）const;
```

#### set/multiset操作

```cpp
iterator find(const key_type& _Keyval);//在容器中搜索与val等效的元素，如果找到则返回一个迭代器，否则返回end迭代器。
size_t count(const key_type& _Keyval);	//在容器中搜索与val等效的元素，并返回匹配数。

//与排序规则有关
iterator lower_bound(const key_type& _Keyval);//找到第一个大于或者等于keyval的值
iterator upper_bound(const key_type& _Keyval);//找到第一个大于keyval的值

pair<iterator, iterator> equal_range(const key_type& _Keyval)
```



## map\multimap容器

#### map/multimap的简介

map(映射)是关联容器，用于存储按特定顺序由*键值*和*映射值*的组合形成的元素，即(key,value)对。它提供基于key的快速检索能力。

map中key值是唯一的。集合中的元素按一定的顺序排列。元素插入过程是按排序规则插入，所以不能指定插入位置。

map的具体实现采用红黑树变体的平衡二叉树的数据结构。在插入操作和删除操作上比vector快。

map可以直接存取key所对应的value，支持[]操作符，如map[key]=value。

<p style="color:red;">multimap与map的区别：set支持唯一键值，每个key只能出现一次；而multiset中同一key可以出现多次。map支持[]操作符，但是multmap不支持</p>

#### map/multimap构造函数

```cpp
map();
map(const map& _Right);
map(const key_compare& _Pred);
map(_Iter _First, _Iter _Last);
map(_Iter _First, _Iter _Last, const key_compare& _Pred);
```

####  map/multimap容量

```cpp
bool empty();
size_t size();
size_t max_size();
```

#### map/multimap元素访问

```cpp
mapped_type& operator[](key_type&& keyval);	//根据key获取value
mapped_type& at(const key_type& _Keyval);	
```

#### map/multimap修改

##### insert

> insert插入的是由键值对组成的pair<key_type,mapped_type>，可称为对组
>
> key_type				键类型
>
> mapped_type 	  值类型
>
> value_type			map装的元素内存，即pair<key_type,mapped_type>

```cpp
pair<iterator,bool> insert (const value_type& val);
pair<iterator,bool> insert (value_type&& val);
```

假设  map<int, string> stu;

**一、通过pair的方式插入对象**

```cpp
stu.insert(pair<int, string>(1, "maye"));
```

**二、通过make_pair的方式插入对象**

```cpp
stu.insert(make_pair(2, "zoey"));
```

**三、通过value_type的方式插入对象**

```cpp
stu.insert(map<int, string>::value_type(3, "lisa"));
```

**四、通过数组的方式插入值**

```cpp
stu[3]= "取个名字好难";
stu[4] = "有人@我";
```

前三种方法，采用的是insert()方法，该方法***返回值为pair<iter,bool>*** 

> iterator 指向插入的pair，bool标识是否插入成功

第四种方法非常直观，但存在一个性能的问题。

> 按key(3)插入元素时，若map中没有key(3),则键值对插入map，若key(3)已经存在，则修改key(3)对于的值。

```cpp
string strName = stu[2];  //获取key对于的值
```

只有当stu存在2这个键时才是正确的取操作，否则会自动插入一个实例，键为2，值为初始化值。

##### earse

```cpp
//删除key为keyval的元素，返回删除成功的数量
size_t erase(const key_type& _Keyval);		
//删除[first,last)区间元素，返回last
iterator erase(const_iterator _First, const_iterator _Last);
//删除where指向的元素，返回下一个元素迭代器
iterator erase(const_iterator _Where);
```

##### clear

```cpp
void clear();	//清空map
```

##### emplace

```cpp
//就地构造，传
template <class... Args>
  pair<iterator,bool> emplace (Args&&... args);
template <class... Args>
  iterator emplace_hint (const_iterator position, Args&&... args);
//stu.emplace(12, "duck");	//key,mapped
```

#### map操作

```cpp
//查找键key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回map.end();
iterator find(const key_type& _Keyval);

//返回容器中key为keyval的pair个数，对于map要么是0，要么是1。对multimap来说，值可能大于1。
size_type count(const key_type& _Keyval);

iterator lower_bound(const key_type& _Keyval);
iterator upper_bound(const key_type& _Keyval);
//返回
pair<iterator, iterator> equal_range(const key_type& _Keyval);

```



# STL容器共性机制

STL容器所提供的都是值（value）寓意，而非引用（reference）寓意，也就是说当我们给容器中插入元素的时候，容器内部实施了拷贝动作，将我们要插入的元素再另行拷贝一份放入到容器中，而不是将原数据元素直接放进容器中，也就是说我们提供的元素必须能够被拷贝。

- 除了queue和stack之外，每个容器都提供可返回迭代器的函数，运用返回的迭代器就可以访问元素。

- 通过STL不会抛出异常，需要使用者传入正确参数。

- 每个容器都提供一个默认的构造函数和默认的拷贝构造函数。

- 大小相关的构造方法：

  - （1）size()返回容器中元素的个数；
  - （2）empty()判断容器是否为空。

  |              | vector   | deque    | list     | set    | multiset | map           | multimap      |
  | ------------ | -------- | -------- | -------- | ------ | -------- | ------------- | ------------- |
  | 内存结构     | 单端数组 | 双端数组 | 双向链表 | 二叉树 | 二叉树   | 二叉树        | 二叉树        |
  | 可随机存取   | 是       | 是       | 否       | 否     | 否       | 对key而言：是 | 否            |
  | 元素查找速度 | 慢       | 慢       | 非常慢   | 快     | 快       | 对key而言：快 | 对key而言：快 |
  | 元素添加移除 | 尾端     | 头尾两端 | 任何位置 | -      | -        | -             | -             |

#### 各容器使用场景

**在实际使用过程中，到底选择这几种容器中的哪一个，应该根据遵循以下原则：**

１、如果需要高效的随机存取，不在乎插入和删除的效率，使用vector；

2、如果需要大量的插入和删除元素，不关心随机存取的效率，使用list；

3、如果需要随机存取，并且关心两端数据的插入和删除效率，使用deque；

4、如果打算存储数据字典，并且要求方便地根据key找到value，一对一的情况使用map，一对多的情况使用multimap；

5、如果打算查找一个元素是否存在于某集合中，唯一存在的情况使用set，不唯一存在的情况使用multiset。

6、如果要求很快的查找速度，根据情况选择使用unordered_map或unordered_set。



# STL算法

STL中算法大致分为四类：     

1、非可变序列算法：指不直接修改其所操作的容器内容的算法。   

2、可变序列算法：指可以修改它们所操作的容器内容的算法。     

3、排序算法：包括对序列进行排序和合并的算法、搜索算法以及有序序列上的集合操作。     

4、数值算法：对容器内容进行数值计算。   以下对所有算法进行细致分类并标明功能： 

##  查找算法(13个)

>判断容器中是否包含某个值

**adjacent_find:** 在iterator对标识元素范围内，查找一对相邻重复元素，找到则返回指向这对元素的第一个元素的ForwardIterator。否则返回last。重载版本使用输入的二元操作符代替相等的判断。

**binary_search:** 在有序序列中查找value，找到返回true。重载的版本实用指定的比较函数对象或函数指针来判断相等。 count:  利用等于操作符，把标志范围内的元素与输入值比较，返回相等元素个数。

**count_if:** 利用输入的操作符，对标志范围内的元素进行操作，返回结果为true的个数。

**equal_range:** 功能类似equal，返回一对iterator，第一个表示lower_bound，第二个表示upper_bound。

**find:**   利用底层元素的等于操作符，对指定范围内的元素与输入值进行比较。当匹配时，结束搜索，返回该元素的一个InputIterator。 

**find_end:** 在指定范围内查找"由输入的另外一对iterator标志的第二个序列"的最后一次出现。找到则返回最后一对的第一个ForwardIterator，否则返回输入的"另外一对"的第一个ForwardIterator。重载版本使用用户输入的操作符代替等于操作。

**find_first_of:** 在指定范围内查找"由输入的另外一对iterator标志的第二个序列"中任意一个元素的第一次出现。重载版本中使用了用户自定义操作符。

**find_if:**  使用输入的函数代替等于操作符执行find。 lower_bound:  返回一个ForwardIterator，指向在有序序列范围内的可以插入指定值而不破坏容器顺序的第一个位置。重载函数使用自定义比较操作。

**upper_bound:**  返回一个ForwardIterator，指向在有序序列范围内插入value而不破坏容器顺序的最后一个位置，该位置标志一个大于value的值。重载函数使用自定义比较操作。

**search:** 给出两个范围，返回一个ForwardIterator，查找成功指向第一个范围内第一次出现子序列(第二个范围)的位置，查找失败指向last1。重载版本使用自定义的比较操作。

**search_n:** 在指定范围内查找val出现n次的子序列。重载版本使用自定义的比较操作。



## 排序和通用算法(14个)

>提供元素排序策略

**inplace_merge:**      合并两个有序序列，结果序列覆盖两端范围。重载版本使用输入的操作进行排序。

**merge:**          合并两个有序序列，存放到另一个序列。重载版本使用自定义的比较。

**nth_element:**       将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面。重载版本使用自定义的比较操作。

**partial_sort:**      对序列做部分排序，被排序元素个数正好可以被放到范围内。重载版本使用自定义的比较操作。 

**partial_sort_copy:**    与partial_sort类似，不过将经过排序的序列复制到另一个容器。

**partition:**        对指定范围内元素重新排序，使用输入的函数，把结果为true的元素放在结果为false的元素之前。

 **random_shuffle:**      对指定范围内的元素随机调整次序。重载版本输入一个随机数产生操作。

**reverse:**         将指定范围内元素重新反序排序。

**reverse_copy:**      与reverse类似，不过将结果写入另一个容器。

**rotate:**         将指定范围内元素移到容器末尾，由middle指向的元素成为容器第一个元素。

**rotate_copy:**       与rotate类似，不过将结果写入另一个容器。

**sort:**          以升序重新排列指定范围内的元素。重载版本使用自定义的比较操作。

```cpp
//该函数专门用来对容器或普通数组中指定范围内的元素进行排序，排序规则默认以元素值的大小做升序排序，除此之外我们也可以选择标准库提供的其它排序规则（比如`std::greater<T>`降序排序规则），甚至还可以自定义排序规则。

//需要注意的是，sort() 函数受到底层实现方式的限制，它仅适用于普通数组和部分类型的容器。换句话说，只有普通数组和具备以下条件的容器，才能使用 sort() 函数：

//1. 容器支持的迭代器类型必须为随机访问迭代器。这意味着，sort() 只对 <font style="color:red">array、vector、deque</font> 这 3 个容器提供支持。

//2. 如果对容器中指定区域的元素做默认升序排序，则元素类型必须支持`<`小于运算符；同样，如果选用标准库提供的其它排序规则，元素类型也必须支持该规则底层实现所用的比较运算符；
```

**stable_sort:**       与sort类似，不过保留相等元素之间的顺序关系。

**stable_partition:**     与partition类似，不过不保证保留容器中的相对顺序。



##  删除和替换算法(15个) 

**copy:**          复制序列

**copy_backward:**      与copy相同，不过元素是以相反顺序被拷贝。

**iter_swap:**        交换两个ForwardIterator的值。

**remove:**         删除指定范围内所有等于指定元素的元素。注意，该函数不是真正删除函数。内置函数不适合使用remove和remove_if函数。

**remove_copy:**       将所有不匹配元素复制到一个制定容器，返回OutputIterator指向被拷贝的末元素的下一个位置。 

**remove_if:**        删除指定范围内输入操作结果为true的所有元素。

**remove_copy_if:**      将所有不匹配元素拷贝到一个指定容器。

**replace:**         将指定范围内所有等于vold的元素都用vnew代替。

**replace_copy:**      与replace类似，不过将结果写入另一个容器。

**replace_if:**       将指定范围内所有操作结果为true的元素用新值代替。

**replace_copy_if:**     与replace_if，不过将结果写入另一个容器。

**swap:**          交换存储在两个对象中的值。

**swap_range:**       将指定范围内的元素与另一个序列元素值进行交换。

**unique:**         清除序列中重复元素，和remove类似，它也不能真正删除元素。重载版本使用自定义比较操作。 

**unique_copy:**       与unique类似，不过把结果输出到另一个容器。 



## 排列组合算法(2个)

>提供计算给定集合按一定顺序的所有可能排列组合 

**next_permutation:**  取出当前范围内的排列，并重新排序为下一个排列。重载版本使用自定义的比较操作。 

**prev_permutation:**  取出指定范围内的序列并将它重新排序为上一个序列。如果不存在上一个序列则返回false。重载版本使用自定义的比较操作。



## 算术算法(4个) 

**accumulate:**       iterator对标识的序列段元素之和，加到一个由val指定的初始值上。重载版本不再做加法，而是传进来的二元操作符被应用到元素上。

**partial_sum:**       创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。重载版本使用自定义操作代替加法。

**inner_product:**      对两个序列做内积(对应元素相乘，再求和)并将内积加到一个输入的初始值上。重载版本使用用户定义的操作。

**adjacent_difference:**   创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。重载版本用指定二元操作计算相邻元素的差。 



##  生成和异变算法(6个)  

**fill:**  将输入值赋给标志范围内的所有元素。

**fill_n:** 将输入值赋给first到first+n范围内的所有元素。

**for_each:** 用指定函数依次对指定范围内所有元素进行迭代访问，返回所指定的函数类型。该函数不得修改序列中的元素。 

**generate:** 连续调用输入的函数来填充指定的范围。

**generate_n:** 与generate函数类似，填充从指定iterator开始的n个元素。

**transform:** 将输入的操作作用与指定范围内的每个元素，并产生一个新的序列。重载版本将操作作用在一对元素上，另外一个元素来自输入的另外一个序列。结果输出到指定容器。



## 关系算法(8个)  

**equal:** 如果两个序列在标志范围内元素都相等，返回true。重载版本使用输入的操作符代替默认的等于操作符。

**includes:**  判断第一个指定范围内的所有元素是否都被第二个范围包含，使用底层元素的<操作符，成功返回true。重载版本使用用户输入的函数。

**lexicographical_compare:** 比较两个序列。重载版本使用用户自定义比较操作。

**max:**  返回两个元素中较大一个。重载版本使用自定义比较操作。

**max_element:** 返回一个ForwardIterator，指出序列中最大的元素。重载版本使用自定义比较操作。

**min:**  返回两个元素中较小一个。重载版本使用自定义比较操作。

**min_element:**  返回一个ForwardIterator，指出序列中最小的元素。重载版本使用自定义比较操作。

**mismatch:**  并行比较两个序列，指出第一个不匹配的位置，返回一对iterator，标志第一个不匹配元素位置。如果都匹配，返回每个容器的last。重载版本使用自定义的比较操作。



## 集合算法(4个) 

**set_union:**        构造一个有序序列，包含两个序列中所有的不重复元素。重载版本使用自定义的比较操作。 

**set_intersection:**     构造一个有序序列，其中元素在两个序列中都存在。重载版本使用自定义的比较操作。 

**set_difference:**      构造一个有序序列，该序列仅保留第一个序列中存在的而第二个中不存在的元素。重载版本使用自定义的比较操作。

**set_symmetric_difference:** 构造一个有序序列，该序列取两个序列的对称差集(并集-交集)。



## 堆算法(4个) 

**make_heap:** 把指定范围内的元素生成一个堆。重载版本使用自定义比较操作。

**pop_heap:**   并不真正把最大元素从堆中弹出，而是重新排序堆。它把first和last-1交换，然后重新生成一个堆。可使用容器的back来访问被"弹出"的元素或者使用pop_back进行真正的删除。重载版本使用自定义的比较操作。  

**push_heap:**   假设first到last-1是一个有效堆，要被加入到堆的元素存放在位置last-1，重新生成堆。在指向该函数前，必须先把元素插入容器后。重载版本使用指定的比较操作。

**sort_heap:**   对指定范围内的序列重新排序，它假设该序列是个有序堆。重载版本使用自定义比较操作 