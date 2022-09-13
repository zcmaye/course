#ifndef _WINDOW_H_
#define _WINDOW_H_
#include<SDL.h>
#include<SDL_image.h>
#include"Renderer.h"
#include<string>
class Window
{
private:
	SDL_Window* window;
public:
	Window(SDL_Window* sdlWindow = nullptr);
	~Window();

	SDL_Window* sdlWindow()const;
public:
	static Window* createWindow(const std::string& title, int w, int y, int flags);
};


#endif // !_WINDOW_H_
