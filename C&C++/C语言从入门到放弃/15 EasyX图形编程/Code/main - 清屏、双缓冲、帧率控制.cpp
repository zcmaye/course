#include<stdio.h>
#include<easyx.h>
#include<time.h>
//清屏
//双缓冲
//帧率控制

int main()
{
	initgraph(640, 480, EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 231, 232));
	cleardevice();
	setbkmode(TRANSPARENT);

	//FPS 60f
	const clock_t FPS = 1000 / 60;	//1秒/60帧 = 16.6  每一帧应该花费的时间
	int startTime = 0;
	int freamTime = 0;	//当前帧实际执行时间

	int score = 0;
	char str[50] = "";
	while (true)
	{
		startTime = clock();	//50ms

		sprintf(str, "Score:%d", score++);
		settextcolor(BLACK);

		//双缓冲防止闪屏
		BeginBatchDraw();
		cleardevice();	//用设置的背景颜色填充整个窗口

		outtextxy(20, 20, str);

		EndBatchDraw();

		freamTime = clock() - startTime;	//56-50 = 6
		if (freamTime > 0)
		{
			Sleep(FPS - freamTime);
		}	
	}

	return 0;
}