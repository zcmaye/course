#include"Game.h"
#include<iostream>
class Shape
{
public:
	int x;
	int y;
public:
	Shape():Shape(0,0) {}
	Shape(int xPos,int yPos)
		:x(xPos),y(yPos)
	{}
	virtual void draw() = 0;
};
class Line :public Shape
{
public:
	int x2;
	int y2;
public:
	Line() {}
	Line(int x1, int y1, int x2, int y2)
		:Shape(x1, y1), x2(x2), y2(y2)
	{

	}
	void draw()override
	{
		SDL_RenderDrawLine(gGame.renderer, x, y, x2, y2);
	}
};
class Rect :public Shape
{
public:
	int w;
	int h;
public:
	Rect() {}
	Rect(int x,int y, int w, int h)
		:Shape(x, y),w(w),h(h)
	{

	}
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		SDL_RenderDrawRect(gGame.renderer, &rect);
	}
};
class Ellipse :public Rect
{
public:
	using Rect::Rect;
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		SDL_RenderDrawEllipse(gGame.renderer, &rect);
	}
};
class Triangle :public Rect
{
public:
	using Rect::Rect;
	void draw()override
	{
		SDL_Point points[] =
		{
			{x+ w/2,y},
			{x+w,y+h},
			{x,y+h},
			{x + w / 2,y}
		};
		SDL_RenderDrawLines(gGame.renderer, points, sizeof(points)/sizeof(points[0]));
	}
};
class Pentastar :public Rect
{
public:
	using Rect::Rect;
	void draw() override
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
		SDL_RenderDrawLines(gGame.renderer, points, sizeof(points) / sizeof(points[0]));
	}
};
class Pentagon :public Rect
{
public:
	using Rect::Rect;
	void draw() override
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
		SDL_RenderDrawLines(gGame.renderer, points, sizeof(points) / sizeof(points[0]));
	}
};

class Controller
{
	Shape** shapes{0};
	SDL_Point begPos{0};
	SDL_Point endPos{0};
	bool isPressed = false;
	SDL_Event *events = nullptr;
	enum ShapeType
	{
		ST_Line,
		ST_Rect,
		ST_Ellipse,
		ST_Triangle,
		ST_Pentastar,
		ST_Pentagon,
		Max_Shape
	};
	int shapeType = ST_Rect;
public:
	Controller()
	{
		static Shape* tshapes[] =
		{
			new Line(0,0,640,480),
			new Rect(0,0,50,50),
			new Ellipse(50,0,50,50),
			new Triangle(100,0,50,50),
			new Pentastar(150,0,50,50),
			new Pentagon(200,0,50,50)
		};
		shapes = tshapes;
	}
	void event(SDL_Event* ev)
	{
		events = ev;
		switch (ev->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			mousePressedEvent(&ev->button);
			break;
		case SDL_MOUSEBUTTONUP:
			mouseReleaseEvent(&ev->button);
			break;
		case SDL_MOUSEMOTION:
			mouseMoveEvent(&ev->motion);
			break;
		}
	}
	void draw()
	{
		//for (int i = 0; i < 6; i++)
		//{
		//	shapes[i]->draw();
		//}
		if (isPressed)
		{
			SDL_Rect rect = { begPos.x,begPos.y,endPos.x - begPos.x,endPos.y - begPos.y };
			switch (shapeType)
			{
			case Controller::ST_Line:
				SDL_RenderDrawLine(gGame.renderer, begPos.x, begPos.y, endPos.x, endPos.y);
				break;
			case Controller::ST_Rect:
				SDL_RenderDrawRect(gGame.renderer,&rect);
				break;
			case Controller::ST_Ellipse:
				SDL_RenderDrawEllipse(gGame.renderer, &rect);
				break;
			case Controller::ST_Triangle:
				break;
			case Controller::ST_Pentastar:
				break;
			case Controller::Max_Shape:
				break;
			default:
				break;
			}

		}
	}
protected:
	void mousePressedEvent(SDL_MouseButtonEvent* ev)
	{
		isPressed = true;
		begPos = endPos = { ev->x,ev->y };

		std::cout << __FUNCTION__ << std::endl;
	}
	void mouseReleaseEvent(SDL_MouseButtonEvent* ev)
	{
		isPressed = false;
		switch (shapeType)
		{
		case Controller::ST_Line:
			break;
		case Controller::ST_Rect:
			break;
		case Controller::ST_Ellipse:
			break;
		case Controller::ST_Triangle:
			break;
		case Controller::ST_Pentastar:
			break;
		case Controller::Max_Shape:
			break;
		default:
			break;
		}
		
		std::cout << __FUNCTION__ << std::endl;
	}
	void mouseMoveEvent(SDL_MouseMotionEvent* ev)
	{
		if (isPressed)
		{
			endPos = { ev->x,ev->y };
		}
		std::cout << __FUNCTION__ << std::endl;
	}
};
int main(int argc,char* argv[])
{
	Controller control;
	game_init("draw", 640, 480);
	while (game_running())
	{
		static SDL_Event ev = { 0 };
		if (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				gamer_Done();
			control.event(&ev);
		}

		SDL_SetRenderDrawColor(gGame.renderer, 255, 255, 255, 255);
		SDL_RenderClear(gGame.renderer);
		SDL_SetRenderDrawColor(gGame.renderer, 255, 0, 0, 255);

		control.draw();

		SDL_RenderPresent(gGame.renderer);
		SDL_Delay(10);
	}
	game_clean();
	return 0;
}