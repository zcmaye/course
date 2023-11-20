## zlib

### 简介

lib是一套通用的解压缩开源库，提供了内存（in-memory）压缩和解压函数，能检测解压出来的数据完整性，zlib 也支持读写 gzip (.gz) 格式的文件，可以阅读：zlib库介绍三：gzip(.gz格式)文件读写。

默认且目前仅使用deflate算法压缩data部分；deflate是一种压缩算法,是huffman编码的一种加强。
### zlib库的应用

数以万计的应用程序直接或间接依靠zlib压缩函式库，包括：

FFmpeg：以zlib读写Matroska等以DEFLATE算法压缩的多媒体串流格式。

OpenSSH、OpenSSL：以zlib达到最佳化加密网络传输。

Linux核心：使用zlib以实作网络协定的压缩、档案系统的压缩以及开机时解压缩自身的核心。

libpng，用于PNG图形格式的一个实现，对bitmap数据规定了DEFLATE作为流压缩方法。

...

### 下载和编译

从[github](https://github.com/madler/zlib)拉取源码！

```cpp
git clone https://github.com/madler/zlib.git
```

拉去完毕进入zlib目录。

```cpp
cd zlib
```

创建build目录并进入

```sh
mkdir build
cd build
```

然后执行cmake，同时设置安装路径

```sh
cmake .. -DCMAKE_INSTALL_PREFIX="../install_2022"
```

编译并安装

```cmake
cmake --build . --target INSTALL --config Release
```

![image-20230909215631023](assets/image-20230909215631023.png)

打开install_2022目录，可以看到一下文件。

![image-20230909215827523](assets/image-20230909215827523.png)

所有文件内容如下图所示：

![image-20230909215756056](assets/image-20230909215756056.png)



### 库使用

#### compress/uncompress

ompress和uncompress是zlib最基本的两个函数了。他们分别用于压缩和解压数据。 原型如下：

```c
int  compress(Bytef *dest,   			
              uLongf *destLen,			
              const Bytef *source, 		
              uLong sourceLen);			

int compress2(unsigned char* dest, 
			 unsigned long*destLen, 
			 const unsigned char* source,
			 unsigned long sourceLen, 
			 int level);				

int uncompress(unsigned char* dest, 
				unsigned long* destLen,
				unsigned char* source, 
				unsigned long sourceLen);
				
int uncompress2(unsigned char* dest,
				unsigned long* destLen,
				unsigned char* source, 
				unsigned long* sourceLen);
```

**参数：**

+ dest：目标缓冲区(存放解/压缩之后的数据)

+ destLen：解/压缩缓冲区长度(解/压缩之前必须传入缓冲区实际大小，解/压缩之后返回实际使用大小)

+ source：源缓冲区(待解/压缩的数据)

+ sourceLen：源缓冲区长度(待解/压缩的数据的长度)
+ level：压缩比例，压缩级别取值：0 - 9。0压缩速度最快，9压缩速度最慢，压缩率最大。0表示不进行压缩。`compress2才有`

**返回值：**

- Z_OK：成功。
- Z_MEM_ERROR：没有足够的内存。
- Z_BUF_ERROR：输出的缓冲区没有足够的空间。
- Z_STREAM_ERROR：level参数设置不正确。`compress2才有`

> uncompress2与uncompress相同，除了sourceLen是一个指针，其中源的长度是*sourceLen。返回时，*sourceLen是消耗的源字节数。

**测试：**

```c
int main()
{
	char de_text[128];
	size_t de_len = 128;

	//char text[] = "zlib compress and uncompress test\nzcmayeo@gmail.com\n2023-10-30\n";
	char text[] = "1111111111111111111111111111111111111111111111111111";
	size_t src_len = strlen(text) + 1;

	char* dst = NULL;
    //compressBound()返回对sourceLen字节进行compress()或compress2()后压缩大小的上界。它将在compress()或compress2()调用之前使用，以分配目标缓冲区。
	size_t dst_len = compressBound(src_len);
	if ((dst = malloc(sizeof(char) * dst_len)) == NULL)
	{
		printf("no enough memory!\n");
		return -1;
	}
	//压缩
	int ret = compress(dst, &dst_len, text, src_len);
	if (ret != Z_OK)
	{
		printf("compress failed! %d\n",ret);
		return -1;
	}

	//查看压缩之后的数据和长度
	printf("%llu %s\n",dst_len,dst);
	//解压
	if (uncompress(de_text, &de_len, dst, dst_len) != Z_OK)
	{
		printf("uncompress failed!\n");
		return -1;
	}

	//打印解压结果
	printf("%s\n", de_text);
	free(dst);

	return 0;
}
```

#### infate/deflate/z_stream

这里infate 和defate 其实是指两组函数.

- deflateInit() + deflate() + deflateEnd()用于完成流的压缩
- inflateInit() + inflate() + inflateEnd()用于完成解压缩功能

```c
//压缩
int deflateInit(z_streamp strm);
int deflate(z_streamp strm, int flush);
int deflateEnd(z_streamp strm);
//解压
int inflateInit(z_streamp strm);
int inflate(z_streamp strm, int flush);
int inflateEnd(z_streamp strm);
```

z_stream是上面两组函数中用到的，用来表示流的数据结构。

```c
typedef struct z_stream_s {
    z_const Bytef *next_in;     /* 下一个输入字节 */
    uInt     avail_in;  /*  下一个输入时可用的字节数 */
    uLong    total_in;  /*  到目前为止已读取的输入字节总数 */

    Bytef    *next_out; /* 下一个输出字节将在这里 */
    uInt     avail_out; /* 下一个输出的剩余空闲空间 */
    uLong    total_out; /* 到目前为止输出的总字节数 */

    z_const char *msg;  /* 最后一个错误消息，如果没有错误，则为NULL */
    struct internal_state FAR *state; /* 内部状态，应用程序不可见 */

    alloc_func zalloc;  /* 用于分配内部状态 */
    free_func  zfree;   /* 用来释放内部状态 */
    voidpf     opaque;  /* 传递给zalloc和zfree的私有数据对象 */

    int     data_type;  /* 关于数据类型的最佳猜测:用于deflate的二进制或文本，或用于膨胀的解码状态 */
    uLong   adler;      /* 未压缩数据的Adler-32或CRC-32值 */
    uLong   reserved;   /* 保留成员供将来使用 */
} z_stream;
```

