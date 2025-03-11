# Protocol Buffers

Protocol buffers 是 Google 的一种与语言无关、与平台无关、可扩展的机制，用于序列化结构化数据——可以将其视为 XML，但更小、更快、更简单。您只需定义一次数据结构，然后可以使用特殊生成的源代码轻松地将结构化数据写入和读取到各种数据流中，并使用各种语言。

+ [Protocol Buffers 文档 - ProtoBuf 文档](https://protobuf.com.cn/)

+ [Protocol Buffers Documentation](https://protobuf.dev/)

## 下载与安装

+ 从[github](https://github.com/protocolbuffers/protobuf)拉取源码！

```sh
git clone -b master https://github.com/protocolbuffers/protobuf.git
```

+ 以管理员身份打开cmd终端，并进入`protobuf`目录

```sh
cd protobuf
```

+ 然后执行cmake命令，进行构建

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release -Dprotobuf_BUILD_SHARED_LIBS=ON -Dprotobuf_WITH_ZLIB=OFF -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_CXX_STANDARD=17
```

+ 然后执行cmake命令，执行编译与安装

```sh
cmake --build build --target INSTALL -j8
```

## CMake

```cmake
cmake_minimum_required(VERSION 3.20)

project(demo1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories("F:/Tools/protobuf/lib")

find_package(protobuf REQUIRED)
find_package(absl REQUIRED)

message(STATUS "===  ")

add_executable(demo1 "App.cpp" "proto/Foo.pb.cc")

target_link_libraries(demo1 protobuf::libprotobuf 
absl::abseil_dll
)
```

