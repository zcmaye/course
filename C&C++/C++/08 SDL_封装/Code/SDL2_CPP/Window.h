#ifndef _WINDOW_H_
#define _WINDOW_H_
#include<SDL.h>
#include<SDL_image.h>
#include"Renderer.h"
#include<string>
class Window
{
protected:
	SDL_Window* window;
	//SDL_Renderer* renderer;
public:
	static  Renderer*renderer;
	SDL_Event events;
	
public:
	Window(const std::string& title, int w, int h, int flags = SDL_WINDOW_SHOWN);
	~Window();
	int exec();
	virtual bool event(SDL_Event*ev);
protected:
	virtual void mousePressEvent(SDL_MouseButtonEvent* ev);
	virtual void mouseReleaseEvent(SDL_MouseButtonEvent* ev);
	virtual void mouseMoveEvent(SDL_MouseMotionEvent* ev);
	virtual void mouseWheelEvent(SDL_MouseWheelEvent* ev);
	virtual void keyPressEvent(SDL_KeyboardEvent* ev);
	virtual void keyReleaseEvent(SDL_KeyboardEvent* ev);
	virtual void paintEvent(SDL_Event* ev);
	virtual void updateEvent(SDL_Event* ev);
	
};


#endif // !_WINDOW_H_
