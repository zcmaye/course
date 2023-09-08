# OBS源码下载与编译

### 先决条件

- Windows 10 1909+ (or Windows 11)
- Visual Studio 2022 (at least Community Edition)
  - Windows 10 SDK (minimum 10.0.20348.0)
  - C++ ATL for latest v143 build tools (x86 & x64)
- [Git for Windows](https://git-scm.com/downloads)
- [CMake 3.24 or newer](https://cmake.org/)

### 配置和构建项目

1. 克隆包含子模块的存储库：

   `git clone --recursive https://github.com/obsproject/obs-studio.git`

2. 设置当前目录到`obs-studio`

   `cd obs-studio`

3. 检查可用的CMake预设：`cmake --list-presets`

4. 选择`windows-x64`预设：`cmake --preset windows-x64`

   + 可用和支持的体系结构有：x64
     + 不再支持X86(32位)版本的obs-studio
   + 任何其他CMake变量都可以像往常一样提供，如果必要的话，也可以覆盖由预设设置的变量

### 详细流程

+ 执行`git clone --recursive https://github.com/obsproject/obs-studio.git`命令，克隆仓库到本地(若下载不成功，请在[网盘下载](https://pan.baidu.com/s/1sR9Nfvp1zZuaSfEd0D3UyQ?pwd=6y8a))。

![image-20230905130455446](assets/image-20230905130455446.png)

+ 切换到`obs-studio`目录

![image-20230905130611139](assets/image-20230905130611139.png)

+ 查看CMake有效预设

  ![image-20230905130640158](assets/image-20230905130640158.png)

+ 选择CMake预设并构建

![image-20230905130827207](assets/image-20230905130827207.png)

#### 包不能下载?

在构建项目时，会自动下载需要的依赖包，如下，总共四个

![image-20230905131153529](assets/image-20230905131153529.png)

![image-20230905131207043](assets/image-20230905131207043.png)

![image-20230905131238766](assets/image-20230905131238766.png)

![image-20230905131254933](assets/image-20230905131254933.png)

但是由于各种原因，会导致下载卡顿、缓慢甚至错误，所以，需要我们自己去下载。

> 只需要复制提示的下载链接然后使用迅雷就可以快速下载了！如果不行，我提供了[网盘已经下载好的包]()！

下载完成后放到指定位置，`obs-studio/.deps/`，<font color=red>注意：不用解压，也不能解压，他会自动给你解压的！</font>

![image-20230905131816150](assets/image-20230905131816150.png)

确保无误之后，重新执行`cmake --preset windows-x64`命令，成功后进入`build_x64`目录。

![image-20230905152522397](assets/image-20230905152522397.png)

然后打开工程，编译

![image-20230905152609349](assets/image-20230905152609349.png)

ok，成功啦！

![image-20230905153210543](assets/image-20230905153210543.png)