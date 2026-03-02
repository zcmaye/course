# IO流

在C++中，流（Stream）是一种抽象概念，用于表示数据的输入和输出操作。流可以是输入流，也可以是输出流，它们分别用于从某个源（如键盘、文件或网络）读取数据，以及向某个目的地（如屏幕、文件或网络）写入数据。

C++标准库提供了一系列的流类，用于处理不同类型的I/O操作。这些流类包括：

- **istream**：用于从标准输入（如键盘）读取数据。
- **ostream**：用于向标准输出（如屏幕）写入数据。
- **ifstream**：用于从文件读取数据。
- **ofstream**：用于向文件写入数据。
- **fstream**：可以同时用于读取和写入文件的数据。
- **stringstream**：用于在内存中读写字符串。

这些流类都是从ios基类派生而来，ios类提供了基本的流操作和状态管理功能。

## 文件流

### 简介

在C++中，文件流操作是通过特定的类来实现的，主要包括`ofstream`用于文件写入，`ifstream`用于文件读取，以及`fstream`同时具备读写功能。这些类都包含在C++标准库`<fstream>`中。

![image-20220912183928787](assets/image-20220912183928787.png)

![image-20220912183932192](assets/image-20220912183932192.png)

### ifstream

ifstream输入文件流，专门用来读取文件！

#### 打开文件

假设有`stu.txt`文件，文件内容如下：

```css
123 顽石 男
456 微笑 男
789 天明 男
110 莫影 男
```

使用ifstream构造函数传递文件名，会自动打开文件：

```cpp
	std::ifstream ifs("stu.txt");
```

文件是否打开成功，必须要手动进行检查，可以通过`is_open`方法判断或者直接判断流对象：

```cpp
	if (!ifs) {
		std::println("open file failed");
		return;
	}
```

不需要手动关闭，因为在对象析构时会自动关闭文件，如果想要手动关闭也可以调用`close`方法来关闭！

#### 读取文件

##### 流式读取

读取文件的方式有很多，但是对于流来说，我们最先想到的可能就是通过流运算符`>>`了！通过流运算符读取文件方式如下：

```cpp
	std::string buf;
	ifs >> buf;
	std::println("{}", buf);	//123
```

读取一次，读到的内容是`123`，因为流式读取遇到空白字符会自动的停止！

可以通过循环来读取所有数据：

```cpp
	std::string buf;
	while (ifs >> buf) {
		std::println("{}", buf);	//123
	}
```

`ifs >> buf`这个表达式会返回ifs流对象，当读到文件结尾后，流对象就变成空了，就不再继续循环！！当然也可以通过一些文件状态检查方法来进行判断：

```cpp
bool is_open()    // 文件是否成功打开
bool good()       // 流状态正常
bool eof()        // 到达文件末尾
bool fail()       // 操作失败但流可恢复
bool bad()        // 严重错误，流不可用
```

使用`eof`方法检查是否读到文件结尾：

```cpp
	while (!ifs.eof()) {
		ifs >> buf;
		std::println("{}", buf);	//123
	}
```

上面输出的结果是把一行内容以空白字符为分隔符，分为多行输出了：

```cpp
123
顽石
男
456
微笑
男
789
天明
男
110
莫影
男
```

如果需要一行一行输出，则需要自己判断是否是行尾，也就是字符`\n`：

```cpp
	while (!ifs.eof()) {
		ifs >> buf;
		std::print("{} ", buf);	//123
		if (ifs.peek() == '\n') {
			std::println();
		}
	}
```

`peek`方法用来窥探下一个字符，并不会移动文件位置指针；如果想要读取下一个字符并移动文件位置指针可以使用`get`方法！！！

##### 方法读取

使用`get`方法能读取一行数据，也就是遇到`\n`结束读取：

```cpp
	std::string buf(100, '\0');
	ifs.get(buf.data(), buf.size());
	std::println("{}", buf);			//123 顽石 男
```

`get`方法还有一个重载，能自己指定分割符：

```cpp
	ifs.get(buf.data(), buf.size(),' ');
	std::println("{}", buf);			//123
```

还有一个`getline`方法，除了不能获取一个字符之外与get用法一样！

##### 全局函数

使用`std::getline`函数可以直接读取一行，而且可以直接读取到`std::string`对象中，比较方便：

```cpp
	std::string buf;
	while (std::getline(ifs, buf)) {
		std::println("{}", buf);
	}
```

##### 流迭代器

通过`	std::istreambuf_iterator`流迭代器，可以将文件所有内容都读取出来：

```cpp
	std::string str(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	//或简化为如下写法
	std::string str(std::istreambuf_iterator<char>(ifs), {});
```

### ofstream

ofstream操作和ifstream类似！

#### 打开文件

```cpp
	//创建输出文件流(将内存中的数据写入到文件中)
	std::ofstream ofs("f.txt");
	//判断文件是否打开成功
	if (!ofs) {
		std::println("open file failed");
		return;
	}
```

#### 写入文件

##### 流式写入

```cpp
	ofs << "hello world" << std::endl;
```

##### 方法写入

```cpp
	std::string buf = "hello 顽石老师";
	ofs.write(buf.data(), buf.size());
```

##### 流式迭代器

通过流式迭代器直接赋值：

```cpp
	std::ostreambuf_iterator<char> iter(ofs);
	for (int i = 0; i < 10; i++) {
		iter = 'a' + i;
	}
```

通过`std::copy`函数拷贝进去，这里写入的是二进制数据：

```cpp
	int nums[] = { 1,2,3,4,5,6,7,8,9,10 };
	std::copy(std::begin(nums), std::end(nums), iter);
```

### fstream

fstream可以读取文件也可以写文件，但是必须要指定打开模式！

#### 打开模式

打开模式以及介绍如下：

| 模式标记    | 适用对象                  | 作用                                                         |
| ----------- | ------------------------- | ------------------------------------------------------------ |
| ios::in     | ifstream fstream          | 打开文件用于读取数据。如果文件不存在，则打开出错。           |
| ios::out    | ofstream fstream          | 打开文件用于写入数据。如果文件不存在，则新建该文件；如果文件原来就存在，则打开时清除原来的内容。 |
| ios::app    | ofstream fstream          | 打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件。 |
| ios::ate    | ifstream                  | 打开一个已有的文件，并将文件读指针指向文件末尾（读写指 的概念后面解释）。如果文件不存在，则打开出错。 |
| ios:: trunc | ofstream                  | 打开文件时会清空内部存储的所有数据，单独使用时与 ios::out 相同。 |
| ios::binary | ifstream ofstream fstream | 以二进制方式打开文件。若不指定此模式，则以文本模式打开。     |

#### 打开文件

##### 只读打开

可以直接通过构造函数指定文件名和打开模式，并自动打开文件：

```cpp
	std::fstream fs("stu.txt", std::ios::in);
	if (!fs) {
		std::println("open file failed");	
	}
```

也可以先创建空对象，然后调用`open`方法打开文件：

```cpp
	std::fstream fs;
	fs.open("stu.txt", std::ios::in);
	if (!fs) {
		std::println("open file failed");	
	}
```

> 同样的，ifstream和ofstream也可以先创建对象然后再打开！

##### 只写打开

只写打开只需要将只读打开中的打开模式变为`std::ios::out`即可！

##### 读写打开

同时指定`in`和`out`模式即可以可读可写的方式打开文件：

```cpp
	std::fstream fs("hdy1.txt", std::ios::in | std::ios::out);
	if (!fs) {
		std::println("open file failed");	
	}
```

当时注意，当文件不存在时文件会打开失败，通过添加`std::ios::trunc`模式可以自动创建文件。

```cpp
	std::fstream fs("hdy1.txt", std::ios::in | std::ios::out | std::ios::trunc);
```

然后就可以进行文件读写了：

```cpp
	//写入文件
	fs << "hello world";

	//重置文件位置指针
	//fs.seekg(0, std::ios::beg);
	fs.seekp(0, std::ios::beg);

	//读取文件
	std::string buf;
	fs >> buf;
	std::println("{}", buf);
```

istream 和 ostream 都提供了用于重新定位文件位置指针的成员函数。这些成员函数包括关于 istream 的 seekg（"seek get"）和关于 ostream 的 seekp（"seek put"）。

seekg 和 seekp 的参数通常是一个长整型。第二个参数可以用于指定查找方向。
查找方向：

+ ios::beg	默认的，从流的开头开始定位
+ ios::cur	从流的当前位置开始定位
+ ios::end	从流的末尾开始定位

## 字符串流

在 C++ 中，**字符串流（String Stream）** 是一种基于内存的流操作机制，定义在 `<sstream>` 头文件中，用于在程序内部处理字符串的输入输出。字符串流允许程序像操作标准输入输出流（`cin`、`cout`）或文件流（`ifstream`、`ofstream`）一样操作字符串数据，特别适合格式化输出、解析输入或在内存中构建和处理字符串。本文将详细讲解 C++ 字符串流操作，包括基本概念、核心类、操作方法、典型应用、错误处理、性能优化以及代码示例。

### 字符串流的基本概念

字符串流是 C++ 流体系的一部分，将字符串作为输入输出的数据源，而不是文件或标准设备。通过字符串流，程序可以在内存中以流的方式读写字符串，简化了字符串的格式化和解析。

#### 字符串流的特点

- **内存操作**：字符串流直接操作内存中的字符串，无需与外部设备交互。
- **类型安全**：通过重载的 `<<` 和 `>>` 操作符，支持多种数据类型的读写（如 `int`、`double`、`string`）。
- **灵活性**：适合动态构建字符串、解析复杂输入或格式化输出。
- **继承流体系**：字符串流继承自 `iostream` 体系，具备流的状态管理和格式化功能。

#### 字符串流的核心类

字符串流定义在 `<sstream>` 中，主要包括以下三个类，继承自标准流类：

- **`istringstream`**：输入字符串流，继承自 `istream`，用于从字符串读取数据。
- **`ostringstream`**：输出字符串流，继承自 `ostream`，用于向字符串写入数据。
- **`stringstream`**：输入输出字符串流，继承自 `iostream`，支持同时读写字符串。

类层次结构如下：

```markdown
ios_base
   |
   ios
   |________________
   |                |
 istream          ostream
   |                |
 iostream
   |________________
   |                |
istringstream  ostringstream
   |                |
   stringstream
```

### 字符串流操作

#### 格式化输出到字符串

```cpp
	std::stringstream is;
	is << "整数:" << 123 << std::endl;
	is << "浮点数:" << 3.14 << std::endl;
	is << "字符串:" << "hello world" << std::endl;
	std::println("{}", is.str());
```

输出如下：

```css
整数:123
浮点数:3.14
字符串:hello world
```

#### 解析字符串

```cpp
	std::stringstream os("1001 顽石 18");	
	
	uint32_t id;
	std::string name;
	int age;
	os >> id >> name >> age;
	std::println("id:{}, name:{}, age:{}", id, name, age);
```

输出如下：

```cpp
id:1001, name:顽石, age:18
```

#### 字符串分割

```cpp
	std::stringstream ss("apple,banana,orange,grape");
	std::string token;

	std::println("原始字符串:{}", ss.str());
	std::print("分割结果:");

	while (std::getline(ss, token, ',')) {
		std::print("{} ", token);
	}
```

输出结果如下：

```css
原始字符串:apple,banana,orange,grape
分割结果:apple banana orange grape
```

#### 注意

通常情况下流对象是无法复用的，如果要复用，需要清除流状态：

```cpp
ss.str(""); // 清空内容
ss.clear(); // 清除状态标志
```

## 流操作

### stream_iterator

流迭代器适配器（stream_iterator），简称流迭代器，其功能就是从指定的流读取/写入数据。介于流对象又可细分为输入流对象（istream）和输出流对象（ostream），C++ STL 标准库中，也对应的提供了 2 类流迭代器：

| 迭代器适配器     | 功能                     |
| ---------------- | ------------------------ |
| istream_iterator | 用来读取输入流中的数据   |
| ostream_iterator | 用来将数据写入到输出流中 |

#### istream_iterator

   istreambuf_iterator 输入流缓冲区迭代器的功能是从指定的流缓冲区中读取指定类型的数据。

> 值得一提的是，该类型迭代器本质是一个输入迭代器，即假设 p 是一个输入流迭代器，则其只能进行 ++p、p++、*p 操作，同时迭代器之间也只能使用 == 和 != 运算符。

##### 读取基本类型

```cpp
int main()
{
	//通过流迭代器获取char类型数据
	{
		//std::cin.unsetf(std::ios::skipws);		//如果需要获取空格，取消掉跳过空白字符标志即可
		std::istream_iterator<char> in(std::cin);
		std::istream_iterator<char> eof;			//创建用于表示结束的迭代器,对于接受char类的迭代器来说，只有按下Ctrl+Z才能结束输入
		std::string str(in, eof);
		std::println("{}", str);
	}

	//通过流迭代器获取double类型数据
	{
		std::istream_iterator<double> in(std::cin);
		std::istream_iterator<double> eof;			//创建用于表示结束的迭代器,遇到不是浮点型/整型的数据时结束输入
		std::vector<int> vec(in, eof);
		std::println("{}", vec);
	}

	//通过流迭代器初始化容器
	{
		std::istream_iterator<int> in(std::cin);
		std::vector<int> nums(in, std::istream_iterator<int>());
		std::println("{}", nums);
	}
	
	return 0;
}
```

##### 读取类

```cpp
int main2()
{
	//1，流迭代器从cin读取数据
	{
		std::istream_iterator<Student> in(std::cin);
		std::istream_iterator<Student> eof;

		std::vector<Student> stus(in, eof);
		for (auto& s : stus) {
			std::cout << s << std::endl;
		}
	}
    
	//2，流迭代器从stringstream读取数据
	{
		std::stringstream ss("1 maye 2 tianming 3 玩蛇");
		std::istream_iterator<Student> in(ss);
		std::istream_iterator<Student> eof;

		std::vector<Student> stus(in, eof);
		for (auto& s : stus) {
			std::cout << s << std::endl;
		}
	}
	//3，流迭代器从ifstream读取数据
	{
		std::ifstream ifs("students.txt");
		if (!ifs) {
			std::cerr << "students.txt open failed" << std::endl;
			return;
		}
		std::istream_iterator<Student> in(ifs);
		std::istream_iterator<Student> eof;

		std::vector<Student> stus(in, eof);
		for (auto& s : stus) {
			std::cout << s << std::endl;
		}
	}
	return 0;
}
```

#### ostream_iterator

  和 istreambuf_iterator 输入流缓冲区迭代器恰恰相反，ostreambuf_iterator 输出流缓冲区迭代器用于将字符元素写入到指定的流缓冲区中。

>  实际上，该类型迭代器本质上是一个输出迭代器，这意味着假设 p 为一个输出迭代器，则它仅能执行 ++p、p++、*p=t 以及 *p++=t 操作。

另外，和 ostream_iterator 输出流迭代器一样，istreambuf_iterator 迭代器底层也是通过重载赋值（=）运算符实现的。换句话说，即通过赋值运算符，每个赋值给输出流缓冲区迭代器的字符元素，都会被写入到指定的流缓冲区中。

```cpp
int main()
{
	std::ostream_iterator<const char*> out_it(std::cout,",");
    
	out_it = "hello";
	out_it = "wrold";
	out_it = "maye";
	return 0;
}
```

![image-20230715164618405](./assets/image-20230715164618405.png)

out_it第一个参数为输出流对象，第二个参数为写入数据之后，每个数据之间的分隔字符串。

输出流迭代器常和 copy() 函数连用，即作为该函数第 3 个参数：

```cpp
	//准备输出的数据
	std::vector<Student> stus = {
		{100,"maye"},
		{101,"hello"},
		{102,"world"},
	};

	//输出到标准输出
	std::copy(stus.begin(), stus.end(), std::ostream_iterator<Student>(std::cout, " | "));

	std::println();

	//输出到字符串流
	std::stringstream ss;
	std::copy(stus.begin(), stus.end(), std::ostream_iterator<Student>(ss, " | "));
	std::println("{}", ss.str());

	//输出到文件流
	std::ofstream of("xxx.txt");
	if (of.is_open()) {
		std::copy(stus.begin(), stus.end(), std::ostream_iterator<Student>(of, " | "));
	}
```

### streambuf_iterator

流缓冲迭代器适配器（streambuf_iterator），简称流缓冲迭代器，其功能也是从指定的流读取/写入数据，但是不支持自定义对象。(和stream_iterator的区别在于stream_iterator更接近底层不会忽略空白字符)介于流对象又可细分为输入流对象（istream）和输出流对象（ostream），C++ STL 标准库中，也对应的提供了 2 类流迭代器：

| 迭代器适配器        | 功能                     |
| ------------------- | ------------------------ |
| istreambuf_iterator | 用来读取输入流中的数据   |
| ostreambuf_iterator | 用来将数据写入到输出流中 |

#### istreambuf_iterator

```cpp
int main()
{
	//通过流缓冲迭代器获取char类型数据，也只能获取char类型的数据，因为构造函数需要basic_istream<_Elem, _Traits>对象
	//cin就是basic_istream<char, char_traits<char>>;这个类型的，所以只能获取char
	//通过流迭代器获取char类型数据
	std::istreambuf_iterator<char> in(std::cin);
	std::istreambuf_iterator<char> eof;			//创建用于表示结束的迭代器,对于接受char类的迭代器来说，只有按下Ctrl+Z才能结束输入
	std::string str(in, eof);
	std::println("{}", str);
	
	return 0;
}
```

#### ostreambuf_iterator

```c
	//ostreambuf_iterator
	{
		std::ostreambuf_iterator<char> out_it(std::cout);
		for (size_t i = 0; i < 26; i++)
		{
			out_it = 'a' + i;
		}

	}
```



# formatter(格式化器)

首先要明确：`std::format` 的灵活扩展性核心来自于**特化 `std::formatter` 模板类**，我们通过为自定义类型（或扩展内置类型）特化这个模板，实现该类型的自定义格式化逻辑，让 `std::format` 能够识别并处理该类型。

## 前置知识准备

1. 依赖标准：`std::format` 是 C++20 引入的，编译器需支持 C++20 及以上（GCC 11+、Clang 14+、MSVC 2019+）。
2. 核心头文件：`<format>`（使用 `std::format`、`std::formatter`、`std::format_context` 等）。
3. 核心概念：
   - `std::formatter<T, CharT>`：核心模板类，特化后提供格式化能力，`T` 是要格式化的类型，`CharT` 是字符类型（默认 `char`，支持 `wchar_t`）。
   - 格式化解析：解析 `std::format` 中的格式说明符（如 `{:>10}` 中的 `>10`）。
   - 格式化输出：将自定义类型转换为格式化后的字符串，写入输出上下文。
   - 两个核心成员函数：`parse()`（解析格式说明符）和 `format()`（执行格式化逻辑）。

## std::formatter 自定义的核心规则

要让 `std::format` 支持自定义类型 `MyType`，必须在 `std` 命名空间下**特化 `std::formatter<MyType>`**（或 `std::formatter<MyType, CharT>` 支持泛型字符），且特化的类必须满足 `Formatter` 概念，即包含：

1. `parse()` 成员函数

   ：解析格式说明符（如 

   ```cpp
   :fmt
   ```

    部分），返回解析结束的迭代器。

   - 函数签名：`template <typename ParseContext> constexpr typename ParseContext::iterator parse(ParseContext& ctx)`。
   - 作用：处理用户传入的格式选项（如对齐、宽度、自定义格式标记），校验格式合法性，保存必要的格式配置。
   - 上下文 `ParseContext`：提供格式字符串的迭代器，`ctx.end()` 表示格式说明符结束。

   

2. `format()` 成员函数

   ：将自定义类型对象转换为格式化字符串，写入输出上下文。

   - 函数签名：`template <typename FormatContext> typename FormatContext::iterator format(const MyType& obj, FormatContext& ctx)`。
   - 作用：根据 `parse()` 解析得到的格式配置，将 `obj` 格式化，写入 `ctx.out()` 提供的输出迭代器。
   - 上下文 `FormatContext`：提供输出迭代器，`std::format_to(ctx.out(), ...)` 用于写入格式化内容。

## 简单类型的格式化器

我们先从简单场景入手：自定义一个 `Person` 类，实现其格式化支持，支持默认格式和自定义格式说明符。

### 定义自定义类型

```cpp
#include <format>
#include <string>
#include <iostream>
#include <charconv> // 用于数值转字符串（可选，简化逻辑）

// 自定义测试类型：人物信息
struct Person {
    std::string name; // 姓名
    int age;          // 年龄
    double height;    // 身高（米）
};
```

### 特化std::formatter\<Person>

我们为 `Person` 实现两种格式化模式：

- 默认模式（无格式说明符）：输出 `Person{姓名: XXX, 年龄: XX, 身高: XX.XX}`。
- 简化模式（格式说明符 `s`）：输出 `XXX (XX岁, XX.XXm)`。

```cpp
// 在 std 命名空间下特化 std::formatter，让 std::format 识别 Person 类型
namespace std {
// 特化 std::formatter<Person>，默认字符类型为 char
template <>
struct formatter<Person> {
    // 定义内部变量：保存解析后的格式模式（false=默认模式，true=简化模式）
    bool use_simple_format = false;

    // --------------- 核心函数1：parse() - 解析格式说明符 ---------------
    template <typename ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx) {
        // 获取格式说明符的起始迭代器（ctx.begin() 指向格式说明符开头，ctx.end() 指向结尾）
        auto it = ctx.begin();
        const auto end = ctx.end();
        
        // 解析格式说明符（仅支持空或 's'）
        if (it != end) {
            if (*it == 's') {
                use_simple_format = true;
                ++it; // 移动迭代器，跳过已解析的 's'
				// 校验：格式说明符只能有一个字符（或空），不能有多余内容
				if (*it != '}') {
					throw format_error("Person 格式说明符过长，仅支持空或 's'");
				}
			}
        }

        // 返回解析结束的迭代器，告诉 std::format 解析完成
        return it;
    }

    // --------------- 核心函数2：format() - 执行格式化逻辑 ---------------
    template <typename FormatContext>
    typename FormatContext::iterator format(const Person& p, FormatContext& ctx) const {
        // 根据解析得到的格式模式，执行不同的格式化逻辑
        if (use_simple_format) {
            // 简化模式：XXX (XX岁, XX.XXm)
            return format_to(
                ctx.out(), // 输出迭代器，格式化内容写入此处
                "{} ({}岁, {:.2f}m)",
                p.name, p.age, p.height
            );
        } else {
            // 默认模式：Person{姓名: XXX, 年龄: XX, 身高: XX.XX}
            return format_to(
                ctx.out(),
                "Person{{姓名: {}, 年龄: {}, 身高: {:.2f}}}",
                p.name, p.age, p.height
            );
        }
    }
};
} // namespace std
```

### 测试自定义格式化器

```cpp
int main() {
    try {
        Person p1 = {"张三", 25, 1.80};
        Person p2 = {"李四", 30, 1.75};

        // 1. 默认格式（无格式说明符）
        std::cout << "默认格式：" << std::format("{}\n", p1) << std::endl;

        // 2. 简化格式（格式说明符 :s）
        std::cout << "简化格式：" << std::format("{:s}\n", p2) << std::endl;

        // 3. 结合其他格式化选项（对齐、宽度，std::formatter 会自动兼容内置选项）
        std::cout << "带对齐的简化格式：" << std::format("{:>30s}\n", p1) << std::endl;

        // 4. 非法格式说明符（会抛出异常）
        // std::cout << std::format("{:x}\n", p1) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

#### 运行结果

```css
默认格式：Person{姓名: 张三, 年龄: 25, 身高: 1.80}

简化格式：李四 (30岁, 1.75m)

带对齐的简化格式：                张三 (25岁, 1.80m)
```

## 复杂格式解析

我们扩展 `Person` 的格式化器，支持：

- 格式说明符 `h`：仅输出身高（支持指定精度，如 `:h.3` 表示保留 3 位小数）。
- 格式说明符 `n`：仅输出姓名（支持对齐，如 `:n>10` 表示右对齐，宽度 10）。

```cpp
namespace std {
template <>
struct formatter<Person> {
    // 定义格式配置
    enum class FormatMode {
        Default,    // 默认
        Simple,     // 简化
        Height,     // 仅身高
        Name        // 仅姓名
    } mode = FormatMode::Default;

    int height_precision = 2; // 身高默认精度
    int name_width = 0;       // 姓名对齐宽度
    bool name_right_align = false; // 姓名是否右对齐

    // 解析复杂格式说明符
    template <typename ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx) {
        auto it = ctx.begin();
        const auto end = ctx.end();

        if (it == end) {
            return it; // 无格式说明符，使用默认模式
        }

        // 第一步：解析模式标记（s/h/n）
        switch (*it) {
            case 's':
                mode = FormatMode::Simple;
                ++it;
                break;
            case 'h':
                mode = FormatMode::Height;
                ++it;
                break;
            case 'n':
                mode = FormatMode::Name;
                ++it;
                break;
            default:
                throw format_error("无效的 Person 格式标记，支持 s/h/n");
        }

        // 第二步：解析对应模式的附加参数
        switch (mode) {
            case FormatMode::Height:
                // 解析身高精度（如 :h.3）
                if (it != end && *it == '.') {
                    ++it;
                    height_precision = 0;
                    // 解析数字参数
                    while (it != end && std::isdigit(*it)) {
                        height_precision = height_precision * 10 + (*it - '0');
                        ++it;
                    }
                    if (height_precision < 0 || height_precision > 10) {
                        throw format_error("身高精度必须在 0-10 之间");
                    }
                }
                break;
            case FormatMode::Name:
                // 解析姓名对齐方式（如 :n>10）
                if (it != end) {
                    if (*it == '>') {
                        name_right_align = true;
                        ++it;
                    } else if (*it == '<') {
                        name_right_align = false;
                        ++it;
                    }
                }
                // 解析姓名宽度
                if (it != end && std::isdigit(*it)) {
                    name_width = 0;
                    while (it != end && std::isdigit(*it)) {
                        name_width = name_width * 10 + (*it - '0');
                        ++it;
                    }
                }
                break;
            default:
                // 无附加参数，直接退出
                break;
        }

        // 校验：无多余未解析内容
        if (it != end) {
            throw format_error("Person 格式说明符包含无效内容");
        }

        return it;
    }

    // 执行复杂格式化逻辑
    template <typename FormatContext>
    typename FormatContext::iterator format(const Person& p, FormatContext& ctx) {
        switch (mode) {
            case FormatMode::Default:
                return format_to(ctx.out(), "Person{{姓名: {}, 年龄: {}, 身高: {:.{}f}}}",
                                 p.name, p.age, p.height, height_precision);
            case FormatMode::Simple:
                return format_to(ctx.out(), "{} ({}岁, {:.{}f}m)",
                                 p.name, p.age, p.height, height_precision);
            case FormatMode::Height:
                return format_to(ctx.out(), "身高：{:.{}f} 米",
                                 p.height, height_precision);
            case FormatMode::Name:
                if (name_width > 0) {
                    if (name_right_align) {
                        return format_to(ctx.out(), "{:>{}}", p.name, name_width);
                    } else {
                        return format_to(ctx.out(), "{:<{}}", p.name, name_width);
                    }
                } else {
                    return format_to(ctx.out(), "{}", p.name);
                }
            default:
                return ctx.out();
        }
    }
};
} // namespace std
```

### 进阶场景测试代码

```cpp
int main() {
    try {
        Person p = {"张三", 25, 1.8056};

        std::cout << "仅身高（3位小数）：" << std::format("{:h.3}\n", p) << std::endl;
        std::cout << "仅姓名（右对齐，宽度10）：" << std::format("{:n>10}\n", p) << std::endl;
        std::cout << "仅姓名（左对齐，宽度10）：" << std::format("{:n<10}\n", p) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### 进阶场景运行结果

```
仅身高（3位小数）：身高：1.806 米
仅姓名（右对齐，宽度10）：        张三
仅姓名（左对齐，宽度10）：张三        
```

## 格式化vector\<Person>

当我们使用std::vector存储Point时，并不能直接试用format格式化，也需要自己提供格式化器！

```c
std::vector<Point> points(5, Point{ 1,2 });
std::cout << std::format("{}", points) << std::endl;
```

提供如下formatter格式化器，还支持手动传递分割符！

```cpp
template<>
struct std::formatter<std::vector<Point>> {
	std::string_view delimiter = ",";
	
	constexpr auto parse(std::format_parse_context& ctx) {
		auto it = ctx.begin();
		if (it == ctx.end())
			return it;

		//解析分割符
		if (*it != '}') {
			delimiter = std::string_view(it, it + 1);
			++it;
		}

		if (it != ctx.end() && *it != '}')
			throw std::format_error("Invalid format args for QuotableString.");

		return it;
	}

	auto format(const std::vector<Point>& pos, std::format_context& ctx)const
	{
		std::ostringstream ss;
		for (auto& p : pos) {
			ss << std::format("{}", p) << delimiter;
		}
		auto str = ss.str();
		str.pop_back();
        //将数据拷贝到输出流中
		return std::copy(str.begin(), str.end(), ctx.out());
	}
};
```

使用案例：

```cpp
std::cout << std::format("{:#}", points) << std::endl;
```

## 关键注意事项与最佳实践

1. **命名空间要求**：必须在 `std` 命名空间下特化 `std::formatter`，因为 `std::format` 会在 `std` 命名空间中查找对应的 `formatter` 特化。
2. **异常处理**：解析非法格式说明符时，应抛出 `std::format_error`（或继承自 `std::exception` 的异常），保持与 `std::format` 内置逻辑一致。
3. **constexpr 解析**：`parse()` 函数尽量声明为 `constexpr`，支持编译期解析格式说明符，提升性能。
4. **避免资源泄露**：`format()` 函数中不建议创建大型临时对象，优先使用 `std::format_to` 直接写入输出上下文。
5. **兼容内置格式选项**：自定义格式化器可以兼容 `std::format` 的内置选项（如对齐、宽度、精度），无需重复实现，只需在 `format()` 中复用内置格式化逻辑。
6. **模板特化限制**：只能对**用户自定义类型**或**明确允许特化的标准库类型**特化 `std::formatter`，禁止对未明确允许的标准库类型（如 `int`、`std::string`）进行特化。

## parse和format函数返回值

### 先明确核心结论

两个函数的返回值**都是「迭代器」**，但对应不同的上下文、承担不同的职责：

1. `parse()`：返回 `ParseContext::iterator` —— 标记「格式说明符解析的结束位置」
2. `format()`：返回 `FormatContext::iterator` —— 标记「格式化内容写入的结束位置」

### 逐函数详细解析

#### `parse()` 函数的返回值

##### （1）返回值类型

函数签名中的返回值：`typename ParseContext::iterator`

- `ParseContext` 是格式化解析的上下文类，它内部封装了「格式说明符字符串」的迭代器（本质是指向格式字符串字符的指针 / 迭代器）。
- 这个迭代器的作用是**遍历 `std::format` 中 `{:xxx}` 里的 `xxx` 部分（格式说明符）**。

##### （2）返回值的核心作用

告诉 `std::format` 库：「我已经解析到格式说明符的这个位置了，后面的内容不归我管（或者已经解析完毕）」。

- 最常见的场景：解析完所有合法的格式说明符后，返回 `ctx.end()`（格式说明符的末尾迭代器），表示解析完成。
- 特殊场景：如果自定义格式化器只解析格式说明符的前半部分，剩下的交给内置逻辑处理（极少用），则返回中间迭代器。

##### （3）通俗类比

把格式说明符看作一条小路，`ctx.begin()` 是小路的起点，`ctx.end()` 是小路的终点。

`parse()` 函数就是沿着小路往前走，边走边解析路边的标识（格式选项），走到不想走 / 走不动（解析完毕 / 遇到非法内容）时，停下脚步，返回当前的位置（迭代器），告诉后面的人「我就处理到这了」。

##### （4）代码示例回顾（突出返回值）

```cpp
template <typename ParseContext>
constexpr typename ParseContext::iterator parse(ParseContext& ctx) {
    auto it = ctx.begin(); // 起点：格式说明符的第一个字符
    const auto end = ctx.end(); // 终点：格式说明符的最后一个字符的下一位

    // 解析 's' 格式符
    if (it != end && *it == 's') {
        use_simple_format = true;
        ++it; // 往前走一步，跳过 's'
    }

    // 校验：不能有多余的未解析内容
    if (it != end) {
        throw std::format_error("格式说明符过长");
    }

    return it; // 返回解析结束的位置（此时 it == end，说明解析完毕）
}
```

##### （5）关键补充

- 为什么要返回这个迭代器？因为 `std::format` 支持「复合格式说明符」，自定义格式化器可能只处理一部分，剩下的由库内置逻辑处理（比如对齐、宽度），返回迭代器是为了实现「分工协作」。
- 对于大多数自定义场景（只处理自己的专属格式符），最终返回的迭代器必须等于 `ctx.end()`，否则会被判定为解析未完成（抛出异常或未定义行为）。

####  `format()` 函数的返回值

##### （1）返回值类型

函数签名中的返回值：`typename FormatContext::iterator`

- `FormatContext` 是格式化输出的上下文类，它内部封装了「输出缓冲区的迭代器」（通常是 `std::back_insert_iterator`，用于向字符串缓冲区中插入字符）。
- 这个迭代器的作用是**标记格式化内容写入到输出缓冲区的哪个位置了**。

##### （2）返回值的核心作用

告诉 `std::format` 库：「我已经把自定义类型的格式化内容写到输出缓冲区的这个位置了，后续如果还有其他内容，从这个位置往后写即可」。

- 几乎所有场景下，我们都会使用 `std::format_to()` 来写入内容，而 `std::format_to()` 的返回值正好就是「写入结束后的输出迭代器」，直接返回这个值即可。
- 无需手动创建迭代器，只需复用 `std::format_to()` 的返回值（这是最佳实践）。

##### （3）通俗类比

把输出缓冲区看作一个空白的笔记本，`ctx.out()` 是笔记本的当前书写位置（笔尖）。

`format()` 函数就是用笔尖在笔记本上写内容（格式化后的字符串），写完之后，笔尖停留在最后一个字符的下一位，返回这个笔尖的位置（迭代器），告诉后面的人「我写到这了，你接着往下写就行」。

##### （4）代码示例回顾（突出返回值）

```cpp
template <typename FormatContext>
typename FormatContext::iterator format(const Person& p, FormatContext& ctx) {
    if (use_simple_format) {
        // std::format_to() 会写入内容，并返回写入后的迭代器，直接返回即可
        return std::format_to(
            ctx.out(), // 起始写入位置
            "{} ({}岁, {:.2f}m)",
            p.name, p.age, p.height
        );
    } else {
        return std::format_to(
            ctx.out(),
            "Person{{姓名: {}, 年龄: {}, 身高: {:.2f}}}",
            p.name, p.age, p.height
        );
    }
}
```

##### （5）关键补充

- 为什么要返回这个迭代器？因为 `std::format` 可能需要格式化多个参数（比如 `std::format("{} - {}", p1, p2)`），返回写入结束的迭代器，能让库高效地继续写入下一个参数的格式化内容，避免重复操作或数据覆盖。
- 禁止手动修改这个迭代器，只需直接返回 `std::format_to()` 的结果，这是最安全、最高效的方式。
- 这个迭代器是「输出迭代器」，只支持写入操作，不支持随机访问（无需关心其具体实现，只需复用即可）。

### 两个返回值的共性与区别

#### 共性

1. 都是「迭代器」，用于标记「位置」，实现高效的连续操作（解析 / 写入）。
2. 都不需要用户手动创建复杂的迭代器对象，只需复用上下文提供的迭代器或相关函数的返回值。
3. 都是模板类型，由 `Context` 类决定具体类型，保证了兼容性（支持 `char`/`wchar_t` 等字符类型）。

#### 区别

| 特性       | `parse()` 返回值                 | `format()` 返回值                  |
| ---------- | -------------------------------- | ---------------------------------- |
| 对应上下文 | `ParseContext`（解析上下文）     | `FormatContext`（输出上下文）      |
| 操作对象   | 格式说明符字符串（只读）         | 输出缓冲区（只写）                 |
| 核心作用   | 标记解析结束位置                 | 标记写入结束位置                   |
| 常见来源   | `ctx.begin()` 遍历后得到         | `std::format_to()` 的返回值        |
| 最终目标   | 通常等于 `ctx.end()`（解析完毕） | 通常是输出缓冲区的末尾（写入完毕） |

### 总结

1. `parse()` 返回 `ParseContext::iterator`，标记**格式说明符的解析结束位置**，告诉 `std::format` 库解析完成，通常返回遍历后的迭代器（最终等于 `ctx.end()`）。
2. `format()` 返回 `FormatContext::iterator`，标记**输出缓冲区的写入结束位置**，告诉 `std::format` 库写入完成，最佳实践是直接返回 `std::format_to()` 的返回值。
3. 两个返回值的核心目的都是「与 `std::format` 库协作」，实现高效、准确的格式化流程，无需深入理解迭代器的具体实现，只需按规范复用即可。

## 自定义format

`std::format`的格式字符串，只能传递编译时常量，如下所示代码，将不能运行。

```cpp
const std::string fmt = "{} {}";
std::cout << std::format(fmt, 1, "nihao") << std::endl;	//对即时函数的调用不是常量表达式
```

如果有这种需求怎么办呢?这就要自己实现一个format函数了！实现如下：

```cpp
namespace hdy {
	template<typename ...Args>
	auto format(std::string_view fmt, Args&& ...args)
	{
		return std::vformat(fmt, std::make_format_args(args...));
	}
}
```

调用它！

```cpp
std::cout << hdy::format(fmt, 1, "nihao") << std::endl;	//调用自己写的format可以
```

这样就能使用任何类型的字符串类型了！

> std::print或std::println格式字符串，只支持编译时常量，不能使用变量！如果你想用先定义格式，可以使用宏定义或者编译时常量。
>
> ```c
> constexpr char const* str = "{} {}";		//编译时常量
> std::println(str, 1, "nihao");				//可以使用
> ```

