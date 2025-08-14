## format(C++20)

>  `std::format` 是 C++20 中引入的一个新特性，它提供了一种类型安全且易于使用的方式来格式化字符串。这个函数在 `<format>` 头文件中定义。

### 基础用法

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

### 类型规格与格式选项

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

## print(C++23)

C++标准流输出std::cout一直以来为人们所诟病：不灵活，格式化支持差，冗长等等。人们有此想法源于C库的printf()函数虽然不提供类型安全保障和线程安全保障，但它非常灵活，格式化支持非常好。

为此，C++23版本引入了std::print()/std::println()函数，完全解决了流输出std::cout为人们所诟病的问题。下面我们就来看看它们。

### 简介

std::print系列函数具有 std::format 的所有性能优势，默认情况下与语言环境无关，减少全局状态，避免分配临时 std::string 对象和调用运算符 <<，并且与 iostreams 和 stdio 相比，拥有更高的效率。

### 头文件

std::print()系列函数定义在头文件\<print>中，使用之前需要包括进去。

### std::print

`std::print` 是基于 `std::format` 实现的，因此**支持绝大部分 `std::format` 的格式规范**，但仍有一些细微差异和限制。

### std::println

`std::println`和`std::print`它们的核心区别在于 **`println` 会自动在输出末尾添加换行符**，而 `print` 不会。