## Ranges(C++20)

C++20引入了范围(Ranges)的新特性，这是一种现代化的、功能强大的处理序列数据的机制。范围(Ranges)的目标是提供一种更简洁、更易读、更安全且更高效的方式来操作数据序列，代替传统的迭代器和手动循环操作。这里是C++20 Ranges的一些详细解释：

1. **范围概念**： 范围(Ranges)是一种统一的序列表示形式，它可以是一个数组、容器、字符串、文件流等一切能够返回一系列元素的数据源。范围将序列数据和处理数据的算法解耦，使得我们可以在一个范围上链式地应用多个算法，实现流畅且功能强大的数据处理操作。
2. **范围视图**： 范围视图(Ranges Views)是范围的一种扩展，它允许我们在一个范围上进行类似于管道操作的连续转换和筛选操作。范围视图是一种惰性求值的机制，它们并不直接生成数据，而是在需要时根据需要生成数据。
3. **范围算法**： C++20引入了一组新的范围算法，这些算法使用统一的范围接口而不是传统的迭代器。这些算法可以直接作用在范围上，而不需要指定范围的开始和结束迭代器。范围算法提供了丰富的功能，包括排序、查找、变换、筛选、分组等，它们与范围视图一起可以完成大部分序列处理任务。
4. **范围适配器**： 范围适配器(Ranges Adapters)是一种范围视图，用于将范围视图转换为不同类型的范围视图，或者在范围上应用其他操作。范围适配器类似于算法，但它们返回的是一个新的范围视图，而不是处理范围上的元素。
5. **标准范围库**： C++20引入了`<ranges>`头文件，其中包含了范围概念、范围视图、范围算法和范围适配器的相关类和函数。通过包含这个头文件，您可以在项目中使用C++20 Ranges特性。

使用C++20 Ranges可以大大简化代码，并提高代码的可读性和可维护性。通过使用范围视图和范围算法，我们可以以一种更现代、更简洁的方式处理序列数据，避免了传统迭代器的复杂性和错误风险。然而，为了使用C++20 Ranges，您需要使用支持C++20标准的编译器和标准库。

当使用C++20 Ranges时，可以使用范围视图和范围算法来执行排序、查找、变换、筛选和分组操作。下面是每种操作的代码示例：

### 排序(Sort)

> #include<algorithm>

```cpp
//排序
void test_sort()
{
	std::vector numbers{5,2,0,1,3,1,4};

	//使用范围视图和范围算法对序列进行排序
	//std::ranges::sort(numbers);					//默认升序排列
	std::ranges::sort(numbers,std::greater<int>());	//修改为降序排列

	for (auto num : numbers)
		std::cout << num << ' ';
}
```

投影是指将对象投影成指定的值，然后按照指定的值进行排序。

```cpp
//排序投影
struct Student
{
	std::string name;
	int age;
};
std::ostream& operator<<(std::ostream& os, const Student& stu)
{
	os << stu.name << " " << stu.age;
	return os;
}
void test_sort_projection()
{
	std::vector<Student> stu_vec{
		{"maye",21},
		{"maye",20},
		{"jerry",40},
		{"tem",35},
		{"tom",30}
	};

	//按姓名排序
	//std::ranges::sort(stu_vec, {}, &Student::name);
	//按年龄排序
	//std::ranges::sort(stu_vec, {}, &Student::age);
	//按年龄和姓名组合排序
	//std::ranges::sort(stu_vec, {}, [](Student& stu)
	//	{
	//		return std::to_string(stu.age) + stu.name;
	//	});

	for (auto& stu : stu_vec)
		std::cout << stu << std::endl;
}
```

### 查找(Find)

> #include<algorithm>

```cpp
//查找
void test_find()
{
	std::list num_list{5,2,0,1,3,1,4};

	{
		auto it = std::ranges::find(num_list, 0);
		if (it != num_list.end())
			std::cout << "found at index:" << std::distance(num_list.begin(), it) << std::endl;
		else
			std::cout << "not found!" << std::endl;
	}

	{
		//auto it = std::ranges::find(stu_vec, "jerry", [](Student& stu)
		//	{
		//		return stu.name;
		//	});

		//按姓名查找学生
		//auto it = std::ranges::find(stu_vec, "jerry", &Student::name);
		//按年龄查找学生
		auto it = std::ranges::find(stu_vec, 30, &Student::age);
		if (it != stu_vec.end())
			std::cout << "found at index:" << std::distance(stu_vec.begin(), it) << std::endl;
		else
			std::cout << "not found!" << std::endl;
	}
}
```

### 变换(Transform)

```cpp
//变换
void test_transform()
{
	std::vector<int> numbers{ 1,2,3,4,5 };

	//使用范围视图和算法求每个元素的平方
	auto squared_number = numbers | std::views::transform([](int n) {return n * n; });

	//必须用const接受
	for (const auto& v : squared_number)
		std::cout << v << ' ';
}
```

### 筛选(Filter)

```cpp
void test_filter()
{
	std::vector<int> numbers{ 1,2,3,4,5 };

	auto even_numbers =  numbers | std::views::filter([](int n) { return n % 2 == 0; });

	for (const auto& v : even_numbers)
		std::cout << v << ' ';
}
```

### 分组(Partial)

```cpp
void test_group()
{
	std::vector<int> numbers = { 10, 2, 4, 3, 5, 8, 7, 6, 9, 1 };
	//对numbers [first,mid) 范围进行排序

	std::ranges::partial_sort(numbers, std::next(numbers.begin(),5),std::greater<int>());
	//对numbers [first,last) 范围进行排序,直到结果填满 [first,mid),也就是说并不会完全对[first,last)范围进行排序
	//如：int arr[5]={1,5,3,2,4}; 如果[first,last) 为[arr,arr+5);而[first,mid)为[arr,arr+3) 则最终输出arr结果为：1 2 3 5 4
	std::ranges::partial_sort(std::next(numbers.begin(), 5), std::prev(numbers.end(), 3), numbers.end()-3);
	for (auto v : numbers)
		std::cout << v << ' ';
}
```

将偶数放在数组左边。

```cpp
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::ranges::partial_sort(numbers, std::next(numbers.begin(), 3), std::greater<int>(), [](int n)
		{
			return n % 2 == 0;
		});
```

上述代码，将对numbers [first,last)范围进行分区，分区[numbers, std::next(numbers.begin(), 3))保存偶数。

结果为：`6 2 4 3 5 1 7 8 9 10`，前三个元素 6 2 4都为偶数。

如果想要偶数放在数组左边，奇数放在数组右边，并排好序，则可以使用`std::ranges::stable_partition`函数。

```cpp
std::ranges::stable_partition(numbers, [](int n) {return n % 2 == 0; });
```

结果为：`2 4 6 8 10 1 3 5 7 9`

### 范围适配器(Range Adapters)

