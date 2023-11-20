#include<SDL2/SDL.h>
#include<stdbool.h>

//按不同的键，使用不同的图片
enum SurfaceType
{
    SFC_Default,
    SFC_Up,
    SFC_Down,
    SFC_Left,
    SFC_Right,
    SFC_Total
};
//图片数组
SDL_Surface* gSurfaces[SFC_Total];

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

int main(int argc, char* argv[])
{
    //启动SDL并创建窗口
    if (!initSDL())
    {
        SDL_Log("Failed to initialize!\n");
        return -1;
    }

    //加载媒体
    if (!loadMedia())
    {
        SDL_Log("Failed to load media!\n");
    }

    //主循环标志
    bool quit = false;
    //当前图片指针
    SDL_Surface* curSurface = gSurfaces[SFC_Default];
    while (!quit)
    {
        static SDL_Event ev;
        //处理队列中的事件
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                quit = true;
            }
            //按键按下
            else if (ev.type == SDL_KEYDOWN)
            {
                switch (ev.key.keysym.sym)
                {
                case SDLK_UP:
                    curSurface = gSurfaces[SFC_Up];
                    break;
                case SDLK_DOWN:
                    curSurface = gSurfaces[SFC_Down];
                    break;
                case SDLK_LEFT:
                    curSurface = gSurfaces[SFC_Left];
                    break;
                case SDLK_RIGHT:
                    curSurface = gSurfaces[SFC_Right];
                    break;
                default:
                    curSurface = gSurfaces[SFC_Default];
                    break;
                }
            }
        }

        //在窗口上显示图片
        SDL_BlitSurface(curSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
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

SDL_Surface* loadSurface(const char* filename)
{
    SDL_Surface * surface = SDL_LoadBMP(filename);
    if (surface == NULL)
    {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
        return NULL;
    }
    return surface;
}

bool loadMedia()
{
    //加载图片
    gSurfaces[SFC_Default] = loadSurface("assets/images/default.bmp");
    if (gSurfaces[SFC_Default] == NULL)
    {
        return false;
    }

    gSurfaces[SFC_Up] = loadSurface("assets/images/up.bmp");
    if (gSurfaces[SFC_Up] == NULL)
    {
        return false;
    }

    gSurfaces[SFC_Down] = loadSurface("assets/images/down.bmp");
    if (gSurfaces[SFC_Down] == NULL)
    {
        return false;
    }

    gSurfaces[SFC_Left] = loadSurface("assets/images/left.bmp");
    if (gSurfaces[SFC_Left] == NULL)
    {
        return false;
    }

    gSurfaces[SFC_Right] = loadSurface("assets/images/right.bmp");
    if (gSurfaces[SFC_Right] == NULL)
    {
        return false;
    }
    return true;
}

void closeSDL()
{
    //释放表面内存
    for (int i = 0; i < SFC_Total; i++)
    {
        SDL_FreeSurface(gSurfaces[i]);
        gSurfaces[i] = NULL;
    }


    //销毁窗口
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //退出SDL子系统
    SDL_Quit();
}