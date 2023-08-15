#pragma once
//把SDL一些接口封装一下，便于使用
#include<stdbool.h>
#include<SDL.h>
#include<sdl_image.h>
/*@Game*/
typedef struct Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;			//游戏是否在运行
}Game;

static Game gGame;		//全局的游戏对象

//初始化SDL
static bool game_init(const char* title,int w,int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
	{
		SDL_Log("game init!\n");
		//创建窗口
		gGame.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (gGame.window)
		{
			SDL_Log("window created!\n");
		}

		//创建渲染器
		gGame.renderer = SDL_CreateRenderer(gGame.window, -1, 0);
		if (gGame.renderer)
		{
			SDL_Log("renderer created!\n");
		}
		gGame.isRunning = true;
	}
	else
	{
		gGame.isRunning = false;
	}
	return gGame.isRunning;
}

//清理SDL
static void game_clean()
{
	SDL_DestroyWindow(gGame.window);
	SDL_DestroyRenderer(gGame.renderer);
	SDL_Quit();
	SDL_Log("game clean!\n");
}

//判断游戏是否在运行
static bool game_running()
{
	return gGame.isRunning;
}

static void gamer_Done()
{
	gGame.isRunning = false;
}

/*@Tools*/
SDL_Texture* loadTexture(const char* file)
{
	//加载一张图片
	SDL_Surface* sfc = IMG_Load(file);
	if (!sfc)
	{
		SDL_Log("load failed,%s\n", SDL_GetError());
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(gGame.renderer, sfc);
	SDL_FreeSurface(sfc);
	return tex;
}

void SDL_RenderDrawEllipse(SDL_Renderer* render, SDL_Rect* rect)
{
	//半轴长
	int aHalf = rect->w / 2;
	int bHalf = rect->h / 2;

	int x, y;
	//求出圆上每个坐标点
	for (float angle = 0; angle < 360; angle += 0.1)
	{
		x = (rect->x + aHalf) + aHalf * SDL_cos(angle);
		y = (rect->y + bHalf) + bHalf * SDL_sin(angle);
		SDL_RenderDrawPoint(render, x, y);
	}
}