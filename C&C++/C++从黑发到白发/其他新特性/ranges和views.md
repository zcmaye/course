# 范围（Ranges）与视图（Views）

## 基本概念

**范围** 是C++20中对[容器](https://cloud.tencent.com/product/tke?from_column=20065&from=20065)或序列的一种抽象概念，它定义了一个元素序列的边界和迭代方式。范围不仅仅包括传统的数组或标准库容器，还可以是输入输出流、指针区间等。范围分为两种类型：可遍历范围（Iterable Range）和可感应范围（Sized Range），分别对应是否能获取元素数量。

**视图** 是构建在范围之上的轻量级、只读的 adaptor，它不拥有数据，而是提供了一种新的观察原有数据的方式。视图允许我们对数据进行过滤、转换、排序等操作，而无需创建数据的副本，这大大提高了效率和灵活性。

> 范围库是对算法库和迭代器库的扩展和泛化，通过使其可组合且更不易出错，从而增强了它们的功能。

## 范围(Ranges)

在 C++20 中，**范围（Ranges）** 是一项核心特性，它提供了一种更简洁、更安全、更高效的方式来处理序列数据。范围库基于 **迭代器（Iterators）** 和 **视图（Views）** 的概念，允许你以声明式风格处理数据集合，避免显式编写循环。

范围是一个可迭代的对象，满足 `std::ranges::range` 概念。它可以是容器（如 `std::vector`）、数组，或自定义类型。

### copy

std::ranges::copy能将一个容器范围内的数据，全部拷贝到另一个容器中。

```cpp
int nums[] = { 1,2,3,4,5 };
int ages[10];

std::ranges::copy(nums,ages);
```

### fill_n

std::ranges::fill_n能对范围进行填充。

```cpp
int ages[10];
std::ranges::fill_n(ages, 10, 18);		//将ages 从第一个元素开始，填充十个元素，每个元素填充为18
std::ranges::copy(ages, std::ostream_iterator<int>(std::cout,","));	//将ages所有数组输出到std::cout,并用逗号分隔
```

### find

std::ranges::find能在一个容器范围内查找指定数据，并返回找到的迭代器，没有找到返回结尾迭代器。

```cpp
std::vector<int> vec = { 2,4,6,8,10 };
if (auto it = std::ranges::find(vec, 6);it != vec.end()) {
	std::println("Is find values is : {}", *it);
}
else {
	std::println("Not found!");
}
```



## 视图(View)

`views`是C++20中Ranges库的一部分，它代表了一个数据序列的虚拟视图。这个视图允许你以一种便捷和现代的方式访问和操作数据，同时不需要实际地拷贝或修改原始数据。`views`的操作是惰性的，只有在使用的时候才会执行。

> 注意:视图不会改变容器中的原有数据~

### 创建视图

你可以通过调用标准容器的`views`成员函数或使用适配器来创建视图。例如，可以使用`std::vector`创建一个视图：

```cpp
	std::vector<int> vec = { 1,2,3,4,5,6,7,8,9,10 };

	auto evenNumbers =  vec | std::views::filter([](int x) {return x % 2 == 0;});
	if (evenNumbers.empty()) {
		std::println("is empty!");
		return -1;
	}
	//直接打印
	std::println("{}", evenNumbers);
	//遍历
	for (auto& v : evenNumbers) {
		std::print("{} ", v);
	}
	std::print("\n");
	//使用迭代器遍历
	for (auto it = evenNumbers.begin();it != evenNumbers.end();it++) {
		std::print("{} ", *it);
	}
	std::print("\n");
```

### 视图的操作

一旦创建了视图，你可以对其执行各种操作，这些操作包括但不限于：

- **筛选（filtering）**：筛选出满足特定条件的元素。
- **映射（mapping）**：将函数应用于序列中的每个元素。
- **切片（slicing）**：选择范围内的元素。
- **排序（sorting）**：对元素进行排序。

你可以将多个操作组合在一起来创建复杂的数据处理管道，而这些操作都是惰性执行的。