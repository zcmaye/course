# spdlog库简介

spdlog 是一个高性能的 C++ 日志库，它设计时充分考虑了速度和易用性，具有以下特点：

+ 高效与快速：Spdlog 专注于提供极致的性能，在大量日志记录场景下也能保持较低的延迟和较高的吞吐量。
+ 轻量化设计：Spdlog 是头文件（header-only）库，这意味着用户只需要包含相应的头文件即可开始使用，无需编译链接额外的库文件。
+ 跨平台支持：它支持多种操作系统，包括但不限于 Windows、Linux 和 macOS，并且在这些平台上都能够良好运行。
+ 丰富的日志级别：Spdlog 支持常见的日志级别，如 TRACE、DEBUG、INFO、WARN、ERROR、CRITICAL 等，用户可以根据需要选择不同级别的日志输出。
+ 格式化与定位信息：通过集成 fmt 库，Spdlog 允许用户自定义日志消息的格式，可以轻松地包含时间戳、线程ID、文件名、行号以及函数名等上下文信息。
+ 多目标输出：可以将日志输出到控制台、普通文本文件、循环写入文件（rotating log files）、每日生成新文件（daily logs）、系统日志等目标，同时也
+ 支持异步写入以提高性能。
+ 线程安全：对于多线程环境，Spdlog 提供了线程安全的日志接口，确保在并发环境下日志记录的正确性和完整性。
+ 异步模式：提供可选的异步日志记录机制，能够将日志操作放入后台线程执行，从而避免阻塞主线程。
+ 条件日志：根据预定义的条件开关，可以动态启用或禁用特定级别的日志输出。

# 下载与配置

spdlog库的使用非常简单，只需要下载源代码，然后把根目录下的`include`目录下的文件拷贝到我们的工程下，在工程中包含相应的头文件即可。

GitHub下载地址：https://github.com/gabime/spdlog

## 直接使用头文件

将`include文件夹`中的spdlog目录复制到构建树中，并使用c11编译器。

```cmake
cmake_minimum_required (VERSION 3.10)

project ("test_spdlog")

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将当前目录添加到包含路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加编译选项
if(MSVC) 
	add_compile_options("/utf-8")
endif()

# 将源代码添加到此项目的可执行文件。
add_executable (test_spdlog "test_spdlog.cpp" )
```



## 编译

+ 首先，生成项目

  ```bash
  cmake -B build
  ```

+ 然后，构建并编译

  ```bash
  cmake --build build
  ```

+ 最后，进行安装

  ```bash
  cmake --install build --prefix="spdlog_install"
  ```

可以将库安装到你专门防止库的目录中，然后将目录配置到CMake中即可：

```cmake
cmake_minimum_required (VERSION 3.10)

project ("test_spdlog")

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#添加编译选项
if(MSVC) 
	add_compile_options("/utf-8")
endif()

#查找spdlog包
find_package (spdlog REQUIRED)

# 将源代码添加到此项目的可执行文件。
add_executable (test_spdlog "test_spdlog.cpp" )

target_link_libraries (test_spdlog PRIVATE spdlog::spdlog_header_only)
```

# 使用

## 基本使用

### 日志级别

spdlog提供了六种日志级别，分别如下：

```cpp
#include "spdlog/spdlog.h"

int main()
{
	spdlog::trace("Hello spdlog {}","trace");
	spdlog::debug("Hello spdlog {}","debug");
	spdlog::info("Hello spdlog {}","info");
	spdlog::warn("Hello spdlog {}","warn");
	spdlog::error("Hello spdlog {}","error");
	spdlog::critical("Hello spdlog {}","cirtical");
	return 0;
}
```

输出如下：

```bash
[2026-03-17 19:11:02.284] [info] Hello spdlog info
[2026-03-17 19:11:02.285] [warning] Hello spdlog warn
[2026-03-17 19:11:02.285] [error] Hello spdlog error
[2026-03-17 19:11:02.286] [critical] Hello spdlog cirtical
```

默认情况下只显示info及以上级别的日志，可以通过设置日志级别控制。

```cpp
spdlog::set_level(spdlog::level::debug);	//调试信息 - 仅当级别为 debug 时显示
spdlog::set_level(spdlog::level::off);		//关闭日志
```

### 日志格式

#### 格式设置

spdlog提供了非常丰富的日志格式，可以通过`	spdlog::set_pattern`函数进行设置：

```cpp
spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [thread %t] %v");
```

日志输出如下：

```bash
[19:37:49.104] [debug] [thread 23404] Hello spdlog debug
[19:37:49.105] [info] [thread 23404] Hello spdlog info
[19:37:49.105] [warning] [thread 23404] Hello spdlog warn
[19:37:49.105] [error] [thread 23404] Hello spdlog error
[19:37:49.106] [critical] [thread 23404] Hello spdlog cirtical
```

时间格式现在就只会显示时分秒以及毫秒了！

其他格式看下表：

#### 时间格式

| 格式                                            | 说明                                | 示例                     |
| ----------------------------------------------- | ----------------------------------- | ------------------------ |
| `%a`                                            | 缩写星期几名称                      | Sun                      |
| `%A`                                            | 完整星期几名称                      | Sunday                   |
| `%b` / `%h`                                     | 缩写月份                            | Jan                      |
| `%B`                                            | 完整月份名称                        | January                  |
| `%c`                                            | 日期和时间表示                      | Thu Aug 23 15:35:46 2014 |
| `%C`                                            | 年份后两位                          | 18                       |
| `%Y`                                            | 年份                                | 2018                     |
| `%D` / `%x`                                     | 短 MM/DD/YY 日期                    | 08/23/01                 |
| `%m`                                            | 月份                                | 1-12                     |
| `%d`                                            | 日                                  | 1-31                     |
| `%H`                                            | 24小时制                            | 0-23                     |
| `%I`                                            | 12小时制                            | 0-12                     |
| `%M`                                            | 分钟                                | 0-59                     |
| `%S`                                            | 秒                                  | 0-59                     |
| `%e`                                            | 毫秒                                | 0-999                    |
| `%f`                                            | 微秒                                |                          |
| `%F`                                            | 纳秒                                |                          |
| `%p`                                            | 上午/下午                           | AM                       |
| `%r`                                            | 12小时制时间                        | 02:55:02 pm              |
| `%R`                                            | 24小时制 HH:MM 时间                 | 23:59                    |
| `%T` / `%X`                                     | HH:MM:SS                            | 23:59:59                 |
| `%z`                                            | UTC 的 ISO 8601 时区偏移（+-HH:MM） | +08:00                   |

#### 其他格式

| 格式                                            | 说明                                | 示例                     |
| ----------------------------------------------- | ----------------------------------- | ------------------------ |
| format	  | explain	  | e.g.                       |                         
| %n	  | logger_name	  | 创建logger时填入的名称     |                           
| %l	  | log_level	  | info,debug,track,error       |                       
| %L	  | short log_level   | 简写的日志等级	I,D,T,E |                           
| %t	  | threadID	  | 线程ID                        |                       
| %v	  | messageContent	  | 日志正文                |                            

## 创建日志

### stdout/stderror日志

```cpp
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
void stdout_example()
{
    // 创建一个多线程彩色日志记录器
    auto console = spdlog::stdout_color_mt("console");    
    auto err_logger = spdlog::stderr_color_mt("stderr");    
    
    // 根据日志名获取日志
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
}
```

### 基本文件日志

```cpp
#include "spdlog/sinks/basic_file_sink.h"
void basic_logfile_example()
{
    try 
    {
        //创建名为basic_logger的日志
        auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}
```

### 轮转文件日志

```cpp
#include "spdlog/sinks/rotating_file_sink.h"
void rotating_example()
{
    // 创建一个大小上限为 5MB、最多保留 3 个副本的日志轮转文件程序
    auto max_size = 5 * 1024 * 1024;
    auto max_files = 3;
    auto logger = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size, max_files);
}
```

### 每日文件日志

```cpp
#include "spdlog/sinks/daily_file_sink.h"
void daily_example()
{
    // 创建一个每日记录器——每天凌晨 2 点 30 分会自动创建一个新的文件。
    auto logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
}
```

#### 多接收器日志

具有多个接收器的日志记录器——每个接收器都有不同的格式和日志级别

```cpp
//创建一个具有两个目标的日志记录器，这些目标具有不同的日志级别和格式。
//控制台将仅显示警告或错误信息，而文件则会记录所有信息。
void multi_sink_example()
{
	//创建控制台接收器
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

	//创建文件接收器
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);

	//使用多个接收器创建日期记录器
    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);

	//记录日志
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
}
```



## 高级功能

### 异步日志

```cpp
#include "spdlog/async.h"

void setup_async_logging() {
	//在创建异步日志记录器之前，可以对默认线程池设置进行修改
	spdlog::init_thread_pool(8192, 1);		// 具有 8k 个元素且配备 1 个后备线程的队列。
    // 创建异步日志器
	auto async_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_logger", "logs/async_log.txt");
	// 下面的创建方式和上面的是等价的
    // auto async_file = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("async_file_logger", "logs/async_log.txt");  

	async_logger->info("hello world");
}
```

### 异步多接收器日志记录器

```cpp
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

void multi_sink_example2()
{
    spdlog::init_thread_pool(8192, 1);
    //标准输出接收器
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    //轮转文件接收器
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("mylog.txt", 1024*1024*10, 3);
    //用vector保存多个接收器
    std::vector<spdlog::sink_ptr> sinks {stdout_sink, rotating_sink};
    //使用接收器创建日志记录器
    auto logger = std::make_shared<spdlog::async_logger>("loggername", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    //将日志记录器注册
    spdlog::register_logger(logger);
}
```

