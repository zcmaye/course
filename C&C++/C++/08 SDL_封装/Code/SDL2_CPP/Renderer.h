#ifndef _RENDER_H_
#define _RENDER_H_
#include<SDL.h>
class Renderer
{
private:
	SDL_Renderer* renderer;
public:
	Renderer() ;
	Renderer(SDL_Renderer* ren);
	~Renderer();

	void setRender(SDL_Renderer* ren);
	SDL_Renderer* render();

	void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void clear();
	void present();
public:	//shape
	void drawPoint(int x,int y);
	void drawPoint(SDL_Point* pos);

	void drawLine(int x1,int y1,int x2,int y2);
	void drawLine(SDL_Point* p1,SDL_Point* p2);

	void drawLines(SDL_Point* points,int count);

	void drawRect(const SDL_Rect* rect);
	void drawRect(int x,int y,int w,int h);

	void drawFillRect(const SDL_Rect* rect);
	void drawFillRect(int x, int y, int w, int h);

	void drawEllipse(SDL_Rect* rect);
	void drawEllipse(int x, int y, int w, int h);

	void drawTriangle(SDL_Rect* rect);
	void drawTriangle(int x, int y, int w, int h);

	void drawPentagon(SDL_Rect* rect);
	void drawPentagon(int x, int y, int w, int h);

	void drawPentastar(SDL_Rect* rect);
	void drawPentastar(int x, int y, int w, int h);

public: //static
	static Renderer* createRenderer(SDL_Window* window, int index, int flags);
};

#endif // !_RENDER_H_

