# 从C语言到C++

## C语言和C++

C++ 和C语言虽然是两门独立的语言，但是它们却有着扯也扯不清的关系。早期并没有“C++”这个名字，而是叫做“带类的C”。“带类的C”是作为C语言的一个扩展和补充出现的，它增加了很多新的语法，目的是提高开发效率。

这个时期的 C++ 非常粗糙，仅支持简单的面向对象编程，也没有自己的编译器，而是通过一个预处理程序（名字叫 cfront），先将 C++ 代码”翻译“为C语言代码，再通过C语言编译器合成最终的程序。
随着 C++ 的流行，它的语法也越来越强大，已经能够很完善的支持面向过程编程、面向对象编程（OOP）和泛型编程，几乎成了一门独立的语言，拥有了自己的编译方式。

我们很难说 C++ 拥有独立的编译器，例如 Windows 下的微软编译器（MSVC）、Linux 下的 GCC 编译器、Mac 下的 Clang 编译器，它们都同时支持C语言和 C++，统称为 C/C++ 编译器。对于C语言代码，它们按照C语言的方式来编译；对于 C++ 代码，就按照 C++ 的方式编译。

从表面上看，C、C++ 代码使用同一个编译器来编译，所以上面我们说“后期的 C++ 拥有了自己的编译方式”，而没有说“C++ 拥有了独立的编译器”。

从语法上看，C语言是 C++ 的一部分，C语言代码几乎不用修改就能够以 C++ 的方式编译。



## 头文件

C++为了兼容C，支持所有的C头文件，但为了符合C++标准，所有的C头文件都有一个C++版本的，即去掉.h，并在名子前面加c。如\<cstring>和\<cmath>。

|  C语言   |   C++    |
| :------: | :------: |
| stdio.h  | iostream |
|  math.h  |  cmath   |
| string.h | cstring  |
| stdlib.h | cstdlib  |
|  ......  |  ......  |

## 命名空间

假设这样一种情况，当一个班上有两个名叫 maye的学生时，为了明确区分它们，我们在使用名字之外，不得不使用一些额外的信息，比如他们的家庭住址，或者他们父母的名字等等。

同样的情况也出现在 C++ 中。比如有两个相同的变量m，编译器就无法判断你使用的是哪个变量m。

+ 为了解决上输入问题，引入了命名空间这个概念，它可作为附加信息来区分不同库中相同名称的函数、类、变量等。本质上，命名空间就是定义了一个范围。
  定义方式：

  ```c++
  namespace name			//name为自定义命名空间名
  {
  	//代码声明
  }
  ```

  使用方式：

  ```cpp
  name::code;					//code可以是变量或函数...
  using  name::code;			//只使用name下面的code
  using namespace name;		//使用name里面的所有内容
  ```

  

## 输入输出

C语言的的输入输出用的主要是scanf()、printf()函数，而C++是使用类对象cin、cout进行输入输出。

```cpp
int a;
double b;
char name[20];
cin >> a >> b >> name;
cout << a << b << name;
```

+ cin 输入流对象

+ cout 输出流对象

+ endl 换行，并清空输出缓冲区(end line 结束一行，并另起一行)

+ \n照样可以在cout中使用

  

## 基本数据类型

C++和C的基本数据类型几乎一样

```cpp 
char 	short 	int  long long	float 	double 	unsigned 	signed ...
```

值得注意的是，C语言中虽然也有bool(布尔类型)，但是需要包含头文件<stdbool.h>,而在C++中则不用，直接使用即可。

布尔类型对象可以被赋予文字值true或false，所对应的关系就是真与假的概念，即1,0。

可以使用boolalpha打印出bool类型的true或false

```cpp
bool cmpare(int a,int b)
{
    return a > b;
}
cout << boolalpha << compare(2,3) << endl;
```



### 强弱类型

C语言：强类型，弱检查—— 一般就叫做弱类型了

```c
void* p = NULL;
int* p1 = p;

int* pn = NULL;
void* pp = pn;
//无报错，无警告，完美
```



C++：强类型，强检查   ——  真正意义上的强类型

```cpp
void* p = NULL;
int* p1 = p;		//错误	“初始化”: 无法从“void *”转换为“int *”

int* pn = NULL;
void* pp = pn;		//正确	任意类型的指针都可以自动转为万能指针
```



### NULL和nullptr

NULL是给指针赋值的，表示指针指向的是空，nullptr 出现的目的是为了替代 NULL。

在C语言中NULL会被定义成(void*)NULL，但是C++不允许直接将 void * 隐式转换到其他类型，NULL 只好被定义为 0。



### const

``C语言中的冒牌货``：C语言中的const并不是真正的常量，只是表示const修饰的变量为只读。

```cpp
const int age = 18;
//age = 19;			//error C2166: 左值指定 const 对象
int* pt = (int*)&age;
*pt = 19;
printf("%d %d\n", age,*pt);	
//output 19  19
```

+ 可以看到常量it的值已经通过指针被间接改变

``C++中的真货``:

```cpp
const int age = 18;
//age = 19;			//error C3892: “age”: 不能给常量赋值
int* pt = (int*)&age;
*pt = 19;
printf("%d %d\n", age,*pt);
//output 18 19
```

+ 明明已经通过指针修改了a值，为什么输出却没有变呢？

+ **解释**：
  C++编译器当碰见常量声明时，在符号表中放入常量，那么如何解释取地址呢？
  编译过程中若发现对const使用了&操作符，则给对应的常量分配存储空间（为了兼容C）

  ![image-20210130153947983](%E4%BB%8EC%E8%AF%AD%E8%A8%80%E5%88%B0C++.assets/image-20210130153947983.png)



**const参数不匹配的情况**

```cpp
void show(char* name)
{
	cout << name << endl;
}

show("maye");	//"const char *" 类型的实参与 "char *" 类型的形参不兼容
//需要给函数形参加上const

char* name = "maye";		//错误
const char*name ="maye";	//正确
```





## 变量的初始化

在C++中变量的初始化，又有了奇葩的操作(极度猥琐)

### 1，背景

 在C++语言中，**初始化**与**赋值**并不是同一个概念：

  **初始化**：**创建变量时**赋予其一个初始值。

  **赋值**：把对象（已经创建）的**当前值**擦除，而用一个**新值**来代替。

### 2，列表初始化

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

### 3，直接初始化

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



## 三目运算符

+ 在C语言中，条件表达式只能做左值

+ 在C++中条件表达式能做左值和右值

```cpp
	int a = 2;
	int b = 10;
	int max;

	max = a > b ? a : b;	//C √  C++ √
	a > b ? a : b = 520;	//C×	C++ √
```

**思考:**为什么呢？怎么让C语言也能够实现，条件表达式作为左值呢？

```cpp
//让表达式返回地址即可
*(a > b ? &a : &b) = 520;
```



## new/delete和malloc/free

在软件开发过程中，常常需要动态地分配和释放内存空间，例如对动态链表中结点的插入与删除。在C语言中是利用库函数malloc和free来分配和释放内存空间的。C++提供了较简便而功能较强的运算符new和delete来取代malloc和free函数。
注意： new和delete是运算符，不是函数，因此执行效率高。

**new申请内存**

```cpp
指针变量 = new 类型;			//申请内存的时候初始化
指针变量 = new 类型[size];	 //申请数组，创建数组时不能指定初始值
```

**delete释放内存**

```cpp 
delete 指针变量;	//释放单个对象
delete[] 指针变量;  //释放数组
```

**示例：**

```cpp
/*new普通数据*/
int* p = new int;
*p = 8;
cout << *p << endl;
delete p;
/*new普通数据，并初始化*/
int* p1 = new int(20);
cout << *p1 << endl;
delete p1;
/*new数组*/
int* p2 = new int[5];
for (int i = 0; i < 5; i++)
{
	p2[i] = i;
	cout << p2[i] << " ";
}
delete[] p2;
/*new数组，并初始化*/
int* p3 = new int[5]{9,8,7,6,5};
for (int i = 0; i < 5; i++)
{
	cout << p3[i] << " ";
}
delete[] p3;
```

**小结：**

+ new 和 malloc不要混用
+ 分配内存使用完，记得释放内存(数组和普通变量释放有些微区别)



## 引用

### 什么是引用？

引用，顾名思义是某一个变量或对象的**别名**，对引用的操作与对其所绑定的变量或对象的操作完全等价

```cpp
语法：类型 &引用名=目标变量名;
```

```c++
//在函数内部改变实参的值需要传变量的地址
void fun(int* n)
{
	*n=18;
}
//指针是非常危险的，因为指针所指向的内存空间，不确定，需要额外判断
fun(nullptr);	//传nullptr 会发生中断，当然，你可以在函数里面判断是否是空，但是如果是野指针呢？

//在C++中，除了使用指针外，还可以通过引用来达到这个目的
void fun(int& n)
{
	n=18;
}
```

**注意事项：**

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

+ 通过使用引用来替代指针，会使 C++ 程序更容易阅读和维护



**引用的用处：**

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

### 引用的本质

引用如此神奇，那么引用的本质到底是什么呢？

+ 引用在C++中，内部实现是一个常指针：type &name <==> type*const name
+ C++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同。
+ 从使用的角度，引用会让人误会其只是一个别名，没有自己的存储空间。这是C++为了实用性而做出的细节隐藏(所以我们查看不了引用的地址)



## 枚举类型

C语言和C++语言都提供了枚举类型，两者是有一定区别。

``有如下定义：``

```cpp
enum SHAPE {CIRCLE,RECT,LINE,POINT};
enum WEEK  {MON,TUE,WED,THI,FIR,SAT,SUN};
```

### 1，C语言中的enum

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



### 2，C++中的enum

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



### 3,C++中的 enum class 强枚举类型

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

### **小结**

+ C 枚举类型支持不同类型枚举值之间赋值、以及数字赋值、比较，并且具有外层作用域。

+ C++ 中枚举不允许不同类型的值给枚举类型变量赋值，但仍然支持不同类型之间枚举进行比较，枚举符号常量具有外层作用域。

+ C++ 强枚举类型不允许不同类型之间的赋值、比较，枚举常量值并不具有外层作用域。



## 进制前缀

```cpp
//十进制
int dec = 520;
//八进制
int oct = 01010;
//二进制
int bin = 0b1000001000;
//十六进制
int hex = 0x208;
```

+ 还有一个好玩的哦，``0b1000001000``  对于这么长的二进制，如果不每隔4个位或8个位分开一下，会眼花缭乱
+ 用单引号隔开数字即可

```cpp
int bin = 0b10'0000'1000;
```



## auto自动类型推导

在 C++11 之前的版本中，定义变量或者声明变量之前都必须指明它的类型，比如 int、char 等；但是在一些比较灵活的语言中，比如 JavaScript、PHP、Python 等，程序员在定义变量时可以不指明具体的类型，而是让编译器（或者解释器）自己去推导，这就让代码的编写更加方便。

C++11 为了顺应这种趋势也开始支持自动类型推导了！C++11 使用 auto 关键字来支持自动类型推导。

注意：auto 仅仅是一个占位符，在编译器期间它会被真正的类型所替代。或者说，C++ 中的变量必须是有明确类型的，只是这个类型是由编译器自己推导出来的。

+ 使用 auto 类型推导的变量必须马上初始化
+ auto 不能在函数的参数中使用(但是能作为函数的返回值)
+ auto 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中
+ auto 关键字不能定义数组
+ auto 不能作用于模板参数



## for循环

对于一个有范围的集合而言，由程序员来说明循环的范围是多余的，有时候还会容易犯错误。
因此C++中引入了基于范围的for循环，for循环后的括号由冒号“ ：”分为两部分：第一部分是范围内用于迭代的变量，第二部分则表示被迭代的范围

```cpp
int arr[]={1,2,3,4,5,6,7};
//一般用法
for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
{
    cout<<arr[i]<<" ";
}
//新用法
for(int i:arr)
{
     cout<<i<<" ";
}
```

**特点：**

+ 从数组的第一个元素开始，逐个赋值给迭代变量
+ 不依赖于下标元素，通用



## typeid

typeid 运算符用来获取一个表达式的类型信息。

``typeid 的操作对象既可以是表达式，也可以是数据类型，下面是它的两种使用方法：``

```cpp
typeid( dataType )
typeid( expression )
```

dataType 是数据类型，expression 是表达式，这和 sizeof 运算符非常类似，只不过 sizeof 有时候可以省略括号`( )`，而 typeid 必须带上括号。

typeid 会把获取到的类型信息保存到一个 type_info 类型的对象里面，并返回该对象的常引用；当需要具体的类型信息时，可以通过成员函数来提取。

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

本例中还用到了 type_info 类的几个成员函数，下面是对它们的介绍：

- name() 用来返回类型的名称。
- raw_name() 用来返回名字编码（Name Mangling）算法产生的新名称。。
- hash_code() 用来返回当前类型对应的 hash 值。hash 值是一个可以用来标志当前类型的整数，有点类似学生的学号、公民的身份证号、银行卡号等。不过 hash 值有赖于编译器的实现，在不同的编译器下可能会有不同的整数，但它们都能唯一地标识某个类型。

**除此之外，还可以用 == 比较两个类型是否相等**

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



## 函数

### 内联函数

函数调用时，需要跳转到函数的地址去执行，执行完成后返回到被调用函数，比较费时，因此，C++中提供了一种操作方式，允许编译时直接把函数替换到调用处，即内联函数。在函数前面加上inline申明为内联函数。

**为什么使用内联函数？**
内联函数没有普通函数调用时的额外开销(压栈，跳转，返回)

**注意：**

+ 内联函数声明时inline关键字必须和函数定义结合在一起，否则编译器会直接忽略内联请求。
+ C++编译器不一定准许函数的内联请求！(只是对编译器的请求，因此编译器可以拒绝)
+ 现代C++编译器能够进行编译优化，因此一些函数即使没有inline声明，也可能被编译器内联编译
  **C++中内联函数的限制：**
  + 不能存在任何形式的循环语句 
  + 不能存在过多的条件判断语句
  + 函数体不能过于庞大
  + 不能对函数进行取址操作
  + 编译器对于内联函数的限制并不是绝对的，内联函数相对于普通函数的优势只是省去了函数调用时压栈，跳转和返回的开销。因此，当函数体的执行开销远大于压栈，跳转和返回所用的开销时，那么内联将无意义。



### 函数默认参数

定义函数时可以给形参指定一个默认的值，这样调用函数时如果没有给这个形参赋值（没有对应的实参），那么就使用这个默认的值。也就是说，调用函数时可以省略有默认值的参数。如果用户指定了参数的值，那么就使用用户指定的值，否则使用参数的默认值。

```cpp
void showX(int x = 666)
{
    cout<<"x:"<<x<<endl;
}
showX();
showX(6);
```

**小结：**

+ 有函数声明时，默认参数可以放在声明或定义中，但不能同时存在

```cpp
int add(int a,int b = 5);
int add(int a,int b)
{
    return a+b;
}
```

+ 在具有多个参数的函数中指定默认值时,默认参数都必须出现在不默认参数的右边,一旦某个参数开始指定默认值,它右边的所有参数都必须指定默认值.

    也就是说，**函数声明时，必须按照从右向左的顺序，依次给与默认值。**

```cpp
int foo(int a, int b = 2, int c = 3);     // 正确
int foo1(int a, int b = 2, int c);         // 错误, i3未指定默认值
int foo2(int a = 1, int b, int c = 3);     // 错误, i2未指定默认值
```



### 占位参数

定义函数时，还可以给函数提供占位参数

+ 占位参数只有参数类型，而没有参数名
+ 在函数体内部无法使用占位参数
+ 占位参数也可以指定默认参数

```cpp
void func(int a,int = 0)
{
    cout<<a<<endl;
}
func(2);
```



### 函数重载

函数重载是指在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。重载函数通常用来命名一组功能相似的函数，这样做减少了函数名的数量，对于程序的可读性有很大的好处。

**不同参数列表：**

+ 参数个数不同
+ 参数类型不同
+ 参数顺序不同
+ 函数重载与返回值类型无关

``来个例子体会一下，比较不同类型的两个变量的大小``

```cpp
int maxmum(int a, int b)
{
	return a > b?a:b;
}
long maxmum(long int a, long int b)
{
	return a > b ? a : b;
}
char maxmum(char a, char b)
{
	return a > b ? a : b;
}
double maxmum(double a, double b)
{
	return a > b ? a : b;
}
const char* maxmum(const char* str1,const char* str2)
{
	return strcmp(str1, str2)==1?str1:str2;
}
char* maxmum(char* str1, char* str2)
{
	return strcmp(str1, str2) == 1 ? str1 : str2;
}

int main()
{
	cout << maxmum(2, 6) << endl;
    cout << maxmum(2L, 6L) << endl;
	cout << maxmum('A', 'C') << endl;

	cout << maxmum("maye", "MAYE") << endl;
	char str1[] = "hello";
	char str2[] = "hello";
	cout << maxmum(str1, str2) << endl;
	return 0;
}
```

函数重载可以根据具体的参数去决定调用哪一个函数。

#### 为什么需要函数重载？

- 试想如果没有函数重载机制，如在C中，你必须要这样去做：为这个maxmum函数取不同的名字，如maxmum_int、maxmum_string等等。这里还只是简单的几种情况，如果是很多个的话，就需要为实现同一个功能的函数取很多个名字，这样做很不友好！
- 类的构造函数跟类名相同，也就是说：构造函数都同名。如果没有函数重载机制，要想实例化不同的对象，那是相当的麻烦！
- 操作符重载，本质上就是函数重载，它大大丰富了已有操作符的含义，方便使用，如+可用于连接字符串等！



#### **重载函数的调用匹配规则**

为了估计哪个重载函数最适合，需要依次按照下列规则来判断：

- **精确匹配**：参数匹配而不做转换，或者只是做微不足道的转换，如数组名到指针、函数名到指向函数的指针；
- **提升匹配**：即整数提升（如bool 到 int、char到int、short 到int），float到double
- **使用标准转换匹配**：如int 到double、double到int、double到long double、Derived*到Base*、T*到void*、int到unsigned int；
- **编译器傻了**：如果在最高层有多个匹配函数找到，调用将被拒绝（因为有歧义、模凌两可）



### 函数重载遇上默认参数

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



## string

**to_string(T val)       **``将数值转化为字符串，返回对应的字符串。``

在C语言中，我们经常使用字符串，但要对字符串进行操作的时候，我们需要使用一些函数进行操作，但也非常麻烦，那么在C++中有没有更好的字符串操作方法呢？

不用多说，肯定是有的，C++ 标准库提供了 string 类型，支持C语言字符串所有的操作，另外还增加了其他更多的功能。(现在我们可能还无法透彻地理解string，因为到目前为止我们还没有讨论类和对象。所以现在粗略地了解下即可，等理解了面向对象的概念之后再回头来理解。)

注意:需要包含头文件#include<string>和命名空间std

```cpp
//初始化
string name= "maye";
string name("maye");
string nm = name;
//输出
cout<<name<<endl;
cout<<name.data()<<endl;	//转成const char*输出
...
```

