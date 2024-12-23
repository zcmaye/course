# grpc

+ [等待就绪 | gRPC 中文](https://grpc.org.cn/docs/guides/wait-for-ready/)

## 下载与安装

+ 从[github](https://github.com/protocolbuffers/protobuf)拉取源码！

```sh
git clone -b master https://github.com/grpc/grpc.git
```

+ 以管理员身份打开cmd终端，并进入`protobuf`目录

```sh
cd grpc
git submodule update --init
```

+ 然后执行cmake命令，进行构建

```sh
cmake -B build_grpc -DgRPC_SSL_PROVIDER=package -DOPENSSL_ROOT_DIR=F:\Tools\OpenSSL-Win64 -DCMAKE_CXX_STANDARD=17

cmake -B build_grpc -DgRPC_SSL_PROVIDER=package -Dprotobuf_BUILD_SHARED_LIBS=OFF -DOPENSSL_ROOT_DIR=F:\Tools\OpenSSL-Win64 -DCMAKE_CXX_STANDARD=17
```

> gRPC_SSL_PROVIDER=package表示使用openSSL而不是boringssl

+ 然后执行cmake命令，执行编译与安装

```sh
cmake --build build_grpc --target INSTALL -j4
```

> 编译时间较久(我编译了1小时20分钟)，请耐心等待~



## CMake配置开发环境

+ CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(p_name VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(absl REQUIRED)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

set(GATESERVER_SOURCES
    App.cpp

    proto/message.pb.h
    proto/message.pb.cc
    proto/message.grpc.pb.h
    proto/message.grpc.pb.cc
)

add_executable(p_name ${GATESERVER_SOURCES})


target_link_libraries(p_name 
protobuf::libprotobuf
gRPC::grpc++
utf8_validity
)
```



> error LNK2019: 无法解析的外部符号 "__declspec(dllimport) protected: __cdecl google::protobuf::Message::Message(void)"...

如果编译时，出现上面的错误，则需要在库中找到port_def.inc文件（一般在`grpc\include\google\protobuf`目录下）然后找到如下所示位置，添加预编译指令`#undef PROTOBUF_USE_DLLS`

port_def.inc

```cpp
#ifdef PROTOBUF_EXPORT
#error PROTOBUF_EXPORT was previously defined
#endif
/*找到上面的宏定义，在下面添加如下代码*/
#undef PROTOBUF_USE_DLLS
```

