#include<SDL2/SDL.h>

//屏幕尺寸常量
const SCREEN_WIDTH = 640;
const SCREEN_HEIGHT = 480;

int main(int argc,char*argv[])
{
	//窗口指针
	SDL_Window* window = NULL;

	//窗口表面
	SDL_Surface* screenSurface = NULL;

	//初始化SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_Log("SDL cannot init! SDL_Error:%s", SDL_GetError());
	}
	else
	{
		//创建窗口
		window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			SDL_Log("Window cannot be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//获取窗口表面
			screenSurface = SDL_GetWindowSurface(window);

			//填充表面为白色
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,0xFF,0,0));
			
			//更新表面
			SDL_UpdateWindowSurface(window);

			//等待2秒
			SDL_Delay(2000);
		}
	}

	//销毁窗口
	SDL_DestroyWindow(window);

	//退出SDL子系统
	SDL_Quit();
	
	return 0;
}