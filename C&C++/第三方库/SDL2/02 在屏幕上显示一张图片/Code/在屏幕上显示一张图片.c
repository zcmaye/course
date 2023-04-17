#include<SDL2/SDL.h>
#include<stdbool.h>

//启动SDL并创建窗口
bool initSDL();

//加载媒体
bool loadMedia();

//释放媒体并关闭SDL
void closeSDL();

const SCREEN_WIDTH = 640;
const SCREEN_HEIGHT = 480;

//要渲染的窗口指针
SDL_Window* gWindow = NULL;

//窗口包含的表面
SDL_Surface* gScreenSurface = NULL;

//我们将载入并显示在屏幕上的图像
SDL_Surface* gHelloWorld = NULL;

int main(int argc, char* argv[])
{
    //启动SDL并创建窗口
    if (!initSDL())
    {
        SDL_Log("Failed to initialize!\n");
    }
    else
    {
        //加载媒体
        if (!loadMedia())
        {
            SDL_Log("Failed to load media!\n");
        }
        else
        {
            //在窗口上显示图片
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            //等待2秒
            SDL_Delay(2000);
        }
    }

    //释放资源和关闭SDL
    closeSDL();

    return 0;
}

bool initSDL()
{
    //初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        //创建窗口
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            //获取窗口表面
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return true;
}

bool loadMedia()
{
    //加载图片
    gHelloWorld = SDL_LoadBMP("assets/02/hello_world.bmp");
    if (gHelloWorld == NULL)
    {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", "assets/02/hello_world.bmp", SDL_GetError());
        return false;
    }

    return true;
}

void closeSDL()
{
    //释放表面内存
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //销毁窗口
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //退出SDL子系统
    SDL_Quit();
}