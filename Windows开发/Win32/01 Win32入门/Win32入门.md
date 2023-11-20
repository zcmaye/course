## 窗口创建的过程

+ 定义WinMain函数
+ 定义窗口处理函数(自定义，处理消息)
+ 注册窗口类(向操作系统写入一些数据)
+ 创建窗口(内存中创建窗口)
+ 显示窗口(绘制窗口的图像)
+ 消息循环(获取/翻译/派发消息)
+ 消息处理

## 窗口创建代码实现

创建一个Windows空项目，把字符集改为`多字节字符集`。

```cpp
#include<windows.h>

//2，窗口处理函数(自定义的处理消息的函数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//1，入口函数
int WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR lpCmdLine, int nCmdShow)
{
	//3，注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;	//窗口水平和垂直方向(窗口大小改变)变化时，窗口重绘
	//注册窗口类(讲以上所有赋值全部写入操作系统)
	RegisterClass(&wc);	
	//4，在内存中创建窗口
	HWND hWnd = CreateWindow(wc.lpszClassName, "Window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	//5，显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//6，消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	//将消息交给窗口处理函数来处理。
	}

	return 0;
}
```

## 消息机制