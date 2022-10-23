# 用Visual C++构建 curl 

本文档描述了如何编译、构建和安装curl和libcurl从源代码使用Visual c++构建工具。用vc++来构建，你会
课程必须先安装vc++。VC的最低要求版本是6(Visual Studio 6的一部分)。然而，使用较新的版本是强烈的推荐。

VC++也是Windows平台SDK的一部分。您不必安装完整的Visual Studio或Visual c++，如果你想要的只是构建curl。

最新的平台SDK可以免费下载 [Windows SDK and emulator archive](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive)

## 先决条件

如果你想支持zlib, openssl, c-ares, ssh2，你必须分别下载它们，并复制到deps目录，如下所示:

    somedirectory\
     |_curl-src
     | |_winbuild
     |
     |_deps
       |_ lib
       |_ include
       |_ bin

也可以在其他一些随机的地方创建deps目录，并使用WITH_DEVEL选项告诉Makefile它的位置。

## 直接从git构建

当你签出代码git并构建它时，与发布的源代码存档不同，你需要首先运行“buildconf.bat”批处理文件(存在于源代码根目录中)来设置东西。

## 打开命令提示符

打开Visual Studio命令提示符:

使用**Developer Command Prompt for VS [version]**菜单项的开发人员命令提示符:其中[version}是Visual Studio版本。开发人员提示符默认使用x86模式。需要调用' vcvarsal .bat '来为您想要的机器类型设置提示符。这种类型的命令提示符可能并不存在于所有Visual Studio版本中。

 See also: [Developer Command Prompt for Visual Studio](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs) and [How to: Enable a 64-Bit, x64 hosted MSVC toolset on the command line](https://docs.microsoft.com/en-us/cpp/build/how-to-enable-a-64-bit-visual-cpp-toolset-on-the-command-line)

使用**VS [version] [platform] [type] Command Prompt**菜单项：其中[version]是Visual Studio版本，[platform]是x64， [type]原生的跨平台构建。这种类型的命令提示符可能并不存在于所有Visual Studio版本中。

例如: [为命令行构建设置路径和环境变量](https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line)

## 在控制台中构建

进入控制台后，转到Curl源代码中的winbuild目录:

    cd curl-src\winbuild

然后你可以调用' nmake /f Makefile。使用所需的选项(见下文)。构建将在顶部的src目录“builds\”目录中，该目录使用给nmake调用的选项命名。

```sh
nmake /f Makefile.vc mode=<static or dll> <options>
#1，
nmake /f Makefile.vc mode=static  ENABLE_IDN=no DEBUG=yes
#2，
```

其中' <options> '是一下选项中的一个或多个:

 - `VC=<num>`                    - VC version. 6 or later.
 - `WITH_DEVEL=<path>`           - Paths for the development files (SSL, zlib, etc.)
                                   Defaults to sibbling directory deps: ../deps
                                   Libraries can be fetched at https://windows.php.net/downloads/php-sdk/deps/
                                   Uncompress them into the deps folder.
 - `WITH_SSL=<dll/static>`       - Enable OpenSSL support, DLL or static
 - `WITH_NGHTTP2=<dll/static>`   - Enable HTTP/2 support, DLL or static
 - `WITH_MSH3=<dll/static>`      - Enable (experimental) HTTP/3 support, DLL or static
 - `WITH_MBEDTLS=<dll/static>`   - Enable mbedTLS support, DLL or static
 - `WITH_CARES=<dll/static>`     - Enable c-ares support, DLL or static
 - `WITH_ZLIB=<dll/static>`      - Enable zlib support, DLL or static
 - `WITH_SSH=<dll/static>`       - Enable libSSH support, DLL or static
 - `WITH_SSH2=<dll/static>`      - Enable libSSH2 support, DLL or static
 - `WITH_PREFIX=<dir>`           - Where to install the build
 - `ENABLE_SSPI=<yes/no>`        - Enable SSPI support, defaults to yes
 - `ENABLE_IPV6=<yes/no>`        - Enable IPv6, defaults to yes
 - `ENABLE_IDN=<yes or no>`      - Enable use of Windows IDN APIs, defaults to yes
                                   Requires Windows Vista or later
 - `ENABLE_SCHANNEL=<yes/no>`    - Enable native Windows SSL support, defaults
                                   to yes if SSPI and no other SSL library
 - `ENABLE_OPENSSL_AUTO_LOAD_CONFIG=<yes/no>`
                                 - Enable loading OpenSSL configuration
                                   automatically, defaults to yes
 - `ENABLE_UNICODE=<yes/no>`     - Enable UNICODE support, defaults to no
 - `GEN_PDB=<yes/no>`            - Generate External Program Database
                                   (debug symbols for release build)
 - `DEBUG=<yes/no>`              - Debug builds
 - `MACHINE=<x86/x64>`           - Target architecture (default is x86)
 - `CARES_PATH=<path>`           - Custom path for c-ares
 - `MBEDTLS_PATH=<path>`         - Custom path for mbedTLS
 - `NGHTTP2_PATH=<path>`         - Custom path for nghttp2
 - `MSH3_PATH=<path>`            - Custom path for msh3
 - `SSH2_PATH=<path>`            - Custom path for libSSH2
 - `SSL_PATH=<path>`             - Custom path for OpenSSL
 - `ZLIB_PATH=<path>`            - Custom path for zlib

## Microsoft的C RunTime (CRT)静态链接:

如果你使用的是mode=static, nmake将创建并链接到libcurl的静态版本，而不是静态CRT。如果你必须，你可以通过RTLIBCFG=static来强制nmake链接静态CRT。通常不应该使用该选项，nmake将默认使用DLL CRT。RTLIBCFG很少被使用，因此也很少被测试。当为已经构建但不使用该选项的配置传递RTLIBCFG时，或者如果该选项的指定方式不同，则必须销毁包含该配置的构建目录，以便nmake可以从头构建它。

除非您有足够的开发经验，知道如何匹配用于链接的运行时库(即CRT)，否则不建议使用此选项。如果RTLIBCFG=static，则发布构建使用/MT，调试构建使用/MTd。

## 使用libcurl构建自己的应用程序(Visual Studio示例)

 当你构建curl和libcurl时，nmake会显示输出目录所在的相对路径。输出目录从构建时使用的选项nmake中命名。您还可能看到同名的临时目录，但后缀为-obj-curl和-obj-lib。

例如，假设你从Visual Studio 2010 x64 Win64命令提示符中构建了curl.exe和libcurl.dll:

 nmake /f Makefile.vc mode=dll VC=10

输出目录的名称类似于..\builds\libcurl-vc10-x64-release-dll-ipv6-sspi-schannel。

输出目录包含子目录bin、lib和include。这些是要在Visual Studio项目中设置的目录。您可以将输出目录复制到项目中，也可以保留它。下面的例子中，假设您保留了它，并且您的curl top源目录为C:\curl-7.82.0。您可以使用x64平台为配置设置这些选项:

~~~
 - Configuration Properties > Debugging > Environment
    PATH=C:\curl-7.82.0\builds\libcurl-vc10-x64-release-dll-ipv6-sspi-schannel\bin;%PATH%

 - C/C++ > General > Additional Include Directories
    C:\curl-7.82.0\builds\libcurl-vc10-x64-release-dll-ipv6-sspi-schannel\include;

 - Linker > General > Additional Library Directories
    C:\curl-7.82.0\builds\libcurl-vc10-x64-release-dll-ipv6-sspi-schannel\lib;

 - Linker > Input > Additional Dependencies
    libcurl.lib;
~~~

对于使用x86平台(也就是Win32平台)的配置，您需要对libcurl进行单独的x86构建。

如果您构建libcurl静态(mode=static)或调试(debug =yes)，那么库名称将会不同，在同一平台中，您的项目的不同配置可能需要单独的构建。这将在下一节中讨论。

## 使用静态libcurl构建自己的应用程序

在Windows上构建使用静态libcurl库的应用程序时，必须定义CURL_STATICLIB。否则链接器将查找动态导入符号。

静态库名在基础名中有一个'_a'后缀，调试库名在基础名中有一个'_debug'后缀。例如,libcurl_a_debug。Lib是libcurl的静态调试版本。

你可能需要为每个VC配置组合单独构建libcurl(例如:调试|Win32，调试|x64，发布|Win32，发布|x64)。

您必须指定构建静态libcurl所需的任何其他依赖项(例如:advapi32.lib;crypt32.lib; normalize.lib;ws2_32.lib;wldap32.lib)。

## 传统Windows和SSL

当您使用此目录中的构建文件构建curl时，默认的SSL后端将是Schannel (Windows SSPI)，这是Windows操作系统自带的原生SSL库。Windows <= XP中的通道无法连接到不再支持这些版本使用的传统握手和算法的服务器。如果您将在这些早期版本的Windows中使用curl，那么您应该选择另一个SSL后端，如OpenSSL。
