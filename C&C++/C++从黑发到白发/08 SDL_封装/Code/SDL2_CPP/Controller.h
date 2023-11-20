#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include"Game.h"
#include"Shapes.h"
class Controller
{
public:
	Controller();
	~Controller();
	void readData(const std::string& path);
	void draw();
	virtual bool event(SDL_Event* ev);
protected:
	void mousePressEvent(SDL_MouseButtonEvent* ev);
	void mouseReleaseEvent(SDL_MouseButtonEvent* ev);
	void mouseMoveEvent(SDL_MouseMotionEvent* ev);
	void mouseWheelEvent(SDL_MouseWheelEvent* ev);

public:
	std::vector<Shape*> shapes;
	SDL_Point begPos{ 0 };
	SDL_Point endPos{ 0 };
	bool isPressed = false;
	int shapeType = ST_Graffiti;
	Graffiti graf;
};
#endif // !_CONTROLLER_H
