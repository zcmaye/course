#include "Window.h"

Window::Window(SDL_Window* sdlWindow)
	:window(sdlWindow)
{
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}

SDL_Window* Window::sdlWindow() const
{
	return window;
}


Window* Window::createWindow(const std::string& title, int w, int h, int flags)
{
	//创建窗口
	auto sdlWindow = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	if (sdlWindow)
	{
		//SDL_Log("window created!\n");
		auto win = new Window(sdlWindow);
		return win;
	}
	return nullptr;
}
