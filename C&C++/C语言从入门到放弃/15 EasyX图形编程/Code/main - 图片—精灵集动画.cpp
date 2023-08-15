#include<stdio.h>
#include<easyx.h>
#include"tool.h"
#include<time.h>
int main()
{
	initgraph(480, 800, EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 231, 232));
	cleardevice();
	
	const int frameDelay = 1000 / 60;
	int frameStart = 0;
	int frameTime = 0;

	//动画
	IMAGE img_sheet;
	loadimage(&img_sheet, "assets/pikachu.png");
	
	int imgSize = 32;	//每帧的尺寸
	int frames = 7;		//总共有多少帧
	int speed = 200;	//多少毫秒切换一张
	int index = 6;		//贴那一张图

	while (true)
	{
		frameStart = clock();

		BeginBatchDraw();
		cleardevice();
		//void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE *pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);
		drawImg(250, 250, imgSize, imgSize, &img_sheet, index * imgSize, 0);

		EndBatchDraw();

		index = (clock() / speed) % frames;

		frameTime = clock() - frameStart;
		if (frameDelay - frameTime > 0)	//16 -10 = 6 >0
		{
			Sleep(frameDelay - frameTime);
		}
		
	}



	getchar();
	return 0;
}