## SDL 简介

### 什么是 SDL？

Simple DirectMedia Layer 是一个跨平台开发库，旨在通过 OpenGL 和 Direct3D 提供对音频、键盘、鼠标、游戏杆和图形硬件的低级访问。它被视频播放软件、模拟器和流行游戏使用，包括[Valve](http://valvesoftware.com/)的获奖目录和许多[Humble Bundle](https://www.humblebundle.com/)游戏。

SDL 正式支持 Windows、Mac OS X、Linux、iOS 和[Android](https://wiki.libsdl.org/Android)。可以在源代码中找到对其他平台的支持。

SDL 是用 C 编写的，在本机上与 C++ 一起使用，并且有适用于其他几种语言的绑定，包括 C# 和 Python。

SDL 3.0 在[zlib 许可](http://www.gzip.org/zlib/zlib_license.html)下分发。此许可证允许您在任何软件中自由使用 SDL。简单直接媒体层库 (SDL) 是一个通用 API，它提供对音频、键盘、鼠标、游戏杆、通过 OpenGL 的 3D 硬件以及跨多个平台的 2D 帧缓冲区的低级别访问。

### SDL 可以做什么？

**视频**

- 3D图形：SDL 可与 OpenGL API 或 Direct3D API 结合使用，用于 3D 图形
- 加速 2D 渲染 API：支持简单的旋转、缩放和 alpha 混合，所有这些都使用现代 3D API 加速，使用 OpenGL 和 Direct3D 支持加速
- 创建和管理多个窗口

**输入事件**

- 提供的事件和 API 函数用于：
  - 应用程序和窗口状态更改
  - 鼠标输入
  - 键盘输入
  - 操纵杆和游戏控制器输入
  - 多点触控手势
- 可以使用[SDL_EventState](https://wiki.libsdl.org/SDL_EventState) ()启用或禁用每个事件
- 事件在发布到内部事件队列之前通过用户指定的过滤器函数
- 线程安全事件队列

**力反馈**

- Windows、Mac OS X 和 Linux 支持力反馈

**音频**

- 设置8位和16位音频、单声道立体声或5.1环绕声的音频播放，如果硬件不支持格式，可选择转换
- 音频在单独的线程中独立运行，通过用户回调机制填充
- 专为定制软件混音器设计，但[SDL_mixer](http://www.libsdl.org/projects/SDL_mixer/)提供完整的音频/音乐输出库

**文件 I/O 抽象**

- 用于打开、读取和写入数据的通用抽象
- 对文件和内存的内置支持

**共享对象支持**

- 加载共享对象（Windows 上的 DLL，Mac OS X 上的 .dylib，Linux 上的 .so）
- 共享对象中的查找函数

**线程**

- 简单的线程创建API
- 简单线程本地存储API
- 互斥体、信号量和条件变量
- 无锁编程的原子操作

**计时器**

- 获取经过的毫秒数
- 等待指定的毫秒数
- 在单独的线程中创建与代码一起运行的计时器
- 使用高分辨率计数器进行分析

**CPU 特性检测**

- 查询CPU数量
- 检测 CPU 特性和支持的指令集

**大端小端支持**

- 检测当前系统的字节序
- 用于快速交换数据值的例程
- 读取和写入指定字节序的数据

**电池管理**

- 查询电源管理状态

### SDL 在哪些平台上运行？

**Windows**

- 使用 Win32 API 进行显示，利用 Direct3D 进行硬件加速
- 使用 DirectSound 和 XAudio2 作为声音

**Mac OS X**

- 使用 Cocoa 进行视频显示，利用 OpenGL 进行硬件加速
- 使用 Core Audio 播放声音

**Linux**

- 使用 X11 进行视频显示，利用 OpenGL 进行硬件加速
- 使用 ALSA、OSS 和 PulseAudio API 来处理声音

**IOS**

- 使用 UIKit 进行视频显示，利用 OpenGL ES 2.0 进行硬件加速
- 使用 Core Audio 播放声音

**Android**

- 使用 JNI 接口进行视频显示，利用 OpenGL ES 1.1 和 2.0 进行硬件加速
- 对声音使用 JNI 音频回调



## 如何获取和安装 SDL

### SDL3库下载

+ SDL3 核心库 [SDL3](https://libsdl.org/download-2.0.php)
+ SDL3 拓展库 [SDL3_image、SDL3_ttf、SDL3_mixer、SDL3_net](https://libsdl.org/projects/)

### 安装SDL3

1. 点击[SDL3 核心库下载](https://libsdl.org)下载SDL3库，进入GitHub下载。

![QQ_1781696730957](./assets/QQ_1781696730957.png)

![QQ_1781696826794](./assets/QQ_1781696826794.png)

2. 下载的是一个压缩包，放到一个合适的目录(记住这个目录哦，经常要用的)，解压。

![QQ_1781697424915](./assets/QQ_1781697424915.png)

3. 进入解压后的目录，如下图：
   1. cmake：cmake配置文件
   3. include：头文件目录，编程需要的
   4. lib：库目录(静态库和动态库都有)

![QQ_1781706006621](./assets/QQ_1781706006621.png)

4. 给环境变量添加库目录，让程序运行的时候能够找到动态库。<font style="color:red">PS：配置好了记得重启Vs</font>

![QQ_1781706359483](./assets/QQ_1781706359483.png)

### VS中使用SDL3

1. 创建一个空项目，如下图：

![QQ_1781706594863](./assets/QQ_1781706594863.png)

2. 进入菜单栏的项目->属性->VC++ 目录，配置包含目录和库目录(详见下图)，注意库目录的版本和你的项目版本要一直哦(图中两个三角形标记的位置，我这是x64的)。

![QQ_1781706715667](./assets/QQ_1781706715667.png)

3. 不要离开，还有静态库需要配置，进入链接器->输入->点击附加依赖项->填入SDL3.lib，然后确定就好

![QQ_1781706845352](./assets/QQ_1781706845352.png)

4. 最后加入如下代码，Ctrl+F5运行

```c
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int main(int argc,char*argv[])
{
	//初始化SDL
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("can not init SDL:%s", SDL_GetError());
		return -1;
	}

	return 0;
}
```

如果能出现黑窗口并且，没有任何错误提示，那么就恭喜你啦，SDL配置完成~(不过麻烦的是每次创建新项目和在x86、x64之间切换时，都要进行配置~后面会讲解更方便的方法)！

SDL 作为动态链接库。动态链接库包含 3 个部分：

- 头文件 (Library.h)
- 库文件（Windows 的Library.lib 或 *nix 的libLibrary.a）
- 二进制文件（Windows 的Library.dll 或*nix 的Library.so）

你的编译器需要能够在编译时找到头文件，以便它知道SDL 函数和结构是什么。可以将编译器配置为在 SDL 头文件所在的附加目录中进行搜索，或者将头文件与编译器附带的其余头文件一起放入。如果编译器提示找不到 SDL.h，则意味着头文件不在编译器查找头文件的位置。

在编译器编译所有源文件后，它必须将它们链接在一起。为了使程序正确链接，它需要知道所有函数的地址，包括 SDL 函数的地址。对于动态链接库，这些地址在库文件中。库文件具有导入地址表，因此您的程序可以在运行时导入函数。与头文件一样，您可以将编译器配置为在 SDL 库文件所在的附加目录中进行搜索，或者将库文件与编译器附带的其余库文件一起放入。您还必须告诉链接器链接到链接器中的库文件。如果链接器报错找不到-lSDL或SDL3.lib，它意味着库文件不在链接器寻找库文件的地方。 如果链接器报错了一个未定义的引用，这可能意味着它没有链接这个库。  

在您的程序被编译和链接之后，您需要能够在运行时链接到该库。为了运行动态链接的应用程序，您需要能够在运行时导入库二进制文件。当您运行程序时，您的操作系统需要能够找到库二进制文件。您可以将库二进制文件放在与可执行文件相同的目录中，也可以放在操作系统保存库二进制文件的目录中。

### CMake使用SDL3

1. 把SDL3的根目录，配置到环境变量`F:\Tools\SDL3\SDL3-2.26.1`

2. 创建CMake项目，并在CMakeLists.txt文件中写入如下命令

   ```cmake
   #CMake最小请求版本
   cmake_minimum_required (VERSION 3.8)
   
   #项目名称
   project ("SDL3_CMake")
   
   #查找SDL3包，REQUIRED强制请求，没找到报错
   find_package(SDL3 REQUIRED)
   
   #使用指定的源文件生成目标(SDL3_CMake)
   add_executable (SDL3_CMake "main.c")
   
   #指定目标在链接时需要的依赖(库)
   target_link_libraries(SDL3_CMake SDL3::SDL3)
   ```

3. 创建`main.c`源文件，写入如下代码

   ```cpp
   #include "SDL3/SDL.h"
   int main(int argc, char* argv[])
   {
   	SDL_Log("%d %s\n", SDL_GetVersion(),SDL_GetRevision());
   	return 0;
   }
   ```
   
4. 成功运行！

![QQ_1781780450791](./assets/QQ_1781780450791.png)

## SDL3教程

+ [SDL3 维基文档](https://wiki.libsdl.org/wiki/index)

+ [SDL3各种教程集合](https://wiki.libsdl.org/Tutorials)

### 1.简单窗口

```c
#include "SDL3/SDL.h"

//屏幕尺寸常量
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
```

首先包含SDL.h头文件。  然后定义我们需要的窗口宽度和高度常量。

```c
int main(int argc, char* argv[])
{
	//初始化SDL子系统
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("can not init SDL:%s", SDL_GetError());
		return -1;
	}
```

注意主函数的形参，必须是一个整型，后跟上一个char*数组(参数分别代表命令行参数个数和命令行参数数组)，不能是其他形式的main函！

在主函数中我们先调用SDL_init初始化函数，如果不先初始化 SDL，就不能调用任何 SDL 函数。暂时我们只需要SDL的视频子系统，所以我们先只将 SDL_INIT_VIDEO 标志传递给它。

当发生错误时，SDL_Init 返回false。当出现错误时，我们可以将具体的错误原因打印到控制台。

在SDL中有一个和printf函数功能相同的函数，即SDL_Log。然后用SDL_GetError获取错误字符串并打印出来。

```c
	//创建窗口
	SDL_Window*window = SDL_CreateWindow(u8"C语言Plus", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	//判断是否创建成功
	if (!window) {
		SDL_Log("can not  create window:%s", SDL_GetError());
		return -1;
	}
```

如果SDL成功初始化，我们将使用SDL_CreateWindow创建一个窗口。 

+ 第一个参数设置窗口的标题；
+ 接下来两个参数分别是窗口的x和y，即窗口在屏幕上的位置，我们不关心位置在那里，所以直接传SDL_WINDOWPOS_UNDEFINED即可；

+ 接下来的两个参数分别表示窗口的宽度和高度；
+ 最后一个参数表示窗口创建成功之后显示出来。

如果有错误，SDL_CreateWindow 返回 NULL。我们将错误打印到控制台。

如果窗口被成功创建，则会显示到桌面。 

为了防止它消失，我们将调用SDL_Delay。 SDL_Delay将等待给定的毫秒数。 一毫秒是千分之一秒。 这意味着上面的代码将使窗口等待2000 /1000秒或2秒。  

需要注意的重要一点是，当SDL延迟时，它不能接受来自键盘或鼠标的输入。 当您运行这个程序时，如果它没有响应，请不要惊慌。 我们没有给它处理鼠标和键盘的代码。  

```c
	//延迟5秒
	SDL_Delay(5000);
	//销毁窗口
	SDL_DestroyWindow(window);
	//清理所有初始化的子系统
	SDL_Quit();
	return 0;
}
```

最后我们让程序延迟5秒再退出，否则窗口会一闪而过；退出之前需要调用SDL_DestroyWindow手动销毁窗口和调用SDL_Quit清理所有初始化的子系统。

### 2.图形渲染

#### 渲染器

渲染器是负责从模型生成图像的工具，主要是将场景中的模型，按照设定好的环境、灯光、材质及渲染参数，投影成数字图像。

模型是用严格定义的语言或者数据结构对于物体的描述，它包括几何、视点、纹理以及照明信息。

```c
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Renderer could not be created!%s", SDL_GetError());
		return -1;
	}

```

创建窗口后，我们必须为窗口创建一个渲染器，以便我们可以在其上渲染纹理。幸运的是，这可以通过调用[SDL_CreateRenderer](http://wiki.libsdl.org/SDL_CreateRenderer)轻松完成。

创建渲染器后，可以使用 [SDL_SetRenderDrawColor](http://wiki.libsdl.org/SDL_SetRenderDrawColor) 初始化渲染颜色。这用于控制各种渲染操作的颜色。

```c
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
```

然后调用SDL_RenderClear清除渲染目标，它会使用前面设置的颜色进行清除，此时还不能让窗口变为白色背景，必须调用SDL_RenderPresent让渲染结果呈现出来。

最后，记得调用SDL_DestroyRenderer销毁掉渲染器。

#### 渲染图形

接下来我们来使用渲染器绘制基本的几何图形，SDL3支持的基本图形有：

+ 点

  ```cpp
  bool SDL_RenderPoint(SDL_Renderer *renderer, float x, float y);
  bool SDL_RenderPoints(SDL_Renderer *renderer, const SDL_FPoint *points, int count);
  ```

+ 线

  ```cpp
  bool SDL_RenderLine(SDL_Renderer *renderer, float x1, float y1, float x2, float y2);
  bool SDL_RenderLines(SDL_Renderer *renderer, const SDL_FPoint *points, int count);
  ```

+ 矩形

  ```cpp
  bool SDL_RenderRect(SDL_Renderer *renderer, const SDL_FRect *rect);
  bool SDL_RenderRects(SDL_Renderer *renderer, const SDL_FRect *rects, int count);
  bool SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_FRect *rect);
  bool SDL_RenderFillRects(SDL_Renderer *renderer, const SDL_FRect *rects, int count);
  ```

+ 颜色混合模式

  ```cpp
  bool SDL_SetRenderDrawBlendMode(SDL_Renderer *renderer, SDL_BlendMode blendMode);
  
  //常用混合模式如下    
  SDL_BLENDMODE_NONE = 0x00000000,     /**< 没有混合，即正常模式*/
  SDL_BLENDMODE_BLEND = 0x00000001,    /**< 透明混合，透明度生效*/                  
  SDL_BLENDMODE_ADD = 0x00000002,      /**< 叠加混合，即颜色叠加*/  
  ...
  ```


+ 自定义的绘制圆形的函数

```cpp
void ZC_RenderCircle(SDL_Renderer*renderer,int x, int y, int radius)
{
	int xbase = 0, ybase = radius, pos = 0;
	int d = (1 - radius) << 1;
	while (ybase >= 0)
	{
		if (d > 0)
		{
			if (((d - xbase) << 1) - 1 <= 0)
			{
				d = d + ((xbase - ybase + 3) << 1);
				xbase++;
				ybase--;
			}

			else
			{
				d = d - (ybase << 1) + 3;
				ybase--;
			}
		}
		else if (d < 0)
		{
			if (((d + ybase) << 1) - 1 <= 0) d = d + (xbase << 1) + 3, xbase++;
			else d = d + ((xbase - ybase + 3) << 1), xbase++, ybase--;
		}
		else
		{
			d = d + ((xbase - ybase + 3) << 1);
			xbase++;
			ybase--;
		}
		SDL_RenderPoint(renderer,x + xbase - 1, y + ybase);        //右下
		SDL_RenderPoint(renderer,x - xbase, y + ybase);                 //左下
		SDL_RenderPoint(renderer,x + xbase - 1, y - ybase);             //右上
		SDL_RenderPoint(renderer,x - xbase, y - ybase);                 //左上
	}
}

void ZC_RenderFillCircle(SDL_Renderer* renderer,int x, int y, int radius)
{
	float y0, y1;
	float xx = 0;
	float msin = 0;
	for (float angle = 0; angle < 3.14; angle += 0.001)
	{
		xx = x + radius * SDL_cos(angle);

		msin = SDL_sin(angle);

		y0 = y + radius * msin;
		y1 = y + radius * (-msin);

		SDL_RenderLine(renderer, xx, y0, xx, y1);
	}
}

void ZC_RenderArc(SDL_Renderer* pRender, SDL_Rect* rect, float startAngle, float endAngle)
{
	if (startAngle == endAngle)
		return;

	//计算开始弧度和结束弧度
	float minA = SDL_min(startAngle, endAngle);
	float maxA = SDL_max(startAngle, endAngle);

	//半轴长
	float aHalf = rect->w / 2;
	float bHalf = rect->h / 2;

	float x, y;													//本次计算的点
	float prevx = (rect->x + aHalf) + aHalf * SDL_cos(minA);	//上一次计算出来的点
	float prevy = (rect->y + bHalf) + bHalf * SDL_sin(minA);
	//求出圆上每个坐标点
	for (float angle = minA; angle <= maxA; angle += 0.05f)
	{
		x = (rect->x + aHalf) + aHalf * SDL_cos(angle);
		y = (rect->y + bHalf) + bHalf * SDL_sin(angle);
		SDL_RenderPoint(pRender, x, y);
		SDL_RenderLine(pRender, prevx, prevy, x, y);
		prevx = x;
		prevy = y;
	}
}

void ZC_RenderEllipse(SDL_Renderer* pRender, SDL_Rect* rect)
{
	//半轴长
	int aHalf = rect->w / 2;
	int bHalf = rect->h / 2;

	float x, y;
	float prevx = (rect->x + aHalf *2);
	float prevy = (rect->y + bHalf);
	float firstx = prevx;
	float firsty = prevy;
	//求出圆上每个坐标点
	for (float angle = 0; angle < 2 * 3.14; angle += 0.05f)
	{
		x = (rect->x + aHalf) + aHalf * SDL_cos(angle);
		y = (rect->y + bHalf) + bHalf * SDL_sin(angle);
		SDL_RenderPoint(pRender, x, y);
		SDL_RenderLine(pRender, prevx, prevy, x, y);
		prevx = x;
		prevy = y;
	}
	SDL_RenderLine(pRender, firstx, firsty, x, y);	//最后连上
}
```

#### 渲染纹理

我们都知道游戏中最常用到的就是图形渲染，简单地说就是将图像显示到屏幕上。图像在 SDL 中被封装为一个叫做纹理的结构体 SDL_Texture，它代表了所有像素相关的内容数据。

SDL 中提供了 SDL_CreateTexture 和 SDL_DestroyTexture来创建和销毁纹理，但是在现实中，很少从头创建一个新纹理，一般情况都是从硬盘上直接加载相关的图片转换为纹理结构体。SDL 也提供了相关的函数：

```c
SDL_Surface *SDL_LoadBMP(const char* file);
```

这个函数可以从本地磁盘上加载一个位图图片，不过这里有两个重点需要提及：

- 文件只能是位图图片，也就是常见以 bmp 后缀的图片文件。

- 函数返回的并不是 SDL_Texture 结构体指针，而是另一种叫做 SDL_Surface 结构体的指针对象。

> 之所以该接口只支持位图是因为位图图像的格式比较简单，并不涉及图片压缩编码之类的操作，图片数据只是按照一定格式对像素的简单排列，这也是为什么位图图片相比于其它图片要大上很多的原因。

```c
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* sfc = SDL_LoadBMP(filename);
	if (!sfc) {
		SDL_Log("<%s> load failed:%s", filename, SDL_GetError());
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sfc);
	if (!tex) {
		SDL_DestroySurface(sfc);
		return NULL;
	}
	SDL_DestroySurface(sfc);
	return tex;
}
```

首先使用SDL_LoadBMP函数把bmp图像加载到内存，然后使用SDL_CreateTextureFromSurface函数从surface创建一个texture，最后吧surface释放掉。

```c
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	SDL_Rect drect = { tex->w,tex->h };
	SDL_RenderTexture(renderer, tex, NULL, &drect);

	SDL_RenderPresent(renderer);
```

接着使用 SDL_RenderTexture将纹理拷贝到后台缓冲中，最后在使用完毕后释放相关资源。

函数原型如下：

```c
bool SDL_RenderTexture(SDL_Renderer*   renderer,
                   SDL_Texture*    texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect)
```

+ renderer 渲染器
+ texture 纹理
+ srcrect 表示纹理的那部分绘制出来，如果为NULL，则全部绘制
+ dsrrect 表示要绘制到屏幕上的目标矩形，如果和srcrect不同，则会自动进行缩放

#### SDL_image

如果想要加载其他格式的图片，需要使用SDL_image拓展库。

```c
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* sfc = IMG_Load(filename);
    ...
```

把loadTexture中的SDL_LoadBMP改为IMG_Load即可支持海量格式的图片。

```c
//SDL_Texture* tex = loadTexture(renderer, "Resource/pig.bmp");
SDL_Texture* tex = IMG_LoadTexture(renderer, "Resource/pig.bmp");
```

或者直接把loadTexture改为IMG_LoadTexture即可直接加载纹理，不需要先加载成Sruface再转成Texture，非常方便。

#### 加载动画(GIF)  

SDL_image还提供了IMG_LoadAnimation用来加载GIF动画。

```c
	//加载GIF
	IMG_Animation* anima = IMG_LoadAnimation("Resource/images/jump.gif");
	if (!anima) {
		SDL_Log("animation load failed:%s", SDL_GetError());
		return -1;
	}
```

IMG_Animation里保存了有关GIF动画的所有信息：

```c
typedef struct
{
	int w, h;				//每帧的大小
	int count;				//总帧数
	SDL_Surface **frames;	//每帧图像数组
	int *delays;			//每帧之间的间隔数组(可能每帧切换时，间隔不一样)
} IMG_Animation;
```

加载之后图像时Surface格式的，我们必须转成Texture才能进行渲染。

```c
	//把GIF的Surface转成Texture
	int w = anima->w;
	int h = anima->h;
	int delay = *anima->delays;
	int size = anima->count;
	SDL_Texture** texs = SDL_calloc(anima->count, sizeof(SDL_Texture*));
	for (int i = 0; i < anima->count; i++) {
		texs[i] = SDL_CreateTextureFromSurface(renderer, anima->frames[i]);
		SDL_Log("%d %d", i, anima->delays[i]);
	}
	IMG_FreeAnimation(anima);
```

定义变量，把IMG_Animation的信息保存下来，然后把anima释放掉。

```c
	int index = 0;
	while (true)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);

		SDL_FRect rect = { 0,100,w,h };
		SDL_RenderTexture(renderer, texs[index], NULL, &rect);
		//index = (index + 1) % size;
		index = SDL_GetTicks() / delay % size;

		//...
		SDL_RenderPresent(renderer);
	}	//延迟5秒
```

定义index表示当前正在渲染的帧，然后使用`index = (index + 1) % size;`让index进行变化，这样就动起来了，当然，这种方式会让动画的播放变得非常快。可以把delay进入进来，使用`index = SDL_GetTicks() / delay % size;`既可以做到以指定的间隔进行播放。

```c
	for (int i = 0; i < size; i++) {
		SDL_DestroyTexture(texs[i]);
	}
	SDL_free(texs);
```

最后记得释放掉相关资源。

### 3.事件处理

#### 事件处理流程

除了将图像放在屏幕上之外，游戏还要求您处理来自用户的输入。您可以使用 SDL事件处理系统来做到这一点。(把一下代码放到main函数中)

```c
            //主循环标志
            bool isRunning = true;
```

在输出表面和更新窗口表面之后，我们声明了一个退出标志，用于跟踪用户是否已退出。由于此时我们刚刚启动了应用程序，显然它被初始化为false。

我们还声明了一个[SDL_Event](http://wiki.libsdl.org/SDL_Event?highlight=(\bCategoryStruct\b)|(CategoryEvents))联合。SDL事件是有意义的，比如 [按键](http://wiki.libsdl.org/SDL_KeyboardEvent?highlight=(\bCategoryStruct\b)|(CategoryEvents))、 [鼠标移动](http://wiki.libsdl.org/SDL_MouseMotionEvent?highlight=(\bCategoryStruct\b)|(CategoryEvents))、 [操纵杆 按钮按下](http://wiki.libsdl.org/SDL_JoyButtonEvent?highlight=(\bCategoryStruct\b)|(CategoryEvents))等。在这个应用程序中，我们将找到退出事件来结束应用程序。

```c
            //应用程序主循环
            while( !isRunning )
            {
```

在之前的教程中，我们让程序在关闭前等待几秒钟。 在这个应用程序中，我们让应用程序等到用户退出后才关闭。  

当用户没有退出时，我们会有应用程序循环。 这种在应用程序处于活动状态时持续运行的循环称为主循环，有时也称为游戏循环。 它是任何游戏应用程序的核心。  

```c
         		//事件处理
            	static SDL_Event ev ={0};

				//处理队列上的事件
                while( SDL_PollEvent( &ev ) != 0 ){
                    //用户请求退出
                    if( ev.type == SDL_EVENT_QUIT){
                       isRunning = false;
                    }
                }
```

在主循环里面写了事件循环。 这样做的作用是继续处理事件队列，直到它为空。  

当您按下一个键、移动鼠标或触摸触摸屏时，事件就会被放到事件队列中。  

![img](assets/enqueue.png)

然后事件队列将按照事件发生的顺序存储它们，等待您处理它们。 当您想知道发生了什么事件以便处理它们时，您可以轮询事件队列，通过调用SDL_PollEvent获取最近的事件。 SDL_PollEvent所做的就是从事件队列中取出最近的事件，并将该事件中的数据放入我们传递给函数的SDL_Event中。  

![img](assets/dequeue.png)

SDL_PollEvent 将不断从队列中取出事件，直到队列为空。当队列为空时，SDL_PollEvent 将返回 0。所以这段代码所做的就是不断轮询事件队列中的事件，直到它为空。如果来自事件队列的事件是 SDL_EVENT_QUIT 事件（用户点击窗口右上角关闭按钮产生的事件），我们将退出标志设置为 true，以便我们可以退出应用程序。

```c
                //输出图片
                SDL_RenderTexture(renderer,tex, NULL,&rect );
            
                SDL_RenderPresent(renderer);
            }
```

在我们处理完一帧的事件后，我们绘制到屏幕并更新它。如果退出标志设置为真，应用程序将在循环结束时退出。如果它仍然是假的，它将一直持续到用户 X 掉窗口。

#### 键盘事件

退出事件只是 SDL 能够处理的事件之一。在游戏中大量使用的另一种输入是键盘。在本教程中，我们将根据您按下的键对图像进行移动  。  

```c
	//加载图片
	SDL_Texture* tex = loadTexture(renderer, "Resource/images/pig.bmp");
	//定义坐标点
	int x = 0;
	int y = 0;


	//主循环标志
	bool isRunning = true;
	while (isRunning)
	{
```

在main函数中，在进入主循环之前，我们先将图片进行加载，并且定义坐标点x和y。  

```c
		static SDL_Event ev;
		//处理队列中的事件
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
			//按键按下
			else if (ev.type == SDL_EVENT_KEY_DOWN) {
				switch (ev.key.key)
				{
				case SDLK_UP:
					y--;
					break;
				case SDLK_DOWN:
					y++;
					break;
				case SDLK_LEFT:
					x--;
					break;
				case SDLK_RIGHT:
					x++;
					break;
				default:
					x = 0;
					y = 0;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//清屏
		SDL_RenderClear(renderer);
		
		//在窗口上显示图片
		SDL_RenderTexture(renderer, tex, NULL, &(SDL_FRect){ x, y, tex->w, tex->h });
		SDL_RenderPresent(renderer);
	}
```

这是我们的事件循环。如您所见，我们像在上一个教程中一样处理[关闭窗口](https://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php)，然后处理 SDL_EVENT_KEY_DOWN 事件。当您按下键盘上的某个键时，就会发生此事件。[SDL 事件](http://wiki.libsdl.org/SDL_Event?highlight=(\bCategoryStruct\b)|(CategoryEvents))内部 是一个 [SDL 键盘事件](http://wiki.libsdl.org/SDL_KeyboardEvent)，它包含按键事件的信息。该 Key 包含标识按下的键的 [SDL 键码](http://wiki.libsdl.org/SDL_Keycode)。 如您所见，此代码的作用是根据按下的键设置表面。如果您想了解其他键的其他键码是什么，请查看 SDL 文档。

#### 鼠标事件

```c
		static SDL_Event ev;
		//处理队列中的事件
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
			//鼠标移动
			else if (ev.type == SDL_EVENT_MOUSE_MOTION) {
				x = ev.motion.x - tex->w / 2;
				y = ev.motion.y - tex->h / 2;
			}
			//鼠标按键按下
			else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)		//左键
				{
					//判断左键是否双击了
					if (ev.button.clicks == 2) {
						SDL_Log(u8"双击666");
					}
					else {
						SDL_Log(u8"左键按下");
					}
				}
				else if (ev.button.button == SDL_BUTTON_RIGHT)	//右键
				{
					SDL_Log(u8"右键按下");
				}
				else if (ev.button.button == SDL_BUTTON_MIDDLE)	//中键
				{
					SDL_Log(u8"中键按下");
				}
			}
			//鼠标按键弹起
			else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				if (ev.button.button == SDL_BUTTON_LEFT)		//左键
				{
					SDL_Log(u8"左键弹起");
				}
				else if (ev.button.button == SDL_BUTTON_RIGHT)	//右键
				{
					SDL_Log(u8"右键弹起");
				}
				else if (ev.button.button == SDL_BUTTON_MIDDLE)	//中键
				{
					SDL_Log(u8"中键弹起");
				}
			}
			//滚轮
			else if (ev.type == SDL_EVENT_MOUSE_WHEEL) {
				SDL_Log("xy(%f %f)  nxy(%d %d)  mxy(%f %f)",
					ev.wheel.x, ev.wheel.y,					//滚轮滚动方向 -1 为远离自己方向滚动 1 为向自己滚动
					ev.wheel.integer_x, ev.wheel.integer_y,	//同上（整数版本的）
					ev.wheel.mouse_x, ev.wheel.mouse_y);		//滚轮滚动时鼠标的坐标
			}
		}
```

### 4.文本渲染

文本渲染和图像渲染本质上是一样的，渲染文字之前先将文字转化为纹理，然后在通过绘制图片的方式绘制文字。SDL 默认是不支持文字渲染的，但是官方的扩展库 [SDL_ttf](https://meishizaolunzi.com/sdl_ttf-jing-tai-bian-yi-jiao-cheng/) 支持文字的渲染。该库支持 TrueType 字体渲染，TrueType 字体就是我们常用的 ttf 为后缀的字体，直接在 Windows 的字体文件夹下就可以找到。

找到合适的字体之后，接下来先用 TTF_OpenFont 打开字体，接着用 TTF_RenderText_Blended 函数将文字转换为 SDL_Surface 结构体，后面的步骤就和显示图片步骤完全一致了。

```c
	if (!TTF_Init()) {
		SDL_Log("can not init SDL ttf:%s", SDL_GetError());
		return -1;
	}

	...
	TTF_Quit();    
```

首先，调用TTF_Init初始化SDL_ttf库，最后，调用TTF_Quit退出。

```c
	SDL_Color text_color = { 255,0,0,255 };
	// 3. 创建文字表面（三种渲染模式）
	// 模式1：Solid 最快，锯齿明显
	//SDL_Surface* surf = TTF_RenderText_Solid(font, "SDL3 文字渲染测试", 0, text_color);
	// 模式2：Shaded 带背景底色
	//SDL_Surface* surf = TTF_RenderText_Shaded(font, u8"SDL3 文字渲染测试",0,  text_color, (SDL_Color){0,0,0,255});
	// 模式3：Blended 抗锯齿，最清晰（推荐）
	SDL_Surface* surf = TTF_RenderText_Blended(font, u8"SDL3 文字渲染测试",0, text_color);
	if (!surf) {
		SDL_Log("renderText failed,%s", SDL_GetError());
	}
	SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, surf);
	if (!textTex) {
		return -1;
	}
	SDL_DestroySurface(surf);

```

在正式渲染文本之前，需要使用TTF_OpenFont打开一个字体。

接着使用TTF_RenderText_Blended把文本按照指定的字体和颜色渲染成图片，再转为纹理，转为纹理之后就可以使用SDL_DestroySurface把图片释放掉了。

> 使用const char * TTF_GetFontFamilyName(const TTF_Font *font)获取字体名

#### 中文乱码

如果你渲染中文，你会发现中文会先出小框框，也就是乱码了。

```c
TTF_RenderText_Blended(font, "hello wrold 顽石", c);
```

![image-20230530182850378](assets/image-20230530182850378.png)

这是因为SDL在内部使用utf8编码，而我们使用Vs写的字符串默认是gbk编码，编码不对中文就会解析出错！

有两种解决方案：

1. 在字符串前面加了u8， 加上u8可以把字符串转为utf8编码。
2. 或者在属性页中将C/C++下的命令行选项中添加`/utf-8`选项！！！

![image-20230530183025256](assets/image-20230530183025256.png)

#### 文本大小

```c
bool TTF_GetStringSize(TTF_Font *font, const char *text, size_t length, int *w, int *h);
```

SDL_ttf提供了获取文本大小的函数，`TTF_GetStringSize`用来获取utf8编码文本大小。

```c
bool  TTF_SetFontSize(TTF_Font *font, float ptsize);
float TTF_GetFontSize(TTF_Font *font);
```

使用`TTF_SetFontSize`可以设置font的大小，`TTF_GetFontSize`获取字体大小。

```c
int SDLCALL TTF_GetFontHeight(const TTF_Font *font);
```

使用TTF_GetFontHeight可以获取文本高度，这通常是字体pointSize。

```c
int SDLCALL TTF_GetFontAscent(const TTF_Font *font)
int  TTF_GetFontDescent(const TTF_Font *font);

int  TTF_GetFontLineSkip(const TTF_Font *font);
void TTF_SetFontLineSkip(TTF_Font *font, int lineskip);
```

`baseline`是文字绘制基准线，一般情况下 `Ascent` 及 `Descent` 分别表示字形绘制区域的上下限。

`LineSkip`用于控制行间距的大小。

![img](assets/20211117140012_a94ouuc45m.image)

#### 字体样式

```c
#define TTF_STYLE_NORMAL        0x00	//正常字体
#define TTF_STYLE_BOLD          0x01	//加粗
#define TTF_STYLE_ITALIC        0x02	//斜体
#define TTF_STYLE_UNDERLINE     0x04	//下划线
#define TTF_STYLE_STRIKETHROUGH 0x08	//删除线
```

以上的几个宏是字体的样式，可以下面两个函数可以对字体设置样式/获取样式。

```c
TTF_FontStyleFlags  TTF_GetFontStyle(const TTF_Font *font);
void  TTF_SetFontStyle(TTF_Font *font, TTF_FontStyleFlags style);
```

如果你想让你的字体有一个轮廓，这也是可以的的。轮廓线是围绕字体的附加边框。这里有一个例子:

![image-20230601151620562](assets/image-20230601151620562.png)

就像大多数这些函数一样，字体轮廓也有一个set/get函数对:(字体设置大一点，小了可能看不出来)

```c
bool TTF_GetFontOutline(const TTF_Font *font);
int  TTF_SetFontOutline(TTF_Font *font, int outline);
```

#### 另一种渲染方案

SDL3拥有了**新一代文本对象系统**，不再手动创建 Surface / Texture，自带缓存、修改文字 / 颜色 / 位置 / 自动换行，更适合大量动态文本、UI 文字管理。

##### 基本流程

整体链路：**创建渲染器文本引擎 → TTF_CreateText 创建文本对象 → 设置颜色 / 位置 → TTF_RenderText 直接绘制**

```c
int main(int argc, char* argv[])
{
	//初始化SDL子系统
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("can not init SDL:%s", SDL_GetError());
		return -1;
	}
	if (!TTF_Init()) {
		SDL_Log("can not init SDL ttf:%s", SDL_GetError());
		return -1;
	}

	//创建窗口和渲染器
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	if (!SDL_CreateWindowAndRenderer(u8"C语言Plus", SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer)) {
		SDL_Log("can not create window and renderer:%s", SDL_GetError());
		return -1;
	}

	//创建渲染文本引擎
	TTF_TextEngine* textEngine = TTF_CreateRendererTextEngine(renderer);
	if (!textEngine) {
		SDL_Log("can not create text engine:%s", SDL_GetError());
		return -1;
	}

	//打开字体
	TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\simkai.ttf", 20);
	if (!font) {
		SDL_Log("load font fialed:%s", SDL_GetError());
		return -1;
	}

	//创建文本对象
	TTF_Text* ttf_text = TTF_CreateText(textEngine, font, "Hello SDL3", 0);
	if (!ttf_text) {
		SDL_Log("create text failed:%s", SDL_GetError());
		return -1;
	}

	//设置文本颜色
	TTF_SetTextColor(ttf_text, 255, 0, 0, 255);

	//主循环标志
	bool isRunning = true;
	while (isRunning)
	{
		static SDL_Event ev;
		//处理队列中的事件
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//清屏
		SDL_RenderClear(renderer);
		//绘制渲染文本
		TTF_DrawRendererText(ttf_text, 0, 0);

		SDL_RenderPresent(renderer);
	}

	//销毁文本对象
	TTF_DestroyText(ttf_text);
	//关闭字体
	TTF_CloseFont(font);
	//销毁渲染文本引擎
	TTF_DestroyRendererTextEngine(textEngine);
	//销毁窗口
	SDL_DestroyWindow(window);
	//退出ttf
	TTF_Quit();
	//清理所有初始化的子系统
	SDL_Quit();
	return 0;
}
```

##### 文本设置

###### 文本颜色

通过RGBA值直接设置颜色！

```c
bool TTF_GetTextColor(TTF_Text *text, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
bool TTF_SetTextColor(TTF_Text *text, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
```

还有一种就是使用百分比进行设置，百分比是在范围[0~255]之间的位置。

```c
bool TTF_GetTextColorFloat(TTF_Text *text, float *r, float *g, float *b, float *a);
bool TTF_SetTextColorFloat(TTF_Text *text, float r, float g, float b, float a);
```

###### 文本字体

可以在创建文本之后，设置新的字体。

```c
bool  TTF_SetTextFont(TTF_Text *text, TTF_Font *font);
TTF_Font*  TTF_GetTextFont(TTF_Text *text);
```

###### 文本位置

此文本位置不是文本输出位置，而是文本相对于文本矩形的位置（文本本身是有一个矩形的，默认情况下，文本从矩形的0,0位置开始，可以设置坐标进行偏移！）

```c
bool TTF_SetTextPosition(TTF_Text *text, int x, int y);
bool TTF_GetTextPosition(TTF_Text *text, int *x, int *y);
```

###### 文本操作

+ 设置新字符串

  ```c
  bool TTF_SetTextString(TTF_Text *text, const char *string, size_t length);
  ```

+ 插入字符串

  ```c
  bool TTF_InsertTextString(TTF_Text *text, int offset, const char *string, size_t length)
  ```

+ 追加字符串

  ```c
  bool TTF_AppendTextString(TTF_Text *text, const char *string, size_t length);
  ```

+ 删除字符串

  ```c
  bool TTF_DeleteTextString(TTF_Text *text, int offset, int length);
  ```

+ 获取文本大小

  ```c
  bool TTF_GetTextSize(TTF_Text *text, int *w, int *h);
  ```

### 5.播放音乐

#### 初始化&创建混音器

先配置好SDL_mixer拓展库，然后初始化库，结束时反初始化！

```c
if (!MIX_Init()) {
		SDL_Log("can not init SDL mixer:%s", SDL_GetError());
		return -1;
}
...
Mix_Quit();
```

接着，创建混音器设备（MIX_Mixer）。

> MIX_Mixer 是此库的顶级对象。要使用 SDL_mixer，您必须至少有一个，但可以有多个。每个混音器负责生成一个混合音频输出流，通常发送到音频设备以实现实时播放。
>
> 混音器可以用于向音频设备输出音频（通过 MIX_CreateMixerDevice()），也可以用于将音频生成到内存缓冲区中，以便后续使用（通过 MIX_CreateMixer()）。

```c
	//创建混音器(将多个音频流混合成一个)
	//SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK == 默认扬声器设备
	MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!mixer) {
		SDL_Log("can not create mixer:%s", SDL_GetError());
		return -1;
	}
```

**参数解析：**

+ `devid`：设备ID，传递 `SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK` 表示使用默认输出设备。
+ `spec`: 期望音频格式，库内部自动做格式转换，传`NULL`自动选用系统最优配置也可以。

> 支持**多个独立 MIX_Mixer 实例**，分别输出不同声卡、互不干扰

如果要自己传递音频格式，使用如下：

```c
	//配置音频参数
	SDL_AudioSpec spec;
	spec.freq = 44100;				//采样频率
	spec.format = SDL_AUDIO_S16;	//采样格式
	spec.channels = 2;				//声道数(立体声)
```

其中：

+ frequency ：播放音频的频率(单位为Hz)。
+ format：音频格式，SDL的`SDL_AudioFormat`枚举值之一。
+ channels：通道数(1是单声道，2是立体声，等等)。

使用完毕后调用`	MIX_DestroyMixer`函数销毁混音器。

#### 打开音频&获取元信息

先使用`MIX_LoadAudio`打开音频文件。

```c
	MIX_Audio* bgmAudio = MIX_LoadAudio(mixer, "Resource/audio/That-Girl.mp3", false);
	if (!bgmAudio) {
		SDL_Log("can not load audio:%s", SDL_GetError());
		return -1;
	}
```

使用完毕后，记得调用`MIX_DestroyAudio`函数释放音频。

```c
	//获取音频时长
	Sint64 duration = MIX_GetAudioDuration(bgmAudio);
	SDL_Log("audio duration:%lld", duration);

	//获取音频格式
	SDL_AudioSpec spec2;
	MIX_GetAudioFormat(bgmAudio, &spec2);
	SDL_Log("audio format:%d", spec2.format);

	//获取音频属性ID
	SDL_PropertiesID id = MIX_GetAudioProperties(bgmAudio);
	if (id == 0) {
		SDL_Log("can not get audio properties:%s", SDL_GetError());
	}
	//根据属性ID获取对应的属性
	else {
		SDL_Log("title:%s", SDL_GetStringProperty(id, MIX_PROP_METADATA_TITLE_STRING, "xxx"));		//标题
		SDL_Log("artist:%s", SDL_GetStringProperty(id, MIX_PROP_METADATA_ARTIST_STRING, "xxx"));	//艺术家(歌手)
		SDL_Log("album:%s", SDL_GetStringProperty(id, MIX_PROP_METADATA_ALBUM_STRING, "xxx"));		//专辑
		SDL_Log("copyright:%s", SDL_GetStringProperty(id, MIX_PROP_METADATA_COPYRIGHT_STRING, "xxx"));	//版权
		SDL_Log("track num:%lld", SDL_GetNumberProperty(id, MIX_PROP_METADATA_TRACK_NUMBER, -1));		//曲目编号
		SDL_Log("total tracks num:%lld", SDL_GetNumberProperty(id, MIX_PROP_METADATA_TOTAL_TRACKS_NUMBER, -1));	//总曲目数
		SDL_Log("year:%lld", SDL_GetNumberProperty(id, MIX_PROP_METADATA_YEAR_NUMBER, 0));						//年份
		SDL_Log("dur:%lld", SDL_GetNumberProperty(id, MIX_PROP_METADATA_DURATION_FRAMES_NUMBER, 0));			//持续时间(帧)
		SDL_Log("dur infi:%d", SDL_GetBooleanProperty(id, MIX_PROP_METADATA_DURATION_INFINITE_BOOLEAN, false));
	}
```

#### 播放音乐

##### 直接播放

直接播放音乐无法对音乐进行控制，比如暂停。

```c
MIX_PlayAudio(mixer, bgmAudio);
```

##### 音轨播放

音轨(Track)用于表示要混合的音频输出源。
>  MIX_Mixer 可以包含任意数量的音轨，每条音轨管理其独有的音频，并将这些音频混合在一起。
>
> 音轨还具有其他属性：增益、循环点、淡入淡出、3D位置，以及其他可改变输出声音的特性；其中许多属性可在播放过程中进行调整。

###### 创建音轨

```c
	//创建音轨
	MIX_Track* bgmTrack = MIX_CreateTrack(mixer);
	if (!bgmTrack) {
		SDL_Log("can not create track:%s", SDL_GetError());
		return -1;
	}
	//给音轨设置音频
	MIX_SetTrackAudio(bgmTrack, bgmAudio);
```

###### 播放、暂停

```c
	//播放音轨
	MIX_PlayTrack(bgmTrack, 0);
	SDL_Delay(2000);
	//暂停
	MIX_PauseTrack(bgmTrack);
	SDL_Delay(1000);
	//恢复播放
	MIX_ResumeTrack(bgmTrack);
	SDL_Delay(5000);
	//停止播放（在5秒内声音逐渐消失）
	MIX_StopTrack(bgmTrack, MIX_TrackMSToFrames(bgmTrack, 5000));
```

###### 调整音量

```c
	//--调整音量
	//--1,调整混音器音量(全局音量)
	MIX_SetMixerGain(mixer, 2.0);
	//--2,调整音轨音量(局部音量)
	MIX_SetTrackGain(bgmTrack, 0.2);
```

###### 播放位置

+ 实时获取播放进度(单位是帧数)

```c
	//帧播放位置
	Sint64 frame_pos = MIX_GetTrackPlaybackPosition(bgmTrack);
	//转为毫秒
	Sint64 ms_pos = MIX_TrackFramesToMS(bgmTrack, frame_pos);
```

+ 设置播放进度(必须要在播放之后设置才生效)

```c
	//将毫秒转为帧数
	Sint64 frames = MIX_TrackMSToFrames(bgmTrack, 1000 * 10);
	//设置播放位置
	MIX_SetTrackPlaybackPosition(bgmTrack,frames);
```

###### 播放次数

```c
	//设置播放循环次数
	MIX_SetTrackLoops(bgmTrack, 2);
	int loop_count = MIX_GetTrackLoops(bgmTrack);
```

##### 简单音乐播放器

先编写创建音乐播放器结构，封装如下数据。

```c
typedef struct MusicPlayer {
	MIX_Audio* audios[3];		/*!音乐列表*/
	int index;					/*!当前播放索引*/
	MIX_Track* track;			/*!轨道*/
}MusicPlayer;
```

然后，创建播放器对象，并加载音乐列表。

```c
	//播放器
	MusicPlayer mPlayer = { 0 };

	//音乐列表
	const char* filenames[] = { 
		"Resource/audio/N0va.mp3",
		"Resource/audio/That-Girl.mp3",
		u8"Resource/audio/小幸运.mp3" 
	};

	for (int i = 0; i < 3; i++) {
		MIX_Audio* audio = MIX_LoadAudio(mixer, filenames[i], false);
		if (!audio) {
			SDL_Log("can not load audio:%s", SDL_GetError());
		}
		else {
			mPlayer.audios[i] = audio;
		}
	}
```

接着，创建音轨，并保存到播放器中。

```c
	MIX_Track* track = MIX_CreateTrack(mixer);
	if (!track) {
		SDL_Log("can not create track:%s", SDL_GetError());
		return -1;
	}
	mPlayer.track = track;
	if (!MIX_SetTrackAudio(track, mPlayer.audios[mPlayer.index])) {
		SDL_Log("can not set track audio:%s", SDL_GetError());
		return -1;
	}

	//播放第一个
	MIX_PlayTrack(track, 0);
```

接着在事件处理中处理空格键播放和暂停。

```c
	//主循环标志
	bool isRunning = true;
	while (isRunning)
	{
		static SDL_Event ev;
		//处理队列中的事件
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
			else if (ev.type == SDL_EVENT_KEY_DOWN) {
				switch (ev.key.key)
				{
				case SDLK_SPACE:
					//判断是否有音乐正在播放（无论音乐是在播放中还是暂停中，都返回非零值）
					if (MIX_TrackPlaying(track)) {
						//如果音乐没有暂停，则暂停
						if (!MIX_TrackPaused(track)) {
							//暂停当前播放的音乐（因为同一时间只能播放一个，所以不需要参数）
							MIX_PauseTrack(track);
							SDL_Log("pause");
						}
					}
					else {
						//如果已经暂停了，则恢复播放
						if (MIX_TrackPaused(track)) {
							//如果有音乐已经暂停了，则恢复播放
							MIX_ResumeTrack(track);
							SDL_Log("resume");
						}
						else {
							//如果没有任何音乐正在播放，则播放
							if (mPlayer.index < 0 || mPlayer.index >= 3) {
								mPlayer.index = 0;
							}
							MIX_SetTrackAudio(track, mPlayer.audios[mPlayer.index]);
							MIX_PlayTrack(track, 0);
							SDL_Log("play");
						}
					}
					break;
```

在主循环里面，进行事件处理，当按下空格键时，实现暂停和播放功能！

如果需要彻底停止音乐的播放，可以使用`MIX_StopTrack`，比如当按下s键时停止，应该这样写代码

```c
				case SDLK_S:
					//停止播放
					MIX_StopTrack(track, MIX_TrackMSToFrames(track, 2000));
					SDL_Log("stop");
					break;
```

如果你想从头重新播放当前音乐，代码如下：

```c
				case SDLK_R:
					//从头开始播放
					MIX_SetTrackPlaybackPosition(track, 0);
					break;
```

当音量太大或太小时，还需要对音量进行设置，使用`MIX_SetMixerGain`函数即可实现。

```c
				case SDLK_UP: {
					//音量+
					float gain = MIX_GetMixerGain(mixer);
					if (gain < 2.1) {
						MIX_SetMixerGain(mixer, gain + 0.1f);
						SDL_Log("gain:%f", gain);
					}
					break;
				}
				case SDLK_DOWN: {
					//音量-
					float gain = MIX_GetMixerGain(mixer);
					if (gain > 0) {
						MIX_SetMixerGain(mixer, gain - 0.1f);
						SDL_Log("gain:%f", gain);
					}
					break;
				}
```

`MIX_SetMixerGain`函数传入需要设置的音量。

我们还需要能够切换上一曲和下一曲，实现代码如下：

```c
				case SDLK_LEFT: {
					//上一曲
					MIX_StopTrack(track, 0);
					mPlayer.index = (mPlayer.index - 1 + 3) % 3;
					MIX_SetTrackAudio(track, mPlayer.audios[mPlayer.index]);
					MIX_PlayTrack(track, 0);
					break;
				}
				case SDLK_RIGHT: {
					//下一曲
					MIX_StopTrack(track, 0);
					mPlayer.index = (mPlayer.index + 1) % 3;
					MIX_SetTrackAudio(track, mPlayer.audios[mPlayer.index]);
					MIX_PlayTrack(track, 0);
					break;
				}
```

除此之外，我们还需要能快进或者快退：

```c
				case SDLK_J: {
					//快退
					Sint64 frame_pos = MIX_GetTrackPlaybackPosition(track);
					Sint64 ms_pos = MIX_TrackFramesToMS(track, frame_pos);
					//设置
					MIX_SetTrackPlaybackPosition(track, frame_pos - MIX_TrackMSToFrames(track, 1000));
					break;
				}
				case SDLK_K: {
					//快进
					Sint64 frame_pos = MIX_GetTrackPlaybackPosition(track);
					Sint64 ms_pos = MIX_TrackFramesToMS(track, frame_pos);
					//设置
					MIX_SetTrackPlaybackPosition(track, frame_pos + MIX_TrackMSToFrames(track, 1000));
					break;
				}
```

最后，还需要释放资源：

```c
				default:
					break;
				}
			}
		}
	}

	//销毁音轨
	MIX_DestroyTrack(track);
	//销毁音轨和音频
	for (int i = 0; i < 3; i++) {
		//销毁音频
		MIX_DestroyAudio(mPlayer.audios[i]);
	}
	//销毁混音器
	MIX_DestroyMixer(mixer);
```

当音乐播放完成时，我们经常回去干一些事情，那么如何知晓音乐是否播放完成呢？答案是使用回调函数，在当前音乐播放完成时，会自动帮我们调用指定的函数。

```c
void trackStoppedCallback(void* userdata, MIX_Track* track)
{
	SDL_Log("track stopped");
	MusicPlayer* mPlayer = (MusicPlayer*)userdata;
	if (!mPlayer) {
		SDL_Log("userdata is NULL");
		return;
	}
	//播放下一个
	mPlayer->index = (mPlayer->index + 1) % 3;
	MIX_SetTrackAudio(mPlayer->track, mPlayer->audios[mPlayer->index]);
	MIX_PlayTrack(track, 0);
}

//在循环之前注册即可！
MIX_SetTrackStoppedCallback(track, trackStoppedCallback, &mPlayer);
```
