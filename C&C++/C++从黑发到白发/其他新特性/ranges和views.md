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

### 视图工厂

#### std::views::iota

用于生成一个**无限或有限的递增序列**。它类似于数学中的 “iota 函数”（生成连续整数），并且支持惰性求值，避免预先生成整个序列，从而节省内存和计算资源。

`std::views::iota` 有两种主要形式：

##### 1. 无限序列（从起始值开始无限递增）

```cpp
auto infinite_view = std::views::iota(start_value);
```

- **`start_value`**：序列的起始值，类型可以是整数、浮点数或任何支持 `++` 运算符的类型。

##### 2. 有限序列（从起始值到终止值前一个元素）

```cpp
auto finite_view = std::views::iota(start_value, end_value);
```

- **`start_value`**：序列的起始值（包含）。
- **`end_value`**：序列的终止条件（不包含），当达到或超过该值时停止生成。

以下是几个使用 `std::views::iota` 的典型场景：

+ 生成无限整数序列

```cpp
{
    //生成从5开始的无限整数序列
	auto numbers = std::views::iota(5);

	//取前五个元素并输出：[5, 6, 7, 8, 9]
	std::println("{}", numbers | std::views::take(5));
}
```

+ 生成有限整数序列

```cpp
{
    //生成从 3 到 7(不包含7)的整数序列
	auto numbers = std::views::iota(3, 7);

	//输出:[3, 4, 5, 6]
	std::println("{}", numbers);
}
```

+ 生成浮点数序列

```cpp
//搭配transform生成 0 到1之间的小数
auto numbers = std::views::iota(0, 100) | std::views::transform([](int x) {return x / 99.0;});
for (auto v : numbers) {
	std::print("{:.2f} ", v);
}
```

#### std::views:repeat

用于生成一个**无限重复某个值**的视图。这个视图会持续产生同一个值，直到被其他适配器（如 `take`）截断，非常适合需要重复元素的场景，例如初始化容器、填充数据等。

以下是几个使用 `std::views::repeat` 的典型场景：

+ 生成重复值的有限序列

```cpp
{
	// 生成无限个 'A'，取前 5 个
	auto  chars = std::views::repeat('A') | std::views::take(5);
    
    //输出：['A', 'A', 'A', 'A', 'A']
	std::print("{}", chars);
}
```

+ 生成二维数组

```cpp
	std::vector<int> nums{ 1,2,3,4,5 };
	std::print("{}", std::views::repeat(nums) | std::views::take(5));
```

或

```cpp
	// 生成 3x3 矩阵，每个元素为 99
    auto row = std::views::repeat(99) | std::views::take(3);
    auto matrix = std::views::repeat(row) | std::views::take(3);
	std::println("{}", matrix);

	//输出矩阵
	for (auto& r : matrix) {
		for (int num : r) {
			std::print("{} ", num);
		}
		std::println();
	}
```

#### std::views::istream

用于从输入流（如 `std::cin` 或文件流）中读取数据，并将其转换为一个**惰性视图**。这个视图会在迭代时从流中读取下一个元素，直到流结束或发生错误，从而避免一次性加载所有数据到内存中。

**核心功能与语法**

`std::views::istream` 的基本语法如下：

```cpp
auto view = std::views::istream<T>(stream);
```

- **`T`**：要读取的数据类型，必须支持 `operator>>`。
- **`stream`**：输入流对象的引用（如 `std::cin`、`std::ifstream`）。

返回的视图会在每次迭代时从流中读取一个 `T` 类型的元素，直到流结束（如遇到文件末尾或输入错误）。

以下是几个使用 `std::views::istream` 的典型场景：

+ 从标准输入读取整数

```cpp
{
	std::print("input int numbers>");
	// 从 std::cin 读取整数，直到输入结束（如 Ctrl+D）
	auto input_view = std::views::istream<int>(std::cin);

	// 计算输入整数的和
	int sum = 0;
	for (int num : input_view) {
		sum += num;
	}
	
	std::print("{}", sum);
}
```

+ 从流中读取字符串并过滤

```cpp
	std::string text = R"(Most of us are taught to pay attention to what issaid-the words.
Words do provide us with some information,but meanings are derived from so many other 
sources that it would hinder our effectivenessas a partner to a relationship to rely too heavily onwords alone.
Words are used to describe only asmall part of the many ideas we associate with any given message.
Sometimes we can gain insight into some of those associations if we listen for more than words.
We dont always say what we mean or mean what we say.
Sometimes our words dont mean anything except Im letting off some steam.
I dont really want you to pay close attention to what Im saying.
Just pay attention to what Im feeling.Mostly we mean several things at once.
A person wanting topurchase a house says to the current owner,This step has to be fixed before Ill buy.
Theowner says,Its been like that for years.Actually,the step hasnt been like that for years,
but the unspoken message is: I dont want to fix it.We put up with it.Why cant you?
The search for a more expansive view of meaning can be developed of examining a message interms of who said it,
when it occurred,the related conditions or situation,and how it was said.)";

	std::stringstream ss(text);

	// 从流中读取字符串，过滤长度大于 5 的单词
	auto words_view = std::views::istream<std::string>(ss)
		| std::views::filter([](const std::string& s) {
			return s.size() > 5;
			});

	//输出过滤后的单词
	std::print("{}", words_view);
}
```

#### std::views::single

用于创建一个只包含**单个元素**的视图。这个视图可以被迭代一次，返回唯一的元素，常用于将单个值纳入视图处理流程，或作为更复杂视图组合的起点。

> `std::views::single` 是一种将单个值纳入视图处理范式的简洁方式，特别适合需要统一处理单个元素和序列的场景

以下是几个使用 `std::views::single` 的典型场景

+ 包装单个值

```cpp
{
	//创建包单个元素 x的视图
	auto single_view = std::views::single(10);

	//输出:[10]
	std::print("{}", single_view);
}
```

+ 与其他视图组合

```cpp
{
	// 创建包含单个元素的视图，乘以 10
	auto processed_view = std::views::single(5)
		| std::views::transform([](int x) { return x * 10; });

	//输出:[10]
	std::print("{}", processed_view[0]);
}
```

#### std::views::empty

用于创建一个**空视图**（不包含任何元素的范围）。这个视图在需要表示 “无数据” 或作为默认值时非常有用，也可用于简化条件逻辑，避免处理特殊情况。

`std::views::empty` 的基本语法如下：

```cpp
auto view = std::views::empty<T>;
```

- **`T`**：视图元素的类型，指定空视图的元素类型（即使没有元素）。

返回的视图是一个空范围，其 `begin()` 和 `end()` 相等，迭代时不会执行任何操作。

以下是几个使用 `std::views::empty` 的典型场景：

+ 创建空视图并验证

```cpp
{
	// 创建元素类型为 int 的空视图
	auto empty_view = std::views::empty<int>;

	// 验证视图为空
	std::cout << "Empty? " << std::boolalpha
		<< std::ranges::empty(empty_view) << "\n";  // 输出：true

	// 迭代空视图（不会执行任何操作）
	for (int value : empty_view) {
		std::cout << value << "\n";  // 不会执行
	}
}
```

### 视图适配器

#### std::views::all

`std::views::all` 是 C++20 标准库中的一个视图适配器，用于将一个**可迭代对象**（如容器、数组）转换为一个**视图**。视图是一种轻量级的包装器，它提供了对底层数据的惰性访问，而不拥有或复制数据本身。`std::views::all` 的主要作用是将非视图类型转换为视图，以便与其他视图适配器（如 `filter`、`transform`、`zip` 等）无缝协作。

```cpp
std::vector a{ 1,2,3,4,5,6 };
//将a转换成视图
auto view =  std::views::all(a);
//打印视图
std::println("{}", view);
//遍历
for (auto& v : view) {
	std::print("{} ", v);
}
std::print("\n");
//使用迭代器遍历
for (auto it = view.begin();it != view.end();it++) {
	std::print("{} ", *it);
}
std::print("\n");
```

#### std::views::as_rvalue

用于将输入视图中的元素转换为右值引用（rvalue reference）。这个适配器在处理需要移动语义的场景中非常有用，例如将元素从一个容器高效地移动到另一个容器，而不是进行复制。

例如，将元素从一个 vector 移动到另一个 vector。

```cpp
std::vector<std::string> names{ "maye","moying","Betty" };
// 使用 as_rvalue 将元素转换为右值引用
auto views =  names | std::views::as_rvalue;
// 将元素从names移动到dest
std::vector<std::string> dest(views.begin(),views.end());

std::println("names {}", names);	//names ["", "", ""]
std::println("dest  {}", dest);		//dest  ["maye", "moying", "Betty"]
```

> 管道运算符（*|*）是一个非常重要的新特性，它属于范围库（Ranges Library）的一部分。管道运算符允许我们以一种更加直观和优雅的方式来组合和操作数据序列。

#### std::views::filter

用于从输入视图中筛选出满足特定条件的元素，形成一个新的视图。这个适配器实现了惰性过滤（lazy evaluation），即只有在迭代时才会实际检查元素是否满足条件，从而避免提前生成中间容器，提高效率和内存利用率。

```cpp
std::vector<int> vec = { 1,2,3,4,5,6,7,8,9,10 };
auto evenNumbers =  vec | std::views::filter([](int x) {return x % 2 == 0;});
std::println("{}", evenNumbers);
```

#### std::views::transform

用于对输入视图中的每个元素应用一个转换函数，生成一个新的视图。

+ 将元素转换为平方

```cpp
 std::vector<int> numbers = {1, 2, 3, 4, 5};

 // 将每个元素转换为其平方
 auto squared_view = numbers | std::views::transform([](int x) { return x * x; });

 // 输出：1, 4, 9, 16, 25,
std::println("{}", squared_view);
```

+ 字符串长度转换

```cpp
std::vector<std::string> words = { "apple", "banana", "grape", "kiwi" };

// 将每个字符串转换为其长度
auto length_view = words | std::views::transform([](const std::string& s) {
	return s.length();
	});

// 输出：5, 6, 5, 4
std::println("{}", length_view);
```

#### std::views::zip

用于将多个视图（或容器）的元素按位置组合成元组，形成一个新的视图。

+ 将两个容器中的元素按照位置打包成一个元组，所有元组构成一个视图。

```cpp
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {10, 20, 30, 40};

    // 组合 a 和 b，生成元组视图
    auto zip_view = std::views::zip(a, b);

	//直接打印 [(1, 10), (2, 20), (3, 30), (4, 40)]
	std::println("{}", zip_view);
    // 遍历元组视图，输出对应元素的和
    for (auto [x, y] : zip_view) {
        std::cout << x + y << ", ";  // 输出：11, 22, 33, 44
    }
```

+ 组合三个容器

```cpp
{
	std::vector<std::string> names = { "Alice", "Bob", "Charlie" };
	std::vector<int> ages = { 25, 30, 35 };
	std::vector<double> scores = { 85.5, 90.0, 78.2 };

	// 组合三个容器
	auto zip_view = std::views::zip(names, ages, scores);
    
	//直接打印 [(1, 10), (2, 20), (3, 30), (4, 40)]
	std::println("{}", zip_view);
	// 遍历并输出每个元组的内容
	for (const auto& [name, age, score] : zip_view) {
		std::cout << name << " (age: " << age
			<< ", score: " << score << ")\n";
	}
}
```

还可以直接获取每个元组，然后使用make_from_tuple构造成类对象。

```cpp
struct Student {
	std::string name;
	int age;
	float score;
};	

for (const auto& tp : zip_view) {
	 auto s = std::make_from_tuple<Student>(tp);
	 std::println("{} {} {}", s.name,s.age,s.score);
}
```

**注意：**如果输入视图长度不一致，`zip` 会以最短视图为准，忽略较长视图的多余元素。

#### std::views::zip_transform

它结合了 **`std::views::zip`** 和 **转换操作** 的功能，允许你同时处理多个视图，并对其中的元素执行转换操作。这个工具在处理并行数据结构时特别有用，可以避免显式的循环和中间容器，提高代码的简洁性和效率。

+ 计算两个数组对应元素的和

```cpp
{
	std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {10, 20, 30, 40};

    // 计算 a 和 b 对应元素的和
    auto sum_view = std::views::zip_transform(
        [](int x, int y) { return x + y; },
        a, b
    );

    // 输出结果：[11, 22, 33, 44]
	std::println("{}", sum_view);
}
```

+ 组合多个容器生成结构化数据

```cpp
{
	std::vector<std::string> names = { "Alice", "Bob", "Charlie" };
	std::vector<int> ages = { 25, 30, 35 };
	std::vector<float> scores = { 85.5, 90.0, 78.2 };

	// 组合三个容器生成 Person 对象
	auto person_view = std::views::zip_transform(
		[](const std::string& name, int age, float score) {
			return Student{ name, age, score };
		},
		names, ages, scores
	);

	// 输出每个 Person 的信息
	for (const auto& person : person_view) {
		std::println("{} (age:{}, score:{})", person.name, person.age, person.score);
	}
}
```



#### std::views::adjacent

用于同时处理相邻的多个元素，将指定个数的相邻元素打包成元组，形成一个新的视图。

+ 组合相邻两个或三个元素

```cpp
	std::vector<int> vec{ 1,3,5,7,9 };

	{
		auto views = vec | std::views::adjacent<3>;
        //输出结果：[(1, 3, 5), (3, 5, 7), (5, 7, 9)]
		std::println("{}", views);
	}

	{
		//pairwise 就是 adjacent<2>
		auto views = vec | std::views::pairwise;
        //输出结果：[(1, 3), (3, 5), (5, 7), (7, 9)]
		std::println("{}", views);
	}
```

#### std::views::adjacent_transform

用于同时处理相邻的多个元素。它允许你定义一个操作，对连续的 N 个元素进行组合或转换，生成一个新的视图。

+ 计算相邻元素的和

```cpp
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 计算相邻两个元素的和
    auto sum_view = numbers | std::views::adjacent_transform<2>([](int a, int b) { return a + b; });

    // 输出：[3, 5, 7, 9]
	std::println("{}", sum_view);
}
```

也可以使用`pairwise_transform`。

```cpp
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 计算相邻两个元素的和
    auto sum_view = numbers | std::views::pairwise_transform([](int a, int b) { return a + b; });

    // 输出：3, 5, 7, 9,
	std::println("{}", sum_view);
}
```

> 当原始视图的元素不足 `N` 个时，将不会生成任何结果

#### std::views:take

用于从输入视图中提取前 `N` 个元素，形成一个新的视图。

返回的 `view` 是一个新视图，包含原视图的前 `N` 个元素。如果原视图的元素不足 `N` 个，则返回所有元素（即视图长度可能小于 `N`）。

以下是几个使用 `std::views::take` 的典型场景：

+ 从序列中取前几个元素

```cpp
{
	std::vector<std::string> names = {"tom","jerry","Tyke","Spike"};
	std::print("{}", names | std::views::take(2));
}
```

+ 结合 filter 和 transform

```cpp
{
	auto seq =  std::views::iota(100, 9999);
	// 先筛选偶数，在取前10个元素，最后把这十个元素求平方
	auto processed = seq 
		| std::views::filter([](int x) {return x % 2 == 0;}) 
		| std::views::take(10) 
		| std::views::transform([](int x) {return x * x;});
	std::print("{}", processed );
}
```

> `std::views::take` 是构建数据处理管道的常用工具，特别适合处理无限序列或需要限制处理数量的场景。

#### std::views:take_while

#### std::views:drop

#### std::views:drop_while

#### std::views:join

#### std::views:join_with

#### std::views:split

#### std::views:lazy_split

#### std::views:concat

#### std::views:counted

#### std::views:common

#### std::views:reverse

#### std::views:as_const

#### std::views:elements

#### std::views:keys

#### std::views:values

#### std::views:enumerate

#### std::views:chunk

#### std::views:chunk_by

#### std::views:slide

#### std::views:stride

#### std::views:cartesian_product

#### std::views:cache_latest

#### std::views:to_input