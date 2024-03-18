## 简介

ibjpeg-turbo 是一个开源的 JPEG图像编解码器。

+ 官网：<https://www.libjpeg-turbo.org/>
+ github:<https://github.com/libjpeg-turbo/libjpeg-turbo/releases>
+ 3.0.2版本库：[安装程序](assets/libjpeg-turbo-3.0.2-vc64.exe)

## 使用

### 将RGB转为jpeg格式

```cpp
bool RGB2Jpeg(const BYTE* rgbData, int w, int h, BYTE** jpegData,uLong* len)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];        //pointer to JSAMPLE row[s]

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_mem_dest(&cinfo, jpegData, len);
	//jpeg_stdio_dest(&cinfo, outfile);
	cinfo.image_width = w;      //image width and height, in pixels
	cinfo.image_height = h;
	cinfo.input_components = 3;         //#RGB of color components per pixel
	//cinfo.in_color_space = JCS_EXT_BGR;         //colorspace of input image
	cinfo.in_color_space = JCS_EXT_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 95, TRUE);//limit to baseline-JPEG values
	jpeg_start_compress(&cinfo, TRUE);

	int row_stride = w * 3; // JSAMPLEs per row in image_buffer
	while (cinfo.next_scanline < cinfo.image_height)
	{
		//这里我做过修改，由于jpg文件的图像是倒的，所以改了一下读的顺序
		//row_pointer[0] = &bits[(cinfo.image_height - cinfo.next_scanline - 1) * row_stride];
		row_pointer[0] = (BYTE*)&rgbData[cinfo.next_scanline * row_stride];
		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	return true;
}
```

### 将jpeg转RGB

```cpp
static bool Jpeg2RGB(const BYTE* jpegData, size_t len, BYTE** rgbData, size_t* rgbLen)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];
	int width = 0, height = 0;

	//初始化jpeg解压对象
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	//指定输入数据
	jpeg_mem_src(&cinfo, jpegData, len);

	//读取jpeg文件头
	jpeg_read_header(&cinfo, TRUE);

	//开始解压
	jpeg_start_decompress(&cinfo);

	//获取宽度和高度
	width = cinfo.output_width;
	height = cinfo.output_height;

	//计算解压后需要的缓冲区大小
	*rgbLen = width * height * 3 * sizeof(BYTE);
	if (!*rgbLen) {
		printf("rgblen get fail\n");
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		return false;
	}
	//分配解压后数据存放的缓冲区
	*rgbData = (BYTE*)malloc(*rgbLen);
	if (!*rgbData)
	{
		printf("rgData get fail\n");
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		return false;
	}

	//朱行读取图像并转换为RGB
	int row_stride = cinfo.output_width * cinfo.output_components;
	while (cinfo.output_scanline < cinfo.output_height)
	{
		row_pointer[0] = &(*rgbData)[cinfo.output_scanline * row_stride];
		//读取一行数据
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
	}
	//结束解压
	jpeg_finish_decompress(&cinfo);
	//释放资源
	jpeg_destroy_decompress(&cinfo);
	return true;
}
```

如果在将jpeg转RGB时，还需要缩放，则需要使用另外的接口。

```cpp
static bool scaleJpeg(const BYTE* jpegData, size_t len,
	BYTE** scaleData, int* scaleW, int* scaleH)
{
	// 初始化TurboJPEG解压对象
	tjhandle decompressor = tjInitDecompress();
	if (!decompressor)
	{
		printf("Failed to initialize TurboJPEG decompressor\n");
		return false;
	}

	//获取图像信息
	int width, height, subsamp = 0;
	if (tjDecompressHeader2(decompressor, (BYTE*)jpegData, len, &width, &height, &subsamp) != 0)
	{
		printf("Failed to read JPEG header\n");
		tjDestroy(decompressor);
		return false;
	}

	// 分配内存存储缩放后的图像数据

	uLong scaleLen = *scaleW * *scaleH * tjPixelSize[TJPF_RGB];
	*scaleData = (BYTE*)malloc(scaleLen);
	if (!*scaleData)
	{
		printf("Memory allocation failed\n");
		tjDestroy(decompressor);
		return false;
	}

	//缩放jpeg图像
	if (tjDecompress2(decompressor, jpegData, len, *scaleData, *scaleW, 0, *scaleH, TJPF_RGB,TJFLAG_FASTDCT) != 0)
	{
		printf("Failed to decompress JPEG data:%s\n",tjGetErrorStr());
		free(*scaleData);
		*scaleData = NULL;
		tjDestroy(decompressor);
		return false;
	}
	//释放资源
	tjDestroy(decompressor);
	return true;
}
```

