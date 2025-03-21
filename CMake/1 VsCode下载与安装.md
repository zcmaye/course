# 1. MinGW

## 1.1 MinGW简介

MinGW 的全称是：Minimalist GNU on Windows 。它实际上是将经典的开源 C语言 编译器 GCC 移植到了 Windows 平台下，并且包含了 Win32API ，因此可以将源代码编译为可在 Windows 中运行的可执行程序。而且还可以使用一些 Windows 不具备的，Linux平台下的开发工具。一句话来概括：MinGW 就是 GCC 的 Windows 版本 。

以上是 MinGW 的介绍，MinGW-w64 与 MinGW 的区别在于 MinGW 只能编译生成32位可执行程序，而 MinGW-w64 则可以编译生成 64位 或 32位 可执行程序。

正因为如此，MinGW 现已被 MinGW-w64 所取代，且 MinGW 也早已停止了更新，内置的 GCC 停滞在了 4.8.1 版本，而 MinGW-w64 内置的 GCC 则更新到了 8.1.0 版本。

## 1.2 下载与安装

### 1.2.1 下载

1） 打开 [MinGW 官网](https://www.mingw-w64.org/downloads)，往下滑动，找到如下图所示位置，点击SourceForge。

![image-20240409002052593](./assets/image-20240409002052593.png)

2）点击之后进入如下页面

![image-20240409002158639](./assets/image-20240409002158639.png)

3）往下翻，一直翻，找到如下图所示位置

![image-20240409002923541](./assets/image-20240409002923541.png)



**最后面的后缀是不同的异常处理模型**

+ 如果你之前选择了 64位，则这里有两个异常处理模型供你选择，seh 是新发明的，而 sjlj 则是古老的。seh 性能比较好，但不支持 32位。 sjlj 稳定性好，支持 32位。
  **操作**：我这里选择了 seh 。

+ 如果选择了 32位 ，则可以用 dwarf 和 sjlj 两种异常处理模型。同样的，dwarf 的性能要优于 sjlj ，可以它不支持 64位 。
  **操作**：建议选择 dwarf 。

4）点击之后，进入缓慢的下载时间 QAQ！！(我偷偷使用迅雷下载了)

![image-20240409003026562](./assets/image-20240409003026562.png)

5）下载之后得到了.7z的压缩包，解压出来，并进入

![image-20240409005947517](./assets/image-20240409005947517.png)

6）进入解压目录后，可以看到有一个mingw64目录，把它复制到合适的位置

![image-20240409010052402](./assets/image-20240409010052402.png)

`我放到了C:/MySoftware目录`

![image-20240409010221983](./assets/image-20240409010221983.png)

7）最后把`C:\mingw64\bin`目录配置到环境变量

![image-20240409010412665](./assets/image-20240409010412665.png)

 配置好后别忘了点击 **确认！确认！确认！**

8）来，验证一下是否配置成功！

打开`cmd`输入`gcc --version`，出现如图所示内容，表示配置成功

![image-20240409010525200](./assets/image-20240409010525200.png)

## 1.3 基本使用

先来一段代码，命名为main.c。

```c
#include<stdio.h>

int main()
{
    printf("hello world");
    getchar();
    return 0;
}
```

在cmd输入命令：`gcc main.c -o hello`

![image-20240409010906314](./assets/image-20240409010906314.png)

# 2. VS Code

## 2.1 VS Code简介

Visual Studio Code（简称“VS Code” ）是Microsoft在2015年4月30日Build开发者大会上正式宣布一个运行于 Mac OS X、Windows和Linux 之上的，针对于编写现代Web和云应用的跨平台源代码编辑器， 可在桌面上运行，并且可用于Windows，macOS和Linux。它具有对JavaScript，TypeScript和Node.js的内置支持，并具有丰富的其他语言（例如C++，C＃，Java，Python，PHP，Go）和运行时（例如.NET和Unity）扩展的生态系统。

## 2.2 下载与安装

1） 打开 [Visual Studio Code 官网](https://code.visualstudio.com/)，点击Download for Windows按钮下载。(如果需要Linux版本，或者Mac版本可以点击后面的下拉箭头选择)

![image-20220410160043848](assets/image-20220410160043848.png)

2）下载之后得到VSCodeUserSetup-x64-1.66.1.exe，鼠标左键双击安装

![image-20220410160310030](assets/image-20220410160310030.png)

![image-20240408235121359](./assets/image-20240408235121359.png)

3）同意协议，点击下一步

<img src="assets/image-20220410160432475.png" alt="image-20220410160432475"  />

4）选择VS Code安装位置，点击下一步

![image-20240408235343874](./assets/image-20240408235343874.png)

5）一直下一步，直到选择附加任务，把其他里面的 创建上下文菜单选上，即在桌面右键时，会在右键菜单中显示用vs code打开。

![image-20220410160726760](assets/image-20220410160726760.png)

6）然后下一步等待安装完成

![image-20240408235459735](./assets/image-20240408235459735.png)

7）几秒之后安装即可完成！！

![image-20240408235646256](./assets/image-20240408235646256.png)

## 2.3 界面介绍

VS Code安装完毕之后，打开界面如下图

![image-20240409000429046](./assets/image-20240409000429046.png)

## 2.4 安装插件

### 2.4.1 汉化插件

1）进入插件商店：搜索chinese > 选择简体中文 >在右边窗口中点击`install`

![image-20240409000657987](./assets/image-20240409000657987.png)

2）安装完成，右下角会弹出一个提示框，点击按钮`修改语言并重启VS Code`即可汉化成功！

![image-20240409000726697](./assets/image-20240409000726697.png)

3）看成果~~

![image-20240409000818642](./assets/image-20240409000818642.png)

### 2.4.2 C/C++插件

![image-20240409001016066](./assets/image-20240409001016066.png)

### 2.4.3 CMake插件

![image-20240409001208354](./assets/image-20240409001208354.png)

# 3. VS Code+MinGW

Vs Code是基于文件夹管理项目的，所以每个C/C++项目都需要一个单独的目录。

1）在合适的位置创建一个文件夹，如helloworld。

![image-20240409011140130](./assets/image-20240409011140130.png)

2）进入helloworld目录，右键`通过Code打开`(win11按着`shift`再点击鼠标右键)

![image-20240409011309395](./assets/image-20240409011309395.png)

3）打开的时候会提示`是否信任此文件夹中的文件的作者`，点击信任即可~~

![image-20220410170905251](assets/image-20220410170905251.png)

4）创建源文件`main.c`,并写入输出`hello word`的代码

![image-20220410171207870](assets/image-20220410171207870.png)

5）Ctrl+F5运行（F5可以进入调试模式），或者点击菜单栏->运行->以非调试模式运行，然后会弹出窗口，需要选择一下

+ 选择C++（GDB/LLDB）

![image-20220410172623275](assets/image-20220410172623275.png)

+ 选择C/C++:gcc.exe

![image-20220410172731122](assets/image-20220410172731122.png)

+ 在最下面会显示执行结果：hello world

![image-20220410172808070](assets/image-20220410172808070.png)

<font style="color:red">注意：调试的时候，需要先选中源文件，不要点击别的文件，否则会出现错误</font>

# 4. CMake

## 3.1 CMake简介

CMake是一个跨平台的安装（[编译](https://baike.baidu.com/item/编译/1258343)）工具，可以用简单的语句来描述所有平台的安装(编译过程)。

## 3.2 下载与安装

1） 打开 [CMake 官网](https://cmake.org/)，点击Download 。

![image-20240409013120401](./assets/image-20240409013120401.png)

2）往下翻，找到如下图所示位置，这里选择64位压缩包版

![image-20240409013512411](./assets/image-20240409013512411.png)

3）下载下来得到`cmake-3.23.0-windows-x86_64.zip`压缩包，解压出来

![image-20240409015242846](./assets/image-20240409015242846.png)

4）拷贝到合适的位置

![image-20240409015203287](./assets/image-20240409015203287.png)

5）把bin目录`C:\cmake-3.23.0-windows-x86_64\bin`配置到path环境变量

![image-20240409015423188](./assets/image-20240409015423188.png)

5）打开cmd，输入cmake --version测试是否配置成功！

![image-20240409015657620](./assets/image-20240409015657620.png)

如上图所示，ok，配置成功！！

[VS Code CMake 插件安装](#2.4.3 CMake插件)

## 3.3 基本使用

还是用前面创建的helloworld项目，先在`main.c`同级目录中创建`CMakeLists.txt`并写入如下cmake指令。

```cmake
cmake_minimum_required(VERSION 3.5)

project(helloworld)

add_executable(helloworld main.c)
```

+ 内部构建

打开控制台，输入`cmake -G "MinGW Makefiles"`会生成如下文件：

![image-20220412125847956](assets/image-20220412125847956.png)

+ 外部构建

```cmake
cmake -G "MinGW Makefiles" -B build
```

最后，输入命令

```shell
cmake --build build
```

或者

```shell
cd build
mingw32-make
```

生成可执行文件。

![image-20240409020941498](./assets/image-20240409020941498.png)

## 3.4 VSCode CMake开发

C/C++插件、CMake插件安装好之后，就可以使用VsCode结合CMake进行C/C++开发了

1）先创建一个文件夹，然后用Vs Code打开

![image-20220410183702415](assets/image-20220410183702415.png)

2）按快捷键`Ctrl+Shift+P`，或者点击菜单栏->帮助->显示所有命令，输入cmake

+ 选择列表中的`CMake:快速入门`

![image-20220410183804950](assets/image-20220410183804950.png)

+ 紧接着选择一个编译器套件，这里就只有一个，有多个可以看着来

![image-20220410183832399](assets/image-20220410183832399.png)

+ 再给你的项目取个名字，一般和你的项目文件夹名一样即可，选好了之后按回车

![image-20220410184048610](assets/image-20220410184048610.png)

+ 接下来选择你需要生成的目标(Libary 库   Executable 可执行程序)
  + 咱们当然要可执行程序啦

![image-20220410184127602](assets/image-20220410184127602.png)

+ 选择之后，稍等一下，即可自动配置完成(需要提前安装好cmake构建工具哟)！！
+ 如果没有开始配置，重启一下Vs即可！

![image-20240409021516203](./assets/image-20240409021516203.png)

3）按Shitf+F5就可以编译，并运行程序啦！

+ 按Ctrl+F5可以进入调试模式哦

![image-20240409021615669](./assets/image-20240409021615669.png)

在左边工具栏的cmake视图中，可以看到项目的状态，并可以进行一些配置：

![image-20240409021720973](./assets/image-20240409021720973.png)
