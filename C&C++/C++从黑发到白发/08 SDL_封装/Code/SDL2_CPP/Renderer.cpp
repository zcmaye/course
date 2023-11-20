#include "Renderer.h"
#include "Window.h"
Renderer::Renderer()
	:Renderer(nullptr)
{
}

Renderer::Renderer(SDL_Renderer* ren)
	:renderer(ren)
{
	
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::setRender(SDL_Renderer* ren)
{
	if (ren)
		renderer = ren;
}

SDL_Renderer* Renderer::render()
{
	return renderer;
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::present()
{
	SDL_RenderPresent(renderer);
}

void Renderer::drawPoint(int x, int y)
{
	SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer::drawPoint(SDL_Point* pos)
{
	drawPoint(pos->x, pos->y);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::drawLine(SDL_Point* p1, SDL_Point* p2)
{
	drawLine(p1->x, p1->y, p2->x, p2->y);
}

void Renderer::drawLines(SDL_Point* points, int count)
{
	SDL_RenderDrawLines(renderer, points, count);
}

void Renderer::drawRect(const SDL_Rect* rect)
{
	SDL_RenderDrawRect(renderer, rect);
}

void Renderer::drawRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x,y,w,h };
	drawRect(&rect);
}

void Renderer::drawFillRect(const SDL_Rect* rect)
{
	SDL_RenderFillRect(renderer, rect);
}

void Renderer::drawFillRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x,y,w,h };
	drawFillRect(&rect);
}

void Renderer::drawEllipse(SDL_Rect* rect)
{
	//半轴长
	int aHalf = rect->w / 2;
	int bHalf = rect->h / 2;

	int x, y;
	//求出圆上每个坐标点
	for (float radian = 0; radian < 2* M_PI; radian += 0.002f)
	{
		x = (rect->x + aHalf) + aHalf * SDL_cos(radian);
		y = (rect->y + bHalf) + bHalf * SDL_sin(radian);
		drawPoint(x, y);
	}
}

void Renderer::drawEllipse(int x,int y, int w, int h)
{
	SDL_Rect rect = { x,y,w,h };
	drawEllipse(&rect);
}

void Renderer::drawTriangle(SDL_Rect* rect)
{
	drawTriangle(rect->x, rect->y, rect->w, rect->h);
}

void Renderer::drawTriangle(int x, int y, int w, int h)
{
	SDL_Point points[] =
	{
		{x + w / 2,y},
		{x + w,y + h},
		{x,y + h},
		{x + w / 2,y}
	};
	drawLines(points, sizeof(points) / sizeof(points[0]));
}

void Renderer::drawPentagon(SDL_Rect* rect)
{
	drawPentagon(rect->x, rect->y, rect->w, rect->h);
}

void Renderer::drawPentagon(int x, int y, int w, int h)
{
	SDL_Point points[] =
	{
		{x + w / 2,y},					//最上面0
		{x + w,y + h / 8 * 3},			//2
		{x + w / 8 * 6.5,y + h},		//4
		{x + w / 8 * 1.5,y + h},		//6
		{x,y + h / 8 * 3},				//8
		{x + w / 2,y}
	};
	drawLines(points, sizeof(points) / sizeof(points[0]));
}

void Renderer::drawPentastar(SDL_Rect* rect)
{
	drawPentastar(rect->x, rect->y, rect->w, rect->h);
}

void Renderer::drawPentastar(int x, int y, int w, int h)
{
	SDL_Point points[] =
	{
		{x + w / 2,y},					//最上面0
		{x + w / 8 * 5,y + h / 8 * 3},	//1
		{x + w,y + h / 8 * 3},			//2
		{x + w / 8 * 5.7,y + h / 8 * 5},//3-
		{x + w / 8 * 6.5,y + h},			//4
		{x + w / 2,y + h / 8 * 6.3},	//5
		{x + w / 8 * 1.5,y + h},		//6
		{x + w / 8 * 2.3,y + h / 8 * 5},//7
		{x,y + h / 8 * 3},				//8
		{x + w / 8 * 3,y + h / 8 * 3},	//9
		{x + w / 2,y}
	};
	drawLines(points, sizeof(points) / sizeof(points[0]));
}


Renderer* Renderer::createRenderer(Window* window, int index, int flags)
{
	SDL_Renderer* ren = SDL_CreateRenderer(window->sdlWindow(), index, flags);
	if (ren)
	{
		SDL_Log("renderer created!\n");
	}
	return new Renderer(ren);
}
