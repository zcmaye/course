#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>

#define SPACE  0	//空地
#define WALL   1	//墙
#define DEST   2	//目的地
#define BOX    3	//箱子
#define PLAYER 4	//玩家
//当前所在关卡
int level = 0;
//定义推箱子地图
int initMap[3][10][10] =
{
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,0,0,1,2,1,0,0,0,0},
		{0,0,0,1,3,1,1,1,1,0},
		{0,1,1,1,0,0,3,2,1,0},
		{0,1,2,3,4,3,1,1,1,0},
		{0,1,1,1,1,0,1,0,0,0},
		{0,0,0,0,1,2,1,0,0,0},
		{0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,1,1,0,0},
		{0,1,2,0,1,1,0,0,1,0},
		{1,0,0,0,3,0,0,0,0,1},
		{1,0,0,3,4,3,0,0,2,1},
		{0,1,2,0,3,0,0,0,1,0},
		{0,0,1,0,0,0,0,1,0,0},
		{0,0,0,1,2,0,1,0,0,0},
		{0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,2,0,0,0,0,2,1,0},
		{0,1,0,0,0,0,0,0,1,0},
		{0,1,0,3,0,3,0,0,1,0},
		{0,1,0,0,4,0,0,0,1,0},
		{0,1,0,3,0,3,0,0,1,0},
		{0,1,2,0,0,0,0,2,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0}
	}
};

int map[3][10][10];

//把initMap赋值给map
void init()
{
	for (int l = 0; l < 3; l++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				map[l][i][k] = initMap[l][i][k];
			}
		}
	}
}

//绘制地图
void drawMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			/*
			if (map[level][i][k] == 0)
			{
				printf("  ");
			}
			else if(map[level][i][k] ==1)
			{
				//printf("%d ", map[level][i][k]);
				printf("墙");
			}
			else if(map[level][i][k] == 2)
			{
				printf("口");
			}*/
			switch (map[level][i][k])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf("▓ ");
				break;
			case DEST:
				printf("☆");
				break;
			case BOX:
				printf("□");
				break;
			case PLAYER:
				printf("♀");
				break;
			case DEST + BOX:				//箱子在目的地上
				printf("★");
				break;
			case DEST + PLAYER:				//玩家在目的地上
				printf("♂");
				break;
			}
		}
		printf("\n");
	}
}
//判断通过当前关卡
bool jude()
{
	for (int  i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (map[level][i][k] == BOX)
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	//初始化数据
	init();
	//输出地图
	drawMap();

	//推箱子
	//获取键盘按键，getchar()  scanf()  ->输入数据之后需要按回车才能继续
	//找一个输入之后不需要按回车的函数，_getch();  需要头文件conio.h,注意：此头文件不是C语言标准头文件
	//72 80 75 77 上  下  左 右  _getch()是一个阻塞函数
	while (true)
	{
		int r = 0, c = 0;	//玩家所在的下标
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (map[level][i][k] == PLAYER)
				{
					r = i;
					c = k;
				}
			}
		}


		char userkey = _getch();
		//printf("%d %c\n", userkey, userkey);
		switch (userkey)
		{
		case 72:
		case 'W':
		case 'w':
			//玩家的前面是空地
			if (map[level][r - 1][c] == SPACE || map[level][r-1][c] == DEST)
			{
				map[level][r - 1][c] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//玩家的前面是箱子
			else if (map[level][r - 1][c] == BOX || map[level][r-1][c] ==BOX+DEST)	
			{
				//箱子的前面是空地，或者目的地
				if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST)
				{
					//1，移动箱子
					map[level][r - 2][c] += BOX;
					map[level][r - 1][c] -= BOX;
					//2，移动玩家
					map[level][r - 1][c] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 80:
		case 's':
		case 'S':
			//玩家的前面是空地
			if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST)
			{
				map[level][r + 1][c] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//玩家的前面是箱子
			else if (map[level][r + 1][c] == BOX || map[level][r + 1][c] == BOX + DEST)
			{
				//箱子的前面是空地，或者目的地
				if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST)
				{
					//1，移动箱子
					map[level][r + 2][c] += BOX;
					map[level][r + 1][c] -= BOX;
					//2，移动玩家
					map[level][r + 1][c] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 75:
		case 'a':
		case 'A':
			//玩家的前面是空地
			if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST)
			{
				map[level][r][c - 1] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//玩家的前面是箱子
			else if (map[level][r][c - 1] == BOX || map[level][r][c - 1] == BOX + DEST)
			{
				//箱子的前面是空地，或者目的地
				if (map[level][r][c - 2] == SPACE || map[level][r][c - 2] == DEST)
				{
					//1，移动箱子
					map[level][r][c - 2] += BOX;
					map[level][r][c - 1] -= BOX;
					//2，移动玩家
					map[level][r][c - 1] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 77:
		case 'd':
		case 'D':
			//玩家的前面是空地
			if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST)
			{
				map[level][r][c + 1] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//玩家的前面是箱子
			else if (map[level][r][c + 1] == BOX || map[level][r][c + 1] == BOX + DEST)
			{
				//箱子的前面是空地，或者目的地
				if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST)
				{
					//1，移动箱子
					map[level][r][c + 2] += BOX;
					map[level][r][c + 1] -= BOX;
					//2，移动玩家
					map[level][r][c + 1] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		}
		system("cls");
		drawMap();
		if (jude())
		{
			if (level > 2)
			{
				level = -1;
				init();
			}
			level++;
			printf("恭喜你，过关了\n");
		}
	}


	return 0;
}