#pragma once
//��SDLһЩ�ӿڷ�װһ�£�����ʹ��
#include<stdbool.h>
#include<SDL.h>
#include<sdl_image.h>
/*@Game*/
typedef struct Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;			//��Ϸ�Ƿ�������
}Game;

static Game gGame;		//ȫ�ֵ���Ϸ����

//��ʼ��SDL
static bool game_init(const char* title,int w,int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
	{
		SDL_Log("game init!\n");
		//��������
		gGame.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (gGame.window)
		{
			SDL_Log("window created!\n");
		}

		//������Ⱦ��
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

//����SDL
static void game_clean()
{
	SDL_DestroyWindow(gGame.window);
	SDL_DestroyRenderer(gGame.renderer);
	SDL_Quit();
	SDL_Log("game clean!\n");
}

//�ж���Ϸ�Ƿ�������
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
	//����һ��ͼƬ
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
	//���᳤
	int aHalf = rect->w / 2;
	int bHalf = rect->h / 2;

	int x, y;
	//���Բ��ÿ�������
	for (float angle = 0; angle < 360; angle += 0.1)
	{
		x = (rect->x + aHalf) + aHalf * SDL_cos(angle);
		y = (rect->y + bHalf) + bHalf * SDL_sin(angle);
		SDL_RenderDrawPoint(render, x, y);
	}
}