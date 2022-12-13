## 标准头文件

C系统提供了丰富的系统文件，称为库文件。在".h"文件中包含了常量定义、 类型定义、宏定义、函数原型以及各种编译选择设置等信息。

这些头文件为我们提供了大量的功能，并通过函数提供给我们，我们无需自己重复写代码时间，包含头文件，调用函数即可。

| 头文件    | 描述                                                         |
| --------- | :----------------------------------------------------------- |
| assert.h  | 头文件提供了一个名为 assert 的宏，它可用于验证程序做出的假设，并在假设为假时输出诊断消息。 |
| stdarg.h  | 提供了一些函数，可用于测试和映射字符。                       |
| ctype.h   | 定义了一批C语言字符分类函数（C character classification functions），用于测试字符是否属于特定的字符类别，如字母字符、控制字符等等 |
| limits.h  | 用于检测整型数据数据类型的表达值范围。                       |
| stdint.h  | 定义了几种扩展的整数类型和宏                                 |
| setjump.h | 提供了一种不同于通常的函数调用和返回顺序的方式，特别是，它允许立即从一个深层嵌套的函数调用中返回。 |
| stdio.h   | 定义了四个变量类型、两个宏和各种操作日期和时间的函数。       |
| stdlib.h  | 即standard library标准库头文件。stdlib.h里面定义了五种类型、一些宏和通用工具函数。 <br>**类型：**例如size_t、wchar_t、div_t、ldiv_t和lldiv_t； <br>**宏：**例如EXIT_FAILURE、EXIT_SUCCESS、RAND_MAX和MB_CUR_MAX等等；<br>**常用的函数：**如malloc()、calloc()、realloc()、free()、system()、atoi()、atol()、rand()、srand()、exit()等等。 |
| string.h  | 定义了一个变量类型、一个宏和各种操作字符数组的函数。         |
| time.h    | 是C语言中的日期和时间头文件。用于需要时间方面的函数。        |
| math.h    | 定义了各种数学函数。在这个库中所有可用的功能都带有一个 double 类型的参数，且都返回 double 类型的结果。 |

### assert.h

#### 简介

C 标准库的 **assert.h**头文件提供了一个名为 **assert** 的宏，它可用于验证程序做出的假设，并在假设为假时输出诊断消息。

#### 库宏

下面列出了头文件 assert.h 中定义的唯一的函数：

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | <span style = "font-size:18px;color:rgb(0,102,0)" >void assert(int expression)</span><br />这实际上是一个宏，不是一个函数，可用于在 C 程序中添加诊断。 |



### stdarg.h

#### 简介

**stdarg.h** 头文件定义了一个变量类型 **va_list** 和三个宏，这三个宏可用于在参数个数未知（即参数个数可变）时获取函数中的参数。

可变参数的函数通在参数列表的末尾是使用省略号(,...)定义的。

#### 库变量

下面是头文件 stdarg.h 中定义的变量类型：

| 序号 | 变量 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | **va_list** 这是一个适用于 **va_start()、va_arg()** 和 **va_end()** 这三个宏存储信息的类型。 |

#### 库宏

下面是头文件 stdarg.h 中定义的宏：

| 序号 | 宏 & 描述                                                    |
| :--- | :----------------------------------------------------------- |
| 1    | void va_start(va_list ap, last_arg)这个宏初始化 **ap** 变量，它与 **va_arg** 和 **va_end** 宏是一起使用的。**last_arg** 是最后一个传递给函数的已知的固定参数，即省略号之前的参数。 |
| 2    | type va_arg(va_list ap, type) 这个宏检索函数参数列表中类型为 **type** 的下一个参数。 |
| 3    | void va_end(va_list ap)这个宏允许使用了 **va_start** 宏的带有可变参数的函数返回。如果在从函数返回之前没有调用 **va_end**，则结果为未定义。 |

#### VA_LIST的用法

+ 首先在函数里定义一具VA_LIST型的变量，这个变量是指向参数的指针；
+ 然后用VA_START宏初始化变量刚定义的VA_LIST变量；
+ 然后用VA_ARG返回可变的参数，VA_ARG的第二个参数是你要返回的参数的类型（如果函数有多个可变参数的，依次调用VA_ARG获取各个参数）；
+ 最后用VA_END宏结束可变参数的获取。

```c
//以下都是带参宏
_INTSIZEOF(n)   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1)) 

va_start(ap,v)	((void)(ap = (va_list)&v + _INTSIZEOF(v)))
va_arg(ap,t)	(*(t*)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))   
va_end(ap)		((void)(ap = (va_list)0))   
```

```c
//自己实现
typedef  char* my_list;
#define my_start(ap,v) ((ap = (my_list)&v + sizeof(v)))
#define my_arg(ap,t)	(*(t*)((ap+=sizeof(t))-sizeof(t)))
#define my_end(ap)		((ap=(my_list)0))
void fun(int n, ...)
{
	my_list list;
	my_start(list, n);

	for (int i = 0; i < n; i++)
	{
		int val = my_arg(list, int);
		printf("%d ", val);
	}
	my_end(list);
}
```



#### 使用VA_LIST应该注意的问题

+ 因为va_start, va_arg, va_end等定义成宏,所以它显得很愚蠢,可变参数的类型和个数完全在该函数中由程序代码控制,它并不能智能地识别不同参数的个数和类型. 也就是说,你想实现智能识别可变参数的话是要通过在自己的程序里作判断来实现的.
+ 另外有一个问题,因为编译器对可变参数的函数的原型检查不够严格,对编程查错不利.不利于我们写出高质量的代码。
+ 由于参数的地址用于VA_START宏，所以参数不能声明为寄存器变量，或作为函数或数组类型。

### ctype.h

#### 简介

C 标准库的 **ctype.h** 头文件提供了一些函数，可用于测试和映射字符。

这些函数接受 **int** 作为参数，它的值必须是 EOF 或表示为一个无符号字符。

如果参数 c 满足描述的条件，则这些函数返回非零（true）。如果参数 c 不满足描述的条件，则这些函数返回零。

#### 库函数

下面列出了头文件 ctype.h 中定义的函数：

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isalnum(int c)</span><br />该函数检查所传的字符是否是字母和数字。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isalpha(int c)</span><br />该函数检查所传的字符是否是字母。 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >int iscntrl(int c)</span><br />该函数检查所传的字符是否是控制字符。 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isdigit(int c)</span><br />该函数检查所传的字符是否是十进制数字。 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isgraph(int c)</span><br />该函数检查所传的字符是否有图形表示法。 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >int islower(int c)</span><br />该函数检查所传的字符是否是小写字母。 |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isprint(int c)</span><br />该函数检查所传的字符是否是可打印的。 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >int ispunct(int c)</span><br />该函数检查所传的字符是否是标点符号字符。 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >int isspace(int c)</span><br />该函数检查所传的字符是否是空白字符。 |
|  10  | <span style = "font-size:18px;color:rgb(0,102,0)" >int isupper(int c)</span><br />该函数检查所传的字符是否是大写字母。 |
|  11  | <span style = "font-size:18px;color:rgb(0,102,0)" >int isxdigit(int c)</span><br />该函数检查所传的字符是否是十六进制数字。 |

标准库还包含了两个转换函数，它们接受并返回一个 "int"

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >int tolower(int c)</span><br />该函数把大写字母转换为小写字母。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >int toupper(int c)</span><br />该函数把小写字母转换为大写字母。 |

#### 字符类型

| 序号 | 字符类型     | 描述                                                         |
| ---- | ------------ | ------------------------------------------------------------ |
| 1    | 数字         | 完整的数字集合 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }              |
| 2    | 十六进制数字 | 集合 { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }         |
| 3    | 小写字母     | 集合 { a b c d e f g h i j k l m n o p q r s t u v w x y z } |
| 4    | 大写字母     | 集合 {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }  |
| 5    | 字母         | 小写字母和大写字母的集合                                     |
| 6    | 字母数字     | 数字、小写字母和大写字母的集合                               |
| 7    | 标点符号     | 集合 ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { |
| 8    | 图形字符     | 字母数字字符和标点符号字符的集合                             |
| 9    | 空格字符     | 制表符、换行符、垂直制表符、换页符、回车符、空格符的集合。   |
| 10   | 可打印字符   | 字母数字字符、标点符号字符和空格字符的集合。                 |
| 11   | 控制字符     | 在 ASCII 编码中，这些字符的八进制代码是从 000 到 037，以及 177（DEL）。 |
| 12   | 空白字符     | 包括空格符和制表符。                                         |
| 13   | 字母字符     | 小写字母和大写字母的集合。                                   |



### limits.h

#### 简介

**limits.h** 头文件决定了各种变量类型的各种属性。定义在该头文件中的宏限制了各种变量类型（比如 char、int 和 long）的值。

这些限制指定了变量不能存储任何超出这些限制的值，例如一个无符号可以存储的最大值是 255。

#### 库宏

下面的值是特定实现的，且是通过 #define 指令来定义的，这些值都不得低于下边所给出的值。

| 宏         | 值          | 描述                                                         |
| :--------- | :---------- | :----------------------------------------------------------- |
| CHAR_BIT   | 8           | 定义一个字节的比特数。                                       |
| SCHAR_MIN  | -128        | 定义一个有符号字符的最小值。                                 |
| SCHAR_MAX  | 127         | 定义一个有符号字符的最大值。                                 |
| UCHAR_MAX  | 255         | 定义一个无符号字符的最大值。                                 |
| CHAR_MIN   | 0           | 定义类型 char 的最小值，如果 char 表示负值，则它的值等于 SCHAR_MIN，否则等于 0。 |
| CHAR_MAX   | 127         | 定义类型 char 的最大值，如果 char 表示负值，则它的值等于 SCHAR_MAX，否则等于 UCHAR_MAX。 |
| MB_LEN_MAX | 1           | 定义多字节字符中的最大字节数。                               |
| SHRT_MIN   | -32768      | 定义一个短整型的最小值。                                     |
| SHRT_MAX   | +32767      | 定义一个短整型的最大值。                                     |
| USHRT_MAX  | 65535       | 定义一个无符号短整型的最大值。                               |
| INT_MIN    | -32768      | 定义一个整型的最小值。                                       |
| INT_MAX    | +32767      | 定义一个整型的最大值。                                       |
| UINT_MAX   | 65535       | 定义一个无符号整型的最大值。                                 |
| LONG_MIN   | -2147483648 | 定义一个长整型的最小值。                                     |
| LONG_MAX   | +2147483647 | 定义一个长整型的最大值。                                     |
| ULONG_MAX  | 4294967295  | 定义一个无符号长整型的最大值。                               |

### stdint.h

#### 简介

**stdint.h** 头文件定义了各种整型的别名。定义在该头文件中的宏限制了各种整型（比如 char、int 和 long）的值。

这些限制指定了变量不能存储任何超出这些限制的值，例如一个无符号可以存储的最大值是 255。

#### 库宏

下面的值是特定实现的，且是通过 #define 指令来定义的，这些值都不得低于下边所给出的值。

| 宏         | 值                   | 描述                                                         |
| :--------- | :------------------- | :----------------------------------------------------------- |
| INT8_MIN   | -128                 | 定义一个字节的比特数。                                       |
| INT16_MIN  | -32768               | 定义一个有符号字符的最小值。                                 |
| INT32_MIN  | -2147483648          | 定义一个有符号字符的最大值。                                 |
| INT64_MIN  | -9223372036854775808 | 定义一个无符号字符的最大值。                                 |
| INT8_MAX   | 127                  | 定义类型 char 的最小值，如果 char 表示负值，则它的值等于 SCHAR_MIN，否则等于 0。 |
| INT16_MAX  | 32767                | 定义类型 char 的最大值，如果 char 表示负值，则它的值等于 SCHAR_MAX，否则等于 UCHAR_MAX。 |
| INT32_MAX  | 2147483647           | 定义多字节字符中的最大字节数。                               |
| INT64_MAX  | 9223372036854775807  | 定义一个短整型的最小值。                                     |
| UINT8_MAX  | 255                  | 定义一个短整型的最大值。                                     |
| UINT16_MAX | 65535                | 定义一个无符号短整型的最大值。                               |
| UINT32_MAX | 4294967295           | 定义一个整型的最小值。                                       |
| UINT64_MAX | 18446744073709551615 | 定义一个整型的最大值。                                       |

#### 别名

```c
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
```



### setjump.h

#### 简介

C 标准库的 **assert.h**头文件提供了长跳转，goto 语句只能是在函数的局部作用域内跳转，而不能实现跨函数跳转。而 setjmp 宏和 longjmp 函数组合提供一种在程序中实现“非本地局部跳转”(non-local goto)的机制

#### 类型定义

```c
typedef int jmp_buf[16];
```

#### 库函数

下面列出了头文件 assert.h 中定义的唯一的函数：

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | <span style = "font-size:18px;color:rgb(0,102,0)" >int  setjmp( jmp_buf _Buf );</span><br />setjmp 宏函数来初始化 jmp_buf 结构体变量 env，并将当前的堆栈环境信息存入 env 中，为以后调用 longjmp 函数恢复原来环境信息时使用。 |
| 2    | <span style = "font-size:18px;color:rgb(0,102,0)" >void longjmp(jmp_buf _Buf,int     _Value);</span><br />程序跳转到setjmp处，并让setjmp返回value |



### stdio.h

#### 简介

**stdio .h** 头文件定义了三个变量类型、一些宏和各种函数来执行输入和输出。

#### 库变量
| 序号 |  变量  |                        描述                        |
| :--: | :----: | :------------------------------------------------: |
|  1   | size_t | 这是无符号整数类型，它是 **sizeof** 关键字的结果。 |
|  2   |  FILE  |       这是一个适合存储文件流信息的对象类型。       |
|  3   | fpos_t |     这是一个适合存储文件中任何位置的对象类型。     |

#### 库宏

| 序号 |          宏           |                             描述                             |
| :--: | :-------------------: | :----------------------------------------------------------: |
|  1   |         NULL          |                 这个宏是一个空指针常量的值。                 |
|  2   |          EOF          |          这个宏是一个表示已经到达文件结束的负整数。          |
|  3   | stderr、stdin、stdout | FILE 类型的常指针，分别对应于标准错误、标准输入和标准输出流。 |

#### 库函数

| 序号 | 函数&描述                                                    |
| :--: | :----------------------------------------------------------- |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >int fclose(FILE *stream)</span><br />关闭文件 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >void clearerr(FILE *stream)   </span><br />清除文件的文件结束和错误标识符 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >int feof(FILE *stream)</span><br />判断文件是否读取结束 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >int ferror(FILE *stream)</span><br />判断文件是否发生错误 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >int fflush(FILE *stream)</span><br />刷新输出缓冲区 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >int fgetpos(FILE *stream，fpos_t *pos)</span><br />获取文件指针的当前位置，并写入到pos |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >FILE fopen(char *fiIeName，char *mode)</span><br />使用指定的模式 mode 打开 filename 所指向的文件 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t fread(void *ptr，size_t size，size_t count ，FILE *stream)</span><br />从指定的文件流中读取数据到ptr所指向的数组中 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >FILE *freopen(const char *filename, const char *mode, FILE *stream)</span><br />把一个新的文件名 filename 与给定的打开的流 stream 关联，同时关闭流中的旧文件。 |
|  10  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fseek(FILE *stream, long int offset, int whence)</span><br />设置流的文件位置为offset，从whence开始便宜，正数向后便宜，负数向前偏移。 |
|  11  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fsetpos(FILE *stream, const fpos_t *pos)</span><br />设置文件位置为pos。 |
|  12  | <span style = "font-size:18px;color:rgb(0,102,0)" >long int ftell(FILE *stream)</span><br />返回文件指针的当前位置 |
|  13  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)</span><br />把 ptr 所指向的数组中的数据写入到给定流 stream 中。 |
|  14  | <span style = "font-size:18px;color:rgb(0,102,0)" >int remove(const char *filename)</span><br />删除指定的文件，filename是路径+文件名 |
|  15  | <span style = "font-size:18px;color:rgb(0,102,0)" >int rename(const char *old_filename, const char *new_filename)</span><br />把 old_filename 的文件名改为 new_filename。 |
|  16  | <span style = "font-size:18px;color:rgb(0,102,0)" >void rewind(FILE *stream)</span><br />设置文件位置为给定流 stream 的文件的开头。 |
|  17  | <span style = "font-size:18px;color:rgb(0,102,0)" >void setbuf(FILE *stream, char *buffer)</span><br />定义流 stream 应如何缓冲。 |
|  18  | <span style = "font-size:18px;color:rgb(0,102,0)" >int setvbuf(FILE *stream, char *buffer, int mode, size_t size)</span><br />另一个定义流 stream 应如何缓冲的函数。 |
|  19  | <span style = "font-size:18px;color:rgb(0,102,0)" >FILE *tmpfile(void)</span><br />以二进制更新模式(wb+)创建临时文件。 |
|  20  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *tmpnam(char *str)</span><br />生成并返回一个有效的临时文件名，该文件名之前是不存在的。 |
|  21  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fprintf(FILE *stream, const char *format, ...)</span><br />发送格式化输出到流 stream 中。 |
|  22  | <span style = "font-size:18px;color:rgb(0,102,0)" >int printf(const char *format, ...)</span><br />发送格式化输出到标准输出 stdout。 |
|  23  | <span style = "font-size:18px;color:rgb(0,102,0)" >int sprintf(char *str, const char *format, ...)</span><br />发送格式化输出到字符串。 |
|  24  | <span style = "font-size:18px;color:rgb(0,102,0)" >int vfprintf(FILE *stream, const char *format, va_list arg)</span><br />使用参数列表发送格式化输出到流 stream 中。 |
|  25  | <span style = "font-size:18px;color:rgb(0,102,0)" >int vprintf(const char *format, va_list arg)</span><br />使用参数列表发送格式化输出到标准输出 stdout。 |
|  26  | <span style = "font-size:18px;color:rgb(0,102,0)" >int vsprintf(char *str, const char *format, va_list arg)</span><br />使用参数列表发送格式化输出到字符串。 |
|  27  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fscanf(FILE *stream, const char *format, ...)</span><br />从流 stream 读取格式化输入。 |
|  28  | <span style = "font-size:18px;color:rgb(0,102,0)" >int scanf(const char *format, ...)</span><br />从标准输入 stdin 读取格式化输入。 |
|  29  | <span style = "font-size:18px;color:rgb(0,102,0)" >int sscanf(const char *str, const char *format, ...)</span><br />从字符串读取格式化输入。 |
|  30  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fgetc(FILE *stream)</span><br />从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。 |
|  31  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *fgets(char *str, int n, FILE *stream)</span><br />从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内。当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。 |
|  32  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fputc(int char, FILE *stream)</span><br />把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。 |
|  33  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fputs(const char *str, FILE *stream)</span><br />把字符串写入到指定的流 stream 中，但不包括空字符。 |
|  34  | <span style = "font-size:18px;color:rgb(0,102,0)" >int getc(FILE *stream)</span><br />从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。 |
|  35  | <span style = "font-size:18px;color:rgb(0,102,0)" >int getchar(void)</span><br />从标准输入 stdin 获取一个字符（一个无符号字符）。 |
|  36  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *gets(char *str)</span><br />从标准输入 stdin 读取一行，并把它存储在 str 所指向的字符串中。当读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。 |
|  37  | <span style = "font-size:18px;color:rgb(0,102,0)" >int fputc(int char, FILE *stream)</span><br />把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。 |
|  38  | <span style = "font-size:18px;color:rgb(0,102,0)" >int putchar(int char)</span><br />把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout 中。 |
|  39  | <span style = "font-size:18px;color:rgb(0,102,0)" >int puts(const char *str)</span><br />把一个字符串写入到标准输出 stdout，直到空字符，但不包括空字符。换行符会被追加到输出中。 |
|  40  | <span style = "font-size:18px;color:rgb(0,102,0)" >int ungetc(int char, FILE *stream)</span><br />把字符 char（一个无符号字符）推入到指定的流 stream 中，以便它是下一个被读取到的字符。 |
|  41  | <span style = "font-size:18px;color:rgb(0,102,0)" >void perror(const char *str)</span><br />把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格。 |
|  42  | <span style = "font-size:18px;color:rgb(0,102,0)" >int snprintf(char *str, size_t size, const char *format, ...)</span><br />格式字符串到 str 中。 |

### stdlib.h

#### 简介

**stdlib .h** 头文件定义了四个变量类型、一些宏和各种通用工具函数。

#### 库变量

下面是头文件 stdlib.h 中定义的变量类型：

| 序号 |  变量   |                        描述                        |
| :--: | :-----: | :------------------------------------------------: |
|  1   | size_t  | 这是无符号整数类型，它是 **sizeof** 关键字的结果。 |
|  2   | wchar_t |         这是一个宽字符常量大小的整数类型。         |
|  3   |  div_t  |           这是 **div** 函数返回的结构。            |
|  4   | ldiv_t  |           这是 **ldiv** 函数返回的结构。           |

#### 库宏

| 序号 | 宏           | 描述                                                         |
| ---- | ------------ | ------------------------------------------------------------ |
| 1    | NULL         | 这个宏是一个空指针常量的值。                                 |
| 2    | EXIT_FAILURE | 这是 exit 函数失败时要返回的值。                             |
| 3    | EXIT_SUCCESS | 这是 exit 函数成功时要返回的值。                             |
| 4    | RAND_MAX     | 这个宏是 rand 函数返回的最大值。                             |
| 5    | MB_CUR_MAX   | 这个宏表示在多字节字符集中的最大字符数，不能大于 MB_LEN_MAX。 |

#### 库函数

下面是头文件 stdlib.h 中定义的函数：

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >double atof(const char *str)</span><br />把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >int atoi(const char *str)</span><br />把参数 str 所指向的字符串转换为一个整数（类型为 int 型）。 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >long int atol(const char *str)</span><br />把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >double strtod(const char *str, char \*\*endptr)</span><br />把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >long int strtol(const char *str, char \*\*endptr, int base)</span><br />把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >unsigned long int strtoul(const char *str, char \*\*endptr, int base)</span><br />把参数 str 所指向的字符串转换为一个无符号长整数 |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *calloc(size_t nitems, size_t size)</span><br />分配所需的内存空间，并返回一个指向它的指针。 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >void free(void *ptr)</span><br />释放之前调用 calloc、malloc 或 realloc 所分配的内存空间。 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *malloc(size_t size)</span><br />分配所需的内存空间，并返回一个指向它的指针。 |
|  10  | <span style = "font-size:18px;color:rgb(0,102,0)" >void *realloc(void *ptr, size_t size)</span><br />尝试重新调整之前调用 malloc 或 calloc 所分配的 ptr 所指向的内存块的大小。 |
|  11  | <span style = "font-size:18px;color:rgb(0,102,0)" >void abort(void)</span><br />使一个异常程序终止。 |
|  12  | <span style = "font-size:18px;color:rgb(0,102,0)" >int atexit(void (*func)(void))</span><br />当程序正常终止时，调用指定的函数 func。 |
|  13  | <span style = "font-size:18px;color:rgb(0,102,0)" >void exit(int status)</span><br />使程序正常终止。 |
|  14  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *getenv(const char *name)</span><br />获取环境变量的的值 如:path 的值 |
|  15  | <span style = "font-size:18px;color:rgb(0,102,0)" >int system(const char *string)</span><br />由 string 指定的命令传给要被命令处理器执行的主机环境。 |
|  16  | <span style = "font-size:18px;color:rgb(0,102,0)" >void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))</span><br />执行二分查找。 |
|  17  | <span style = "font-size:18px;color:rgb(0,102,0)" >void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))</span><br />数组排序。 |
|  18  | <span style = "font-size:18px;color:rgb(0,102,0)" >int abs(int x)</span><br />返回 x 的绝对值。 |
|  19  | <span style = "font-size:18px;color:rgb(0,102,0)" >div_t div(int numer, int denom)</span><br />分子除以分母。 |
|  20  | <span style = "font-size:18px;color:rgb(0,102,0)" >long int labs(long int x)</span><br />返回 x 的绝对值。 |
|  21  | <span style = "font-size:18px;color:rgb(0,102,0)" >ldiv_t ldiv(long int numer, long int denom)</span><br />分子除以分母。 |
|  22  | <span style = "font-size:18px;color:rgb(0,102,0)" >int rand(void)</span><br />返回一个范围在 0 到 RAND_MAX 之间的伪随机数。 |
|  23  | <span style = "font-size:18px;color:rgb(0,102,0)" >void srand(unsigned int seed)</span><br />该函数播种由函数 rand 使用的随机数发生器 |
|  24  | <span style = "font-size:18px;color:rgb(0,102,0)" >int mblen(const char *str, size_t n)</span><br />返回参数 str 所指向的多字节字符的长度 |
|  25  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t mbstowcs(schar_t *pwcs, const char *str, size_t n)</span><br />把参数 str 所指向的多字节字符的字符串转换为参数 pwcs 所指向的数组。 |
|  26  | <span style = "font-size:18px;color:rgb(0,102,0)" >int mbtowc(whcar_t *pwc, const char *str, size_t n)</span><br />检查参数 str 所指向的多字节字符。 |
|  27  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t wcstombs(char *str, const wchar_t *pwcs, size_t n)</span><br />把宽字节pwcs 转换为窄字节字符，并把它们存储在字符串 str 中。 |
|  28  | <span style = "font-size:18px;color:rgb(0,102,0)" >int wctomb(char *str, wchar_t wchar)</span><br />检查对应于参数 wchar 所给出的多字节字符的编码。 |

### string.h

#### 简介

**string .h** 头文件定义了一个变量类型、一个宏和各种操作字符数组的函数。

#### 库变量

下面是头文件 string.h 中定义的变量类型：

| 序号 | 变量   | 描述                                               |
| ---- | ------ | -------------------------------------------------- |
| 1    | size_t | 这是无符号整数类型，它是 **sizeof** 关键字的结果。 |

#### 库宏

下面是头文件 string.h 中定义的宏：

| 序号 | 宏   | 描述                         |
| ---- | ---- | ---------------------------- |
| 1    | NULL | 这个宏是一个空指针常量的值。 |

#### 库函数

下面是头文件 string.h 中定义的函数：

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *memchr(const void *str, int c, size_t n)</span><br />在参数 str 所指向的字符串的前 n 个字节中搜索第一次出现字符 c（一个无符号字符）的位置。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >int memcmp(const void *str1, const void *str2, size_t n)</span><br />把 str1 和 str2 的前 n 个字节进行比较。 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *memcpy(void *dest, const void *src, size_t n)</span><br />从 src 复制 n 个字符到 dest。 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *memmove(void *dest, const void *src, size_t n)</span><br />另一个用于从 src 复制 n 个字符到 dest 的函数。 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >void *memset(void *str, int c, size_t n)</span><br />复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strcat(char *dest, const char *src)</span><br />把 src 所指向的字符串追加到 dest 所指向的字符串的结尾。 |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strncat(char *dest, const char *src, size_t n)</span><br />把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止。 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strchr(const char *str, int c)</span><br />在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >int strcmp(const char *str1, const char *str2)</span><br />把 str1 所指向的字符串和 str2 所指向的字符串进行比较。 |
|  10  | <span style = "font-size:18px;color:rgb(0,102,0)" >int strncmp(const char *str1, const char *str2, size_t n)</span><br />把 str1 和 str2 进行比较，最多比较前 n 个字节。 |
|  11  | <span style = "font-size:18px;color:rgb(0,102,0)" >int strcoll(const char *str1, const char *str2)</span><br />把 str1 和 str2 进行比较，结果取决于 LC_COLLATE 的位置设置。 |
|  12  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strcpy(char *dest, const char *src)</span><br />把 src 所指向的字符串复制到 dest。 |
|  13  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strncpy(char *dest, const char *src, size_t n)</span><br />把 src 所指向的字符串复制到 dest，最多复制 n 个字符。 |
|  14  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t strcspn(const char *str1, const char *str2)</span><br />检索str2中的字符，在str1中是否存在，存在匹配的第一个字符之前的长度 |
|  15  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strerror(int errnum)</span><br />从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。 |
|  16  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t strlen(const char *str)</span><br />计算字符串 str 的长度，直到空结束字符，但不包括空结束字符。 |
|  17  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strpbrk(const char *str1, const char *str2)</span><br />检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。 |
|  18  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strrchr(const char *str, int c)</span><br />在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置。 |
|  19  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t strspn(const char *str1, const char *str2)</span><br />检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。 |
|  20  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strstr(const char *haystack, const char *needle)</span><br />在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置。 |
|  21  | <span style = "font-size:18px;color:rgb(0,102,0)" >char *strtok(char *str, const char *delim)</span><br />分解字符串 str 为一组字符串，delim 为分隔符。 |
|  22  | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t strxfrm(char *dest, const char *src, size_t n)</span><br />根据程序当前的区域选项中的 LC_COLLATE 来转换字符串 src 的前 n 个字符，并把它们放置在字符串 dest 中。 等同strncpy |
|  23  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strdup(char const* _String        );</span><br />拷贝字符串，返回动态分配的内存，使用完毕后需要手动free |
|  24  | <span style = "font-size:18px;color:rgb(0,102,0)" >int  strcmpi(char const* _String1,char const* _String2);</span><br />根据程 |
|  25  | <span style = "font-size:18px;color:rgb(0,102,0)" >int  stricmp(char const* _String1,char const* _String2); </span><br />根据程 |
|  26  | <span style = "font-size:18px;color:rgb(0,102,0)" >int  strnicmp(char const* _String1,char const* _String2,size_t      _MaxCount);</span><br />根据程 |
|  27  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strnset(char* _String,int    _Value,size_t _MaxCount);</span><br />将一个字符串中的前n个字符都设为指定字符ch的函数。 |
|  28  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strrev(char* _String); </span><br />strrev用于反转字符串。strrev属于非标准函数，Linux不支持。 |
|  29  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strset(char* _String,int   _Value);</span><br />把字符串s中的所有字符都设置成字符c |
|  30  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strlwr(char* _String);</span><br />将字符串S转换为小写形式 |
|  31  | <span style = "font-size:18px;color:rgb(0,102,0)" >char* strupr(char* _String);</span><br />将字符串s转换为大写形式 |



### time.h

#### 简介

**time.h** 头文件定义了四个变量类型、两个宏和各种操作日期和时间的函数。

#### 库变量

下面是头文件 time.h 中定义的变量类型：

| 序号 | 变量      | 描述                                             |
| :--: | --------- | ------------------------------------------------ |
|  1   | size_t    | 是无符号整数类型，它是 **sizeof** 关键字的结果。 |
|  2   | clock_t   | 这是一个适合存储处理器时间的类型。               |
|  3   | time_t    | 这是一个适合存储日历时间类型。                   |
|  4   | struct tm | 这是一个用来保存时间和日期的结构。               |

struct tm结构的定义如下:

```c
struct tm 
{
   int tm_sec;     /* 秒，范围从 0 到 59        	  			 */
   int tm_min;     /* 分，范围从 0 到 59        	    		 */
   int tm_hour;    /* 小时，范围从 0 到 23        	   			*/
   int tm_mday;    /* 一月中的第几天，范围从 1 到 31    		*/
   int tm_mon;     /* 月，范围从 0 到 11        				 */
   int tm_year;    /* 自 1900 年起的年数        				 */
   int tm_wday;    /* 一周中的第几天(0是星期天),取值区间为[0,6]   */
   int tm_yday;    /* 一年中的第几天，范围从 0 到 365   		 */
   int tm_isdst;   /* 夏令时  我国已废弃              		  	*/
};
```



#### 库宏

下面是头文件 time.h 中定义的宏：

| 序号 |       宏       |               描述               |
| :--: | :------------: | :------------------------------: |
|  1   |      NULL      |   这个宏是一个空指针常量的值。   |
|  2   | CLOCKS_PEG_SEC | 这个宏表示每秒的处理器时钟个数。 |

#### 库函数

下面是头文件 time.h 中定义的函数：

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >char *asctime(const struct tm *timeptr)</span><br />返回一个指向字符串的指针，它代表了结构 timeptr 的日期和时间。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >clock_t clock(void)</span><br />返回程序执行起（一般为程序的开头），处理器时钟所使用的时间。 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >char *ctime(const time_t *timer)</span><br />返回一个表示当地时间的字符串，当地时间是基于参数 timer。 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >double difftime(time_t time1, time_t time2)</span><br />返回 time1 和 time2 之间相差的秒数 (time1-time2)。 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >struct tm *gmtime(const time_t *timer)</span><br />timer 的值被分解为 tm 结构，并用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示。 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >struct tm *localtime(const time_t *timer)</span><br />timer 的值被分解为 tm 结构，并用本地时区表示 |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >time_t mktime(struct tm *timeptr)</span><br />把 timeptr 所指向的结构转换为一个依据本地时区的 time_t 值。 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)</span><br />根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中。 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >time_t time(time_t *timer)</span><br />计算当前日历时间，并把它编码成 time_t 格式。 |



### math.h

#### 简介

**math.h** 头文件定义了各种数学函数和一个宏。在这个库中所有可用的功能都带有一个 **double** 类型的参数，且都返回 **double** 类型的结果。

#### 库函数

| 序号 | 函数&描述                                                    |
| :--: | ------------------------------------------------------------ |
|  1   | <span style = "font-size:18px;color:rgb(0,102,0)" >double acos(double x)</span><br />返回以弧度表示的 x 的反余弦。 |
|  2   | <span style = "font-size:18px;color:rgb(0,102,0)" >double asin(double x)</span><br />返回以弧度表示的 x 的反正弦。 |
|  3   | <span style = "font-size:18px;color:rgb(0,102,0)" >double atan(double x)</span><br />返回以弧度表示的 x 的反正切。 |
|  4   | <span style = "font-size:18px;color:rgb(0,102,0)" >double atan2(double y, double x)</span><br />返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。 |
|  5   | <span style = "font-size:18px;color:rgb(0,102,0)" >double cos(double x)</span><br />返回弧度角 x 的余弦 |
|  6   | <span style = "font-size:18px;color:rgb(0,102,0)" >double cosh(double x)</span><br />返回 x 的双曲余弦。 |
|  7   | <span style = "font-size:18px;color:rgb(0,102,0)" >double sin(double x)</span><br />返回弧度角 x 的正弦。 |
|  8   | <span style = "font-size:18px;color:rgb(0,102,0)" >double sinh(double x)</span><br />返回 x 的双曲正弦。 |
|  9   | <span style = "font-size:18px;color:rgb(0,102,0)" >double tanh(double x)</span><br />返回 x 的双曲正切。 |
|  10  | <span style = "font-size:18px;color:rgb(0,102,0)" >double exp(double x)</span><br />返回 e 的 x 次幂的值。 |
|  11  | <span style = "font-size:18px;color:rgb(0,102,0)" >double frexp(double x, int *exponent)</span><br />把浮点数 x 分解成尾数和指数。返回值是尾数，并将指数存入 exponent 中。所得的值是 x = mantissa * 2 ^ exponent。 |
|  12  | <span style = "font-size:18px;color:rgb(0,102,0)" >double ldexp(double x, int exponent)</span><br />返回 x 乘以 2 的 exponent 次幂。 |
|  13  | <span style = "font-size:18px;color:rgb(0,102,0)" >double log(double x)</span><br />返回 x 的自然对数（基数为 e 的对数）。 |
|  14  | <span style = "font-size:18px;color:rgb(0,102,0)" >double log10(double x)</span><br />返回 x 的常用对数（基数为 10 的对数）。 |
|  15  | <span style = "font-size:18px;color:rgb(0,102,0)" >double modf(double x, double *integer)</span><br />返回值为小数部分（小数点后的部分），并设置 integer 为整数部分。 |
|  16  | <span style = "font-size:18px;color:rgb(0,102,0)" >double pow(double x, double y)</span><br />返回 x 的 y 次幂。 |
|  17  | <span style = "font-size:18px;color:rgb(0,102,0)" >double sqrt(double x)</span><br />返回 x 的平方根。 |
|  18  | <span style = "font-size:18px;color:rgb(0,102,0)" >double ceil(double x)</span><br />返回大于或等于 x 的最小的整数值。 |
|  19  | <span style = "font-size:18px;color:rgb(0,102,0)" >double fabs(double x)</span><br />返回 x 的绝对值。 |
|  20  | <span style = "font-size:18px;color:rgb(0,102,0)" >double floor(double x)</span><br />返回小于或等于 x 的最大的整数值。 |
|  21  | <span style = "font-size:18px;color:rgb(0,102,0)" >double fmod(double x, double y)</span><br />返回 x 除以 y 的余数。 |



## 其他

### sys/stat.h

#### 简介

**sys/stat.h**头文件提供了获取文件详细信息的功能。

#### 函数

下面列出了头文件 **sys/stat.h** 中定义的唯一的函数：

| 序号 | 函数&描述                                                    |
| ---- | ------------------------------------------------------------ |
| 1    | <span style = "font-size:18px;color:rgb(0,102,0)" >int stat(char const* const _FileName, struct stat* const _Stat)</span><br />通过文件名fileName获取文件信息，并保存在Stat结构体中；成功返回，失败返回-1，并设置错误码 |

##### struct stat 结构体

```c
struct stat
{
    _dev_t         st_dev;		//文件设备编号
    _ino_t         st_ino;		//inode节点
    unsigned short st_mode;		//文件的类型和存取权限
    short          st_nlink;	//连到改文件的硬连接数目，刚建立的文件值为1
    short          st_uid;		//用户ID
    short          st_gid;		//组ID
    _dev_t         st_rdev;		//设备类型(若此文件为设备文件，则为期设备编号)
    _off_t         st_size;		//文件字大小(字节数)
    time_t         st_atime;	//访问时间
    time_t         st_mtime;	//修改时间
    time_t         st_ctime;	//创建时间
};
```

##### 成员st_mode所有情况

| 序号 | 宏       | 描述          |
| ---- | -------- | ------------- |
| 1    | S_IFMT   | 文件类型掩码  |
| 2    | S_IFDIR  | 是目录        |
| 3    | S_IFCHR  | 字符文件      |
| 4    | S_IFREG  | 一般文件      |
| 5    | S_IREAD  | 读权限        |
| 6    | S_IWRITE | 写权限        |
| 7    | S_IEXEC  | 执行/查找权限 |

#### demo

```c
int main()
{
	struct stat st;
	if (stat("./Console.exe", &st))
	{
		perror("stat failed");
	}
	else
	{
		//有用的成员
		printf("%u\n", st.st_mode);
		printf("%ld\n", st.st_size);
		printf("%s\n", ctime(&st.st_atime));
		printf("%s\n", ctime(&st.st_mtime));
		printf("%s\n", ctime(&st.st_ctime));

		//获取文件类型
		switch (st.st_mode & S_IFMT)
		{
		case S_IFCHR:
			printf("S_IFCHR\n");
			break;
		case S_IFDIR:
			printf("S_IFDIR\n");
			break;
		case S_IFREG:
			printf("S_IFREG\n");
			break;
		default:
			printf("default\n");
				break;
		}
		//获取权限
		if (st.st_mode & S_IREAD)
		{
			printf("S_IREAD\n");
		}
		if (st.st_mode & S_IWRITE)
		{
			printf("S_IWRITE\n");
		}
		if (st.st_mode & S_IEXEC)
		{
			printf("S_IEXEC\n");
		}
	}
	return 0;
}
```



### direct.h

#### 简介

direct.h中提供了改变当前工作目录、创建和删除目录的操作。

`注意：改变当前工作目录之后，创建文件也会在改变之后的目录中`

#### 函数

| 序号 | 函数&描述                                                    |
| ---- | ------------------------------------------------------------ |
| 1    | <span style = "font-size:18px;color:rgb(0,102,0)" >char* __cdecl getcwd(char* _DstBuf,int   _SizeInBytes);</span><br />获取当前工作目录 |
| 2    | <span style = "font-size:18px;color:rgb(0,102,0)" >int __cdecl chdir(char const* _Path);</span><br />更改当前工作目录(成功返回0，失败返回-1，并设置errno) |
| 3    | <span style = "font-size:18px;color:rgb(0,102,0)" >int __cdecl mkdir(char const* _Path);</span><br />创建一个新目录 |
| 4    | <span style = "font-size:18px;color:rgb(0,102,0)" >int __cdecl rmdir(char const* _Path);</span><br />删除指定的目录 |

#### demo

```c
int main()
{
	//修改当前工作目录
	if (-1 == chdir("D:/AllData"))
	{
		perror("change dir failed");
	}
	//获取当前工作目录
	char workPath[BUFSIZ] = { 0 };
	if (NULL != getcwd(workPath, BUFSIZ))
	{
		printf("curent work path is:%s\n", workPath);
	}

	//创建目录
	if (-1 == mkdir("aa"))
	{
		perror("mkdir failed");
	}

	//删除目录
	if (-1 == rmdir("aa"))
	{
		perror("aa");
	}
	
	 return 0;
}
```

### dirent.h

**dirent.h**是个unix系统下常见的接口，但windows平台的MSVC编译器并没有提供这个接口，对于跨平台的项目开发就会带来一些麻烦，如果在MSVC下编译时可能因为windows平台缺少这个接口就要为windows平台另外写一些代码。

但是目前已经有人完成了windows平台下 [dirent.h](./dirent.h)文件编写。

#### 函数

| 序号 | 函数&描述                                                    |
| ---- | ------------------------------------------------------------ |
| 1    | <span style = "font-size:15px;color:rgb(0,102,0)" >DIR *opendir (const char *dirname);</span><br />打开目录 |
| 2    | <span style = "font-size:15px;color:rgb(0,102,0)" >struct dirent *readdir (DIR *dirp);</span><br />读取目录，返回目录项(目录中的文件信息) |
| 3    | <span style = "font-size:15px;color:rgb(0,102,0)" >int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);</span><br />读取entry的下一个条目到result被分配的缓冲区中。 成功返回0。 如果到达目录流的末尾，则将result设置为NULL并返回0。 |
| 4    | <span style = "font-size:15px;color:rgb(0,102,0)" >int closedir (DIR *dirp);</span><br />关闭目录 |
| 5    | <span style = "font-size:15px;color:rgb(0,102,0)" >void rewinddir (DIR* dirp);</span><br />重置目录到开头 |
| 6    | <span style = "font-size:15px;color:rgb(0,102,0)" >int scandir (const char \*dirname, struct dirent \*\*\*namelist,<br/>    int (\*filter)(const struct dirent*),<br/>    int (\*compare)(const void *, const void *));</span><br />扫描dirname目录下(不包括子目录)满足filter过滤模式的文件，返回的结果是compare函数经过排序的，并保存在namelist中；<br/>注意namelist是通过malloc动态分配内的,所以在使用时要注意释放内存。alphasort和versionsort是使用到的两种排序的函数。 |
| 7    | <span style = "font-size:15px;color:rgb(0,102,0)" >int alphasort (const struct dirent \*\*a, const struct dirent \*\*b);</span><br/>按目录名排序 |
| 8    | <span style = "font-size:15px;color:rgb(0,102,0)" >static int versionsort (const struct dirent \*\*a, const struct dirent \*\*b);</span><br />同上，也是按目录名排序(可以自己实现排序函数) |

#### 结构

##### struct DIR

```c
struct DIR {
    struct dirent ent;
    struct _WDIR *wdirp;
};
```

##### struct dirent

```c
struct dirent 
{
    long d_ino;					//总是0
    long d_off;					//文件在流中的位置
    unsigned short d_reclen;	//结构大小(记录长度，当前结构体的大小)
    size_t d_namlen;			//文件名长度
    int d_type;					//文件类型
    char d_name[PATH_MAX+1];	//文件名
};
```

#### demo

```c
int main()
{
	DIR* dir = opendir("./");
	dirent* diret = readdir(dir);
	while (diret)
	{
		printf("%s  %lu %ld\n", diret->d_name,diret->d_namlen,diret->d_reclen);
		diret = readdir(dir);
	}
	closedir(dir);

	rewinddir(dir);
	diret = readdir(dir);
	while (diret)
	{
		printf("%s  %lu %ld\n", diret->d_name, diret->d_namlen, diret->d_reclen);
		diret = readdir(dir);
	}

	 return 0;
}
```

### Windows.h

#### 简介

Windows提供的的 **Windows.h**头文件提供了一些用于操作console窗口的函数。

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | <span style = "font-size:15px;color:rgb(0,102,0)" >void SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine，BOOL Add)</span><br />添加控制台处理函数，Add为 TRUE，则添加处理程序 |
| 更多 | https://docs.microsoft.com/en-us/windows/console/            |

#### 捕获关闭按钮点击消息

```c
#include <Windows.h>
#include <stdio.h>

BOOL isExit = TRUE;
BOOL WINAPI ConsoleHandler(DWORD msgType)
{
    if (msgType == CTRL_C_EVENT)
    {
        printf("CTRL_C_EVENT\n");
        isExit = FALSE;
        return TRUE;
    }
    else if (msgType == CTRL_CLOSE_EVENT)
     {
        printf("Close console window!\n");
        MessageBox(NULL, "确定关闭窗口吗？", " Close", MB_OK);
        isExit = FALSE;
        //while (1);用处不大
        /*注意：在这种情况下，系统留给你的推出时间非常有限,即使用死循环卡主，稍后，窗口也会被销毁*/
        return TRUE;
     }

    /*
        CTRL_C_EVENT            按下Ctrl+C 
        CTRL_CLOSE_EVENT        左上角关闭控制台窗口
        Other messages:
        CTRL_BREAK_EVENT         Ctrl + Break pressed
        CTRL_LOGOFF_EVENT        注销
        CTRL_SHUTDOWN_EVENT      关机
    */

    return FALSE;
}

int main(void)
{
    //设置控制台处理函数
    BOOL ok = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
  
    while (isExit);//如果没有通知窗口关闭，那么一直等待
    return 0;
}
```

#### 禁用关闭按钮

	DeleteMenu(GetSystemMenu(GetConsoleWindow(),
		FALSE),
		SC_CLOSE,
		MF_BYCOMMAND);
