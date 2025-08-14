# 类型转换

C++为了规范C中的类型转换，加强类型转换的可视性，引入了四种强制类型转换操作符：

+ **static_cast：**
+ **reinterpret_cast：**
+ **const_cast：**
+ **dynamic_cast：** 

## static_cast

> static_cast<type-id>(expression)

该运算符把expression转换为type-id类型，但没有运行时类型检查来保证转换的安全性。 编译器隐式执行任何类型转换都可由static_cast显示完成

+ 基本类型转换

  ```cpp
  double score = 59.5;
  int nScore = static_cast<int>(score);
  ```

+ void指针和其他类型指针之间的转换(其他类型指针之间不能转换)

  ```cpp
  void* p = new int(20);
  int* pi = static_cast<int*>(p);
  void* pc = static_cast<void*>(pi);		//这里可以隐式转换，可以省略static_cast
  delete p;
  ```

+ 用于基类派生类之间指针、引用的转换

  ```cpp
  class Base
  {
  public:
  	virtual void show()
  	{
  		std::cout << "Base " << std::endl;
  	}
  };
  
  class Derive :public Base
  {
  	char* name = nullptr;
  public:
  	Derive()
  	{
  		name = new char[5]{ "玩蛇" };
  	}
  	~Derive()
  	{
  		delete name;
  	}
  	void print()
  	{
  		std::cout << "Derive " << name << std::endl;
  	}
  };
  ```

  + **上行转换：**把派生类指针、引用转为基类的指针、引用（可以自动隐式转换）

  ```cpp
  //指针
  Derive* derive = new Derive;
  Base* base = static_cast<Derive*>(derive);
  //引用
  Derive& refDerive = *derive;
  Base& refBase = static_cast<Base&>(refDerive);
  
  delete derive;
  ```

  + **下行转换：**把基类指针、引用转为派生类的指针、引用（必须强制静态转换）

  ```cpp
  Base* base = new Base;
  Derive* derive = static_cast<Derive*>(base);
  derive->print();
  
  delete base;
  ```

  **注意：**下行转换使用`static_cast`不安全，请使用`dynamic_cast`（不安全：因为不知道基类的指针，到底是不是指向的要转换的派生类对象，如果不是，访问数据成员会有错误）

## reinterpret_cast

为操作数的位模式提供较低层的重新解释.

**主要用于以下六种情况：**

+ 任意类型指针之间的转换

  ```cpp
  int* p = nullptr;
  char* pc = reinterpret_cast<char*>(p);
  ```

+ 指针转整型，整型转指针

  ```cpp
  int* p = nullptr;
  uint64_t a = reinterpret_cast<uint64_t>(p);	//x64 指针是8个字节，所以要用uint64_t保存，否则可能会丢失数据
  double* pd = reinterpret_cast<double*>(a);
  ```

+ 函数指针也可以转换哦~

  ```cpp
  uint64_t funMax = reinterpret_cast<uint64_t>(_max);
  cout<<reinterpret_cast<int(*)(int, int)>(funMax)(2, 3);
  
  int _max(int a, int b)
  {
  	return a > b ? a : b;
  }
  ```

+ 一个官方案例

  ```cpp
  int arr[10];
  for (int i = 0; i < 10; i++)
  {
  	cout << arr+i <<"  " <<hex<< ::hash(arr+i) << endl;;
  }
  
  uint32_t _hash(void* p)
  {
  	uint64_t val = reinterpret_cast<uint64_t>(p);
  	return val ^ (val >> 32);
  }
  ```

## const_cast

const_cast用来移除类型的const属性。const_cast 中的类型必须是指针、引用或指向对象类型成员的指针

+ const指针、引用不能直接赋值给非const的对象，需要去掉const之后再赋值

  ```cpp
  const char* name = "hello";
  char* pname = const_cast<char*>(name);
  
  const int& refA = 8;
  int& refB = const_cast<int&>(refA);
  ```

+ 可以在类的const函数里面修改成员变量

  ```cpp
  class Integer
  {
  private:
  	int number;
  public:
  	Integer(int number = 0)
  		:number(number)
  	{
  	}
  	operator int()const
  	{
  		const_cast<int&>(number)++;		//必须去掉const才能修改
          const_cast<Integer*>(this)->number++;
  		return number;
  	}
  };
  
  Integer num = 10;
  int n = num;		//11
  ```

  

## dynamic_cast

dynamic_cast用于有继承关系的多态类（基类必须有虚函数）的指针或引用之间的转换。

+ 通过dynamic_cast，将派生类指针转换为基类指针（上行转换），这个操作与static_cast的效果是一样的。

+ 通过dynamic_cast，将基类指针转换为派生类指针（下行转换），dynamic_cast具有类型检查的功能，比static_cast更安全（如果转换的是指针，失败时会返回空指针；如果转换的是引用，会抛出std::bad_cast异常）



+ 指针转换，转换失败返回nullptr

  ```cpp
  	Animal* dog = new Dog;
  	dog->cry();
  	//转成实际的类型
  	Dog* d = dynamic_cast<Dog*>(dog);
  	if (!d)
  		std::cout << "dog is not Dog" << std::endl;
  	d->cry();
  	//尝试转成其他子类,失败返回nullptr
  	Cat* cat = dynamic_cast<Cat*>(dog);
  	if (!cat)
  		std::cout << "dog is not Cat";
  	else
  		cat->cry();	
  ```

+ 转换引用，转换失败抛异常std::bad_cast

  ```cpp
  Animal& refA = *dog;
  //转成实际的类型
  Dog& refD = dynamic_cast<Dog&>(refA);
  refD.cry();
  //尝试转成其他子类,失败抛异常
  Cat& refC = dynamic_cast<Cat&>(refA);
  refC.cry();
  ```

  

# 正则表达式

在很多技术领域（如：自然语言处理，数据存储等），正则表达式可以很方便的提取我们想要的信息，所以正则表达式是一个很重要的知识点！

## 概念

正则表达式（Regular Expression）是用于描述一组字符串特征的模式，用来匹配特定的字符串。通过特殊字符+普通字符来进行模式描述，从而达到文本匹配目的工具。

正则表达式目前被集成到了各种文本编辑器/文本处理工具当中。

## 应用场景

（1）验证：表单提交时，进行用户名密码的验证。

（2）查找：从大量信息中快速提取指定内容，在一批url中，查找指定url。

（3）替换：将指定格式的文本进行正则匹配查找，找到之后进行特定替换。

## 基本要素

（1）字符类

（2）数量限定符

（3）位置限定符

（4）特殊符号

注意：正则表达式基本是与语言无关的，我们可以结合语言/工具与正则表达式进行文本处理

### 1，字符类

| 字符 |                        含义                        |                             举例                             |
| :--: | :------------------------------------------------: | :----------------------------------------------------------: |
|  .   |                  匹配任意一个字符                  |                   adc.可以匹配abcd或abc6等                   |
|  []  |              匹配括号中的任意一个字符              |                    [abc]d可以匹配ad,bd,cd                    |
|  -   |                 在[]内表示字符范围                 |         [0-9a-zA-Z]可以匹配任意大写、小写和数字字符          |
|  ^   | 位于括号内的开头，匹配除括号内的字符之外的任意字符 | [^xy]z匹配xy之外的任意字符，可以匹配az、bz,但是不可以匹配xz、yz |

### 2，数量限定符

| 字符  |                   含义                   |                          举例                          |
| :---: | :--------------------------------------: | :----------------------------------------------------: |
|  ？   |    紧跟在它前面的单元应匹配零次或一次    |    [0-9]?.[0-9]匹配0.0、5.2、.3,匹配.需要使用\转义     |
|   +   |    紧跟在它前面的单元应匹配一次或多次    | [a-zA-Z0-9*]+@[a-zA-Z0-9]+.[a-zA-Z0-9*]+ 匹配email地址 |
|   *   |  紧跟在它前面的单元应匹配匹配零次或多次  |               [0-9] [0-9]*至少匹配一位数               |
|  {N}  |     紧跟在它前面的单元应精准匹配N次      |           [1-9] [0-9]{2}匹配从100到999的整数           |
| {N,}  |    紧跟在它前面的单元应匹配至少一N次     |        [1-9] [0-9]{2,}匹配大于等于三位数的整数         |
| {0,M} |     紧跟在它前面的单元应匹配最多M次      |          [0-9]{,2}匹配空或者匹配小于99的整数           |
| {N,M} | 紧跟在它前面的单元应匹配至少N次，最多M次 |       [0-9]{1,3}. [0-9]. [0-9]. [0-9]匹配IP地址        |



### 3，位置限定符

| 字符 | 含义                       | 举例                                   |
| ---- | -------------------------- | -------------------------------------- |
| ^    | 匹配行首的位置             | ^maye匹配一行开头的maye                |
| $    | 匹配行末的位置             | ;$匹配位于一行结尾的;号<br>^\$匹配空行 |
| \b   | 匹配单词开头或结尾的位置   | at\b 匹配at不能匹配att                 |
| \B   | 匹配非单词开头或结尾的位置 |                                        |



### 4，特殊符号

| 字符 | 含义                                                         | 举例                |
| ---- | ------------------------------------------------------------ | ------------------- |
| \    | 转义字符                                                     |                     |
| ()   | 将正则表达式的一部分括起来组成一个单元，可以对整个单元使用数量限定符 |                     |
| \|   | 连接两个子表达式，表示或的关系                               | n(o\|ot)匹配no或not |

### 5，其他普通字符及其替换

| 符号 | 替换正则    | 匹配                 |
| ---- | ----------- | -------------------- |
| \d   | [0-9]       | 数字字符             |
| \D   | [^0-9]      | 非数字字符           |
| \w   | [a-zA-Z0-9] | 数字、字母、下划线   |
| \W   | [^\w]       | 非数字、字母、下划线 |
| \s   | [\r\t\n\f]  | 表格、换行等空白区域 |
| \S   | [^\s]       | 非空白区域           |

## 简单练习

[Regex正则表达式在线测试、生成、解析工具 - GoRegex.cn](https://goregex.cn/)

[正则表达式在线测试 | 菜鸟工具 (runoob.com)](https://c.runoob.com/front-end/854/)

[正则表达式的语法汇总](https://blog.csdn.net/qq28129019/article/details/115913596)

## regex算法

### regex_match

全文匹配，要求整个字符串符合正则表达式的匹配规则。用来判断一个字符串和一个正则表达式是否模式匹配，如果匹配成功则返回true，否则返回false。

#### 1，是否匹配

```cpp
void match()
{
    regex pattern("<.*>.*</.*>");
    string str("<title>maye25</title>");
    bool isOk = false;
    isOk = regex_match(str.data(), pattern);                //const char*
    isOk = regex_match(str, pattern);                       //string
    isOk = regex_match(str.begin(),str.end(), pattern);     //[first last]
    if (isOk)
    {
        cout << "匹配成功" << endl;
    }
    else
    {
        cout << "匹配失败" << endl;
    }
}
```

#### 2，匹配结果

更多的时候我们希望能够获得匹配结果（字符串），对结果进行操作。这时就需要对匹配结果进行存储

```cpp
void matchGetResult()
{
    regex pattern("<title.*>.*</title>");
    string str("<title>maye25</title>");
    //1,使用要匹配的字符串类型为const char*，对应的匹配结果类型为cmatch
    cmatch result;
    bool isOk = false;
    isOk = regex_match(str.data(), result, pattern);        //const char* <==> cmatch
    
    //2,使用要匹配的字符串类型为string，对应的匹配结果类型为smatch
    smatch result_it;
    isOk = regex_match(str, result_it, pattern);
    
    if (isOk)
    {
        cout << "匹配成功" << endl;
        for (auto& r : result)
        {
            cout << r.str() << endl;

        }
    }
    else
    {
        cout << "匹配失败" << endl;

    }
}
```



### regex_search

搜索匹配，根据正则表达式来搜索字符串中是否存在符合规则的子字符串。

#### 1，是否查找到

```cpp
void search()
{
    regex pattern("<img.*/>");
    string str("<title>maye25</title>\n<img src='maye/haha.png'/>\n<img/>\n<img/ src=''/>");

    bool isOk = regex_search(str, pattern);
    if (isOk)
    {
        cout << "查找到了 " << endl;
    }
    else
    {
        cout << "没有找到哟~" << endl;
    }
}
```

#### 2，查找并存储结果

```cpp
void searchGetResult()
{
    regex pattern("<img.*/>");
    string str("<title>maye25</title>\n<img src='maye/haha.png'/>\n<img/>\n<img src=''/>");

    smatch result;
    //找到一个匹配的之后，立马返回
    bool isOk = regex_search(str, result,pattern);
    if (isOk)
    {
        cout << "查找到了 "<<result.size()<<"个" << endl;
        for (auto& r : result)
        {
            cout << r.str() << endl;
            //r.first 为匹配到的序列的开始
            //r.second 为匹配到的序列的最后一个位置
            //注意:返回的都是str的迭代器
            cout << *r.first << " " << *r.second << endl;
            cout << (r.first - str.cbegin()) << " " << (r.second  - str.begin())<< endl;
        }
    }
    else
    {
        cout << "没有找到哟~" << endl;
    }
}
```

#### 3，查找所有(循环查找)

```cpp
void loopSearch()
{
    regex pattern("<img.*/>");
    string str("<title>maye25</title>\n<img src='maye/haha.png'/>\n<img/>\n<img src=''/>");

    smatch result;
    bool isOk = false;
    cout << "loop search 1" << endl;
    //循环查找1(不推荐)，所有满足条件的
    string s = str;
    do
    {
        isOk = regex_search(s, result, pattern);
        if (isOk)
        {
            for (auto& r : result)
            {
                cout << r.str() << endl;
                //cout <<"---" << *r.first << *(r.first + 5) << " " << *r.second << *(r.second + 5) << endl;
                s.assign(r.second,s.cend());    //这种方式不好，每次都要拷贝
            }
            
        }

    } while (isOk);
    cout << "loop search 2" << endl;
    //循环查找2(推荐)，所有满足条件的
    auto csit = str.cbegin();
    do
    {
        isOk = regex_search(csit,str.cend(), result, pattern);
        if (isOk)
        {
            for (auto& r : result)
            {
                cout << r.str() << endl;
                //cout <<"---" << *r.first << *(r.first + 5) << " " << *r.second << *(r.second + 5) << endl;
                //s.assign(r.second, s.cend()); //这种方式不好，每次都要拷贝
                csit = r.second;
            }
        }

    } while (isOk);
}
```



### regex_replace

替换匹配，即可以将符合匹配规则的子字符串替换为其他字符串。要求输入一个正则表达式，以及一个用于替换匹配子字符串的格式化字符串。

#### 1,替换

```cpp
void replace()
{
    regex pattern("(hi|u|c)");
    string str = "oh!shit!fuck you!";
    cout<< regex_replace(str, pattern,"*");
}
```

以上代码会把str中所有的hi|u|uc替换成*，并返回一个新的string对象(str没有改变)，如果只想替换第一个匹配的，可以给`regex_replace`加上标志。

```
regex_replace(str, pattern,"*",regex_constants::format_first_only);
```

这样的话就只会把shit变为s*t,其他的不会改变。关于标志请参考[微软文档](https://learn.microsoft.com/zh-cn/cpp/standard-library/regex-constants-class?view=msvc-170)。

**除了以上方法之外还有一种方法操作。**

```cpp
    //1，复制 [first,last) 中的字符到 out ，以 re 所格式化的字符替换任何匹配 fmt 的序列
    //string output;
    //output.resize(str.size());    //注意访问越界问题
    //regex_replace(output.begin(), str.cbegin(), str.cend(), pattern, "*");
    //cout << "output:" << output << endl;
    //1.1同上，只不过传入的是char*数组
    char buf[1024] = {0};
    regex_replace(buf, str.cbegin(), str.cend(), pattern, "*");
    cout << "buf:" << buf << endl;

    //1.2 写结果到输出迭代器
    regex_replace(std::ostreambuf_iterator<char>(std::cout), str.begin(), str.end(), pattern, "*");
```

## regex迭代

正则表达式迭代器用于遍历序列中找到的整个正则表达式匹配集。

### [regex_iterator](https://en.cppreference.com/w/cpp/regex/regex_iterator)

 循环访问字符序列中与正则表达式匹配的项。

```cpp
void test_regex()
{
    std::string s = "I am maye";
    std::regex regex("[^\\s]+");
    
    std::sregex_iterator words_begin(s.cbegin(), s.cend(), regex);
    std::sregex_iterator words_end;

    std::cout << "found "<<std::distance(words_begin,words_end) << " words:\n";

    for (auto it = words_begin;it!=words_end;it++)
    {
        auto match_res = *it;
        std::cout << match_res.str() << "\n";
    }
}
```

### [regex_token_iterator](https://en.cppreference.com/w/cpp/regex/regex_token_iterator)

  循环访问给定字符串中所有正则表达式匹配项中的指定子表达式，或通过不匹配的子字符串 （类模板） 

#### 基本使用

```cpp
{
    const char* str = "aaxaayaaz";
    size_t len = strlen(str);

    std::regex regex("(a)a");

    std::cregex_token_iterator next(str, str + len, regex);
    std::cregex_token_iterator end;

    //展示完整匹配
    for (; next != end; next++)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

    //展示匹配之前的前缀(相当于按匹配的项对字符串进行分隔)
    next = std::regex_token_iterator(str, str + len, regex,-1);
    for (; next != end; next++)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

    //只展示(a)子匹配,因为regex("(a)a");只有一组，所以sub指定为1
    next = std::regex_token_iterator(str, str + len, regex, 1);
    for (; next != end; next++)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

    //同时展示前缀和子匹配
    std::vector<int> vec;
    vec.push_back(-1);
    vec.push_back(1);
    next = std::regex_token_iterator(str, str + len, regex, vec);
    for (; next != end; next++)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

    //同时展示前缀和完整匹配
    int arr[]{ -1,0 };
    next = std::regex_token_iterator(str, str + len, regex, arr);
    for (; next != end; next++)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

}
```

#### 小案例

##### 拆分单词

把英文字符串中每个单词拿出来。

```
{
    std::string text = "I am maye,and you ?";
    std::regex rx("[\\s.,?]+");
    
    std::sregex_token_iterator next(text.begin(), text.end(), rx, -1);
    std::sregex_token_iterator end;

    for (; next != end; next++)
        std::cout << next->str() << std::endl;
    std::cout << std::endl;
}
```

正则`[\s.,?]+`表示匹配空白字符、点、逗号、问号中的任意一个，后面有+号，表示可以出现一次或多次。简单来说就是按空白字符、点、逗号、问号对字符串进行分割。

##### 获取\<a>超链接

```
{
    std::string html = "<p><a href='https://www.baidu.com'>百度一下</a></p>"
        "< a   HREF='https://www.baidu.com'>百度一下</a>";


    std::regex rx("<\\s*a\\s+href\\s*=\\s*'([^']+)'\\s*>", std::regex::icase);

    std::sregex_token_iterator next(html.begin(), html.end(), rx, 1);
    std::sregex_token_iterator end;

    for (; next != end; next++)
        std::cout << next->str() << std::endl;
    std::cout << std::endl;

}
```

## 贪婪与非贪婪模式

贪婪与非贪婪模式影响的是被量词修饰的子表达式的匹配行为，贪婪模式在整个表达式匹配成功的前提下，尽可能多的匹配，而非贪婪模式在整个表达式匹配成功的前提下，尽可能少的匹配。

属于贪婪模式的量词，也叫做匹配优先量词，包括： `{m,n}`、`{m,}`、`?`、`*`和`+`。

在匹配优先量词后加上“?”，即变成属于非贪婪模式的量词，也叫做忽略优先量词，包括： `{m,n}?`、`{m,}?`、`??`、`*?`和`+?`。

从正则语法的角度来讲，被匹配优先量词修饰的子表达式使用的就是贪婪模式，如`(Expression)+`；被忽略优先量词修饰的子表达式使用的就是非贪婪模式，如`(Expression)+?`。 

**举个栗子：**

```cpp
std::string s = "hello 1234567 world";
std::regex rx("he.*(\\d+).*rld$");
std::smatch match;
if (std::regex_match(s, match, rx))
{
    std::cout << match[1] << std::endl;
}
```

这里要获取中间的数字，正则表达式这样写看似没什么问题，但是运行结果却只有 **7** ，这是怎么回事呢？

默认是贪婪匹配的，在贪婪匹配下，.* 会匹配尽可能多的字符。正则表达式中.*后面是\d+，也就是至少一个数字，并没有指定具体多少个数字，因此，.*就尽可能匹配多的字符，这里就把123456匹配了，给\d+留下个可满 足条件的数字 7。最后得到的内容就只有数字7了。

但这很明显会给我们带来很大的不便。有时候，匹配结果会莫名其妙少了部分内容。 其实，这里只需要使用非贪婪匹配就好了。非贪婪匹配的写法是.*?，多了一个?，那么它可以达到怎样的效果?

```cpp
std::regex rx("he.*?(\\d+).*rld$");
```

这里我们只是将第一个.*改成了.*? 这样就转变为非贪婪匹配了。

此时就可以成功获取1234567了。原因可想而知，贪婪匹配是尽可能匹配多的字符，非贪婪匹配就是尽叮能匹配少的字符。当.*?匹配到hello后面的空白字符时，再往后的字符就是数字了，而\d+恰好可以匹配，那么这里. *?就不再进行匹配，交给\d+去匹配后面的数字。所以这样，*?匹配了尽可能少的字符，\d+ 的结果就是1234567了。
