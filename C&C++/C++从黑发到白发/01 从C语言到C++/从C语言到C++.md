# 从C语言到C++

C++ 是一种高级语言，它是由 Bjarne Stroustrup 于 1979 年在贝尔实验室开始设计开发的。C++ 进一步扩充和完善了 C 语言，最初命名为带类的C，后来在 1983 年更名为 C++。是一种面向对象的程序设计语言。C++ 可运行于多种平台上，如 Windows、MAC 操作系统以及 UNIX 的各种版本。

我们可以说C++ 是 C 的一个超集，事实上，**几乎**任何合法的 C 程序都是合法的 C++ 程序。

接下来，我们来学习C++在C语言基础上做的一些改变，帮助我们从C语言平滑过渡到C++。

## 基本变化

### 头文件

C++为了兼容C，支持所有的C头文件。但为了符合C++标准，所有的C头文件都有一个C++版本的，即去掉.h，并在名子前面加c。如\<cstring>和\<cmath>。

|  C语言   |   C++    |
| :------: | :------: |
| stdio.h  | iostream |
|  math.h  |  cmath   |
| string.h | cstring  |
| stdlib.h | cstdlib  |
|  ......  |  ......  |

### 命名空间

命名空间（Namespace）是C++中**避免命名冲突**的机制，它将全局作用域划分为不同的命名域。

#### 为什么需要命名空间？

加入我们引入了两个库，这两个库中都定义了相同名称的函数，那么在调用时，编译器会报错！因为无法确定你要调用哪个函数。

```cpp
// 库A
void print() { printf("I'm first print!"); }

// 库B  
void print() { printf("I'm last print!"); }

// 使用时会冲突！
print(); // 调用哪个？
```

我们可以将这两个函数放到不同的命名空间中，在使用时显示指定使用哪个命名空间内的`print`函数即可！

#### 定义命名空间

定义命名空间使用`namespace`关键字，语法如下：

```cpp
namespace <name>{
    //变量、函数、类、命名空间都可以放在命名空间中
}
```

例如：

```cpp
// 库A
namespace hdy{
    void print() { printf("I'm first print!"); }
}


// 库B  
namespace zc{
    void print() { printf("I'm last print!"); }
}

print(); // 此时提示未定义的标识符
```

#### 使用命名空间

有三种使用命名空间的方式，每一种都大不一样，不同时机可以选择不同的方式。

##### 作用域解析符（推荐）

```cpp
void test_1()
{
    hdy::print();   //明确调用hdy库中的print函数
    zc::print();    //明确调用zc库中的print函数
}
```

###### **✅ 优点**

1. **最安全**：完全避免命名冲突
2. **最清晰**：代码自文档化，明确知道每个标识符的来源
3. **可维护性强**：重命名或重构时容易查找和替换
4. **适用于头文件**：不会污染其他文件的命名空间

###### **❌ 缺点**

1. **代码冗长**：重复书写命名空间前缀
2. **可能降低可读性**：长命名空间会使代码行过长

###### **💡 适用场景**

- 头文件中的声明和定义
- 大型项目或库开发
- 频繁切换使用不同库的同名函数时

##### using声明（引入特定名称）

```cpp
void  test_2()
{
    //只引入需要的名称(推荐在最小作用域中使用)
    using hdy::print;

    //可以直接调用print，实际上是hdy::print()
    print();
}

// 不推荐：在全局或头文件使用
// using hdy::print;  // 避免在全局作用域，暴漏给全局作用域，可能导致与全局作用域的名称冲突。
```

###### **✅ 优点**

1. **相对安全**：只引入需要的名称，冲突概率低
2. **代码简洁**：在局部作用域内减少重复
3. **控制精细**：可以精确控制引入哪些名称
4. **作用域明确**：通常用于函数或类内部，不会影响外部

###### **❌ 缺点**

1. **可能引入冲突**：引入的名称与局部名称冲突
2. **需要管理**：需维护using声明列表

##### using指令（引入整个命名空间）

```cpp
void test_3()
{
    //在局部作用域中引入整个命名空间
	using namespace hdy;

    //直接使用print()，不需要加命名空间前缀
    print();
}
```

###### **✅ 极少数的优点**

1. **代码最短**：无需任何前缀
2. **原型开发方便**：快速编写测试代码

###### **❌ 严重缺点**

1. **命名冲突高风险**：可能覆盖自定义函数或变量
2. **代码不清晰**：无法一眼看出标识符来源
3. **编译错误难调试**：冲突时错误信息可能不明确
4. **污染命名空间**：在头文件中使用会污染包含它的所有文件
5. **破坏封装性**：暴露了不需要的接口

#### 使用建议

1. **新手程序员**：始终使用完全限定名，最安全
2. **中级程序员**：在.cpp文件的函数内部使用using声明
3. **高级程序员**：根据团队规范和项目需求选择
4. **原型/测试代码**：可以临时使用using指令，但提交前要清理
5. **大型项目/库开发**：严格执行完全限定名规范

记住：**代码清晰性和可维护性通常比少打几个字符更重要**。在团队项目中，遵循一致的命名空间使用规范比个人习惯更重要。

#### std命名空间

`std` 是 **Standard（标准）** 的缩写，是C++标准库中所有标识符所在的命名空间。

比如我们常用的`printf`函数，在C++中，我们可以使用std命名空间访问。

```cpp
std::printf("hello,I'm %s\n", "maye");
```

#### 命名空间嵌套

C++ 支持嵌套命名空间，即在一个命名空间内部定义另一个命名空间。

##### 嵌套定义与使用

在 C++17 中，引入了一种新的嵌套命名空间的定义方式，使得代码更加简洁。例如，以下两种定义方式是等价的：

```cpp
namespace A {
    namespace B {
        namespace C {
            void show() { std::printf("hello A::B::C"); }
        }
    }
}

namespace A::B::D {
    void show() { std::printf("hello A::B::D"); }
}
```

使用方法如下：

```cpp
void test_4()
{
    A::B::C::show();
    A::B::D::show();
}
```

##### 命名空间别名

当命名空间嵌套过多，或者名字比较长时，可以使用别名来简化命名空间。

```cpp
namespace hdy {
    namespace TestNamespace {
        int a = 10;
        void printA(){ std::printf("a = %d\n", a); }
    }
}

//给命名空间取别名
namespace nspt = hdy::TestNamespace;

void test_5()
{
    //使用别名访问
    nspt::printA();
}
```

##### 内联命名空间

C++11 引入了一种新的嵌套命名空间，称为内联命名空间（inline namespace）。内联命名空间中的名字可以被外层命名空间直接使用。定义内联命名空间的方式是在关键字 *namespace* 前添加关键字 *inline*。例如：

```cpp
namespace work {
    namespace task1 {
        void doWork() { std::printf("task1::doWork\n"); }
    }

    inline namespace task2 {
        void doWork() { std::printf("task2::doWork\n"); }
    }
}

void test_6()
{
    work::task1::doWork();  //调用task1命名空间中的doWork函数
    work::doWork();         //调用task2命名空间中的doWork函数
}
```

#### 匿名命名空间

在C++中，匿名命名空间提供了一种将全局变量和函数限制在单个文件内部的机制。这种命名空间没有名称，因此在定义时不需要指定名称。匿名命名空间的特点是，其中声明的所有内容都具有内部链接属性，这意味着它们只在定义它们的文件中可见，无法在其他文件中通过*extern*关键字访问。

> 在C++新标准中，推荐使用匿名命名空间来代替*static*关键字声明具有文件作用域的全局变量和函数。这是因为*static*在不同的上下文中可能有不同的含义，可能会造成混淆。此外，*static*不能用于修饰类，而匿名命名空间没有这个限制。

```cpp
// 相当于static，限制作用域在当前文件
namespace {  // 匿名命名空间
    int internalVar = 42;  // 只在当前文件中可见
    
    void helper() {        // 类似static函数
        std::cout << "内部帮助函数\n";
    }
}

// 在同一个文件中可以访问
void foo() {
    helper();  // OK
}

// 其他文件无法访问unnamed namespace的内容
```

### 输入输出

> 头文件：<iostream>

C++ 的 I/O 发生在流中，流是字节序列。如果字节流是从设备（如键盘、磁盘驱动器、网络连接等）流向内存，这叫做**输入操作**。如果字节流是从内存流向设备（如显示屏、打印机、磁盘驱动器、网络连接等），这叫做**输出操作**。

必须要包含`iostream`头文件才能使用C++标准输入输出，该文件定义了 **cin、cout、cerr** 和 **clog** 对象，分别对应于标准输入流、标准输出流、非缓冲标准错误流和缓冲标准错误流。

#### 标准输出流（cout）

预定义的对象 **cout** 是 **iostream** 类的一个实例。cout 对象"连接"到标准输出设备，通常是显示屏。**cout** 是与流插入运算符 << 结合使用的，如下所示：

```cpp
void test_7()
{
	char name[] = "Hello C++";
    int age = 45;
    float score = 99.8;

	std::cout << "I'm " << name << " and I'm " << age << " years old. My score is " << score << std::endl;
}
```

当上面的代码被编译和执行时，它会产生下列结果：

```css
I'm Hello C++ and I'm 45 years old. My score is 99.8
```

C++ 编译器根据要输出变量的数据类型，选择合适的流插入运算符来显示值。<< 运算符被重载来输出内置类型（整型、浮点型、double 型、字符串和指针）的数据项。

流插入运算符 << 在一个语句中可以多次使用，如上面实例中所示，**endl** 用于在行末添加一个换行符。

C++直接支持布尔(bool)类型，不需要再包含`stdbool.h`头文件了，当然包含了也不会报错！而且也能直接支持输出`true`和`false`字符串，不需要再经过条件运算符转换了！

```cpp
    bool isOk = (1 == 1);
	std::cout << std::boolalpha << isOk << std::endl;
```

#### 标准输入流（cin）

预定义的对象 **cin** 是 **iostream** 类的一个实例。cin 对象附属到标准输入设备，通常是键盘。**cin** 是与流提取运算符 >> 结合使用的，如下所示：

```cpp
void test_8()
{
    char name[32];
    int age;
    float score;

    std::cout<< "请输入姓名：";
    std::cin >> name;
    std::cout<< "请输入年龄：";
    std::cin >> age;
    std::cout<< "请输入成绩：";
    std::cin >> score;

	std::cout << "姓名：" << name << " 年龄：" << age << " 成绩：" << score << std::endl;
}
```

C++ 编译器根据要输入值的数据类型，选择合适的流提取运算符来提取值，并把它存储在给定的变量中。

流提取运算符 >> 在一个语句中可以多次使用，如果要求输入多个数据，可以使用如下语句：

```cpp
    std::cout << "请输入姓名 年龄 成绩>";
	std::cin >> name >> age >> score;
```

### 万能指针与空指针

#### 万能指针

**万能指针**是指C/C++中的`void*`类型指针，它被称为**无类型指针**或**通用指针**。它可以存储任意类型的数据地址，但在未进行类型转换之前，无法直接对其进行解引用操作。这种特性使得`void*`在泛型编程和处理未知数据类型时非常有用。

+ C语言：在C语言中万能指针能和其他任意类型指针之间相互自动转换。

  ```cpp
  void* p = NULL;
  int* pi = p;
  void* pv = pi;
  ```

  完美运行，没有任何警告！

+ C++：其他类型指针能自动转换为`void*`，但是`void*`不能自动转换为其他类型指针，必须强转。

  ```cpp
  void* p = NULL;
  int* pi = p;        //error C2440: “初始化”: 无法从“void *”转换为“int *”
  void* pv = pi;
  ```

#### 空指针

在C++中，**空指针**是一种特殊的指针，表示它不指向任何有效的内存地址。空指针的值通常被定义为`NULL`、`0`或`nullptr`，其中`nullptr`是C++11引入的一个更安全的空指针表示法。

**为什么引入`nullptr`表示空指针？**

首先，我们看下`NULL`的定义：

```css
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
```

从上面可以看出：

+ 在C语言中`NULL`被定义为`((void *)0)`，也就是把0转成了万能指针了！又因为在C语言中，万能指针能自动转换为其他类型指针，所以可以直接使用！

+ 在C++中`NULL`被定义为`0`，也就是说，使用NULL初始化指针时，实际上是给指针赋值一个0，为什么呢？因为在C++中万能指针不能自动转换为其他类型指针，所以只能出此下策！

因为在C++中`NULL`被定义为0，所以在某些场景下会出现一些问题！

```cpp
#include<iostream>
using namespace std;

void func(int x)
{
	cout << __FUNCSIG__<< endl;
}

void func(char* px)
{
	cout << __FUNCSIG__ << endl;
}

int main()
{
    //都调用的整数版本的func函数
	func(2);			//void __cdecl func(int)
	func(NULL);			//void __cdecl func(int)

	return 0;
}
```

从运行结果来看，无论是数字还是NULL都是调用的，参数为int类型的函数，这是毋庸置疑的，C++中NULL就是0。

但是这个结果更本不符合语义，我们传NULL，肯定是想传一个空指针进去的，而不是作为一个整数0，为此C++11引入了新的空指针关键字。

下面我们来修改一下上面的程序，将 NULL 替换为 nullptr，修改后如下所示：

```cpp
int main()
{
	func(2);			//void __cdecl func(int)
	func(nullptr);		//void __cdecl func(char *)

	return 0;
}
```

修改之后，运行结果正常！

看到这里你应该明白为什么 C++11 引入 nullptr 了吧！就是因为 NULL 在 C++ 程序中容易引起歧义！

### 常量

#### 运行时常量

运行时常量是指在程序运行时，无法直接修改的常量，但是能通过指针间接去修改！

```cpp
    int N = 10;
    const int num = N;
	int* pt = (int*)&num;
	*pt = 19;
	std::cout << num << " " << *pt << std::endl;		//output:19 19
```

在上面代码中，我们使用一个变量来初始化一个常量，这样常量`num`就是一个运行时常量：

```cpp
    int N = 10;
    const int num = N;
```

然后使用一个指针`pt`指向num常量，通过指针修改之后，输出num和`*pt`都是19了！也就是说运行时常量，确实能通过指针间接修改！

const 还可以修饰函数参数，函数返回值，函数本身，类等。在不同的条件下，const有不同的意义，大多数情况const描述的都是”运行时常量概念“，既具有运行时数据不可更改性。

#### 编译时常量

**编译期常量**是指在编译阶段即可确定其值的常量。这种常量能够提升程序性能，因为它们允许编译器在编译时进行优化（在编译时可能会直接被替换，相当于内联），而无需在运行时计算。

```cpp
    const int num = 10;
	int* pt = (int*)&num;
	*pt = 19;
	std::cout << num << " " << *pt << std::endl;		//output:18 19
```

还是上面的代码，只不过，我们直接给常量初始化一个字面量，这样num就是编译时常量了！

大家会发现结果为`18 19`，为什么呢？因为编译器在编译时，发现num是一个编译时常量，就会自动的将使用num的地方都替换为10了！所以无论如何，输出num都将是18。

至于`*pt`为什么能存储19，那是因为编译器自动在栈区定义了一个变量，并将pt指向了这块内存！！！

**constexpr**

但是使用const可能无法很直观的看出是不是编译时常量，所以C++引入了另外一个关键字`constexpr`既常量表达式(const expression)。用来取代const来定义编译时常量！

```cpp
constexpr int WEEK_DAY_COUNT = 7;	//编译时常量

constexpr int GetWeekDayCount(){	//编译时函数
    return WEEK_DAY_COUNT;
}
```

#### const字符指针

在C++中const修饰的指针，不能直接赋值给没有const修饰的指针，需要强制类型转换，或者把被赋值的指针也声明为const

```cpp
char* name = "maye";		//错误
const char*name ="maye";	//正确
```

+ 函数参数为字符指针的时候需要特别注意

```cpp
void show(char* name)
{
	cout << name << endl;
}
void test()
{
	show("maye");	//"const char *" 类型的实参与 "char *" 类型的形参不兼容
	//void show(const char* name)	//请把函数原型里的参数加上const
}
```

### if/switch 初始化子句

在C++17中，`if/switch`语句支持在条件判断前直接初始化变量。这种特性使代码更加简洁，并将变量的作用域限制在`if/switch`语句块内。

先来定义一个函数

```cpp
int getValue(int i)
{
	return i * 2;
}
```

#### if中的初始化子句

在以前，如果我们要判断函数返回值，必须先定义变量获取返回值，然后做判断！

```cpp
void test(){
	//C++ 17以前，if中只能放逻辑判断condition：if (condition)，这样写a的作用域在整个main函数中，这个作用域就比较大
	int a = getValue(2);
	if (a > 3){
		std::cout << "a " << a << " greater 3" << std::endl;
	}
	else{
		std::cout << "a " << a << " lessEqual 3" << std::endl;
	}
	
	//int a = 4;//重定义了
}
```

现在有了初始化子句，就可以很方便的使用了。

```cpp
void test_if_17()
{
	//C++ 17之后，if中可以直接初始化变量，并进行逻辑判断condition，语法：if (initializer; condition)
	//这样写a的作用域在只在 if/else 控制结构中，这个作用域就精确的控制到 if/else 控制结构中，超出这个作用域就不能在使用 a 了。
	if (int v = getValue(4); v > 3){
		std::cout << "v " << v << " greater 3" << std::endl;
	}
	else{
		std::cout << "v " << v << " lessEqual 3" << std::endl;
	}
	int v = 0;	//没问题，if中的v只在if语句作用范围内
}
```

特性说明

1. **作用域限制**：在*if*语句中初始化的变量，其作用域仅限于该语句及其附属的*else*块。
2. **简化代码**：无需在*if*语句外部定义变量，减少命名冲突的可能性。

#### switch中的初始化子句

在switch中可以直接定义变量，无需在之前定义。

```cpp
void ff()
{
    switch (int n = getValue(4))
    {
    case 1:
        std::cout << "11" << std::endl;
        break;
    case 4:
		std::cout << "77" << " " << n << std::endl;
        break;
    default:
        break;
    }
}
```

简单来说就是该新特性可以将变量的作用域控制在 if/else 或者switch 控制结构内中，精细的控制变量的作用域，使代码看起来更加紧凑，将代码行数减少，并且使代码更加直观和易于理解，同时还解决了变量命名问题。

### 变量的初始化

在C++中变量的初始化，又有了奇葩的操作(极度猥琐)

#### 1，背景

 在C++语言中，**初始化**与**赋值**并不是同一个概念：

  **初始化**：**创建变量时**赋予其一个初始值。

  **赋值**：把对象（已经创建）的**当前值**擦除，而用一个**新值**来代替。

#### 2，列表初始化

作为C++11新标准的一部分，用**花括号**来初始化变量得到了全面应用（在此之前，只是在初始化数组的时候用到）。列表初始化有两种形式，如下所示：

```cpp
int a = 0;			//常规
int a = { 0 };		
int a{ 0 };
```

说明：上述的两种方式都可以将变量a初始化为0。

**2.1 局限**

当对**内置类型**使用**列表初始化**时，若**初始值存在丢失的风险**，编译将报错，如：

```cpp
int a = 3.14;	//正确，编译器会警告		“初始化”: 从“double”转换到“int”，可能丢失数据
int a = {3.14};	//错误，编译器会报错		从“double”转换到“int”需要收缩转换
```

#### 3，直接初始化

如果在新创建的变量右侧使用括号将初始值括住（不用等号），也可以达到初始化效果

```cpp
int a(20);
```

``其他实例：``

```cpp
const char* name("maye");
char sex[3]("男");

const char* name{ "maye" };
char sex[3]{"男"};

cout << name << " "<<sex << endl;

char id[5]{ 1,2,3,4,5 };	//正确
char id[5](1,2,3,4,5);		//错误
```

### 动态内存分配

在软件开发过程中，常常需要动态地分配和释放内存空间，例如对动态链表中结点的插入与删除。在C语言中是利用库函数malloc和free来分配和释放内存空间的。C++提供了较简便而功能较强的运算符new和delete来取代malloc和free函数。

**malloc**的职责仅仅是分配内存，**new**除了分配内存外，还干一件事，调用构造函数。

**free**的职责仅仅是释放内存，**delete**除了释放内存之外，还干一件事，调用析构函数。

#### 申请对象

```cpp
Type* pointer = new Type;
//...
delete pointer;
```

**示例：**

```cpp
int* p = new int;
cout<<*p<<endl;	
delete p;
```

以上代码输出`-842150451`，据此可以知道，new是不会自动初始化内存的，那么我们可以在new的时候，指定初始值，简单方便！

```cpp
int *p = new int(18);
```

#### 申请对象数组:

```cpp
Type* pointer = new Type[N];
//...
delete[] pointer;	//数组的释放必须加上[]
```

**示例：**

```cpp
int* parr = new int[5];
for (int i = 0; i < 5; i++){
	cout << parr[i] << " ";
}
delete[] parr;
```

`output：-842150451 -842150451 -842150451 -842150451 -842150451`输出时垃圾值，同样的，也可以在new的时候初始化！

```cpp
int* parr = new int[5]{0};
```

#### 定位放置

一般来说，使用new申请空间时，是从系统的“堆”（heap）中分配空间。申请所得的空间的位置时根据当时的内存的实际使用情况决定的。但是，在某些特殊情况下，可能需要在程序员指定的特定内存创建对象，这就是所谓的“定位放置new”（placement new）操作。

定位放置new操作的语法形式不同于普通的new操作。例如，一般都用如下语句A* p=new A;申请空间，而定位放置new操作则使用如下语句A* p=new (ptr) A;申请空间，其中ptr就是程序员指定的内存首地址。

```cpp
Type* pointer = new(ptr) Type;
//根据情况是否释放内存
```

**示例：**

```cpp
int a = 123;
int* p = new(&a) int;
cout << a << " " << *p << endl;	//123 123
```

通过定位放置new，把对象a所在的空间首地址，返回了回来，所以输出的值也是123。在这里不需要释放内存哦！

**小结：**

+ new 和 malloc不要混用
+ 分配内存使用完，记得释放内存(数组和普通变量释放有些微区别)



## 内容扩充

### 条件表达式

`?:` **条件运算符**（又称三目运算符）是一种简洁替代 *if-else* 的写法，用于根据条件返回不同的值。

来一个案例，体会条件运算符在C/C++中的不同：

```c
void test(){
	int a = 2;
	int b = 3;

	//取值
	int max = (a > b ? a : b);	//获取a,b中最大的值					C √  C++ √

	//赋值
	(a > b ? a : b) = 66;		//把a,b中最大的那个变量，赋值为66	    C ×	C++ √
}
```

通过代码测试发现，无论是在C语言还是C++中，条件表达式都可以作为一个右值，赋值给其他变量；

**但是**，C语言中的条件表达式不能作为左值，即不能被赋值，而在C++中却是可以的，为什么呢？

因为，在C语言中，条件表达式的结果是一个值（纯右值），而不是变量本身；但是在C++中，如果两个操作数都是相同类型的左值，那么结果也是左值，其实就是变量本身。

**思考：**既然说C++中返回的是变量的本身，俺么在C语言中如何模拟呢？

```cpp
*(a > b ? &a : &b) = 520;
```

可以在条件表达式中返回变量的地址，返回之后解引用，即可达到和C++中一样的效果，那么说明C++中是自动帮我们做了这件事情的，绝绝子！



### 引用

#### 什么是引用？

引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称来操作变量。对引用的操作与对其所绑定的变量或对象的操作完全等价。

```cpp
Type &refName = variable_name;
```

#### 创建引用

先来定义一个变量。

```cpp
int i = 18;
```

再为变量i声明一个引用。

```cpp
int& r = i;
```

在这些声明中，& 读作**引用**。因此，第一个声明可以读作 "r 是一个初始化为 i 的整型引用";

```cpp
cout<<i<<" "<<r<<endl;
```

i和r的值都为18，因为他们两个其实都是同一块内存空间的名字。

```cpp
r = 20;
1cout<<i<<" "<<r<<endl;
```

当通过引用修改了值之后，i的值也会发生变化，都输出20。



#### 注意事项

+ 引用必须初始化

```cpp
int& refa;		//错误 没有初始化
int a = 8;
int& refa = a;	//正确 
```

+ 一旦引用被初始化为一个对象，就不能被指向到另一个对象

```cpp
int a = 8,b = 9;
int& refa = a;
refa = b;		//只是把b的值赋值给了refa，而不是让refa引用b
```

+ 如果要引用右值，那么必须使用常量引用

```cpp
int& refc = 12;		//错误 “初始化”: 无法从“int”转换为“int &”，非常量引用的初始值必须为左值
const int&refc =12;	//正确 
```

+ 当然，也可以使用右值引用来引用常量；或者使用std::move()把左值转成右值

  + 引用右值

    ```cpp
    int&& refr = 21;
    ```

  + 引用经过std::move()转换过的变量

    ```cpp
    int a = 123;
    int&& refr = 21;
    ```

  **常引用和右值引用有什么区别呢？**

  1，常引用引用的值是不可以修改的；但是右值引用引用的值是可以修改的！(大多数情况用常引用：函数参数)

  2，右值引用一般用来实现移动语义（资源权限的转移）

+ 通过使用引用来替代指针，会使 C++ 程序更容易阅读和维护

#### 引用的用处

+ 作为函数参数

```cpp
//在函数内部改变实参的值需要传变量的地址
void fun(int* n)
{
	*n=18
}
//指针是非常危险的，因为指针所指向的内存空间，不确定，需要额外判断
fun(nullptr);	//传nullptr 会发生中断，当然，你可以在函数里面判断是否是空，但是如果是野指针呢？

//在C++中，除了使用指针外，还可以通过引用来达到这个目的
void fun(int& n)
{
	n=18
}
//可以用指针的引用替代二级指针
```

+ 作为函数返回值

```cpp
int& getAge()
{
	int age = 18;
	return age;		//注意：不要返回局部变量的引用或地址，可以使用静态变量或全局变量替代
}
int& refAge = getAge();
refAge = 23;
```

#### 引用的本质

引用如此神奇，那么引用的本质到底是什么呢？

+ 引用在C++中，内部实现是一个常指针：type &name <==> type*const name
+ C++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同。
+ 从使用的角度，引用会让人误会其只是一个别名，没有自己的存储空间。这是C++为了实用性而做出的细节隐藏(所以我们查看不了引用的地址)

### auto自动类型推导

在C++11中，`auto`关键字被重新定义为类型占位符，用于在编译期间自动推导变量的类型。这种特性使代码更加简洁，减少了手动指定类型的繁琐操作。

> auto 仅仅是一个占位符，在编译器期间它会被真正的类型所替代。或者说，C++ 中的变量必须是有明确类型的，只是这个类型是由编译器自己推导出来的。

基本语法如下：

```css
auto 变量名 = 初始值;
```

#### 基本类型推导

对于基本类型的推导是最常用的，也是最简单的。

```cpp
auto n = 10;							//n被推导为int
auto f = 3.14;							//f被推导为double
auto url = "https://www.baidu.com";		//url被推导为const char*
```

变量必须在声明时初始化，因为*auto*需要通过初始值推导类型。

#### 指针、引用推导

*auto*可以与指针、引用、*const*等修饰符结合使用：

```cpp
auto p = &n;		//p被推导为int*
auto* pf = &f;		//pf被推导为double*

auto& refn = n;		//refn被推导为int&
const auto m = f;	//m被推导为const double
```

#### 推导函数参数、返回类型

```cpp
auto sub(const auto& a, auto b) {
	return a + b;
}

auto ret = sub(1, 3);	//ret被推导为int
```

> 不能定义数组，例如*auto arr[] = {1, 2, 3};*是非法的。

通过*auto*，C++代码可以更简洁、更易维护，尤其在复杂类型和泛型编程中具有显著优势。

### 范围for循环

在C++11中，引入了**范围for循环**（range-based for loop），它提供了一种更简洁和统一的方式来遍历容器和数组。这种循环结构不需要明确指定开始和结束的迭代器，而是直接在容器或数组上进行迭代。

基于范围的for循环语法如下：

```css
for(type var : range){
    var;
}
```

for循环由冒号`:`分为两部分：第一部分是范围内用于**迭代的变量**，第二部分则表示被迭代的**范围**。

有如下数组：

```cpp
int arr[] = {1,2,3,4,5,6,7};
```

在以前我们需要手动指定数组长度，才能遍历整个数组：

```cpp
for(int i = 0;i < sizeof(arr) / sizeof(arr[0]); i++){
    std::cout << arr[i] << " ";
}
```

这种方法，倒也不难，但是所有的数组都是这样，所以C++就提供了基于范围的for循环，能自动处理数组的边界，能遍历整个数组范围内的元素：

```cpp
for(int i : arr){
     std::cout << i << " ";
}
```

当需要修改容器中的元素或避免不必要的拷贝时，可以使用引用。

```cpp
for(auto& i : arr){
    i*=2;
}
```

如果不需要修改元素，可以使用*const*关键字来确保元素的值不会被改变。

```cpp
for(const auto& i : arr){
    i*=2;
}
```

当遍历大型容器或复杂对象时，使用引用可以提高性能，因为它避免了对象的拷贝。同时，使用*auto*关键字可以让编译器自动推断元素的类型，简化代码并可能提高性能。

总结来说，C++11的范围for循环使得代码更加简洁易读，并且通过使用引用和*auto*关键字，还能提升性能。

### 结构化绑定(C++17)

**结构化绑（Structured binding）定**是C++17引入的一项新特性，它允许以一种更加简洁和直观的方式从复合类型中提取成员变量，并将它们绑定到命名变量上。这种特性极大地提高了代码的可读性和简洁性。

结构化绑定的语法非常直观，它使用方括号 *[]* 来列出需要绑定的变量名。这些变量将按照它们在方括号中出现的顺序与聚合类型的元素进行匹配。

#### 解包数组

对于数据比较小的数组，比如用来保存坐标、大小的数组，可以直接使用结构化绑定来获取值：

```cpp
int point[] = { 13,45 };
auto [x, y] = point;
std::cout<< x << " " << y << std::endl;	//13 45
```

这样就可以直接使用x,y变量来访问数组中的数据了，当然不能通过x，y修改数组数据，要想修改可以使用引用：

```cpp
auto& [x, y] = point;
x = 10;
y = 50;
std::cout << point[0] << " " << point[1] << std::endl;
```

#### 解包结构体

先定义一个结构体：

```cpp
struct User {
	int id;
	char name[32];
	bool isActive;
};
```

解包结构体：

```cpp
User user{ 1, "zhangsan", true };
auto [id, name, isActive] = user;
std::cout<< id << " " << name << " " << isActive << std::endl;
```

结构体解包后，使用就很方便了，不用通过结构体变量去访问成员了，还可以**解包结构体数组**：

```cpp
User users[] = { {1, "zhangsan", true}, {2, "lisi", false} };
for (auto& [id, name, isActive] : users) {
	std::cout<< id << " " << name << " " << isActive << std::endl;
}
```

#### 解包函数返回值

众所周知，函数只能返回一个值，那么想返回多个值怎么办呢？答案是使用结构体包装多个值：

```cpp
struct HPair {
	int first;
	int second;
};

HPair GetInfo() {
	return HPair{1,4};
}
```

调用函数并解包返回值：

```cpp
const auto& [first, second] = GetInfo();
std::cout << first << " " << second << std::endl;
```



### 类型信息

在 C++ 中，**类型信息**是描述数据类型及其属性的重要工具，尤其在运行时类型识别（RTTI）中起到关键作用。C++ 提供了 *typeid* 运算符和 *type_info* 类来获取类型信息，这在多态和类型安全的代码中非常有用。

#### typeid 运算符

*typeid* 是 C++ 中用于获取类型信息的运算符。它可以作用于对象或类型，返回一个 *std::type_info* 对象，包含该类型的相关信息。

```cpp
//获取一个普通变量的类型信息
int n = 100;
const type_info& nInfo = typeid(n);
cout << nInfo.name() << " | " << nInfo.raw_name() << " | " << nInfo.hash_code() << endl;

//获取一个字面量的类型信息
const type_info& dInfo = typeid(25.65);
cout << dInfo.name() << " | " << dInfo.raw_name() << " | " << dInfo.hash_code() << endl;

//获取一个普通类型的类型信息
const type_info& charInfo = typeid(char);
cout << charInfo.name() << " | " << charInfo.raw_name() << " | " << charInfo.hash_code() << endl;
	
//获取一个表达式的类型信息
const type_info& expInfo = typeid(20 * 45 / 4.5);
cout << expInfo.name() << " | " << expInfo.raw_name() << " | " << expInfo.hash_code() << endl;
```

**输出结果**可能因编译器而异，例如：

```css
int | .H | 12638232278978672507
double | .N | 12638230079955414429
char | .D | 12638219084838855839
double | .N | 12638230079955414429
```

#### type_info 类

*type_info* 是 *typeid* 返回的类型信息类，提供以下常用方法：

- *name()*：返回类型名称。
- *operator==* 和 *operator!=*：比较两个类型是否相同。
- *before()*：判断两个类型的排列顺序（与继承无关）。

如有以下定义：

```cpp
char *str;
int a = 2;
int b = 10;
float f;
```

类型判断结果为：

| 类型比较                      | 结果  | 类型比较                     | 结果  |
| ----------------------------- | ----- | ---------------------------- | ----- |
| typeid(int) == typeid(int)    | true  | typeid(int) == typeid(char)  | false |
| typeid(char*) == typeid(char) | false | typeid(str) == typeid(char*) | true  |
| typeid(a) == typeid(int)      | true  | typeid(b) == typeid(int)     | true  |
| typeid(a) == typeid(a)        | true  | typeid(a) == typeid(b)       | true  |
| typeid(a) == typeid(f)        | false | typeid(a/b) == typeid(int)   | true  |

### 枚举类型

C语言和C++语言都提供了枚举类型，两者是有一定区别。

``有如下定义：``

```cpp
enum SHAPE {CIRCLE,RECT,LINE,POINT};
enum WEEK  {MON,TUE,WED,THI,FIR,SAT,SUN};
```

#### 1，C语言中的enum

+ 允许非枚举值赋值给枚举类型，允许其他枚举类型的值赋值给另一个枚举类型

  enum WEEK today = 3;	//正确
  today = CIRCLE;			//正确

+ 枚举具有外层作用域，容易造成名字冲突``(在不同作用域不会冲突，但是遵循就近原则，访问不到外层作用域的枚举)``

```c++
enum OTHER { RECT };//error C2365: “RECT”: 重定义；以前的定义是“枚举数”
int RECT = 12;		//同上
```

+ 不同类型的枚举值可以直接比较

```cpp
if (CIRCLE == MON)
{
	printf("oh.yes");
}
```

#### 2，C++中的enum

+ 只允许赋值枚举值

```c
enum WEEK today = 3;	//错误	error C2440: “初始化”: 无法从“int”转换为“main::WEEK”
today = CIRCLE;			//错误	error C2440: “=”: 无法从“main::SHAPE”转换为“main::WEEK”
```

+ 枚举元素会暴露在外部作用域，不同两个枚举类型，若含有相同枚举元素，则会冲突

```cpp
enum OTHER { RECT };	//错误 	error C2365: “RECT”: 重定义；以前的定义是“枚举数”
int RECT = 12;			//错误同上	但是可以通过枚举名访问指定的枚举属性
OTHER::RECT;			//正确
```

+ 不同类型的枚举也可以直接比较

```cpp
if (CIRCLE == MON)
{
	cout<<"oh.yes";
}
```

#### 3,C++中的 enum class 强枚举类型

```cpp
enum class SHAPE {CIRCLE,RECT,LINE,POINT};
enum class WEEK  {MON,TUE,WED,THI,FIR,SAT,SUN};
```

+ 强枚举类型不会将枚举元素暴露在外部作用域，必须通过枚举名去访问

```cpp
cout<<SHAPCE::RECT<<endl;	//输出 1 
```

+ 不相关的两个枚举类型不能直接比较，编译报错

```cpp
if (SHAPE::CIRCLE == WEEK::MON)	//error C2676: 二进制“==”:“main::SHAPE”不定义该运算符或到预定义运算符可接收的类型的转换
{
	cout<<"oh.yes";
}
```

#### **小结**

+ C 枚举类型支持不同类型枚举值之间赋值、以及数字赋值、比较，并且具有外层作用域。

+ C++ 中枚举不允许不同类型的值给枚举类型变量赋值，但仍然支持不同类型之间枚举进行比较，枚举符号常量具有外层作用域。

+ C++ 强枚举类型不允许不同类型之间的赋值、比较，枚举常量值并不具有外层作用域。

### 函数

#### 内联函数

内联函数在C++中是一种常用的优化技术，它可以减少函数调用时的开销。当一个函数被声明为内联时，编译器会尝试将函数的代码直接插入到每个调用点，从而避免了函数调用的成本。内联函数通常用于小型、频繁调用的函数。

##### 内联函数定义与特点

内联函数通过在函数定义前加上*inline*关键字来声明。例如，一个简单的内联函数，用于比较两个整数并返回较大值，可以这样定义：

```cpp
inline int Max(int x, int y) {
   return (x > y) ? x : y;
}
```

内联函数的主要特点包括：

- **减少调用开销**：内联函数可以减少函数调用的时间成本，尤其是在函数体较小且调用频繁的情况下。
- **编译器优化**：内联是一种编译时优化，编译器有权决定是否真正将函数内联。即使函数被声明为内联，也不一定会被编译器内联展开。
- **代码膨胀问题**：过度使用内联可能会导致代码膨胀，增加程序的大小。因此，建议只对小型函数使用内联。
- **类成员函数**：在类定义中直接定义的成员函数默认是内联的，即使没有显式使用*inline*关键字。

##### 注意事项

在使用内联函数时，需要注意以下几点：

1. **避免内联大型函数**：不建议内联超过10行代码的函数，因为这可能会导致代码膨胀，反而降低程序性能。
2. **限制内联的使用场景**：不应该内联包含循环、递归或*switch*语句的函数，因为这可能不会带来性能提升。
3. **内联函数的定义位置**：内联函数的定义需要在调用之前或者在同一个文件中，通常放在头文件中以便于在多个源文件之间共享。

#### 函数默认参数

在C++中，定义函数时可以为形参指定一个默认值，这样在调用函数时，如果没有为该形参提供实参，就会使用这个默认值。这使得函数调用更加灵活和简洁。

##### 基本使用

```cpp
#include <iostream>
using namespace std;
// 带默认参数的函数
void func(int n, float b = 1.2, char c = '@') {
   cout << n << ", " << b << ", " << c << endl;
}
int main() {
   // 为所有参数传值
   func(10, 3.5, '#');
   // 为n、b传值，相当于调用func(20, 9.8, '@')
   func(20, 9.8);
   // 只为n传值，相当于调用func(30, 1.2, '@')
   func(30);
   return 0;
}
```

##### 默认参数规则

- **默认参数的位置**：默认参数必须从右向左依次指定。例如：

```cpp
int foo(int a, int b = 2, int c = 3);     // 正确
int foo1(int a, int b = 2, int c);         // 错误, i3未指定默认值
int foo2(int a = 1, int b, int c = 3);     // 错误, i2未指定默认值
```

+ **声明和定义中的默认参数**：默认参数不能在声明和定义中同时出现。例如：

```cpp
int add(int a,int b = 5);	//声明
int add(int a,int b){		//定义
    return a+b;
}
```

通过使用默认参数，可以在设计类时减少析构函数、方法以及方法重载的数量，从而提高代码的可维护性。

总之，C++中的默认参数提供了一种便捷的方式，使函数调用更加灵活，同时也减少了代码的复杂性和冗余。

#### 占位参数

在C++中，占位参数是一种特殊的函数参数，它们在函数声明中占据一个位置，但并不在函数体内使用。占位参数的存在主要是为了与C语言的兼容性以及为将来可能的函数扩展留下空间。

##### 基本使用

占位参数在声明时只指定了类型，而没有指定参数名。在调用函数时，即使占位参数在函数体内不会被使用，调用者也必须为其提供实参。这是因为占位参数仍然是函数签名的一部分。例如：

```cpp
void func(int a,int){
    cout << a << endl;
}
func(2,3);
```

##### 占位参数与默认参数的结合

占位参数可以与默认参数结合使用。这样做的好处是，可以不为占位参数提供实参，而是使用默认值。这种方式可以减少调用时的参数数量，同时保留了为将来扩展功能的能力。例如：

```cpp
// 声明一个带有占位参数和默认参数的函数
void func(int a, int b, int = 0) {
   return a + b;
}
// 调用函数时可以不提供占位参数的实参
int main() {
   func(1, 2); // 第三个参数使用默认值0
   return 0;
}
```

占位参数在C++中的使用虽然不常见，但它们提供了一种机制，用于在不影响现有函数调用的情况下，为将来可能的修改或扩展保留空间。此外，它们也有助于维持与C语言代码的兼容性。在实际开发中，应谨慎使用占位参数，确保它们的存在有明确的目的和合理的用途。

#### 函数重载

在C++中，函数重载是一种允许在同一作用域中存在多个同名函数的特性，但这些函数的参数列表必须不同。这意味着，函数可以有相同的名称，只要它们的**参数类型**或**参数数量**不同。这使得开发者能够为相似的操作提供统一的接口，同时也提高了代码的可读性和易用性。

##### 函数重载工作原理

当声明或定义一个重载函数时，编译器会通过参数列表来解决命名冲突。例如，如果有两个名为 *print* 的函数，一个接受 *int* 类型参数，另一个接受 *string* 类型参数，编译器会根据参数类型来区分这两个函数。在调用重载函数时，编译器会根据传递的参数类型来决定调用哪个函数版本。

```cpp
#include <iostream>
using namespace std;
void print(int i) {
   cout << "整数为: " << i << endl;
}
void print(double f) {
   cout << "浮点数为: " << f << endl;
}
void print(char c[]) {
   cout << "字符串为: " << c << endl;
}
int main(void) {
   print(5); // 调用 print(int)
   print(500.263); // 调用 print(double)
   char c[] = "Hello C++";
   print(c); // 调用 print(char[])
   return 0;
}
```

编译器在进行重载决策时，会考虑以下几个因素：

- **精确匹配**：编译器首先寻找完全匹配调用参数类型的函数。
- **提升匹配**：如果没有精确匹配，编译器会尝试通过类型提升来找到匹配的函数。
- **标准转换匹配**：如果提升匹配不成功，编译器会尝试标准类型转换。
- **用户自定义类型匹配**：如果以上都不成功，编译器会尝试用户自定义的类型转换。

##### 重载函数的限制

尽管函数重载提供了很大的灵活性，但也有一些限制。例如，不能仅通过返回类型的不同来重载函数。此外，如果两个函数的参数只是在是否为 *const* 或 *volatile* 上有所不同，那么它们也不能被视为重载函数。

```cpp
void foo(int a)
{
	std::cout<< "int" << std::endl;
}
void foo(const int b) {
	std::cout << "const int" << std::endl;
}

foo(1);	//error C2668: “foo”: 对重载函数的调用不明确，可能是“void foo(const int &)”或 “void foo(int)”
```

##### 函数重载结合默认参数

在给重载函数指定默认参数时，要考虑是否会和别的重载函数冲突

```cpp
void fun(int a)
{
	cout << "fun(int a) " << a << endl;
}
void fun(int a, int b = 8)
{
	cout << "fun(int,int =8) " << a <<" "<< b << endl;
}
int main()
{
	//fun(5);	//error C2668: “fun”: 对重载函数的调用不明确
	fun(5, 6);//正确
	return 0;
}
```

函数重载是C++中一个强大的特性，它允许开发者为不同的数据类型提供相同的函数名。这不仅使得代码更加清晰，也使得函数的使用更加直观。然而，开发者需要注意重载函数的规则和限制，以避免可能的二义性和编译错误。

## 字符串

### std::string类

在 C++ 中，*std::string* 是对 C 风格字符串的封装，提供了丰富且安全的字符串处理方法，包括初始化、拼接、查找、替换等。

#### 构造字符串

`std::string` 可以通过多种方式初始化：

```cpp
void test_string()
{
	//构造字符串
	std::string str;					//空字符串
	std::string str1 = "hello hdy";		//初始化
	std::string str2("hello hdy");		//圆括号初始化
	std::string str3{ "hello hdy" };	//花括号初始化
	std::string str4(15, 'A');			//初始化为15个'A'
	auto str5 = std::string("hello hdy");	//拷贝初始化
	std::cout << str1 << "\n" << str2 << "\n" << str3 << "\n" << str4<<"\n"<<str5 << std::endl;

	//拷贝
	std::string str6 = str1;			//拷贝构造
	//移动
	std::string str7 = std::move(str6);	//移动构造
	std::cout << "str6:" << str6 << "str7:" << str7 << std::endl;
}
```

#### 获取数据

```cpp
void f()
{
    std::string str = "hello hdy";
	//获取数据
	// -- 1.获取字符串长度
	std::cout << "str size:" << str.size() << " | " << str.length() << std::endl;
	// -- 2.获取C风格字符串
	std::cout << "str c str:" << str.c_str() << " | " << str.data() << std::endl;
	// -- 3.获取指定位置的字符
	std::cout << "str[0]:" << str[0] << " | " << str.at(0) << std::endl;
	// -- 4.获取子串
	std::cout << "substr:" << str.substr() << " | " << str.substr(6, 3) << std::endl;
}
```

#### 清空/判空/判断开始和结尾

```cpp
void f()
{
    // -- 5.清空字符串
	str.clear();
	// -- 6.判断字符串是否为空
	if(str.empty())
		std::cout << "str is empty" << std::endl;
	else
		std::cout << "str is not empty" << std::endl;
	// -- 7.判断字符串是否以指定字符串开头或结尾
	str = "hello hdy";
	if(str.starts_with("hello"))
		std::cout << "str starts with hello" << std::endl;
	if(str.ends_with("hdy"))
		std::cout << "str ends with hdy" << std::endl;
}
```

#### 字符串操作

##### 比较

```cpp
void f(){
	std::string str1 = "maye";
	std::string str2 = "maye";
	//使用运算符直接比较，支持(==, !=, >, <, >=, <=)
	if(str1 == str2)
		std::cout << "str1 == str2" << std::endl;
	else if(str1 > str2)
		std::cout << "str1 > str2" << std::endl;
	else if(str1 < str2)
		std::cout << "str1 < str2" << std::endl;
    
	//使用函数进行比较
	auto ret = str1.compare(str2);	
	if(ret == 0)
		std::cout << "str1 == str2" << std::endl;
	else if(ret > 0)
		std::cout << "str1 > str2" << std::endl;
	else
		std::cout << "str1 < str2" << std::endl;
    
	//使用三路比较运算符 <=> 返回值：0，1，-1
	if (auto ret = (str1 <=> str2); ret == 0) {
		std::cout << "str1 == str2" << std::endl;
	}
	else if (ret  < 0) {
		std::cout << "str1 < str2" << std::endl;
	}
	else if (ret > 0) {
		std::cout << "str1 > str2" << std::endl;
	}
}
```

##### 查找

```cpp
{
	std::string str = "I'm maye,and you?";
	//-- 1.查找指定字符,find正向查找,rfind反向查找
	if (auto idx = str.find(' '); idx != std::string::npos) {		//查找第一个空格
		std::cout << "find first space at " << idx << std::endl;
		//str[idx] = '_';	//可以通过idx修改指定位置的字符
	}
	else {
		std::cout << "not find space" << std::endl;
	}
    
	//-- 2.查找
	if (auto idx = str.find_first_of("aeiou");idx != std::string::npos) {		//查找第一个元音字母
		std::cout << "find first vowel at " << idx << std::endl;
	}
	else {
		std::cout << "not find vowel" << std::endl;
	}
	if (auto idx = str.find_first_not_of("aeiou");idx != std::string::npos){	//查找第一个非元音字母
		std::cout << "find first non-vowel at " << idx << std::endl;
	}
	else {
		std::cout << "not find non-vowel" << std::endl;
	}
}
```

##### 替换

```cpp
{
	std::string str = "I'm maye,and you?";
    
	str.replace(1, 2, " am");				//替换前两个字符
	std::cout << "str:" << str << std::endl;//I am maye,and you?
    
	str.replace(str.find("you"), 3, "you are");	//替换you
	std::cout << "str:" << str << std::endl;//I am maye,and you are?
    
	str.replace(5, 4, 2, 'A');					//将maye替换为AA
	std::cout << "str:" << str << std::endl;//I am AA,and you are?
}
```

##### 插入

```cpp
{
	std::string str = "I'm maye,and you?";
	str.insert(4, "hdy ");					//在指定位置插入字符串
	std::cout<< "str:" << str << std::endl;	//I'm hdy maye,and you?
    
	str.insert(str.find("and"), 1, ' ');	//在指定位置插入字符
	std::cout<< "str:" << str << std::endl;	//I'm hdy maye, and you?
    
	str.insert(0, "hi!I'm jerry!", 0, 3);		//在指定位置插入字符串的子串
	std::cout<< "str:" << str << std::endl;	//hiI'm hdy maye, and you?
}
```

##### 删除

```cpp
{
	std::string str = "I'm hdy maye,and you?";
    
	str.erase(4, 4);				//删除指定位置的字符串
	std::cout<< "str:" << str << std::endl;	//I'm maye,and you?
    
	str.erase(str.find("and"), 3);	//删除指定位置的字符串
	std::cout<< "str:" << str << std::endl;	//I'm maye, you?
    
	str.erase();					//清空字符串
	std::cout << "str:" << str << std::endl;	//(null) 
}
```

##### 字符串连接

```cpp
{
	std::string str;
    
	str.push_back('h');						//在字符串末尾插入字符
	str.append("ello");						//在字符串末尾插入字符串
	str.append(" hdy is my company", 4);	//在字符串末尾插入字符串的子串
	std::cout<< "str:" << str << std::endl;	//hello hdy
	str += "! good!";						//使用运算符字符串连接
	std::cout<< "str:" << str << std::endl;	//str:hello hdy! good!
    
	str.assign("nice!");					//赋值字符串,会清空原字符串
	std::cout<< "str:" << str << std::endl;	//nice!
    
	str.pop_back();							//删除字符串末尾的字符
	std::cout << str.front() << std::endl;	//字符串第一个字符
	std::cout << str.back() << std::endl;   //字符串最后一个字符
	std::cout<< "str:" << str << std::endl;	//nice
    
	char buf[16];
	auto len = str.copy(buf, 2, 1);			//将字符串的子串复制到buf中，不会自动添加\0，返回复制的字符个数
	buf[len] = '\0';
}
```

##### 容量/大小/交换

```cpp
	{
		std::string str(100, 'A');
		// -- 1,字符串容量
		std::cout << "capacity:" << str.capacity() << " size:" << str.size() << std::endl;
		str.clear();
		std::cout << "capacity:" << str.capacity() << " size:" << str.size() << std::endl;
		str.reserve();			//将容量调整为合适大小
		std::cout << "capacity:" << str.capacity() << " size:" << str.size() << std::endl;
		str.reserve(128);		//将容量调整为128，如果容量小于128，则调整为128，否则不变
		std::cout << "capacity:" << str.capacity() << " size:" << str.size() << std::endl;

		// -- 2，字符串大小
		std::string buf("hello wrold,who is you?");
		buf.resize(10);		//将字符串大小调整为10，如果字符串长度小于10，则多余部分填充'\0'，否则截断字符串
		std::cout << "str:" << str << std::endl;	

		// -- 3,字符串交换
		std::string str1 = "hello";
		std::string str2 = "world";
		str1.swap(str2);		//成员函数
		std::swap(str1, str2);	//标准库函数
		std::cout << "str1:" << str1 << " str2:" << str2 << std::endl;
	}
```

### std::string转换

#### other to string

```cpp
string to_string(int _Val);
string to_string(unsigned int _Val);
string to_string(long _Val);
string to_string(unsigned long _Val);
string to_string(long long _Val) ;
string to_string(unsigned long long _Val);
string to_string(double _Val);
string to_string(float _Val);
string to_string(long double _Val);
```

#### string to other

```cpp
int stoi(const string& _Str, size_t* _Idx = nullptr, int _Base = 10);
long stol(const string& _Str, size_t* _Idx = nullptr, int _Base = 10); 
unsigned long stoul(const string& _Str, size_t* _Idx = nullptr, int _Base = 10);
long long stoll(const string& _Str, size_t* _Idx = nullptr, int _Base = 10);
unsigned long long stoull(const string& _Str, size_t* _Idx = nullptr, int _Base = 10); 
float stof(const string& _Str, size_t* _Idx = nullptr); 
double stod(const string& _Str, size_t* _Idx = nullptr); 
long double stold(const string& _Str, size_t* _Idx = nullptr);
```

+ `size_t* _Idx = nullptr`此参数返回从字符串中解析数据结束的位置，比如：`stoi("123hdy",&idx)`，idx的值将是3。
+ `int _Base = 10`：此参数表示要解析的字符串中包含的整数的进制数，比如`std::stoi("0x12345678", &idx, 16)`，stoi函数将以16进制格式解析字符串。

### format(C++20)

>  `std::format` 是 C++20 中引入的一个新特性，它提供了一种类型安全且易于使用的方式来格式化字符串。这个函数在 `<format>` 头文件中定义。

#### 基础用法

+ **占位符**：使用花括号占位符进行占位，后面的值会依次对占位符进行替换。

```cpp
auto str = std::format("I'm {}, {} years old", "maye", 12);
```

> output：I'm maye, 12 years old

注意：

1. 如果占位符{}数量比值的数量多，则会抛出`std::format_error`异常！

2. 如果占位符{}数量比值的数量少，则多出的值会忽略！

+ **占位索引**：如果想要用一个值替换多个占位符，则必须使用占位索引(索引从0开始)。

```cpp
auto str = std::format("I'm {0},{0} is good {1}", "maye","teacher");
```

> output：I'm maye,maye is good teacher
>
> 注意：一旦使用了占位索引，每个占位符都必须使用占位索引，否则会抛出`std::format_error`异常

#### 类型规格与格式选项

`std::format`支持各种类型规格与格式选项，以便对输出进行详细的控制。以下是一些常见的类型规格与格式选项：

1. **整数**

- `d`：十进制整数。
- `x`：小写十六进制整数。
- `X`：大写十六进制整数。
- `o`：八进制整数。
- `b`：二进制整数。

示例：

```cpp
std::cout << std::format("{0:d} {0:x} {0:X} {0:o} {0:b}", 42) << std::endl;
```

2. **浮点数**

- `f`：固定点表示法。
- `e`：小写科学计数法。
- `E`：大写科学计数法。
- `g`：根据值选择最简表示法（`f`或`e`）。
- `G`：根据值选择最简表示法（`f`或`E`）。

示例：

```cpp
std::cout << std::format("{0:f} {0:e} {0:E} {0:g} {0:G}", 3.1415926535)<<std::endl;
```

3. **字符串**

- `s`：字符串。

示例：

```cpp
std::cout << std::format("{:s}", "Hello, World!") << std::endl;
```

4. **宽度、对齐和填充**

- `<`：左对齐。
- `>`：右对齐。
- `^`：居中对齐。
- `数字`：指定输出宽度。
- `字符`：指定填充字符。
  示例：

```cpp
std::cout << std::format("{:<10} | {:>10} | {:^10}", "left", "right", "center") << std::endl;
std::cout << std::format("{:*<10} | {:#>10} | {:_^10}", "left", "right", "center") << std::endl;;
```

5. **精度**

对于浮点数，精度用于指定小数点后的位数；对于字符串，精度用于指定最大输出长度。
示例：

```cpp
std::cout << std::format("{:.2f} | {:.3e} | {:.4s}", 3.1415926, 12345.6789, "abcdefgh") << std::endl;
```

6. **整数和浮点数的进位**

整数和浮点数的进位可以使用`#`选项，它会在八进制和十六进制数字前添加`0`或`0x`（`0X`）前缀，或在浮点数上强制输出小数点。
示例：

```cpp
std::cout << std::format("{:#x} | {:#o} | {:#f}", 42, 42, 3.14)<<std::endl;
```

7. **正负号**

使用`+`选项可以强制输出正数的正号。
示例：

```cpp
std::cout << std::format("{:+d} | {:+f}", 42, 3.14)<<std::endl;
```

8. **自定义类型**

要格式化自定义类型，需要为类型特化`std::formatter`模板，并提供`parse`和`format`成员函数。这使得`std::format`可以以一种统一的方式处理内置类型和自定义类型。
示例：

```cpp
struct Point {
    int x, y;
};

// 为 Point 定义格式化器
template <>
struct std::formatter<Point> : std::formatter<std::string> {
    auto format(const Point& p, format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("({}, {})", p.x, p.y), ctx);
    }
};

std::cout << std::format("{}", Point{3, 4})<<std::endl;
```

**std::format_to**

`std::format`格式化后返回`std::string`，如果想要格式化到指定的位置，则需要使用`std::format_to`。

```cpp
//将格式化结果写入迭代器指向的位置，返回最终位置的迭代器。
char buffer[123];
std::format_to(buffer, "{}", 123);

//最多写入 n 个字符（不包含终止符），返回包含写入信息的结构体（写入数和新位置）。
std::string buf;
std::format_to_n(std::back_inserter(buf),1, "{}", 123);
```

[C++ format函数](https://www.yisu.com/jc/902923.html)

[【C++ 格式化输出 】C++20 现代C++格式化：拥抱std--format简化你的代码-阿里云开发者社区](https://developer.aliyun.com/article/1463275)

### print(C++23)

> #include<print>

C++标准流输出std::cout一直以来为人们所诟病：不灵活，格式化支持差，冗长等等。人们有此想法源于C库的printf()函数虽然不提供类型安全保障和线程安全保障，但它非常灵活，格式化支持非常好。

为此，C++23版本引入了std::print()/std::println()函数，完全解决了流输出std::cout为人们所诟病的问题。下面我们就来看看它们。

#### 格式化打印到标准输出

```cpp
	std::print("hello world\n");		//格式化输出，不自带换行，需要手动添加
	std::println("hello world");		//格式化输出，自带换行

	std::print("I'm {},{} years old!", "maye", 18);		//格式化输出，{}占位符
	std::println();										//换行
	std::println("I'm {1} years old! {0}", "maye", 18);	//格式化输出，{}占位符，可以指定顺序
```

#### 格式化打印到流

```cpp
	//-- 1.格式化输出到文件
	FILE* fp = fopen("log.txt", "a");
	if (!fp) {
		std::cerr << "open log.txt failed!" << std::endl;
		return;
	}
	std::println(fp, "hello world");		//格式化输出到文件
	std::println(fp);						//换行

	fclose(fp);

	//-- 2.格式化输出到流
	std::print(std::cout, "--hello world");		//格式化输出到字符串
```





