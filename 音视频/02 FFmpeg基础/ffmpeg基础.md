# FFmpeg开发环境搭建

## windows

### 下载编译好的ffmpeg包

进去[Releases · ShiftMediaProject/FFmpeg](https://github.com/ShiftMediaProject/FFmpeg/releases)下载VS开发包。

![image-20251204190141784](./assets/image-20251204190141784.png)

### 配置Vs

1. 创建项目，并将头文件目录添加到<右键项目 → 属性 → **C/C++ → 常规 → 附加包含目录**>中：

```css
F:\Tools\ffmpeg-8.0.1-full_build-shared\include
```

2. 将库文件目录添加到<属性 → **链接器 → 常规 → 附加库目录**>中：

```css
F:\Tools\ffmpeg-8.0.1-full_build-shared\lib
```

3. 将库文件添加到<属性 → **链接器 → 输入 → 附加依赖项**>中：

```css
avformat.lib
avcodec.lib
avutil.lib
swresample.lib
swscale.lib
avfilter.lib
avdevice.lib
```

也可以使用`#pragma comment`直接在代码中加载库：

```css
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avfilter.lib")
```

4. 因为库是动态库，所以还需要将bin目录配置到环境变量`PATH`中，这样运行时就可以直接找到`.dll`文件了（如果要将程序发给别人，则需要拷贝bin中的dll拷贝到exe同级目录中）！

```css
F:\Tools\ffmpeg-8.0.1-full_build-shared\bin
```

5. **测试代码**

```c
#include <stdio.h>

//extern "C" {
#include "libavformat/avformat.h"
//}

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avfilter.lib")

int main()
{
	printf("%s",av_version_info());

	return 0;
}
```

注意：如果在C++中测试，需要使用`extern "C" {}`将ffmpeg的头文件包括起来。

# ffmpeg库

## 八大库

ffmpeg提供了“八大金刚” 核心开发库，用于实现对音视频的各种操作。

| 库         | 介绍                                                     |
| :--------- | :------------------------------------------------------- |
| avcodec    | 音视频编解码核心库                                       |
| avformat   | 音视频容器格式的封装和解析                               |
| avutil     | 核心工具库                                               |
| swscale    | 图像格式转换的模块                                       |
| swresample | 音频重采样                                               |
| avfilter   | 音视频滤镜库，如视频加水印、音频变声                     |
| avdevice   | 输入输出设备库，提供设备数据的输入与输出，和硬件设备交互 |

## ffmpeg播放流程

通常情况下，视频文件如 MP4，MKV、FLV 等都属于封装格式，就是将已经压缩编码的视频数据和音频数据按照一定的格式放到一起。当我们播放一个媒体文件时，通常需要经过以下几个步骤：

![img](./assets/2221558-20230318141030236-977060406.jpg)

可以看到这个视频播放器的实现需要涉及到以下内容：

- **解封装(Demuxing)**：就是将输入的封装格式的数据，分离成为音频流压缩编码数据和视频流压缩编码数据。例如，FLV 格式的数据，经过解封装操作后，输出 H.264 编码的视频码流和 AAC 编码的音频码流。
- **软硬件解码(Decode)**：就是将视频/音频压缩编码数据，解码成为非压缩的视频/音频原始数据。通过解码，将压缩编码的视频数据 H.264，MPEG2 解码成为非压缩的颜色数据，例如 YUV 等等；将压缩编码的音频数据 AAC，MP3 解码成为非压缩的音频抽样数据，例如 PCM 数据。解码分为硬编码和软编码。
- **像素格式转换**：将 YUV 数据格式转换成 RGB 数据格式。
- **重采样**：对音频重新采样。
- **dts/pts**：dts 是解码的时间戳，而 pts 是显示的时间戳。pts 用于获取当前播放进度。进度条移动需要用到`av_seek_frame`函数。
- **音视频同步**：就是根据解封装模块处理过程中获取到的参数信息，同步解码出来的音频和视频数据，并将音视频频数据送至系统的显卡和声卡播放出来（Render）。

其中解码是最重要的，下面介绍一下解码的流程以及用到的 API 和结构体。

## ffmpeg解码流程

### 流程图

![image-20251206154544636](./assets/image-20251206154544636.png)

### ffmpeg API说明

#### avformat_alloc_context()

用于初始化 AVFormatContext 对象。其原型如下：

```c
AVFormatContext *avformat_alloc_context(void)
```

- 因为AVFormatContext 必须初始化为 NULL 或者用`avformat_alloc_context()`进行初始化。

#### avformat_open_input()

打开媒体文件，并获得解封装上下文。其原型如下：

```c
int avformat_open_input(AVFormatContext **ps, const char *url,
                        const AVInputFormat *fmt, AVDictionary **options);
```

- `ps`：AVFormatContext 二级指针，函数调用成功之后将解封装上下文赋值给 ps。
- `url`：可以是 rtsp、http 网络流地址，或者本地视频文件路径。
- `fmt`：指定输入音视频的封装格式，一般情况下可以设置为 nullptr，则会自动探索。
- `options`：附加的一些选项，一般情况下可以设置为 nullptr，但有时候播放 rtsp 时需要设置下。

#### avformat_find_stream_info()

探测获取流信息。其原型如下：

```c
int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options)
```

- 因为在一些格式当中没有头部信息，如 flv 格式，h264 格式，调用`avformat_open_input()`在打开文件之后就没有参数，也就无法获取到里面的信息。
- 这个时候就可以调用此函数，因为它会试着去探测文件的格式，但是如果格式当中没有头部信息，那么它只能获取到编码、宽高这些信息，还是无法获得总时长。
- 如果总时长无法获取到，则需要把整个文件读一遍，获取一下它的总帧数来计算。

#### avcodec_find_decoder()

查找解码器。函数的参数是所要用解码器的ID，成功返回查找到的解码器（没有找到就返回 NULL）。其原型如下：

```c
AVCodec *avcodec_find_decoder(enum AVCodecID id);
```

- `id`：查找到的解码器

#### avcodec_open2()

用于初始化一个音视频编解码器的 AVCodecContext，声明位于 `libavcodec/avcodec.h`。其原型如下：

```c
int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options)
```

- `avctx`：需要初始化的 AVCodecContext。
- `codec`：输入的AVCodec。
- `options`：一些选项。例如使用 libx264 编码的时候，“preset”，“tune” 等都可以通过该参数设置。

#### av_read_frame()

读取码流中的音频若干帧或者视频一帧。例如，解码视频的时候，每解码一个视频帧，需要先调用`av_read_frame()`获得一帧视频的压缩数据，然后才能对该数据进行解码。其原型如下：

```c
int av_read_frame(AVFormatContext *s, AVPacket *pkt)
```

- `s`：解封装上下文。
- `pkt`：存储一帧视频的压缩数据。

#### avcodec_send_packet()

将编码数据包（AVPacket）发送到解码器。输入一个压缩编码的结构体 AVPacket，后续通过`avcodec_receive_frame`函数接受解码后的数据。其原型如下：

```c
int avcodec_send_packet(AVCodecContext *s, const AVPacket *avpkt);
```

- `s`：解封装上下文。
- `avpkt`：传入一帧视频的压缩数据

#### avcodec_receive_frame()

从解码器中接收解码后的帧（AVFrame）。接受调用`avcodec_send_packet`函数之后，编码器返回的帧。

```c
int avcodec_receive_frame(AVCodecContext *s, AVFrame *frame);
```

- `s`：解封装上下文。
- `frame`：解码之后的帧

> 注意：一个packet可能会解码出多个frame（例如，一些编码格式如B帧可能会产生多个帧），所以我们需要循环接收直到没有数据为止。

#### avformat_close_input()

关闭释放解封装上下文，并且设置为 0。其原型如下：

```c
void avformat_close_input(AVFormatContext **s)
```

- `s`：解封装上下文。

### ffmpeg结构体说明

#### AVFormatContext

解封装上下文，是存储音视频封装格式中包含信息的结构体。

```c
char *url;			 	// 保存打开的url
unsigned int nb_streams // 音视频流的个数
AVStream **streams 		// 存储视频流、音频流、字幕流信息
int64_t duration 		// 媒体文件的总时长，单位是把 1 秒切成 AV_TIME_BASE（1000000）份，即单位。为 us，注意不一定每个视频都能获取到 duration
int64_t bit_rate 		// 比特率（单位bps，转换为kbps需要除以1000）
```

#### AVStream

AVStream 是存储每一个音频/视频流信息的结构体。其重要的变量如下所示：

```c
int index 				// 当前流在AVFormatContext中的索引
AVRational time_base 	// 时间基。通过该值可以把PTS，DTS转化为实际的时间（单位为秒s）
int64_t duration 		// 该视频/音频流时长，单位为 ms
AVRational avg_frame_rate 	// 帧率（注：对视频来说，这个挺重要的）
AVPacket attached_pic 		// 附带的图片。比如说一些 MP3，AAC 音频文件附带的专辑封面
AVCodecParameters *codecpar // 音视频参数，新增用来替换AVCodecContext *codec
```

#### AVCodecContext

AVCodecContext 是一个描述编解码器上下文的结构体，包含了众多编解码器需要的参数信息。下面挑一些关键的变量来看看（这里只考虑解码）。

```c
enum AVMediaType codec_type 	// 编解码器的类型（视频，音频...）
struct AVCodec  *codec 			// 采用的解码器AVCodec（H.264,MPEG2...）    
enum AVCodecID codec_id 		// 标示特定的编解码器（H.264,MPEG2...）
int format 						// 视频像素格式/音频采样数据格式
int width, height 				// 表示视频的宽和高
int bit_rate 					// 平均比特率    
AVChannelLayout ch_layout;		// (仅音频)通道布局和通道数
int sample_rate 				// 采样率（音频）
AVRational time_base; 			// 时基。通过该值可以把PTS，DTS转化为实际的时间（单位为秒s）
uint8_t *extradata; int extradata_size; // 针对特定编码器包含的附加信息（例如对于H.264解码器来说，存储SPS，PPS等）
```

#### AVCodec

AVCodec 是存储编码器信息的结构体。其重要的变量如下所示：

```c
const char *name; 			// 编解码器的名字的简称
const char *long_name; 		// 编解码器名字的全称
enum AVMediaType type; 		// 指明了类型，是视频，音频，还是字幕
enum AVCodecID id; 			// ID，不重复
```

#### AVCodecParameters

新增用来替换`AVCodecContext *codec`。因为 AVCodecContext 结构体包含的参数太多，AVCodecParameters 将编码器的参数从 AVCodecContext 分离出来，AVCodecParameters 结构体中部分重要的参数如下：

```c
enum AVMediaType codec_type 	// 编解码器的类型（视频，音频...）   
enum AVCodecID codec_id 		// 标示特定的编解码器（H.264,MPEG2...）
int format 						// 视频像素格式/音频采样数据格式
int width, height 				// 表示视频的宽和高
int bit_rate					// 平均比特率    
AVChannelLayout ch_layout;		// (仅音频)通道布局和通道数
int sample_rate 				// (仅音频)采样率
uint8_t *extradata; int extradata_size; // 针对特定编码器包含的附加信息（例如对于H.264解码器来说，存储SPS，PPS等）
```

可以看到两者的成员基本一致。

#### AVPacket

AVPacket 是存储压缩编码数据相关信息的结构体。其重要的变量如下所示：

```c
uint8_t *data; 			// 压缩编码的数据。
/* 例如对于H.264来说。1个AVPacket的data通常对应一个NAL。
注意：在这里只是对应，而不是一模一样。他们之间有微小的差别：使用FFMPEG类库分离出多媒体文件中的H.264码流。因此在使用FFMPEG进行音视频处理的时候，常常可以将得到的AVPacket的data数据直接写成文件，从而得到音视频的码流文件。*/
int size; 			// data的大小
int64_t pts; 		// 显示时间戳
int64_t dts; 		// 解码时间戳
int stream_index; 	// 标识该AVPacket所属的视频/音频流。
```

#### AVFrame

AVFrame 结构体一般用于存储原始数据（即非压缩数据，例如对视频来说是 YUV，RGB，对音频来说是 PCM），此外还包含了一些相关的信息。比如说，解码的时候存储了宏块类型表，QP 表，运动矢量表等数据。编码的时候也存储了相关的数据。因此在使用 FFmpeg 进行码流分析的时候，AVFrame 是一个很重要的结构体。

下面看几个主要变量的作用（在这里考虑解码的情况）：

```c
uint8_t *data[AV_NUM_DATA_POINTERS]; 	// 解码后原始数据（对视频来说是YUV，RGB，对音频来说是PCM）
int linesize[AV_NUM_DATA_POINTERS]; 	// data中“一行”数据的大小。注意：未必等于图像的宽，一般大于图像的宽。
int width, height; 						// 视频帧宽和高（1920x1080,1280x720...）
int nb_samples; 						// 音频的一个AVFrame中可能包含多个音频帧，在此标记包含了几个
int format; 							// 解码后原始数据类型（YUV420，YUV422，RGB24...）
int key_frame; 							// 是否是关键帧
enum AVPictureType pict_type; 			// 帧类型（I,B,P...）
AVRational sample_aspect_ratio;		 	// 宽高比（16:9，4:3...）
int64_t pts; 							// 显示时间戳
```

# ffmpeg SDK开发

SDK（Software Development Kit）即软件开发工具包，是一系列软件工具、库、文档和示例代码的集合，旨在帮助开发者针对特定平台、系统或服务创建应用程序。

## 日志系统

通过FFmpeg日志系统可以控制FFmpeg警告或错误输出内容和方式。

### av_log

av_log()是FFmpeg中输出日志的函数。随便打开一个FFmpeg的源代码文件，就会发现其中遍布着av_log()函数。一般情况下FFmpeg类库的源代码中是不允许使用printf()这种的函数的，所有的输出一律使用av_log()。

函数原型如下：

```c
void av_log(void *avcl, int level, const char *fmt, ...)
```

- void* avcl：指向任意结构的指针，指定该log所属的结构体，例如AVFormatContext、AVCodecContext等等。
- int level：输出日志内容的等级
- const char *fmt：指定后续参数如何转换为输出的格式字符串（printf 兼容）。
- 函数最后一个参数是“…”。在C语言中，在函数参数数量不确定的情况下使用“…”来代表参数

### 日志级别

日志等级用于表示日志信息的重要性和详细程度，不同的等级适用于不同的场景。ffmpeg中定义了如下日志级别：

| 级别           | 描述                                   |
| -------------- | -------------------------------------- |
| AV_LOG_QUIET   | 不打印任何输出                         |
| AV_LOG_PANIC   | 严重问题，程序退出                     |
| AV_LOG_FATAL   | 出现了无法恢复的问题                   |
| AV_LOG_ERROR   | 错误日志                               |
| AV_LOG_WARNING | 警告日志                               |
| AV_LOG_INFO    | 信息日志                               |
| AV_LOG_VERBOSE | 详细日志                               |
| AV_LOG_DEBUG   | 调试日志(给发发人员自己看的)           |
| AV_LOG_TRACE   | 非常详细的调试日志(给发发人员自己看的) |

打印不同级别的日志：

```c
	av_log(NULL, AV_LOG_QUIET,		"Hello, QUIET!\n");
	av_log(NULL, AV_LOG_PANIC,		"Hello, PANIC!\n");
	av_log(NULL, AV_LOG_FATAL,		"Hello, FATAL!\n");
	av_log(NULL, AV_LOG_ERROR,		"Hello, ERROR!\n");
	av_log(NULL, AV_LOG_WARNING,	"Hello, WARNING!\n");
	av_log(NULL, AV_LOG_INFO,		"Hello, INFO!\n");
	av_log(NULL, AV_LOG_VERBOSE,	"Hello, VERBOSE!\n");
	av_log(NULL, AV_LOG_DEBUG,		"Hello, DEBUG!\n");
	av_log(NULL, AV_LOG_TRACE,		"Hello, TRACE!\n");
```

输入如下：

```c
Hello, QUIET!
Hello, PANIC!
Hello, FATAL!
Hello, ERROR!
Hello, WARNING!
Hello, INFO!
```

发现`VERBOSE`、`DEBUG`、`TRACE`级别的日志没有输出！为啥呢？因为ffmpeg默认的日志级别是`INFO`级别的，只打印级别大于等于`INFO`级别的日志。

可以通过`av_log_set_level`设置日志级别：

```c
av_log_set_level(AV_LOG_DEBUG);
```

这样就可以打印`VERBOSE`、`DEBUG`级别的日志了！通过`av_log_get_level`还可以获取当前日志级别哟~

### 日志回调

可以使用`av_log_set_callback`自己设置日志回调函数，自定义日志输出格式和位置。

```c
/**
 * 获取日志级别字符串.
 * 
 * \param level 级别
 * \return  返回级别字符串.
 */
const char* get_level_string(int level) {
	switch (level) {
	case AV_LOG_QUIET:
		return "QUIET";
	case AV_LOG_PANIC:
		return "PANIC";
	case AV_LOG_FATAL:
		return "FATAL";
	case AV_LOG_ERROR:
		return "ERROR";
	case AV_LOG_WARNING:
		return "WARNING";
	case AV_LOG_INFO:
		return "INFO";
	case AV_LOG_VERBOSE:
		return "VERBOSE";
	case AV_LOG_DEBUG:
		return "DEBUG";
	case AV_LOG_TRACE:
		return "TRACE";
	}
	return "UNKNOW";
}

/**
 * 获取日志字符串.
 * 
 * \param level 日志级别
 * \param log   日志内容
 * \return		返回日志字符串.
 */
const char* get_log_string(int level, const char* log) {
	static char buf[1024];

	const char* level_str = get_level_string(level);
	switch (level) {
	case AV_LOG_QUIET:
	case AV_LOG_PANIC:
	case AV_LOG_FATAL:
	case AV_LOG_ERROR:
		sprintf(buf, "\033[31m [%-7s] %s\033[0m", level_str, log);
		break;
	case AV_LOG_WARNING:
		sprintf(buf, "\033[33m [%-7s] %s\033[0m", level_str, log);
		break;
	case AV_LOG_INFO:
		sprintf(buf, "\033[37m [%-7s] %s\033[0m", level_str, log);
		break;
	case AV_LOG_VERBOSE:
	case AV_LOG_DEBUG:
		sprintf(buf, "\033[32m [%-7s] %s\033[0m", level_str, log);
		break;
	case AV_LOG_TRACE:
		sprintf(buf, "\033[90m [%-7s] %s\033[0m", level_str, log);
		break;
	}
	return buf;
}

void custom_log_callback(void* avcl, int level, const char* fmt, va_list vl) {

	static char buf[1024];
	vsnprintf(buf, sizeof(buf), fmt, vl);

	printf(get_log_string(level, buf));
}
```

测试：

```c
void test()
{
	av_log_set_level(AV_LOG_TRACE);

	av_log_set_callback(custom_log_callback);

	av_log(NULL, AV_LOG_QUIET, "Hello, QUIET!\n");
	av_log(NULL, AV_LOG_PANIC, "Hello, PANIC!\n");
	av_log(NULL, AV_LOG_FATAL, "Hello, FATAL!\n");
	av_log(NULL, AV_LOG_ERROR, "Hello, ERROR!\n");
	av_log(NULL, AV_LOG_WARNING, "Hello, WARNING!\n");
	av_log(NULL, AV_LOG_INFO, "Hello, INFO!\n");
	av_log(NULL, AV_LOG_VERBOSE, "Hello, VERBOSE!\n");
	av_log(NULL, AV_LOG_DEBUG, "Hello, DEBUG!\n");
	av_log(NULL, AV_LOG_TRACE, "Hello, TRACE!\n");
}
```

## 字典结构(AVDictionary)

AVDictionary是一个健值对存储工具，类似于c++中的map，ffmpeg中有很多 API 通过它来传递参数。

关键结构体如下：

```c
typedef struct AVDictionaryEntry {
    char *key;
    char *value;
} AVDictionaryEntry;

typedef struct AVDictionary AVDictionary;
```

### 基本使用

+ 首先，定义AVDictionary指针：

```c
AVDictionary* dict = NULL;
```

+ 然后，直接使用`	av_dict_set`函数设置键值对：

```c
av_dict_set(&dict, "name", "maye", 0);
```

"name"是键，”maye"是值，0是标志，暂时先写0。

+ 接下来使用`av_dict_get`函数获取值，函数原型如下：

```c
		av_dict_get(dict,"name",NULL,0);
		av_log(NULL, AV_LOG_INFO, "key=%s, value=%s\n", entry->key, entry->value);
```

+ 最后不要忘记释放字典哟

```c
av_dict_free(&dict);
```

### av_dict_get

av_dict_get用于根据key从字典中获取值。

+ 函数原型如下：

```c
AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, int flags);
```

+ **参数：**

  + **m**：是字典

  + **key**：是要获取的键

  + **prev**：是检索提示，用于加快查找速度，可以写NULL，如果不为空，则从prev之后的条目开始检索，`prev - m->elems + 1`为prev的下一个条目的索引。

  + **flags**：为查找键时对键进行比较的标志，支持如下两种值：

    - AV_DICT_MATCH_CASE：如果flags包含此标志，则key的比较区分大小写，否则不区分。

    - AV_DICT_IGNORE_SUFFIX：如果flags包含此标志，则传入的key如果是字典某个key的前面一部分，则直接返回。

+ **案例：**

  + 最简单的获取项的方式

    ```c
    	AVDictionaryEntry* entry;
    	entry = av_dict_get(dict, "name", NULL, 0);
    	entry = av_dict_get(dict, "NaMe", NULL, 0);	//默认忽略大小写
    ```

  + 如果想要区分大小写，的加上AV_DICT_MATCH_CASE标志

    ```c
    	entry = av_dict_get(dict, "NaMe", NULL, AV_DICT_MATCH_CASE);
    ```

    这样，就查找不到key为`NaMe`的项了。

  + 如果只想写key的前面一部分，可以加上AV_DICT_IGNORE_SUFFIX表示，来忽略字典中key多余的后缀

    ```c
    	entry = av_dict_get(dict, "Na", NULL, AV_DICT_IGNORE_SUFFIX);
    ```

    只写`Na`也能查找到键为`name`的项。

  + 当然，两个标志组合在一起也是可以的：

    ```c
    	entry = av_dict_get(dict, "Na", NULL, AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX);
    ```

    但是因为区分大小写，所以查找不到项了。

### av_dict_set

av_dict_set用于向字典中设置键值对，功能很简单，但是选项有很多。

+ 函数原型如下：

  ```c
  int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags);
  ```

+ **参数：**
  + **pm：**传出参数，传入时(*pm)必须为NULL
  + **key：**要设置的键
  + **value：**要设置的值
  + **flags：**标志，可以是如下值之一：
    + AV_DICT_MULTIKEY：此标志能让key可以重复。
    + AV_DICT_DONT_STRDUP_KEY
    + AV_DICT_DONT_STRDUP_VAL
    + AV_DICT_DONT_OVERWRITE
    + AV_DICT_APPEND

#### AV_DICT_MULTIKEY(重复KEY)

设置此标志，当key重复时，可以新增一个，也就是说允许重复key。

```c
	av_dict_set(&dict, "name", "maye", 0);
	av_dict_set(&dict, "name", "zc", AV_DICT_MULTIKEY);

	//查找所有key为name的项
	AVDictionaryEntry* entry = NULL;
	while (entry = av_dict_get(dict, "name", entry, 0)) {
		av_log(NULL, AV_LOG_INFO, "key=%s, value=%s\n", entry->key, entry->value);
    }
```

输出：

```c
key=name, value=maye
key=name, value=zc
```

#### AV_DICT_DONT_OVERWRITE(不覆盖)

设置此标志，当key存在时，不做任何操作；否则当key存在，则会覆盖掉值。

> 注意：设置了AV_DICT_MULTIKEY再设置这个标志将无效。

```c
av_dict_set(&dict, "age", "12", 0);	
av_dict_set(&dict, "age", "28", 0);	//会覆盖前面的12	

av_dict_set(&dict, "age", "66", AV_DICT_DONT_OVERWRITE);	//设置标志后，就不会覆盖了
```

#### AV_DICT_DONT_STRDUP_KEY|VALUE

AV_DICT_DONT_STRDUP_KEY标志控制是否拷贝key字符串。

AV_DICT_DONT_STRDUP_VAL标志控制是否拷贝value字符串。

什么意思呢？其实字典中存储的键值对都是存储在堆内存中的，也就是会动态内存分配！默认情况下，字典是会自动分配内存，拷贝我们传递的键值对参数的！在释放字典时，会自动释放掉。

那么我们也可以自己分配内存之后，传递进去，这样就可以不让字典自动拷贝了！

```c
	const char* key = av_strdup("height");
	const char* value = av_strdup("173");
	av_dict_set(&dict, key, value, AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

	//遍历所有项
	AVDictionaryEntry* entry = NULL;
	while (entry = av_dict_iterate(dict, entry)) {
		av_log(NULL, AV_LOG_INFO, "key=%s, value=%s\n", entry->key, entry->value);
	}
```

#### AV_DICT_APPEND

设置此标志时，如果key已经存在，则会将value追加到现有value的后面。如果不存在则设置。

```c
	const char* key = av_strdup("height");
	const char* value = av_strdup("173");
	av_dict_set(&dict, key, value, AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

	av_dict_set(&dict, "height", "cm", AV_DICT_APPEND);
```

设置之后，height的值变成了`173cm`。

### av_dict_set_int

此函数专门用来设置值为int累的键值对。

```c
	av_dict_set_int(&dict, "weight", 62, 0);
```

### av_dict_copy

此函数用于拷贝字典。

```c
		AVDictionary* dict2 = NULL;
		av_dict_copy(&dict2, dict, AV_DICT_MULTIKEY);

		AVDictionaryEntry* entry = NULL;
		while (entry = av_dict_iterate(dict2, entry)) {
			av_log(NULL, AV_LOG_INFO, "key=%s, value=%s\n", entry->key, entry->value);
		}
```

### av_dict_count

此函数用于获取字典中的键值对数量。

```c
		av_log(NULL,AV_LOG_INFO,"dict count is %d" ,av_dict_count(dict2));
```

### av_dict_parse_string

**字符串 → 字典**。将格式化的字符串解析为键值对，并添加到字典中。

```c
void test_dict2()
{
	AVDictionary* dict = NULL;

	//将字符串解析为字典
	//假设字符串格式为 key=value;key=value,键值对分隔符为;键值分隔符为=
	av_dict_parse_string(&dict, "name=maye;age=18;name=zc", "=", ";", AV_DICT_MULTIKEY);

	AVDictionaryEntry* entry = NULL;
	while (entry = av_dict_iterate(dict, entry)) {
		av_log(NULL, AV_LOG_INFO, "key=%s, value=%s\n", entry->key, entry->value);
	}

	av_dict_free(&dict);
}
```

### av_dict_get_string

**字典 → 字符串**。将字典中的条目序列化为一个格式化的字符串，返回的字符串使用动态分配，必须由调用者手动释放！

```c
	char* serialized_str = NULL;
	int len = av_dict_get_string(dict, &serialized_str, '=', ';');
	av_free(serialized_str);
```

[FFmpeg接口-AVDictionary的使用介绍和源码分析 - 简书](https://www.jianshu.com/p/89f2da631e16)

## ParseUtils

> #include "libavutil/parseutils.h"

### av_parse_video_size

此函数用于从字符串解析视频尺寸（宽度和高度）的函数。函数原型原型如下：

```c
int av_parse_video_size(int *width_ptr, int *height_ptr, const char *str);
```

**参数：**

- `width_ptr`：指向存储宽度值的整型指针
- `height_ptr`：指向存储高度值的整型指针
- `str`：**包含尺寸信息的字符串**

支持的字符串格式有很多：

+ 标准格式：宽度x高度`，如 `1920x1080`、`1280x720

```c
	int w, h;
	if (av_parse_video_size(&w, &h, "1920*1080") < 0) {
		av_log(NULL, AV_LOG_ERROR, "parse video size failed\n");
	}
	av_log(NULL, AV_LOG_INFO, "video size (%d, %d)\n",w,h);
```

+ 预定义名称：

```c
void test_parse_video_size()
{

	const char* video_size_names[] = {
		// 标准电视格式
		"ntsc",         // 720x480
		"pal",          // 720x576
		"qntsc",        // 352x240
		"qpal",         // 352x288
		"sntsc",        // 640x480
		"spal",         // 768x576
		"film",         // 352x240
		"ntsc-film",    // 352x240

		// CIF系列
		"sqcif",        // 128x96
		"qcif",         // 176x144
		"cif",          // 352x288
		"4cif",         // 704x576
		"16cif",        // 1408x1152

		// VGA系列
		"qqvga",        // 160x120
		"qvga",         // 320x240
		"vga",          // 640x480
		"svga",         // 800x600
		"xga",          // 1024x768
		"uxga",         // 1600x1200
		"qxga",         // 2048x1536
		"sxga",         // 1280x1024
		"qsxga",        // 2560x2048
		"hsxga",        // 5120x4096
		"wvga",         // 852x480
		"wxga",         // 1366x768
		"wsxga",        // 1600x1024
		"wuxga",        // 1920x1200
		"woxga",        // 2560x1600
		"wqsxga",       // 3200x2048
		"wquxga",       // 3840x2400
		"whsxga",       // 6400x4096
		"whuxga",       // 7680x4800

		// 传统显示标准
		"cga",          // 320x200
		"ega",          // 640x350

		// HD高清系列
		"hd480",        // 852x480
		"hd720",        // 1280x720
		"hd1080",       // 1920x1080

		// 2K系列
		"2k",           // 2048x1080
		"2kflat",       // 1998x1080
		"2kscope",      // 2048x858
		"2kdci",        // 2048x1080

		// 4K/超高清系列
		"4k",           // 4096x2160
		"4kflat",       // 3996x2160
		"4kscope",      // 4096x1716
		"4kdci",        // 4096x2160
		"uhd2160",      // 3840x2160
		"uhd4320",      // 7680x4320

		// 其他格式
		"nhd",          // 640x360
		"hqvga",        // 240x160
		"wqvga",        // 400x240
		"fwqvga",       // 432x240
		"hvga",         // 480x320
		"qhd",          // 960x540

		// 宽屏变体
		"wqvga",        // 400x240
		"wvga",         // 852x480
		NULL  // 结束标记
	};

	int width, height;

	// 遍历所有分辨率名称并解析
	for (int i = 0; video_size_names[i] != NULL; i++) {
		if (av_parse_video_size(&width, &height, video_size_names[i]) >= 0) {
			printf("%-15s -> %4dx%-4d\n",
				video_size_names[i], width, height);
		}
		else {
			printf("%-15s -> FAILED\n", video_size_names[i]);
		}
	}
}
```

### av_parse_video_rate

此函数用于从字符串解析视频帧率的函数。函数原型如下：

```c
int av_parse_video_rate(AVRational *rate, const char *str);
```

**参数：**

- **`rate`**：指向 `AVRational` 结构体的指针，用于存储解析后的帧率（分子/分母形式）
- **`str`**：**包含帧率信息的字符串**

**字符串格式：**

1. 标准分数格式

```c
	AVRational rate;
	if (av_parse_video_rate(&rate, "30/1") < 0) {
		av_log(NULL, AV_LOG_ERROR, "Failed to parse video rate\n");
	}
	else {
		av_log(NULL, AV_LOG_INFO, "Parsed rate: %d/%d\n", rate.num, rate.den);
	}
```

2. 小数格式

```c
	AVRational rate;
	if (av_parse_video_rate(&rate, "29.97") < 0) {
		av_log(NULL, AV_LOG_ERROR, "Failed to parse video rate\n");
	}
	else {
		av_log(NULL, AV_LOG_INFO, "Parsed rate: %d/%d\n", rate.num, rate.den);
	}
```

3. 预定义帧率名称

```c
	const char* frame_rate_names[] = {
		// NTSC相关帧率
		"ntsc",         // 30000/1001 ≈ 29.97 fps
		"ntsc-film",    // 24000/1001 ≈ 23.976 fps

		// PAL相关帧率  
		"pal",          // 25 fps
		"qpal",         // 25 fps (PAL四分之一)
		"spal",         // 25 fps (PAL方形像素)

		// 电影帧率
		"film",         // 24 fps
		"24",           // 24 fps

		// 常用帧率
		"25",           // 25 fps
		"30",           // 30 fps
		"50",           // 50 fps
		"60",           // 60 fps

		// 分数表示
		"24000/1001",   // ≈23.976 fps
		"30000/1001",   // ≈29.97 fps
		"60000/1001",   // ≈59.94 fps

		// 高帧率
		"48",           // 48 fps
		"72",           // 72 fps
		"96",           // 96 fps
		"100",          // 100 fps
		"120",          // 120 fps
		"240",          // 240 fps

		NULL  // 结束标记
	};


	AVRational frame_rate;
	for (int i = 0; frame_rate_names[i]; i++) {
		if (av_parse_video_rate(&frame_rate, frame_rate_names[i]) >= 0) {
			printf("%-12s -> %d/%d (≈%.3f fps)\n",
				frame_rate_names[i],
				frame_rate.num,
				frame_rate.den,
				(double)frame_rate.num / frame_rate.den);
		}
		else {
			printf("%-12s -> Failed to parse\n", frame_rate_names[i]);
		}
	}
```

### av_parse_time

此函数用于将时间字符串解析为微秒时间戳的函数。函数原型如下：

```c
int av_parse_time(int64_t *timeval, const char *timestr, int duration);
```

**参数：**

+ **timeval：**输出参数，存储解析后的时间(微妙)
+ **timestr：**要解析的时间字符串
+ **duration：**标志位：1 表示解析持续时间，0 表示解析绝对时间

**时间字符串格式：**

1. 标准时间格式：

```c
void print_parsed_time(const char *timestr, int duration) {
    int64_t microseconds;
    int ret = av_parse_time(&microseconds, timestr, duration);
    
    if (ret >= 0) {
        double seconds = microseconds / 1000000.0;
        printf("%-20s -> %12lld us = %8.3f s", 
               timestr, microseconds, seconds);
        
        if (duration) {
            printf(" (duration)");
        } else {
            printf(" (absolute)");
        }
        printf("\n");
    } else {
        printf("%-20s -> 解析失败 (错误码: %d,%s)\n", timestr, ret,av_err2str(ret));
    }
}

    print_parsed_time("01:30:00", 1);      // 1.5小时
    print_parsed_time("45.5s", 1);         // 45.5秒
```

2. 特殊格式，貌似只支持now

```c
    print_parsed_time("now", 0);
```



## I/O操作（AVIO*）

> #include "libavformat/avformat.h"

avio是FFmpeg中的一个模块，用于实现多种输入输出方式的封装。

### 文件I/O

#### 打开与关闭

使用`AVIOContext*`保存打开文件的上下文，后续通过上下文进行文件操作。

首先，打开文件：

```c
	AVIOContext* ctx = NULL;
	//打开文件
	if (0 > avio_open(&ctx, "hdy.txt", AVIO_FLAG_WRITE | AVIO_FLAG_READ)) {
		av_log(ctx, AV_LOG_ERROR, "avio_open failed!\n");
		return;
	}
```

`avio_open`第三个参数是打开标志，对于文件操作来说有如下几种：

+ AVIO_FLAG_READ：只读打开
+ AVIO_FLAG_WRITE：只写打开

+ AVIO_FLAG_READ_WRITE：读写打开

文件操作完毕后，需要关闭上下文：

```c
	avio_close(ctx);
```

+ 获取文件大小

```c
	av_log(NULL, AV_LOG_INFO, "avio_size=%lld\n", avio_size(ctx));
```

+ 获取文件位置指针

```c
	av_log(NULL, AV_LOG_INFO, "avio_tell=%lld\n", avio_tell(ctx));
```

+ 移动文件位置指针

```c
	av_log(NULL, AV_LOG_INFO, "avio_seek=%lld\n", avio_seek(ctx, 5, SEEK_CUR));
	av_log(NULL, AV_LOG_INFO, "avio_skip=%lld\n", avio_skip(ctx, -5));
```

#### 写文件

+ 使用`avio_printf`，能像printf一样，格式化写内容到文件中。

  ```c
  avio_printf(ctx, "Hello, World! %s\n", "hdy");
  ```

+ 使用`avio_print_string_array`，能将以`NULL`结尾的字符串数组批量写入文件中：

  ```c
  	const char* strs[] = { "锄禾日当午\n","汗滴禾下土\n","谁知盘中餐\n","粒粒皆辛苦\n",NULL};
  	avio_print_string_array(ctx,strs);
  ```

  为了方便使用，还提供了包装宏：

  ```c
  	avio_print(ctx, "锄禾日当午\n","汗滴禾下土\n","谁知盘中餐\n","粒粒皆辛苦\n");
  ```

+ 对于简单字符串可以直接使用`avio_put_str`写入：

  ```c
  	avio_put_str(ctx, "宏定义信息科技\n");
  ```

+ 对于二进制数据或者想写入指定长度的字符串，则可以使用`	avio_write`：

  ```c
  	//写入指定长度的字符串
  	avio_write(ctx, "Hello, World!", 5);
  	//写入二进制数据
  	int tel = 5280620;
  	avio_write(ctx, (const unsigned char*)&tel, sizeof(tel));
  ```

+ 因为整数类型有大小端，所以还专门为写入整数类型提供了函数：

  + 一个字节的整数没有大小端之分

  ```c
  	avio_w8(ctx, 'A');
  ```

  + 大端(big end)写入整数

  ```c
  	avio_wb16(ctx, 0x1234);
  	avio_wb24(ctx, 0x123456);
  	avio_wb32(ctx, 0x12345678);
  	avio_wb64(ctx, 0x12345678AABBCCDD);
  ```

  + 小端写入整数

  ```c
  	avio_wl16(ctx, 0x1234);
  	avio_wl24(ctx, 0x123456);
  	avio_wl32(ctx, 0x12345678);
  	avio_wl64(ctx, 0x12345678AABBCCDD);
  ```

  

#### 读文件

+ 读取字符串，在遇到空格或者最大长度或者无法读取更多数据后，自动停止：

  函数原型如下：

  ```c
  int avio_get_str(AVIOContext *pb, int maxlen, char *buf, int buflen);
  ```

  示例：

  ```c
  	char buf[BUFSIZ] = {0};
  	avio_get_str(ctx, BUFSIZ, buf,BUFSIZ);
  ```

+ 读取指定长度的数据：下面这两个函数对于文件操作来说，是一样的。

  ```c
  	int len;
  	//1,读取指定长度
  	//len = avio_read(ctx, buf, BUFSIZ);
  	//av_log(ctx, AV_LOG_INFO, "len:%d buf=%s\n",len, buf);
  
  	//2,读取指定长度
  	len = avio_read_partial(ctx, buf, BUFSIZ);
  	av_log(ctx, AV_LOG_INFO, "len:%d buf=%s\n", len, buf);
  ```

+ 按照大小端读取整数

  ```c
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_r8(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rb16(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rb24(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rb32(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rb64(ctx));
  
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rl16(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rl24(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rl32(ctx));
  	av_log(NULL, AV_LOG_INFO, "%#x\n", avio_rl64(ctx));
  ```

  

## 多媒体文件处理

### 提取音频(extract audio)

要使用FFmpeg C API从视频中提取音频，核心流程是读取多媒体文件，从中筛选出音频数据包，然后将其写入新的音频文件。

1. 为了方便输入参数，我们使用命令行参数

   ```c
   int main(int argc, char** argv)
   {
   	//检查参数
   	if (argc < 3) {
   		printf("usage:%s <input file> <output file>\n", argv[0]);
   		return 0;
   	}
   	//获取输入输出文件名
   	const char* src = argv[1];
   	const char* dst = argv[2];
   ```

2. 然后，打开输入文件

   ```c
   	AVFormatContext* iFmtCtx = NULL;
   	AVFormatContext* oFmtCtx = NULL;
   
   	int ret,idx;
   	do
   	{	
   		//打开输入文件
   		if ((ret = avformat_open_input(&fmt_ctx, src, NULL, NULL)) < 0) {
   			av_log(NULL, AV_LOG_ERROR, "avformat_open_input failed!%s\n", av_err2str(ret));
   			break;
   		}
   ```

   **AVFormatContext** 是 FFmpeg 中的一个核心结构体，它包含了媒体文件的格式上下文信息，涵盖了音频、视频、字幕等流的相关信息和元数据。

3. 查找音频流索引

   ```c
   		//查找音频流索引
   		idx = av_find_best_stream(iFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
   		if (idx < 0) {
   			if (idx == AVERROR_STREAM_NOT_FOUND)
   				av_log(NULL, AV_LOG_ERROR, "av_find_best_stream failed! AVERROR_STREAM_NOT_FOUND\n");
   			else if (idx == AVERROR_DECODER_NOT_FOUND)
   				av_log(NULL, AV_LOG_ERROR, "av_find_best_stream failed! AVERROR_DECODER_NOT_FOUND\n");
   			break;
   		}
   		//根据索引拿到音频流
   		AVStream* iStream = iFmtCtx->streams[idx];
   ```

   

4. 创建输出文件格式上下文

   ```c
   		//分配输出文件格式上下文
   		oFmtCtx = avformat_alloc_context();
   		if (!oFmtCtx) {
   			av_log(NULL, AV_LOG_ERROR, "avformat_alloc_context failed!\n");
   			break;
   		}
   		//设置输出文件格式
   		oFmtCtx->oformat = av_guess_format(NULL, src, NULL);
   ```

5. 创建输出音频流，并拷贝编码参数

   ```c
   		//创建新的音频流
   		AVStream* oStream = avformat_new_stream(oFmtCtx, NULL);
   		if (!oStream) {
   			av_log(NULL, AV_LOG_ERROR, "avformat_new_stream failed!\n");
   			break;
   		}
   
   		//设置音频编码参数
   		if(avcodec_parameters_copy(oStream->codecpar, iStream->codecpar) < 0) {
   			av_log(NULL, AV_LOG_ERROR, "avcodec_parameters_copy failed!\n");
   			break;
   		}
   		//oStream->codecpar->codec_tag = 0;
   ```

6. 打开输出文件，写入数据

   ```c
   		//打开输出文件，打开后由oFmtCtx接管，无需手动关闭
   		if ((ret = avio_open2(&oFmtCtx->pb, dst, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
   			av_log(NULL, AV_LOG_ERROR, "avio_open2 failed!%s\n",av_err2str(ret));
   			break;
   		}
   
   		//写文件头
   		if ((ret = avformat_write_header(oFmtCtx, NULL)) < 0) {
   			av_log(NULL, AV_LOG_ERROR, "avformat_write_header failed!%s\n", av_err2str(ret));
   			break;
   		}
   
   		//从输入文件读取数据包
   		AVPacket pkt;
   		while (av_read_frame(iFmtCtx, &pkt) == 0) {
   			//不是音频流，跳过
   			if (pkt.stream_index != idx) {
   				av_packet_unref(&pkt);
   				continue;
   			}
   			//是音频流，写入到输出文件
   			else {
   				pkt.pts = av_rescale_q_rnd(pkt.pts, iStream->time_base, 
   					oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
   				pkt.dts = pkt.pts;
   				pkt.duration = av_rescale_q(pkt.duration, iStream->time_base, oStream->time_base);
   				pkt.stream_index = 0;
   				pkt.pos = -1;
   				//将pkt写入输出文件
   				av_interleaved_write_frame(oFmtCtx, &pkt);
   				av_packet_unref(&pkt);
   			}
   		}
   
   		//写文件尾
   		av_write_trailer(oFmtCtx);
   		
   	} while (0);
   ```

7. 释放资源

   ```c
   	//关闭输出文件
   	avformat_close_input(&oFmtCtx);
   	//关闭输入文件
   	avformat_close_input(&iFmtCtx);
   }
   ```

### 提取视频(extract video)

提取视频与音频类似，只需要修改几个地方即可！

1. 将查找音频流修改为查找视频流

   ```c
   	idx = av_find_best_stream(iFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
   ```

2. 因为视频可能存在B帧，所以dts不能等于pts了，需要进行计算

   ```c
   	pkt.dts = av_rescale_q_rnd(pkt.dts, iStream->time_base,
   			oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
   ```


### 转封装（remux）

转封装就是把一种封装格式变为另一种封装格式，比如把MP4转成flv格式。

![image-20251211152604192](./assets/image-20251211152604192.png)

转封装，可以说就是把提取音频和视频的代码结合在一起：

1. 把第3、4、5步改成如下代码

```c
		//打开输出文件
		if((ret = avformat_alloc_output_context2(&oFmtCtx, NULL, NULL, dst)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_alloc_output_context2 failed!%s\n",av_err2str(ret));
			break;
		}
		//遍历输入文件的流，找到音视频流
		for (size_t i = 0; i < iFmtCtx->nb_streams; i++) {
			AVStream* stream = iFmtCtx->streams[i];
			AVCodecParameters* codecpar = stream->codecpar;

			//创建新的音频流
			AVStream* oStream = avformat_new_stream(oFmtCtx, NULL);
			if (!oStream) {
				av_log(NULL, AV_LOG_ERROR, "avformat_new_stream failed!\n");
				break;
			}

			//设置音频编码参数
			if (avcodec_parameters_copy(oStream->codecpar, stream->codecpar) < 0) {
				av_log(NULL, AV_LOG_ERROR, "avcodec_parameters_copy failed!\n");
				break;
			}
			oStream->codecpar->codec_tag = 0;
		}
```

2. 把读取数据包，写入数据包部分稍微修改一下：

```c
while (av_read_frame(iFmtCtx, &pkt) == 0) {
			//不是流，跳过
			if (pkt.stream_index < 0) {
				av_packet_unref(&pkt);
				continue;
			}
			//是流，写入到输出文件
			else {
				AVStream* iStream = iFmtCtx->streams[pkt.stream_index];
				AVStream* oStream = oFmtCtx->streams[pkt.stream_index];

				//将数据包中的所有时间基转换为输出流的时间基
				if (0) {
					pkt.pts = av_rescale_q_rnd(pkt.pts, iStream->time_base,
						oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
					pkt.dts = av_rescale_q_rnd(pkt.dts, iStream->time_base,
						oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
					pkt.duration = av_rescale_q(pkt.duration, iStream->time_base, oStream->time_base);
					//pkt.pos = -1;
				}
				else {
					av_packet_rescale_ts(&pkt, iStream->time_base, oStream->time_base);
				}

				//将pkt写入输出文件
				av_interleaved_write_frame(oFmtCtx, &pkt);
				av_packet_unref(&pkt);
			}
		}
```

完成代码如下：

```c
int test4(int argc, char** argv)
{
	//检查参数
	if (argc < 3) {
		printf("usage:%s <input file> <output file>\n", argv[0]);
		return 0;
	}
	//获取输入输出文件名
	const char* src = argv[1];
	const char* dst = argv[2];

	AVFormatContext* iFmtCtx = NULL;
	AVFormatContext* oFmtCtx = NULL;

	int ret;
	do
	{
		//打开输入文件
		if ((ret = avformat_open_input(&iFmtCtx, src, NULL, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_open_input failed!%s\n", av_err2str(ret));
			break;
		}

		//打开输出文件
		if((ret = avformat_alloc_output_context2(&oFmtCtx, NULL, NULL, dst)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_alloc_output_context2 failed!%s\n",av_err2str(ret));
			break;
		}
		//遍历输入文件的流，找到音视频流
		for (size_t i = 0; i < iFmtCtx->nb_streams; i++) {
			AVStream* stream = iFmtCtx->streams[i];
			AVCodecParameters* codecpar = stream->codecpar;

			//创建新的音频流
			AVStream* oStream = avformat_new_stream(oFmtCtx, NULL);
			if (!oStream) {
				av_log(NULL, AV_LOG_ERROR, "avformat_new_stream failed!\n");
				break;
			}

			//设置音频编码参数
			if (avcodec_parameters_copy(oStream->codecpar, stream->codecpar) < 0) {
				av_log(NULL, AV_LOG_ERROR, "avcodec_parameters_copy failed!\n");
				break;
			}
			oStream->codecpar->codec_tag = 0;
		}

		if ((ret = avio_open2(&oFmtCtx->pb, dst, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avio_open2 failed!%s\n", av_err2str(ret));
			break;
		}

		//写文件头
		if ((ret = avformat_write_header(oFmtCtx, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_write_header failed!%s\n", av_err2str(ret));
			break;
		}

		//从输入文件读取数据包
		AVPacket pkt;
		while (av_read_frame(iFmtCtx, &pkt) == 0) {
			//不是流，跳过
			if (pkt.stream_index < 0) {
				av_packet_unref(&pkt);
				continue;
			}
			//是流，写入到输出文件
			else {
				AVStream* iStream = iFmtCtx->streams[pkt.stream_index];
				AVStream* oStream = oFmtCtx->streams[pkt.stream_index];

				//将数据包中的所有时间基转换为输出流的时间基
				if (0) {
					pkt.pts = av_rescale_q_rnd(pkt.pts, iStream->time_base,
						oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
					pkt.dts = av_rescale_q_rnd(pkt.dts, iStream->time_base,
						oStream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
					pkt.duration = av_rescale_q(pkt.duration, iStream->time_base, oStream->time_base);
					//pkt.pos = -1;
				}
				else {
					av_packet_rescale_ts(&pkt, iStream->time_base, oStream->time_base);
				}

				//将pkt写入输出文件
				av_interleaved_write_frame(oFmtCtx, &pkt);
				av_packet_unref(&pkt);
			}
		}

		//写文件尾
		av_write_trailer(oFmtCtx);

	} while (0);

	//if (oFmtCtx && oFmtCtx->pb) {
	//	avio_close(oFmtCtx->pb);
	//	oFmtCtx->pb = NULL;
	//}
	//关闭输出文件
	avformat_close_input(&oFmtCtx);
	//关闭输入文件
	avformat_close_input(&iFmtCtx);
}
```

### 视频裁剪

可以将视频指定时间段的内容裁剪出来。

1. 主要是在循环读取数据包之前，将帧定位到指定时间

```c
		//定位到开始时间
		if ((ret = av_seek_frame(iFmtCtx, -1, startTime * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "av_seek_frame failed!%s\n", av_err2str(ret));
			break;
		}

		//保存每个流的起始时间戳
		typedef struct Ts {
			int64_t pts;
			int64_t dts;
		}Ts;
		Ts* ts = av_malloc(iFmtCtx->nb_streams * sizeof(Ts));
		for (size_t i = 0; i < iFmtCtx->nb_streams; i++) {
			ts[i].pts = AV_NOPTS_VALUE;
			ts[i].dts = AV_NOPTS_VALUE;
		}
```

2. 然后在循环中，计算裁剪之后的数据包的pts和dts

```c
		//从输入文件读取数据包
		AVPacket pkt;
		while (av_read_frame(iFmtCtx, &pkt) == 0) {

			if (ts[pkt.stream_index].dts == AV_NOPTS_VALUE && pkt.dts != AV_NOPTS_VALUE) {
				ts[pkt.stream_index].dts = pkt.dts;
			}
			if (ts[pkt.stream_index].pts == AV_NOPTS_VALUE && pkt.pts != AV_NOPTS_VALUE) {
				ts[pkt.stream_index].pts = pkt.pts;
			}

            //到达结束时间，跳出循环
			if (endTime > 0 && av_q2d(iFmtCtx->streams[pkt.stream_index]->time_base) * pkt.pts >= endTime) {
				av_packet_unref(&pkt);
				av_log(NULL, AV_LOG_ERROR, "endtime\n");
				break;
			}

			//不是流，跳过
			if (pkt.stream_index < 0) {
				av_packet_unref(&pkt);
				continue;
			}
			//是流，写入到输出文件
			else {
				AVStream* iStream = iFmtCtx->streams[pkt.stream_index];
				AVStream* oStream = oFmtCtx->streams[pkt.stream_index];

				//将数据包中的所有时间基转换为输出流的时间基
				pkt.pts = pkt.pts - ts[pkt.stream_index].pts;
				pkt.dts = pkt.dts - ts[pkt.stream_index].dts;

				//如果显示时间戳小于解码时间戳，则将显示时间戳设置为解码时间戳
				if (pkt.pts < pkt.dts) {
					pkt.pts = pkt.dts;
				}

				av_packet_rescale_ts(&pkt, iStream->time_base, oStream->time_base);

				//将pkt写入输出文件
				pkt.pos = -1;
				av_interleaved_write_frame(oFmtCtx, &pkt);
				av_packet_unref(&pkt);
			}
		}
		av_free(ts);

		//写文件尾
		av_write_trailer(oFmtCtx);

	} while (0);
```

完整代码如下：

```c
int test4(int argc, char** argv)
{
	//检查参数
	if (argc < 3) {
		printf("usage:%s <input file> <output file> [start end]\n", argv[0]);
		return 0;
	}
	//获取输入输出文件名
	const char* src = argv[1];
	const char* dst = argv[2];
	int startTime = 60;
	int endTime = 80;

	AVFormatContext* iFmtCtx = NULL;
	AVFormatContext* oFmtCtx = NULL;

	int ret;
	do
	{
		//打开输入文件
		if ((ret = avformat_open_input(&iFmtCtx, src, NULL, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_open_input failed!%s\n", av_err2str(ret));
			break;
		}

		//打开输出文件
		if((ret = avformat_alloc_output_context2(&oFmtCtx, NULL, NULL, dst)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_alloc_output_context2 failed!%s\n",av_err2str(ret));
			break;
		}
		//遍历输入文件的流，找到音视频流
		for (size_t i = 0; i < iFmtCtx->nb_streams; i++) {
			AVStream* stream = iFmtCtx->streams[i];
			AVCodecParameters* codecpar = stream->codecpar;
			//if (codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			//	codecpar->codec_type != AVMEDIA_TYPE_VIDEO ) {
			//	idx = i;
			//	break;
			//}

			//创建新的音频流
			AVStream* oStream = avformat_new_stream(oFmtCtx, NULL);
			if (!oStream) {
				av_log(NULL, AV_LOG_ERROR, "avformat_new_stream failed!\n");
				break;
			}

			//设置音频编码参数
			if (avcodec_parameters_copy(oStream->codecpar, stream->codecpar) < 0) {
				av_log(NULL, AV_LOG_ERROR, "avcodec_parameters_copy failed!\n");
				break;
			}
			oStream->codecpar->codec_tag = 0;
		}

		if ((ret = avio_open2(&oFmtCtx->pb, dst, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avio_open2 failed!%s\n", av_err2str(ret));
			break;
		}

		//写文件头
		if ((ret = avformat_write_header(oFmtCtx, NULL)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "avformat_write_header failed!%s\n", av_err2str(ret));
			break;
		}

		//定位到开始时间
		if ((ret = av_seek_frame(iFmtCtx, -1, startTime * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD)) < 0) {
			av_log(NULL, AV_LOG_ERROR, "av_seek_frame failed!%s\n", av_err2str(ret));
			break;
		}

		//保存每个流的起始时间戳
		typedef struct Ts {
			int64_t pts;
			int64_t dts;
		}Ts;
		Ts* ts = av_malloc(iFmtCtx->nb_streams * sizeof(Ts));
		for (size_t i = 0; i < iFmtCtx->nb_streams; i++) {
			ts[i].pts = AV_NOPTS_VALUE;
			ts[i].dts = AV_NOPTS_VALUE;
		}

		//从输入文件读取数据包
		AVPacket pkt;
		while (av_read_frame(iFmtCtx, &pkt) == 0) {

			if (ts[pkt.stream_index].dts == AV_NOPTS_VALUE && pkt.dts != AV_NOPTS_VALUE) {
				ts[pkt.stream_index].dts = pkt.dts;
			}
			if (ts[pkt.stream_index].pts == AV_NOPTS_VALUE && pkt.pts != AV_NOPTS_VALUE) {
				ts[pkt.stream_index].pts = pkt.pts;
			}

			if (endTime > 0 && av_q2d(iFmtCtx->streams[pkt.stream_index]->time_base) * pkt.pts >= endTime) {
				av_packet_unref(&pkt);
				av_log(NULL, AV_LOG_ERROR, "endtime\n");
				break;
			}

			//不是流，跳过
			if (pkt.stream_index < 0) {
				av_packet_unref(&pkt);
				continue;
			}
			//是流，写入到输出文件
			else {
				AVStream* iStream = iFmtCtx->streams[pkt.stream_index];
				AVStream* oStream = oFmtCtx->streams[pkt.stream_index];

				//将数据包中的所有时间基转换为输出流的时间基
				pkt.pts = pkt.pts - ts[pkt.stream_index].pts;
				pkt.dts = pkt.dts - ts[pkt.stream_index].dts;

				//如果显示时间戳小于解码时间戳，则将显示时间戳设置为解码时间戳
				if (pkt.pts < pkt.dts) {
					pkt.pts = pkt.dts;
				}

				av_packet_rescale_ts(&pkt, iStream->time_base, oStream->time_base);

				//将pkt写入输出文件
				pkt.pos = -1;
				av_interleaved_write_frame(oFmtCtx, &pkt);
				av_packet_unref(&pkt);
			}
		}
		av_free(ts);

		//写文件尾
		av_write_trailer(oFmtCtx);

	} while (0);

	//关闭输出文件
	avformat_close_input(&oFmtCtx);
	//关闭输入文件
	avformat_close_input(&iFmtCtx);
}
```

