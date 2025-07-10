# 宏定义C++阶段综合考察试题

1. C++ 在 C 语言的基础上引入了哪种新的编程范式？

   A、 面向过程编程

​	B、 面向对象编程

​	C、 函数式编程

​	D、 逻辑编程

​	答案：B

2. 下哪个特性是 C++ 独有而 C 语言没有的？

​	A、指针	

​	B、结构体

​	C、 引用（Reference）

​	D、 数组

​	答案：C

3. C++ 中用于处理输入输出的标准库是：

​	A、stdio.h		

​	B、iostream

​	C、fileio

​	D、console

​	答案：B

4. C++ 中的 namespace 关键字的主要作用是：

	A、定义类的作用域
	
	B、避免命名冲突
	
	C、 优化内存使用
	
	D、提高程序执行速度

​	答案：B

6. 以下哪项是 C++ 特有的内存管理方式？

​	A、 malloc/free

​	B、 new/delete

​	C、 自动垃圾回收

​	D、 内存池

​	答案：B

7. C++ 中的类与结构体最主要的区别是：

​	A、 类可以包含函数，而结构体不能

​	B、 类的成员默认是私有的，而结构体默认是公有的

​	C、 类支持继承，而结构体不支持

​	D、 类需要使用 new 创建，而结构体不需要

​	答案：B

8. 在 C++ 中，标准输入流对象是：

​	A、cout

​	B、 cin

​	C、 cerr

​	D、 clog

​	答案：B

9. 使用 C++ 标准库读取用户输入的整数，正确的写法是：

​	A、scanf("%d", &num);

​	B、 cin >> num;

​	C、 getline(cin, num);

​	D、 input(num);

​	答案：B

10. 若要输出浮点数并保留两位小数，应使用：

​	A、cout << fixed << setprecision(2) << num;

​	B、 printf("%.2f", num);

​	C、 以上两种均可

​	D、 cout << round(num, 2);

​	答案：C

11. endl 操作符的作用是：

​	A、仅换行

​	B、仅刷新输出缓冲区

​	C、换行并刷新输出缓冲区

​	D、等同于 \n

​	答案：C

12. 从标准输入读取一行字符串（包含空格），应使用：

​	A、cin >> str;

​	B、 getline(cin, str);

​	C、 scanf("%s", str);

​	D、 cin.getline(str);

​	答案：B

13. C++ 中，用于格式化输出的头文件是：

​	A、iostream

​	B、 iomanip

​	C、 stdio

​	D、 format

​	答案：B

​	解析：iomanip 库中的函数允许开发者控制输出格式，如设置小数点后的位数、设置宽度、对齐方式等； std::format是C++20引入的，提供了一种现代化、类型安全的字符串格式化方法。它基于 Python 的 *str.format()* 函数，使用花括号 *{}* 作为占位符。



14. 关于cerr和clog的区别，正确的是：

​	A、cerr 无缓冲，clog 有缓冲

​	B、cerr 输出错误信息，clog 输出日志信息

​	C、以上都对

​	D、它们完全相同

​	答案：C

​	解析：A和B答案都是正确的



15. 若要读取文件内容，需包含的头文件是：

​	A、fstream

​	B、filestream

​	C、fileio

​	D、iostream

​	答案：A

16. 以下哪种方式可以禁用输入流的缓冲？

​	A、cin.sync_with_stdio(false);

​	B、cin.setbuf(nullptr);

​	C、cin.unbuffer();

​	D、C++ 无法禁用输入缓冲

​	答案：B

​	解析：setbuf函数用于控制标准输出流的缓冲行为。通过将缓冲区设置为nullptr，可以关闭标准输出的缓冲，从而使输出立即生效。

17. 读取单个字符的正确方法是：

​	A、char c = cin.get();

​	B、 char c; cin >> c;

​	C、 以上两种均可

​	D、 char c = getch();

​	答案：C

​	解析：D答案，C/C++中都没有这个函数。

18. C++ 在 C 语言基础上新增的布尔类型是：

​	A、 bool

​	B、 boolean

​	C、 logical

​	D、 C++ 没有新增布尔类型

​	答案：A

19. 关于 C++ 中的 nullptr，正确的是：

​	A、 它是 C++11 新增的空指针字面量

​	B、 它比 C 语言的 NULL 更安全		

​	C、 它的类型是 std::nullptr_t

​	D、 以上都是

​	答案：D

20. C++ 中，auto 关键字的作用是：

​	A、 自动推导变量类型

​	B、 声明自动存储期变量（同 C 语言）

​	C、 仅用于函数返回值

​	D、 C++ 取消了 auto 关键字

​	答案：A

21. C++11 引入的 decltype 关键字用于：

​	A、 声明函数返回值类型

​	B、 在编译时推导表达式的类型

​	C、 动态类型识别

​	D、 替代 typeof 运算符

​	答案：B

22. C 语言中的 enum 在 C++ 中有哪些改进？

​	A、 作用域枚举（enum class）

​	B、 可以指定底层类型

​	C、 更严格的类型检查

​	D、 以上都是

​	答案：D

23. C++ 中，constexpr 关键字的作用是：

​	A、 声明常量表达式（编译时求值）

​	B、 替代 const 关键字

​	C、 仅用于函数参数

​	D、 提高运行时性能

​	答案：A

24. C++ 的 const 与 C 语言的 const 最主要区别是：

​	A、 C++ 的 const 必须初始化

​	B、 C++ 的 const 可以用于类成员函数

​	C、 C 语言的 const 本质是只读变量

​	D、 以上都是

​	答案：D

25. C++11 引入的右值引用（&&）主要用于：

​	A、 提高函数参数传递效率

​	B、 实现移动语义（Move Semantics）

​	C、 支持 Lambda 表达式

​	D、 替代左值引用（&）

​	答案：B

26. C++ 的内联函数（inline）与 C 语言的宏（#define）相比：

​	A、 内联函数有类型检查，宏没有

​	B、 内联函数在编译时展开，宏在预处理时展开

​	C、 内联函数更安全，不易产生副作用

​	D、 以上都是

​	答案：D

27. C++ 中，默认参数的规则是：

​	A、 只能在函数声明中指定

​	B、 必须从右向左连续指定

​	C、 不能在函数定义中重复指定

​	D、 以上都是

​	答案：D

28. 以下关于 C++ 函数默认参数的说法，正确的是：

    A、 可以在函数声明和定义中同时指定默认参数
    
    B、 默认参数必须从左到右连续指定
    
    C、 函数调用时，若未提供某个参数，则使用默认值
    
    D、 C 语言也支持函数默认参数

​	答案：C

29. 以下哪个函数声明是合法的？

​	A、int func(int a, int b = 0, int c = 1);

​	B、int func(int a = 0, int b, int c = 1);

​	C、int func(int a = 0, int b = 1, int c);

​	D、int func(int a = 0, int b, int c);

答案：A

30. 如果函数声明中已指定默认参数，定义时：

​	A、 可以重复指定相同的默认参数

​	B、 不能重复指定默认参数

​	C、 必须重新指定所有默认参数

​	D、 只能重新指定部分默认参数

答案：B

31. 以下代码的输出是：

```cpp
void print(int x = 10) { std::cout << x; }  
int main() { print(); }  
```

​	A、 0

​	B、 10

​	C、 编译错误

​	D、 运行时错误

​	答案：B

32. 默认参数可以是：

​	A、 常量表达式

​	B、 全局变量

​	C、 函数调用

​	D、 以上都是

​	答案：D

33. 以下哪个函数调用会导致编译错误？

```cpp
void func(int a, double b = 3.14, char c = 'A');  
```

​	A、func(10);   

​	B、func(10, 2.71); 

​	C、func(10, 'X'); 

​	D、func(10, 2.71, 'X');  

​	答案：C

34. 默认参数在函数重载决议中：

​	A、 会影响函数匹配优先级

​	B、 仅当参数类型不同时生效

​	C、 与函数重载无关

​	D、 导致二义性错误

​	答案：D

​	解析：默认参数可能导致多个重载函数在补全默认参数后均可被调用，从而引发二义性错误。

35. 以下代码的输出是：

```cpp
void f(int x = 0) { std::cout << "int"; }  
void f(double x) { std::cout << "double"; }  
int main() { f(3.14); f(); }  
```

​	A、 double int

​	B、 int double

​	C、 编译错误（二义性）

​	D、 double double

​	答案：A

36. C++ 函数重载的条件是：

​	A、 函数名相同，但参数列表不同

​	B、 函数返回类型必须不同

​	C、 参数名称必须不同

​	D、 仅适用于成员函数

​	答案：A

​	解析：请牢记规则

37. 以下哪组函数构成合法重载？

​	A、int add(int a, int b); double add(double a, double b);

​	B、int max(int a, int b); int max(const int a, const int b);

​	C、void print(int x); void print(int* x);

​	D、void func(int a); void func(int a = 0);

​	答案：AC

​	解析：B选项，顶层 const（即参数本身是常量）不构成重载。两个函数的参数类型在本质上都是 int，编译器无法区分调用哪个函数。D选项，默认参数仅改变调用时的写法，不构成参数列表的差异。两个函数的参数列表完全相同（都是 int），因此属于重复定义，导致编译错误。

38. 函数重载解析时，编译器优先选择：

​	A、 需要类型转换最少的函数

​	B、 参数数量匹配的函数

​	C、 第一个声明的函数

​	D、 内联函数

​	答案：A

39. 以下代码的输出是：

```cpp
void f(int x) { std::cout << "int"; }  
void f(double x) { std::cout << "double"; }  
int main() { f('A'); }  
```

​	A、 int

​	B、 double

​	C、 编译错误（二义性）

​	D、 运行时错误

​	答案：A

40. 以下哪个因素不影响函数重载？

​	A、 参数类型

​	B、 参数数量

​	C、 函数返回类型

​	D、 参数顺序

​	答案：C

41. 以下代码会导致：

```cpp
void func(int x) {}  
void func(int& x) {}  
int main() {  
    int a = 10;  
    func(a);  // 调用哪个函数？  
}  
```

​	A、 编译错误（二义性）

​	B、 调用 void func(int x)

​	C、 调用 void func(int& x)

​	D、 运行时错误

​	答案：A

42. 以下代码的输出是：

```cpp
void f(int x) { std::cout << "int"; }  
void f(int x, int y = 0) { std::cout << "int, int"; }  
int main() { f(10); }  
```

​	A、 int

​	B、 int, int

​	C、 编译错误（二义性）

​	D、 运行时错误

​	答案：C

43. 以下哪个函数调用会导致二义性错误？

```cpp
void g(int x, double y);  
void g(double x, int y);  
```
​	A、g(1, 2); 

​	B、g(1.0, 2);

​	C、g(1, 2.0);

​	D、g(1.0, 2.0);

​	答案：A

44. 以下代码的输出是：

```cpp
void h(int x) { std::cout << "int"; }  
void h(double x) { std::cout << "double"; }  
void h(char x) { std::cout << "char"; }  
int main() { h(0); h('0'); }  
```

​	A、 int char

​	B、 int int

​	C、 char char

​	D、 double char

​	答案：A

45. 函数重载可以基于以下哪些特性？

​	A、 参数是否为常量引用

​	B、 是否为右值引用

​	C、 参数类型的 cv 限定符（如 const）

​	D、 以上都是

​	答案：D

46. 以下代码的输出是：

```cpp
void func(int x) { std::cout << "int"; }  
void func(int x, int y) { std::cout << "int, int"; }  
int main() {  
    func(10);  
    func(10, 20);  
}  
```

​	A、 int int, int

​	B、 int, int int

​	C、 编译错误（二义性）

​	D、 运行时错误

​	答案：A

47. 以下哪种方式是 C++11 引入的统一初始化语法？

​	A、 int a = 10;

​	B、int a(10);

​	C、int a{10};

​	D、 以上都是

​	答案：C

​	解析：A选项，这是C++诞生时就支持的；B选项，这是C++面向对象支持的，用于构造对象的语法，普通类型照样支持；C选项，这是C++11引入的，用于统一各种对象的初始化语法等。

48. 列表初始化（braced initialization）的主要优势是：

​	A、 防止隐式缩窄转换

​	B、 支持聚合初始化

​	C、 统一各种对象的初始化语法

​	D、 以上都是

​	答案：D

49. 以下代码会导致编译错误的是：

​	A、int a = 3.14;  

​	B、int b(3.14);      

​	C、int c{3.14};      

​	D、int d = {3.14};   

​	答案：CD

50. 默认初始化的结果是：

​	A、 基本类型的值未定义

​	B、 类类型调用默认构造函数

​	C、 数组元素未初始化（基本类型）

​	D、 以上都是

​	答案：D

51. 以下哪个是拷贝初始化？

​	A、int a = 5;

​	B、int a(5);

​	C、int a{5};

​	D、int a = {5};

​	答案：A

​	解析：A选项，本质是把5拷贝一份放到变量a中；BC选项都是直接把5存到了变量a中，不需要经过拷贝环节；D选项编译错误。

52. 拷贝初始化与直接初始化的区别是：

​	A、拷贝初始化可能调用隐式转换构造函数

​	B、直接初始化优先调用匹配的构造函数

​	C、拷贝初始化可能被编译器优化为直接初始化

​	D、以上都是

​	答案：D

53. const 变量必须：

​	A、在声明时初始化

​	B、使用常量表达式初始化

​	C、只能通过构造函数初始化（类类型）

​	D、以上都不对

​	答案：A

54. 静态变量的初始化发生在：

​	A、首次进入包含该变量的函数时

​	B、程序启动前（静态初始化）

​	C、类加载时（类静态成员）

​	D、以上都可能

​	答案：D

​	解析：A选项，当静态变量定义在函数内部时，只有当第一次进入函数时才会初始化；B选项，当定义的静态变量是全局变量时，会在程序启动前进行初始化；C选项，类中的静态成员会在程序启动前就初始化

55. 静态局部变量的初始化是：

​	A、线程安全的（C++11 及以后）

​	B、仅在首次调用函数时执行

​	C、保证在程序结束前销毁

​	D、以上都是

​	答案：D

56. 以下哪种类型可以使用聚合初始化？

​	A、普通数组

​	B、没有用户定义构造函数的结构体

​	C、所有成员都是公有的类

​	D、以上都是

​	答案：D

57. 聚合初始化可以使用：

​	A、等号加花括号 = { ... }

​	B、仅花括号 { ... }

​	C、圆括号 ( ... )

​	D、A 和 B

​	答案：D

58. 在 C++ 中，动态分配单个对象使用：

​	A、 malloc()

​	B、 new

​	C、 alloc()

​	D、 allocate()

​	答案：B

59. 动态释放内存使用：

​	A、free()

​	B、delete

​	C、destroy()

​	D、release()

​	答案：B

60. 动态分配数组使用：

​	A、new int[10];

​	B、new int(10);

​	C、malloc(10 * sizeof(int));

​	D、new [10]int;

​	答案：A

​	解析：B选项，是申请一个int类型并初始化为10；C选项，是C语言的内存分配；D选项，语法错误。

61. 释放动态分配的数组使用：

​	A、delete [] ptr;

​	B、delete ptr;

​	C、free(ptr);

​	D、deleteArray(ptr);

​	答案：A



62. 内存泄漏发生在：

​	A、动态分配的内存未被释放

​	B、重复释放同一块内存

​	C、使用已释放的内存

​	D、以上都是

​	答案：A

63. 野指针是指：

​	A、未初始化的指针

​	B、指向已释放内存的指针

​	C、指向栈内存的指针

​	D、A 和 B

​	答案：D

​	解析：A选项，未初始化的指针是一个野指针毋庸置疑，B选项实际上也是野指针，因为指向的内存不能使用了(也可以叫做悬空指针)。

64. 双重释放（Double free）会导致：

​	A、内存泄漏

​	B、程序崩溃

​	C、数据损坏

​	D、B 和 C

​	答案：D

​	解析：Double Free，即双重释放，是指程序在释放某块内存后，又尝试再次释放该内存。这种错误会破坏内存管理机制，导致程序行为不可预测，通常会触发运行时错误（如段错误）或内存破坏。

65. new 与 malloc() 的主要区别是：

​	A、new 会调用构造函数，malloc() 不会

​	B、new 返回正确类型的指针，malloc() 返回 void*

​	C、new 可以被重载，malloc() 不能

​	D、以上都是

​	答案：D

66. 以下代码的问题是：

```cpp
int* ptr = (int*)malloc(sizeof(int));  
*ptr = 10;  
delete ptr;  
```

​	A、类型不匹配（malloc 返回 void*）

​	B、混合使用 malloc 和 delete

​	C、未初始化指针

​	D、没有问题

​	答案：B

67. C++11 引入的智能指针用于：

​	A、自动管理动态内存

​	B、防止内存泄漏

​	C、实现 RAII（资源获取即初始化）

​	D、以上都是

​	答案：D

68. std::unique_ptr 的特点是：

​	A、独占对象所有权

​	B、不能拷贝，但可以移动

​	C、对象在指针离开作用域时自动释放

​	D、以上都是

​	答案：D

69. std::shared_ptr 使用：

​	A、引用计数管理对象生命周期

​	B、多个指针可以共享同一对象

​	C、对象在最后一个引用被销毁时释放

​	D、以上都是

​	答案：D



70. 动态内存分配可能抛出的异常是：

​	A、std::runtime_error

​	B、std::bad_alloc

​	C、std::out_of_memory

​	D、不会抛出异常

​	答案：B

71. 以下代码是否异常安全？

```cpp
void func() {  
    int* ptr = new int[1000];  
    // 可能抛出异常的操作  
    delete[] ptr;  
}  
```

​	A、是

​	B、否（异常可能导致内存泄漏）

​	C、仅在无异常时安全

​	D、取决于编译器

​	答案：B

​	解析：如果在注释处，代码发生了异常，那么ptr将得不到释放，导致内存泄漏，正确的方法是使用智能指针，因为智能指针在超出作用域时自动释放。



72. 定位 new（Placement new）的作用是：

​	A、在指定内存地址构造对象

​	B、提高内存分配效率

​	C、替代 malloc()

​	D、仅用于嵌入式系统

​	答案：A



73. 以下代码的输出是：

```cpp
int* ptr = new int(5);  
delete ptr;  
std::cout << *ptr;  
```

​	A、5

​	B、未定义行为

​	C、编译错误

​	D、运行时错误

​	答案：B

​	解析：当ptr释放之后，就不能在访问该内存了，如果访问则行为是未定义的。

74. 以下代码是否合法？

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);  
std::shared_ptr<int> ptr2 = ptr1;  
delete ptr1.get();  
```

​	A、合法

​	B、非法（双重释放）

​	C、仅在 ptr2 销毁后合法

​	D、仅在使用 std::unique_ptr 时合法

​	答案：B

​	解析：ptr1和ptr2都持有同一个内存空间的引用，通过delete ptr1.get();  释放了内存，那么当ptr1和ptr2释放的时候还会分别释放一次内存，多次重复释放了。

75. 为避免内存泄漏，应优先使用：

​	A、原始指针 + new/delete

​	B、std::unique_ptr

​	C、std::shared_ptr

​	D、B 和 C

​	答案：D

​	解析：在C++中，如果需要使用指针，优先使用智能指针。



76. std::string 位于哪个头文件中？

​	A、<string>

​	B、<cstring>

​	C、<string.h>

​	D、<str>

​	答案：A

77. 以下哪种方式不能初始化 std::string？

​	A、std::string s = "hello";

​	B、std::string s("hello");

​	C、std::string s = {'h', 'e', 'l', 'l', 'o'};

​	D、std::string s = 123;

​	答案：D

78. 访问 std::string 中第 i 个字符的合法方式是：

​	A、s[i]

​	B、s.at(i)

​	C、以上都是

​	D、仅 B

​	答案：C

​	解析：s[i]是下标访问形式，如果越界访问可能会直接中断；s.at(i)是函数获取字符，如果越界会抛出std::out_of_range异常！

79. 连接两个 std::string 对象可以使用：

​	A、+ 运算符

​	B、append() 方法

​	C、+= 运算符

​	D、以上都是

​	答案：D

80. 查找子字符串的方法有：

​	A、find()

​	B、rfind()

​	C、substr()

​	D、A 和 B

​	答案：D

81. 以下代码的输出是：

```cpp
std::string s = "hello";  
s.resize(3);  
std::cout << s;  
```

​	A、hel

​	B、hello

​	C、he

​	D、未定义行为

​	答案：A

​	解析：使用resize调整字符串大小时，如果传递的大小小于当前size则会阶段。

82. 将整数转换为 std::string 可以使用：

​	A、std::to_string()

​	B、std::stringstream

​	C、C++20 的 std::format()

​	D、以上都是

​	答案：D

83. 将 std::string 转换为整数可以使用：

​	A、std::stoi()

​	B、atoi()

​	C、std::stringstream

​	D、以上都是

​	答案：D

84. std::format 首次出现在哪个 C++ 标准中？

​	A、C++11

​	B、C++17

​	C、C++20

​	D、C++23

​	答案：C

85. std::format 的主要优势是：

​	A、类型安全

​	B、无需手动指定格式说明符（如 %d）

​	C、性能更高

​	D、以上都是

​	答案：D

86. 格式化字符串 std::format("{} + {} = {}", 1, 2, 3) 的输出是：

​	A、1 + 2 = 3

​	B、{} + {} = {}

​	C、编译错误

​	D、运行时错误

​	答案：A

87. 指定浮点数精度的语法是：

​	A、{:.2f}

​	B、{0:2f}

​	C、{2f}

​	D、{f:2}

​	答案：A

88. 以下代码的输出是：

```cpp
std::format("{0} {1} {0}", "a", "b");  
```

​	A、a b a

​	B、a b

​	C、b a b

​	D、编译错误

​	答案：A

89. std::format 相比 printf 的优势是：

​	A、类型安全

​	B、无需手动匹配格式说明符

​	C、更好的国际化支持

​	D、以上都是

​	答案：D

90. 以下哪种情况会导致 std::format 抛出异常？

​	A、参数数量与占位符不匹配

​	B、格式说明符无效

​	C、内存分配失败

​	D、以上都是

​	答案：D

91. std::string_view 的主要作用是：

​	A、高效传递字符串片段

​	B、避免不必要的内存拷贝

​	C、替代 const char*

​	D、以上都是

​	答案：D

​	解析：std::string_view是对字符串的一种非拥有式（non-owning）表示，意味着它不拥有字符串的内存，而是通过指针和长度来引用现有的字符串数据。

92. 以下代码是否合法？

```cpp
std::string_view sv = "hello";  
sv[0] = 'H';  // 修改第一个字符  
```

​	A、合法

​	B、非法（string_view 是只读的）

​	C、仅在 C++23 中合法

​	D、取决于编译器

​	答案：B

93. 分割 std::string 最便捷的方法是：

​	A、使用 std::stringstream

​	B、C++20 的 std::ranges::split_view

​	C、手动遍历查找分隔符

​	D、以上都是

​	答案：D

94. 以下代码的输出是：

```cpp
std::string s = "  trim me  ";  
auto trimmed = std::format("'{}'", s);  
std::cout << trimmed;  
```

​	A、'  trim me  '

​	B、'trim me'

​	C、编译错误

​	D、运行时错误

​	答案：A

95. 构造函数的作用是：

​	A、初始化对象的成员变量

​	B、为对象分配内存

​	C、定义对象的行为

​	D、以上都是

​	答案：A

96. 构造函数的名称必须与：

​	A、类名相同

​	B、返回类型相同

​	C、任意名称

​	D、以上都不对

​	答案：A

97. 以下关于构造函数的说法，正确的是：

​	A、可以有多个重载的构造函数

​	B、不能有返回类型（包括 void）

​	C、可以带默认参数

​	D、以上都是

​	答案：D

98.  默认构造函数是指：

​	A、不带参数的构造函数

​	B、所有参数都有默认值的构造函数

​	C、显式定义的无参构造函数

​	D、以上都是

​	答案：D

​	解析：只要构造函数调用时，不需要传递参数，就可以叫做默认构造函数。

99. 当类中没有显式定义任何构造函数时：

​	A、编译器会生成一个默认构造函数

​	B、对象无法被创建

​	C、必须使用初始化列表

​	D、以上都不对

​	答案：A

100. 拷贝构造函数的参数通常是：

​	A、类的对象

​	B、类的对象的引用

​	C、类的对象的常量引用

​	D、B 或 C

​	答案：C

101. 以下哪种情况会调用拷贝构造函数？

​	A、对象作为函数参数按值传递

​	B、对象作为函数返回值按值返回

​	C、使用另一个对象初始化新对象

​	D、以上都是

​	答案：D

102. 如果类中未定义拷贝构造函数，编译器会：

​	A、生成一个浅拷贝的拷贝构造函数

​	B、禁止对象的拷贝操作

​	C、导致编译错误

​	D、以上都不对

​	答案：A

103.  析构函数的作用是：

​	A、释放对象占用的资源

​	B、销毁对象的成员变量

​	C、为对象回收内存

​	D、A 和 C

​	答案：D

104. 析构函数的名称是：

​	A、类名前加波浪号（~）

​	B、与类名相同

​	C、任意名称

​	D、以上都不对

​	答案：A

105. 以下关于析构函数的说法，正确的是：

​	A、不能带参数

​	B、不能有返回类型（包括 void）

​	C、只能有一个析构函数

​	D、以上都是

​	答案：D

106. 当创建一个包含成员对象的类的对象时：

​	A、成员对象的构造函数先被调用

​	B、类自身的构造函数先被调用

​	C、构造顺序不确定

​	D、以上都不对

​	答案：A

107. 当销毁一个包含成员对象的类的对象时：

​	A、成员对象的析构函数先被调用

​	B、类自身的析构函数先被调用

​	C、析构顺序不确定

​	D、以上都不对

​	答案：B

108. C++ 的 "三 / 五法则" 中的特殊成员函数包括：

​	A、拷贝构造函数

​	B、拷贝赋值运算符

​	C、析构函数

​	D、以上都是

​	答案：D

​	解析：三之法则，若某个类需要用户定义的析构函数、用户定义的复制构造函数或用户定义的复制赋值运算符，则它几乎肯定三者全部都需要。五之法则：因为用户定义析构函数、复制构造函数或复制赋值运算符的存在阻止移动构造函数和移动赋值运算符的隐式定义，所以任何想要移动语义的类必须声明全部五个特殊成员函数。

109. 移动构造函数的参数类型是：

​	A、左值引用

​	B、右值引用

​	C、常量左值引用

​	D、常量右值引用

​	答案：B

110. 委托构造函数的作用是：

​	A、调用基类的构造函数

​	B、在一个构造函数中调用另一个构造函数

​	C、实现构造函数的重载

​	D、以上都不对

​	答案：B

111. 以下代码是否合法？

```cpp
class A {  
public:  
    A(int x) : val(x) {}  
    A() : A(0) {}  // 委托构造函数  
private:  
    int val;  
};  
```

​	A、合法

​	B、非法（循环委托）

​	C、仅在 C++17 及以后合法

​	D、仅在类有默认构造函数时合法

​	答案：A

112. explicit 关键字的作用是：

​	A、禁止隐式类型转换

​	B、强制显式调用构造函数

​	C、仅用于单参数构造函数

​	D、以上都是

​	答案：D

113. 以下代码会导致编译错误的是：

```cpp
class B {  
public:  
    explicit B(int x) : val(x) {}  
private:  
    int val;  
};  

void func(B b) {}  

int main() {  
    func(10);  // A  
    B b = 10;  // B  
    B b(10);   // C  
    B b = B(10);  // D  
}  
```

​	A、A 和 B

​	B、仅 B

​	C、仅 A

​	D、无错误

​	答案：A

114. 浅拷贝和深拷贝的主要区别是：

​	A、浅拷贝复制指针，深拷贝复制指针指向的内容

​	B、浅拷贝可能导致内存泄漏，深拷贝不会

​	C、浅拷贝更快，深拷贝更安全

​	D、以上都是

​	答案：D

115. 成员初始化列表的主要作用是：

​	A、提高性能（避免默认初始化）

​	B、初始化 const 成员变量

​	C、初始化引用成员变量

​	D、以上都是

​	答案：D

116. 以下代码的输出是：

```cpp
class C {
public:
	C() : x(x), y(10) {}
	int x;
	int y;
};

int main() {
	C c;
	std::cout << c.x << " " << c.y;
}
```

​	A、10 10

​	B、未定义值 10 

​	C、编译错误

​	D、运行时错误

​	答案：B

​	解析：当类对象创建时，构造函数的初始化列表中的调用顺序，是由成员的定义顺序决定的，先定义的先初始化；也就是说在这里先用y构造x，但是此时y还没有初始化，所以是未定义值(垃圾值)，x构造完成最后在构造y。

117. 静态成员变量的初始化发生在：

​	A、类的对象创建时

​	B、程序启动前

​	C、首次使用该类时

​	D、由编译器决定

​	答案：B

118. 静态成员函数能否访问非静态成员？

​	A、能，通过对象实例

​	B、能，直接访问

​	C、不能，静态成员函数没有 this 指针

​	D、取决于成员的访问权限

​	答案：C



119. 为什么基类的析构函数通常声明为虚函数？

​	A、确保正确调用派生类的析构函数

​	B、允许通过基类指针删除派生类对象

​	C、防止内存泄漏

​	D、以上都是

​	答案：D

120. 以下代码的行为是：

```cpp
class Base {  
public:  
    ~Base() { std::cout << "Base::~Base()"; }  
};  

class Derived : public Base {  
public:  
    ~Derived() { std::cout << "Derived::~Derived()"; }  
};  

int main() {  
    Base* ptr = new Derived();  
    delete ptr;  // 调用哪个析构函数？  
}  
```

​	A、仅调用 Base::~Base()

​	B、仅调用 Derived::~Derived()

​	C、先调用 Derived::~Derived()，再调用 Base::~Base()

​	D、未定义行为

​	答案：A

121. 移动构造函数的参数类型是：

​	A、T&

​	B、const T&

​	C、T&&

​	D、const T&&

​	答案：C

122. 移动语义的主要目的是：

​	A、避免深拷贝，提高性能

​	B、实现资源的所有权转移

​	C、处理临时对象（右值）

​	D、以上都是

​	答案：D

123. RAII（资源获取即初始化）原则是指：

​	A、资源的生命周期与对象的生命周期绑定

​	B、构造函数获取资源，析构函数释放资源

​	C、避免手动管理资源（如内存、文件句柄）

​	D、以上都是

​	答案：D

124. 如果类管理动态资源（如动态分配的内存），通常需要：

​	A、显式定义拷贝构造函数

​	B、显式定义拷贝赋值运算符

​	C、显式定义析构函数

​	D、以上都是

​	答案：D

125. C++11 中，默认生成的特殊成员函数包括：

​	A、默认构造函数

​	B、拷贝构造函数

​	C、拷贝赋值运算符

​	D、以上都是

​	答案：D

126. 使用 = delete 可以：

​	A、禁止特定的特殊成员函数

​	B、删除已定义的函数

​	C、仅用于析构函数

​	D、以上都不对

​	答案：A

127. 委托构造函数的语法是：

​	A、ClassName() : ClassName(args) {}

​	B、ClassName(args) : this(args) {}

​	C、ClassName() { ClassName(args); }

​	D、ClassName(args) : base(args) {}

​	答案：A

128.  C++11 引入的继承构造函数允许：

​	A、派生类继承基类的构造函数

​	B、基类继承派生类的构造函数

​	C、替代委托构造函数

​	D、以上都不对

​	答案：A

​	解析：使用using Base::Base;能够让子类继承基类的构造函数。

129. 类成员的初始化顺序由什么决定？

​	A、成员在初始化列表中的顺序

​	B、成员在类定义中的声明顺序

​	C、构造函数的参数顺序

​	D、以上都不对

​	答案：B

130. 聚合类的特点是：

​	A、 所有成员都是公有的

​	B、没有用户定义的构造函数

​	C、 没有基类和虚函数

​	D、 以上都是

​	答案：D

​	解析：在C++中，聚合类型（Aggregate Type）是指满足特定条件的一类数据结构。聚合类型的定义和特性使其在初始化和使用上具有独特的优势。根据C++标准，聚合类型需要满足以下条件：

​	a. 没有用户声明的构造函数。

​	b. 没有私有或受保护的非静态数据成员。

​	c. 没有基类。

​	d. 没有虚函数。

131. 以下哪个类可以使用聚合初始化？

	A、class E {int x; int y;}; 
	
	B、struct F {private:  int x;  int y;  };
	
	C、class G {public:  G(int x, int y) : x(x), y(y) {}  int x;  int y;  };  
	
	D、struct H {int x;  int y;  }; 

​	答案：D

​	解析：D选项可以直接使用 H h{2,3};这种聚合的方式初始化；C选项，其实也可以，但是本质上还是调用构造函数初始化；B选项，成员是私有的；A选项，成员默认也是私有的。

132. 析构函数抛出异常会导致：

​	A、程序立即终止（调用 std::terminate）

​	B、未定义行为

​	C、只有在异常处理中才会终止程序

​	D、以上都不对

​	答案：A

133. 为防止析构函数抛出异常，应：

​	A、在析构函数中捕获所有异常

​	B、使用 noexcept 说明符

​	C、确保资源释放不会抛出异常

​	D、以上都是

​	答案：D

134. 常量成员函数的主要作用是：

​	A、防止修改类的成员变量

​	B、允许在常量对象上调用

​	C、提高代码安全性

​	D、以上都是

​	答案：D

135. 声明常量成员函数的语法是：

​	A、void func() const;

​	B、const void func();

​	C、void const func();

​	D、void func(const);

​	答案：A

136. 以下代码是否合法？

```cpp
class A {  
public:  
    void modify() const { x = 10; }  // 修改成员变量  
private:  
    int x;  
};  
```

​	A、合法

​	B、非法（常量成员函数不能修改非 mutable 成员）

​	C、仅在 C++20 及以后合法

​	D、取决于编译器

​	答案：B

137.  静态成员变量的特点是：

​	A、所有对象共享同一个实例

​	B、必须在类外初始化

​	C、可以通过类名直接访问

​	D、以上都是

​	答案：D

​	解析：注意B选项，在C++17之后，可以通过inline关键字直接在类内初始化。

138.  静态成员函数的特点是：

​	A、没有 this 指针

​	B、只能访问静态成员变量

​	C、可以通过类名直接调用

​	D、以上都是

​	答案：D

139. 以下代码的输出是：

```cpp
class B {  
public:  
    static int count;  
    B() { count++; }  
};  

int B::count = 0;  

int main() {  
    B b1, b2;  
    std::cout << B::count;  
}  
```

​	A、0

​	B、1

​	C、2

​	D、编译错误

​	答案：C

140. 常量静态成员变量可以：

​	A、在类内直接初始化（C++11 及以后）

​	B、无需类外定义

​	C、用于模板参数（如数组大小）

​	D、以上都是

​	答案：D

141. 以下关于静态成员的说法，正确的是：

​	A、静态成员函数不能被声明为 const

​	B、静态成员变量的类型可以是其所属类的类型

​	C、静态成员可以是私有的

​	D、以上都是

​	答案：D

142. 以下代码的作用是：

```cpp
class C {  
public:  
    C() = default;  
    C(const C&) = delete;  
    C& operator=(const C&) = delete;  
};  
```

​	A、允许默认构造，但禁止拷贝操作

​	B、禁止所有构造函数

​	C、仅允许移动语义

​	D、以上都不对

​	答案：A



143. 常量成员函数和非常量成员函数可以重载吗？

​	A、可以，根据对象是否为常量决定调用哪个版本

​	B、不可以，函数签名相同

​	C、仅在返回类型不同时可以重载

​	D、仅在 C++20 及以后可以重载

​	答案：A

144. 以下代码的输出是：

```cpp
class D {  
public:  
    void func() const { std::cout << "const"; }  
    void func() { std::cout << "non-const"; }  
};  

int main() {  
    const D d1;  
    D d2;  
    d1.func();  
    d2.func();  
}  
```

​	A、const non-const

​	B、non-const const

​	C、编译错误（函数重复定义）

​	D、运行时错误

​	答案：A

145. 基类和派生类是否共享同一个静态成员变量？

​	A、是，静态成员在整个继承层次中唯一

​	B、否，每个类有自己的静态成员实例

​	C、取决于继承方式（public/protected/private）

​	D、以上都不对

​	答案：A

146. 静态成员函数能否被声明为虚函数？

​	A、可以，允许通过基类指针调用派生类的静态函数

​	B、不可以，静态函数没有 this 指针

​	C、仅在 C++17 及以后可以

​	D、以上都不对

​	答案：B

147. mutable 关键字的作用是：

​	A、允许在常量成员函数中修改成员变量

​	B、仅用于静态成员变量

​	C、提高变量的访问权限

​	D、以上都不对

​	答案：A

148. 以下代码的输出是：

```cpp
class Foo {  
public:  
    void increment() const { count++; }  
    int getCount() const { return count; }  
private:  
    mutable int count = 0;  
};  

int main() {  
    const Foo e;  
    e.increment();  
    std::cout << e.getCount();  
}  
```

​	A、0

​	B、1

​	C、编译错误（修改常量对象）

​	D、运行时错误

​	答案：B

149. 运算符重载允许：

​	A、改变运算符的优先级

​	B、改变运算符的结合性

​	C、为自定义类型定义运算符行为

​	D、以上都是

​	答案：C

150. 不能被重载的运算符是：

​	A、::（作用域解析）

​	B、.（成员访问）

​	C、?:（三元条件）

​	D、以上都是

​	答案：D

151. 重载运算符必须至少有一个操作数是：

​	A、内置类型

​	B、自定义类型

​	C、指针类型

​	D、引用类型

​	答案：B

152. 二元运算符可以重载为：

​	A、成员函数（左操作数为隐式this）

​	B、非成员函数（两个操作数均为参数）

​	C、A 或 B

​	D、仅 A

​	答案：C

153. 一元运算符++重载为成员函数时，参数列表应为：

​	A、()（前置版本）

​	B、(int)（后置版本）

​	C、以上都是

​	D、仅 B

​	答案：C

154. 重载赋值运算符（operator=）时，通常返回：

​	A、void

​	B、T（类类型）

​	C、T&（类的引用）

​	D、const T&

​	答案：C

155. 重载流插入运算符（operator<<）通常实现为：

​	A、成员函数

​	B、非成员函数

​	C、友元函数

​	D、B 或 C

​	答案：D

156. 以下代码是否合法？

```cpp
class Vector {  
public:  
    int x, y;  
    Vector operator+(const Vector& v) const {  
        return Vector{x + v.x, y + v.y};  
    }  
};  
```

A、合法

​	B、非法（缺少返回类型）

​	C、非法（必须为友元函数）

​	D、非法（不能重载+）

​	答案：A

157. 重载运算符时，不允许改变的是：

​	A、操作数的个数

​	B、运算符的语法结构

​	C、运算符的优先级

​	D、以上都是

​	答案：D

158. 以下哪种情况会导致运算符重载二义性？

​	A、同时重载成员和非成员版本的同一运算符

​	B、多个重载版本均可匹配参数

​	C、A 和 B

​	D、仅 B

​	答案：C

159. 重载下标运算符（operator[]）通常返回：

​	A、引用（允许修改）

​	B、常量引用（只读）

​	C、值类型

​	D、A 或 B

​	答案：D

160. 重载函数调用运算符（operator()）可以实现：

​	A、函数对象（Functor）

​	B、Lambda 表达式

​	C、以上都是

​	D、语法错误

​	答案：A

161. 类型转换运算符（如operator int()）：

​	A、必须为成员函数

​	B、不能有返回类型声明（但隐式返回目标类型）

​	C、以上都是

​	D、仅 A

​	答案：C

162. 以下代码的作用是：

```cpp
class Fraction {  
public:  
    operator double() const { return numerator / denominator; }  
private:  
    int numerator, denominator;  
};  
```

​	A、定义从Fraction到double的隐式转换

​	B、定义从double到Fraction的构造函数

​	C、编译错误（缺少返回类型）

​	D、以上都不对

​	答案：A

163. 友元函数重载运算符的优势是：

​	A、可以访问类的私有成员

​	B、两个操作数均可进行隐式类型转换

​	C、以上都是

​	D、仅 B

​	答案：C

164. 重载<<和>>运算符时，通常声明为友元函数是因为：

​	A、需要访问类的私有成员

​	B、第一个参数必须是流对象（非类类型）

​	C、以上都是

​	D、仅 B

​	答案：C

165. 重载赋值运算符时，通常实现为 “拷贝并交换”（Copy-and-Swap）惯用法是为了：

​	A、提高性能

​	B、实现异常安全

​	C、简化代码

​	D、以上都是

​	答案：D

166. 重载+和+=运算符时，合理的实现方式是：

​	A、+=基于+实现

​	B、+基于+=实现

​	C、两者独立实现

​	D、仅实现其中一个

​	答案：B

167. 以下代码的输出是：

```cpp
class Point {  
public:  
    int x, y;  
    Point(int x = 0, int y = 0) : x(x), y(y) {}  
    Point operator+(const Point& p) const {  
        return Point(x + p.x, y + p.y);  
    }  
};  

int main() {  
    Point p1(1, 2), p2(3, 4);  
    Point p3 = p1 + p2;  
    std::cout << p3.x << " " << p3.y;  
}  
```

​	A、4 6

​	B、1 2

​	C、3 4

​	D、编译错误

​	答案：A

168. 重载运算符时，应遵循的原则是：

​	A、保持运算符的原有语义

​	B、避免过度重载

​	C、确保一致性和直观性

​	D、以上都是

​	答案：D

169. 继承允许：

​	A、子类复用父类的属性和方法

​	B、子类扩展父类的功能

​	C、实现多态性

​	D、以上都是

​	答案：D

170. 基类的私有成员在派生类中：

​	A、可直接访问

​	B、不可访问

​	C、可通过接口函数访问

​	D、B 和 C

​	答案：D

​	解析：父类中的私有成员，子类是没有办法直接访问的，只能通过父类提供的接口函数来访问。

171. 继承方式（public/protected/private）影响：

​	A、基类成员在派生类中的访问权限

​	B、基类自己的访问权限

​	C、派生类的成员访问权限

​	D、没有影响

​	答案：A

172. 公有继承（public）时：

​	A、基类的 public 成员变为派生类的 public 成员

​	B、基类的 protected 成员变为派生类的 protected 成员

​	C、基类的 private 成员仍为基类私有

​	D、以上都是

​	答案：D

​	解析：无论以何种权限继承，基类中private权限的成员，在子类中都不可访问。

173. 私有继承（private）时：

​	A、基类的所有成员变为派生类的 private 成员

​	B、无法通过派生类对象访问基类的任何成员

​	C、派生类不能进一步派生

​	D、派生类的私有成员，派生类不能访问；其他成员都变成了派生类的私有成员

​	答案：D

174. 派生类对象构造时：

​	A、基类构造函数先执行

​	B、派生类构造函数先执行

​	C、构造顺序不确定

​	D、仅执行派生类构造函数

​	答案：A

175. 派生类对象析构时：

​	A、基类析构函数先执行

​	B、派生类析构函数先执行

​	C、析构顺序不确定

​	D、仅执行基类析构函数

​	答案：B

176.  如果基类没有默认构造函数，派生类必须：

​	A、定义自己的默认构造函数

​	B、在初始化列表中显式调用基类的带参构造函数

​	C、无法编译

​	D、以上都不对

​	答案：B

177. 派生类中定义与基类同名的函数会：

​	A、覆盖（override）基类的虚函数

​	B、隐藏（hide）基类的非虚函数

​	C、导致编译错误

​	D、A 或 B

​	答案：D

178. 虚函数的作用是：

​	A、实现运行时多态

​	B、允许通过基类指针 / 引用调用派生类函数

​	C、以上都是

​	D、让类不肾虚

​	答案：C

179. 纯虚函数的定义是：

​	A、virtual void func() = 0;

​	B、void func() = 0;

​	C、virtual void func() {}

​	D、以上都不对

​	答案：A

180. 包含纯虚函数的类称为：

​	A、抽象类

​	B、接口类

​	C、不能实例化的类

​	D、以上都是

​	答案：D

181. 多重继承允许：

​	A、一个类继承多个基类

​	B、一个类继承两个基类

​	C、一个类派生多个子类

​	D、一个雷派生一个子类

​	答案：A

182. 菱形继承（钻石继承）会导致：

​	A、数据冗余

​	B、二义性问题

​	C、以上都是

​	D、以上都不是

​	答案：C

183. 使用virtual继承可以：

​	A、解决菱形继承中的数据冗余

​	B、确保基类的一份拷贝

​	C、以上都是

​	D、以上都不是

​	答案：C

184.  基类的 protected 成员：

​	A、可被基类的成员函数访问

​	B、可被派生类的成员函数访问

​	C、不可被外部对象访问

​	D、以上都是

​	答案：D

185. 组合（Has-A 关系）与继承（Is-A 关系）的主要区别是：

​	A、组合通过成员对象实现，继承通过派生类实现

​	B、组合更灵活，继承更紧密

​	C、组合支持运行时变化，继承是静态的

​	D、以上都是

​	答案：D

186. 以下代码的输出是：

```cpp
class Base {  
public:  
    virtual void func() { std::cout << "Base"; }  
};  

class Derived : public Base {  
public:  
    void func() override { std::cout << "Derived"; }  
};  

int main() {  
    Base* ptr = new Derived();  
    ptr->func();  
    delete ptr;  
}  
```

​	A、Base

​	B、Derived

​	C、编译错误

​	D、运行时错误

​	答案：B

​	解析：多态。

187. C++ 多态的实现方式包括：

​	A、编译时多态（函数重载、模板）

​	B、运行时多态（虚函数）

​	C、预编译多态（函数重载、模板）

​	D、链接时多态 

​	答案：AB

188. 运行时多态的核心机制是：

​	A、 虚函数表（vtable）

​	B、 虚表指针（vptr）

​	C、父类指针或引用指向或引用子类对象

​	D、以上都不对

​	答案：AB

​	解析：多态的底层原理就是把虚函数都存入到虚函数表中，然后在类中放一个虚函数表指针，调用虚函数的时候，去虚函数表中调用对应的具体函数。

189. 以下关于虚函数的说法，正确的是：

​	A、虚函数必须在基类中声明

​	B、派生类中重写的虚函数必须与基类原型完全一致

​	C、虚函数不能是静态成员函数

​	D、以上都是

​	答案：D

190. 动态绑定发生在：

​	A、编译时

​	B、运行时

​	C、链接时

​	D、以上都不对

​	答案：B

191. 以下代码，输出结果是

```cpp
class Parent {
public:
	virtual void say() = 0 {
		printf("parent ");
	}
};

class Child : public Parent {
public:
	void say() override {
		Parent::say();
        printf("child ");
	}
};
int main()
{
    Child c;
    c.say();
    return 0;
}
```

​	A、parent child

​	B、child parent

​	C、child child

​	D、编译错误

​	答案：A

​	解析：纯虚函数也可以有函数体，可以提供一个默认实现，但是子类必须重写，子类可以不自己实现，直接调用父类的实现。

192. 每个包含虚函数的类有：

​	A、一个虚函数表（vtable）

​	B、每个对象有一个 vptr（虚函数表指针）

​	C、以上都是

​	D、以上都不是

​	答案：C

193. 虚函数调用的开销主要来自：

​	A、通过 vptr 间接访问 vtable

​	B、动态类型检查

​	C、以上都是

​	D、仅 A

​	答案：A

194. 以下情况无法实现多态：

​	A、通过对象（而非指针 / 引用）调用虚函数

​	B、在构造函数 / 析构函数中调用虚函数

​	C、调用普通函数

​	D、以上都无法实现多态

​	答案：D

195. 虚函数不能是：

​	A、静态成员函数

​	B、内联函数

​	C、构造函数

​	D、以上都是

​	答案：D

196. C++11 引入的override关键字的作用是：

​	A、显式声明重写基类的虚函数

​	B、确保函数签名与基类一致

​	C、以上都是

​	D、仅 A

​	答案：C

197. C++11 引入的final关键字可以：

​	A、禁止类被继承

​	B、禁止函数被重写

​	C、禁止类定义对象

​	D、禁止通过对象调用函数

答案：AB

198. 以下代码是否合法？

```cpp
class Base {  
public:  
    virtual void func() final;  
};  

class Derived : public Base {  
public:  
    void func() override;  // 重写final函数  
};  
```

​	A、合法

​	B、非法（不能重写 final 函数）

​	C、仅在 C++17 及以后合法

​	D、取决于编译器

​	答案：B

199. 字符串流的主要作用是：

​	A、实现字符串与其他数据类型的相互转换

​	B、高效处理字符串拼接

​	C、模拟文件操作

​	D、以上都是

​	答案：D

200. 文件流的三种基本类型是：
     A、ifstream（输入文件流）
     B、ofstream（输出文件流）
     C、fstream（读写文件流）
     D、以上都是

​	答案：D

201. 使用stringstream进行类型转换时：

​	A、<< 用于插入数据到流中

​	B、>> 用于从流中提取数据

​	C、需包含<sstream>头文件

​	D、以上都是

​	答案：D

202. 以下代码的输出是：

```cpp
int main() {  
    std::stringstream ss;  
    ss << 42;  
    std::string str = ss.str();  
    std::cout << str;  
}  
```

​	A、42

​	B、未定义行为

​	C、编译错误

​	D、运行时错误

​	答案：A

203. 将字符串解析为整数的正确方式是：std::string s = "123"; int num; 

​	A、std::stringstream(s) >> num;  

​	B、std::stoi(s);  

​	C、使用atoi(s.c_str())  

​	D、以上都是  

​	答案：D

204. 打开文件时，文件打开模式包括：
     A、std::ios::in（读模式） 

​	B、std::ios::out（写模式）  

​	C、std::ios::app（追加模式）  

​	D、以上都是  

​	答案：D

205. 检查文件是否成功打开的方法是：

​	A、is_open()  

​	B、直接使用流对象的布尔值（如if (file)）  

​	C、good()  

​	D、以上都是  

​	答案：D

206. 读取文件的一行内容到字符串中，应使用：

​	A、file >> str;  

​	B、std::getline(file, str);  

​	C、file.read(str);  

​	D、以上都不对  

​	答案：B

207. 流的状态标志包括：

​	A、eof()（文件结束）  

​	B、fail()（操作失败）  

​	C、bad()（严重错误）  

​	D、以上都是  

​	答案：D

208. 重置流的状态标志使用：  

​	A、clear()  

​	B、reset()  

​	C、flush()  

​	D、seekg(0)  

​	答案：A

209. 移动文件指针到文件末尾的方法是：  

​	A、file.seekg(0, std::ios::end);  

​	B、file.seekp(0, std::ios::end);  

​	C、以上都是  

​	D、仅A（输入流）或B（输出流）  

​	答案：C

210. 获取当前文件指针位置使用：  

​	A、file.tellg()（输入流）  

​	B、file.tellp()（输出流）  

​	C、file.pos()  

​	D、file.position()  

​	答案：AB

211. 以下代码的作用是：  

     ``` cpp
     std::ifstream file("data.txt");  
     std::stringstream buffer;  
     buffer << file.rdbuf();  
     std::string content = buffer.str();  
     ```

​	A、将文件内容读入字符串content

​	B、清空文件内容

​	C、复制文件到另一个位置

​	D、编译错误

​	答案：A

212. 安全关闭文件的方法是：

​	A、调用close()

​	B、让文件流对象超出作用域（自动析构）

​	C、以上都是

​	D、仅 B

​	答案：C

213. 检查文件是否存在的最佳方法是：

​	A、尝试打开文件并检查is_open()

​	B、使用操作系统 API（如stat()）

​	C、检查文件流状态

​	D、以上都是

​	答案：A

214. C++ 异常处理机制的关键字包括：

​	A、try

​	B、catch

​	C、throw

​	D、except

​	答案：ABC

215. 抛出异常使用：

​	A、try 块

​	B、catch 块

​	C、throw 语句

​	D、以上都不对

​	答案：C

216. 捕获异常时，catch 块的参数类型应：

​	A、与抛出的异常类型完全匹配

​	B、是抛出的异常类型的基类

​	C、使用引用（如 catch (const ExceptionType& e)）

​	D、以上都是

​	答案：D

217.  C++11 弃用的异常规范语法是：

​	A、void func() throw(int, char);

​	B、void func() noexcept;

​	C、void func() noexcept(true);

​	D、以上都不对

​	答案：A

​	解析： 动态异常规范（throw(optional_type_list) 规范）在 C++11 中已弃用，并已在 C++17 中删除，但 throw() 除外，它是 noexcept(true) 的别名。

218. noexcept 说明符的作用是：

​	A、声明函数不会抛出异常

​	B、强制函数内部捕获所有异常

​	C、提高性能（编译器可优化）

​	D、声明函数只能抛出一种类型的异常

​	答案：AC

​	解析：noexcept声明函数不会抛出异常，但实际上抛出了一场也不会有问题，所以要自己保证使用noexcept声明了的函数不抛出异常。

219.  C++ 标准库的异常基类是：

​	A、std::exception

​	B、std::runtime_error

​	C、std::logic_error

​	D、以上都不对

​	答案：A

220. 以下哪个异常类用于处理动态内存分配失败？

​	A、std::bad_alloc

​	B、std::overflow_error

​	C、std::out_of_range

​	D、std::invalid_argument

​	答案：A

221. C++ 的四种显式类型转换运算符是：

​	A、static_cast

​	B、dynamic_cast

​	C、const_cast

​	D、reinterpret_cast

​	E、object_cast

​	F、cast

​	答案：ABCD

222. static_cast 可用于：

​	A、基本数据类型转换（如 int 转 double）

​	B、父类指针 / 引用与子类指针 / 引用的相互转换

​	C、枚举值与整数的转换

​	D、以上都是

​	答案：D

223. dynamic_cast 的主要用途是：

​	A、安全地将基类指针 / 引用转换为派生类指针 / 引用

​	B、运行时类型检查

​	C、仅适用于包含虚函数的类

​	D、以上都是

​	答案：D

224. 当 dynamic_cast 转换失败时：

​	A、对于指针，返回 nullptr

​	B、对于指针，返回原指针

​	C、对于引用，抛出 std::bad_cast 异常

​	D、导致未定义行为

​	答案：AB

225. const_cast 可用于：

​	A、去除变量的 const 属性

​	B、添加变量的 const 属性

​	C、仅适用于指针和引用

​	D、以上都是

​	答案：D

226. 使用 const_cast 去除 const 并修改常量对象会导致：

​	A、编译错误

​	B、运行时未定义行为

​	C、仅在对象本身不是常量时安全

​	D、以上都不对

​	答案：C

227. Lambda 表达式的基本语法是：

​	A、[capture](parameters) -> return_type { body }

​	B、function[capture](parameters) { body }

​	C、lambda(parameters) { body }

​	D、以上都不对

​	答案：A

228. Lambda 表达式的捕获列表（[ ]）可包含：

​	A、值捕获（如 [x]）

​	B、引用捕获（如 [&x]）

​	C、隐式捕获（如 [=] 或 [&]）

​	D、以上都是

​	答案：D

229. 引用捕获（[&x]）可能导致悬空引用的情况是：

​	A、Lambda 在变量作用域结束后执行

​	B、捕获的变量被移动或销毁

​	C、以上都是

​	D、Lambda 被立即调用

​	答案：C

230. 以下代码的输出是：

```cpp
int x = 10;  
auto lambda = [x]() mutable { x++; return x; };  
std::cout << lambda();  
```

​	A、10

​	B、11

​	C、编译错误（不能修改值捕获的变量）

​	D、运行时错误

​	答案：B

231. Lambda 表达式常用于：

​	A、作为 STL 算法的谓词（如 std::find_if）

​	B、实现简单的函数对象

​	C、延迟执行代码块

​	D、以上都是

​	答案：D

232. 以下代码的作用是：

```cpp
std::vector<int> v = {1, 2, 3, 4};  
std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });  
```

​	A、计算向量元素的和

​	B、将每个元素乘以 2

​	C、查找第一个偶数

​	D、编译错误

​	答案：B

233. 以下代码是否合法？

```cpp
try {  
    throw std::string("Error");  
} catch (const char* msg) {  
    std::cout << msg;  
}  
```

​	A、合法（捕获字符串字面量）

​	B、非法（类型不匹配，无法捕获 std::string）

​	C、仅在 C++17 及以后合法

​	D、取决于编译器

​	答案：B

234. C++模板的主要作用是：

​	A、实现代码复用和泛型编程

​	B、提高运行时性能

​	C、减少可执行文件大小

​	D、替代面向对象编程

​	答案：A

235. 类模板的实例化发生在：

​	A、编译时

​	B、运行时

​	C、链接时

​	D、预处理时

​	答案：A

236. 函数模板可以重载的依据是：

​	A、参数个数不同

​	B、参数类型不同

​	C、返回值类型不同

​	D、以上都可以

​	答案：D

237. 模板特化是指：

​	A、为特定类型提供特殊实现

​	B、限制模板使用范围

​	C、优化模板编译速度

​	D、声明模板默认参数

​	答案：A

238. std::vector是：

​	A、类模板

​	B、函数模板

​	C、别名模板

​	D、变量模板

​	答案：A

239. 模板元编程主要利用：

​	A、模板实例化机制

​	B、虚函数机制

​	C、异常处理机制

​	D、动态内存分配

​	答案：A

240. 可变参数模板使用什么符号表示：

​	A、...

​	B、&&

​	C、::

​	D、->

​	答案：A

241. 模板参数的默认值：

​	A、可以从右往左省略

​	B、可以任意顺序省略

​	C、必须全部指定

​	D、不能有默认值

​	答案：A

242. 下列哪个不是模板类型：

​	A、类模板

​	B、函数模板

​	C、变量模板

​	D、指针模板

​	答案：D

243. SFINAE的全称是：

​	A、Substitution Failure Is Not An Error

​	B、Special Function In Namespace Area

​	C、Standard Form In Native Application

​	D、Syntax For Internal Node Access

​	答案：A

244. 模板模板参数是指：

​	A、参数本身是模板

​	B、参数必须是模板

​	C、参数包含模板

​	D、参数生成模板

​	答案：A

245. 下列哪个C++标准引入变量模板：

​	A、C++14

​	B、C++11

​	C、C++17

​	D、C++20

​	答案：A

246. 模板别名使用什么关键字：

​	A、using

​	B、typedef

​	C、define

​	D、template

​	答案：A

247. 模板参数推导发生在：

​	A、函数模板调用时

​	B、类模板定义时

​	C、模板特化时

​	D、模板实例化时

​	答案：A

248. 完美转发使用的引用类型是：

​	A、右值引用

​	B、左值引用

​	C、常引用

​	D、指针引用

​	答案：A

249. 类型萃取技术主要用于：

​	A、编译期类型检查

​	B、运行时类型识别

​	C、动态类型转换

​	D、类型安全删除

​	答案：A

250. 下列哪个不是标准类型特征：

​	A、std::is_integer

​	B、std::is_pointer

​	C、std::is_class

​	D、std::is_floating_point

​	答案：A

​	解析：A选项 std::is_integer并非标准类型特征。标准库中对应的正确写法是 std::is_integral（注意拼写差异），用于检查类型是否为整数类型（如int、char、bool等）。因此，A 是错误选项。

251. std::vector的主要特点是：

​	A、动态数组，支持快速随机访问

​	B、链表结构，支持快速插入删除

​	C、哈希表实现，支持快速查找

​	D、平衡二叉树实现，自动排序

​	答案：A

252. 下列哪个容器最适合实现先进先出(FIFO)队列：

​	A、std::queue

​	B、std::stack

​	C、std::vector

​	D、std::set

​	答案：A

253. std::map的底层实现通常是：

​	A、红黑树

​	B、哈希表

​	C、动态数组

​	D、双向链表

​	答案：A

254. 需要快速查找且不关心元素顺序时，应该使用：

​	A、std::unordered_set

​	B、std::set

​	C、std::vector

​	D、std::list

​	答案：A

255. std::array与原生数组的主要区别是：

​	A、提供成员函数和迭代器接口

​	B、存储在堆内存中

​	C、大小可以动态改变

​	D、不支持随机访问

​	答案：A

256. 下列哪个容器不支持随机访问迭代器：

​	A、std::list

​	B、std::vector

​	C、std::deque

​	D、std::array

​	答案：A

257. std::deque的特点是：

​	A、双端队列，两端都能高效插入删除

​	B、单端队列，只能尾部插入

​	C、固定大小数组

​	D、自动排序的集合

​	答案：A

258. 需要维护有序元素且允许重复时，应该使用：

​	A、std::multiset

​	B、std::set

​	C、std::unordered_set

​	D、std::vector

​	答案：A

259. std::forward_list相比std::list的主要区别是：

​	A、单向链表，节省内存

​	B、双向链表，功能更全

​	C、支持随机访问

​	D、自动排序

​	答案：A

260. 下列哪个不是关联容器：

​	A、std::vector

​	B、std::map

​	C、std::set

​	D、std::multimap

​	答案：A

261. std::unordered_map的查找时间复杂度是：

​	A、平均O(1)

​	B、O(log n)

​	C、O(n)

​	D、O(n log n)

​	答案：A

262. 需要频繁在中间位置插入元素时，最合适的容器是：

​	A、std::list

​	B、std::vector

​	C、std::array

​	D、std::deque

​	答案：A

263. std::bitset主要用于：

​	A、位级操作和标志存储

​	B、字符串处理

​	C、大整数运算

​	D、浮点数精度控制

​	答案：A

264. 下列哪个容器会自动去重：

​	A、std::set

​	B、std::vector

​	C、std::list

​	D、std::deque

​	答案：A

265. std::stack的底层容器默认是：

​	A、std::deque

​	B、std::vector

​	C、std::list

​	D、std::array

​	答案：A

266. 需要同时维护键值对和按键排序时，应该使用：

​	A、std::map

​	B、std::unordered_map

​	C、std::multimap

​	D、std::vector

​	答案：A

267. std::string本质上是：

​	A、std::basic_string<char>的特化

​	B、C风格字符串的包装

​	C、std::vector<char>的别名

​	D、独立的基本类型

​	答案：A

268. 下列哪个容器最适合实现后进先出(LIFO)：

​	A、std::stack

​	B、std::queue

​	C、std::priority_queue

​	D、std::deque

​	答案：A

269. std::priority_queue的特点是：

​	A、元素按优先级出队

​	B、元素按插入顺序出队

​	C、自动去重

​	D、支持随机访问

​	答案：A

270. 需要处理键值对且不关心顺序时，最高效的选择是：

​	A、std::unordered_map

​	B、std::map

​	C、std::multimap

​	D、std::vector

​	答案：A

271. C++ 标准容器分为哪几类？

​	A、序列容器（如`vector`, `list`）

​	B、关联容器（如`map`, `set`）

​	C、无序关联容器（如`unordered_map`, `unordered_set`）

​	D、容器适配器（如`stack`, `queue`）

​	答案：ABCD

272. 所有标准容器都支持的操作是：

​	A、`push_back()`

​	B、`size()`

​	C、`clear()`

​	D、以上都是

​	答案：B