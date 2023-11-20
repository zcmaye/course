#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define ROW 10
#define COL 10
void initMap(int map[ROW][COL]);
void loadImg(IMAGE img[]);
void drawMap(int map[ROW][COL], IMAGE img[]);
void mouseEvent(int map[ROW][COL]);
void openNull(int map[ROW][COL], int row, int col);
void judge(int map[ROW][COL], int row, int col);
void showMap(int map[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			printf("%2d ", map[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}
bool isOver = false;	//点到雷了，游戏结束标记
bool isWin = false;
int main()
{
	initgraph(COL*40, ROW*40,EW_SHOWCONSOLE);

	mciSendString("open ./images/start.mp3", NULL, 0, NULL);
	mciSendString("play ./images/start.mp3", NULL, 0, NULL);


	//设置随机数种子
	srand((unsigned)time(NULL));

	//扫雷游戏的数据
	int map[ROW][COL] = { 0 };
	//通过界面把数据展现给用户
	IMAGE img[12];

	initMap(map);
	loadImg(img);

	showMap(map);
	while (true)
	{
		mouseEvent(map);
		drawMap(map, img);
		
		//if (isOver)
		//{
		//	int ret = MessageBox(GetHWnd(), "你点到雷了,是否再来一把？", "提示", MB_OKCANCEL);
		//	if (ret == IDOK)
		//	{
		//		initMap(map);
		//		isOver = false;
		//	}
		//	else
		//	{
		//		exit(0);//退出程序
		//	}
		//}
		//else if(isWin)
		//{
		//	int ret = MessageBox(GetHWnd(), "你过关了,是否再来一把？", "提示", MB_OKCANCEL);
		//	if (ret == IDOK)
		//	{
		//		initMap(map);
		//		isWin = false;
		//	}
		//	else
		//	{
		//		exit(0);//退出程序
		//	}
		//}

		if (isOver || isWin)
		{
			char text[50] = { 0 };
			if (isOver)
				strcpy(text, "你点到雷了，是否再来一把？");
			else
				strcpy(text, "你过关了,是否再来一把？");

			int ret = MessageBox(GetHWnd(), text, "提示", MB_OKCANCEL);
			if (ret == IDOK)
			{
				initMap(map);
				isWin = false;
				isOver = false;
			}
			else
			{
				exit(0);//退出程序
			}
		}
	}
		
		

	getchar();
	return 0;
}

void initMap(int map[ROW][COL])
{
	//把数组元素全部初始化为0
	memset(map, 0, ROW*COL*sizeof(map));
	//给数组里面随机埋雷 雷用-1表示 只要10个
	for (int i = 0; i < 10; )
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;			//只有成功设置了一个雷，i才会自增
		}
	}

	//雷周围的九宫格数字都加1（雷自己除外 -1）
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//找到每一个雷
			if (map[i][k] == -1)
			{
				//遍历雷周围的九宫格
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = k - 1; c <= k + 1; c++)
					{
						if ((r >= 0 && r < ROW && c >= 0 && c < COL) && map[r][c] != -1)
						{
							map[r][c] ++;
						}
					}
				}

			}
		}
	}

	//加密格子
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			map[i][k] += 20;
		}
	}
}
void loadImg(IMAGE img[])
{
	//加载图片
	for (int i = 0; i < 12; i++)
	{
		char imgName[50] = { 0 };
		sprintf(imgName, "./images/%d.jpg", i);
		loadimage(img + i, imgName, 40, 40);
	}
}
void drawMap(int map[ROW][COL], IMAGE img[])
{
	//贴图片
	for (int i = 0; i < ROW; i++)			//对应y
	{
		for (int k = 0; k < COL; k++)		//对应x
		{
			if (map[i][k] >= 0 && map[i][k] <= 8)
			{
				putimage(k * 40, i * 40, &img[map[i][k]]);
			}
			else if (map[i][k] == -1)
			{
				putimage(k * 40, i * 40, img + 9);
			}
			else if (map[i][k] >= 19 && map[i][k] <= 28)
			{
				putimage(k * 40, i * 40, img + 10);
			}
			else if(map[i][k] > 28)
			{
				putimage(k * 40, i * 40, img + 11);
			}
		}
	}
}
void mouseEvent(int map[ROW][COL])
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		//鼠标msg 里面有x，y但是没有行和列，自己求一下
		int r = msg.y/40;
		int c = msg.x/40;
		//鼠标左键点击打开对应的格子,让数组元素-20
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			mciSendString("close click",NULL,0,NULL);
			mciSendString("open ./images/click.wav alias click", NULL, 0, NULL);
			mciSendString("play click", NULL, 0, NULL);
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				if (map[r][c] == 0)
				{
					mciSendString("close search", NULL, 0, NULL);
					mciSendString("open ./images/search.wav alias search", NULL, 0, NULL);
					mciSendString("play search", NULL, 0, NULL);
				}
				openNull(map,r, c);
				judge(map, r, c);
				showMap(map);
			}		
		}
		//鼠标右键标记格子
		else if (msg.uMsg == WM_RBUTTONDOWN)
		{
			mciSendString("close rightClick", NULL, 0, NULL);
			mciSendString("open ./images/rightClick.wav alias rightClick", NULL, 0, NULL);
			mciSendString("play rightClick", NULL, 0, NULL);
			if (map[r][c] >= 19 && map[r][c] <= 28)	//如果没有打开，也没有标记，就标记一下
			{
				map[r][c] += 20;
				showMap(map);
			}
			else if(map[r][c]>28)	//已经标记过了，取消标记
			{
				map[r][c] -= 20;
			}
		}
	}
}
void openNull(int map[ROW][COL],int row, int col)
{
	if (map[row][col] == 0)
	{
		for (int i = row-1; i <= row+1; i++)
		{
			for (int k = col-1; k <= col+1; k++)
			{
				//如果周围的格子没有被打开，就打开
				if ((i>=0 &&i<ROW && k>=0 &&k<COL) &&map[i][k] > 19 && map[i][k]<=28)
				{
					map[i][k] -= 20;
					openNull(map, i, k);
				}
			}
		}
	}
}
void judge(int map[ROW][COL], int row, int col)
{
	//如果点到了雷
	if (map[row][col] == -1)
	{
		//把所有的雷都打开
		for (int i = 0; i < ROW; i++)
		{
			for (int k = 0; k < COL; k++)
			{
				//雷没有打开，但是也没有被标记
				if (map[i][k] == 19)
				{
					map[i][k] -= 20;
				}
				//标记了的雷也要打开
				else if (map[i][k] == 39)
				{
					map[i][k] -= 40;
				}
			}
		}
		isOver = true;
	}

	//把应该点开的格子都点开了，游戏就胜利了
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] >= 0 && map[i][k] <= 8)
			{
				cnt++;
			}
		}
	}
	if (cnt == ROW * COL - 10)
	{
		isWin = true;
	}
	printf("cnt:%d\n", cnt);
}