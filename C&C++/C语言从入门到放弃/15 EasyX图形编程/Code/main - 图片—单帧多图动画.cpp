#include<stdio.h>
#include<easyx.h>
#include"tool.h"
#include<time.h>
int main()
{
	initgraph(480, 800, EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 231, 232));
	cleardevice();

	//动画
	IMAGE img_enemy[4];
	char path[100] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		sprintf(path, "assets/enemy1_down%d.png", i + 1);
		loadimage(img_enemy + i, path);
	}

	const int frameDelay = 1000 / 60;
	int frameStart = 0;
	int frameTime = 0;


	int index = 0;
	int frames = 4;
	int speed = 200;	//每隔500毫秒切换一帧
	while (true)
	{
		frameStart = clock();

		BeginBatchDraw();
		cleardevice();
		
		drawImg(0, 0, img_enemy + index);

		EndBatchDraw();

		//index = (index + 1) % frames;
		index = (clock() / speed) % frames;		//1250 / 500

		frameTime = clock() - frameStart;
		if (frameDelay - frameTime > 0)	//16 -10 = 6 >0
		{
			Sleep(frameDelay - frameTime);
		}
		
	}



	getchar();
	return 0;
}