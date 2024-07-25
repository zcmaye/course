# JWT-CPP

JWT(JSON Web Tokens)是一种开放的标准（RFC 7519），它定义了一种紧凑、自包含的方式来安全地在各方之间传输信息作为 JSON 对象。这种信息可以被认为是经过验证并被信任的，因为它是数字签名的。

+ 需要提前安装好openssl库

## 下载与安装


从[github](https://github.com/Thalhammer/jwt-cpp)拉取源码！

```cpp
git clone -b master https://github.com/Thalhammer/jwt-cpp.git
```

拉去完毕进入zlib目录。

```cpp
cd jwt-cpp
```

创建build目录并进入

```sh
mkdir build
cd build
```

然后执行cmake，同时设置安装路径

```sh
cmake .. -DCMAKE_INSTALL_PREFIX="../install_jwt-cpp"
```

编译并安装(必须以管理员权限打开终端哟~)

```sh
cmake --build . --target INSTALL --config [Debug|Release]
```
