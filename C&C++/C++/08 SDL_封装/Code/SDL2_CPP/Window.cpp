#include "Window.h"
Renderer* Window::renderer;
Window::Window(const std::string& title, int w, int h, int flags)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
	{
		SDL_Log("game init!\n");
		//创建窗口
		window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (window)
		{
			SDL_Log("window created!\n");
		}

		//创建渲染器
		renderer = Renderer::createRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_Log("renderer created!\n");
		}
	}
	else
	{
		SDL_Log("SDL Init failed!\n");
		exit(0);
	}
}

Window::~Window()
{
	delete renderer;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Window::exec()
{
	bool isDone = false;
	while (!isDone)
	{
		if (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
				isDone = true;
			this->event(&events);
		}
		this->updateEvent(&events);
		renderer->setDrawColor(255, 255, 255, 255);
		renderer->clear();
		this->paintEvent(&events);
		renderer->present();
	}
	return !isDone;
}

bool Window::event(SDL_Event* ev)
{
	switch (ev->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		mousePressEvent(&ev->button);
		break;
	case SDL_MOUSEBUTTONUP:
		mouseReleaseEvent(&ev->button);
		break;
	case SDL_MOUSEMOTION:
		mouseMoveEvent(&ev->motion);
		break;
	case SDL_MOUSEWHEEL:
		mouseWheelEvent(&ev->wheel);
		break;
	case SDL_KEYDOWN:
		keyPressEvent(&ev->key);
		break;
	case SDL_KEYUP:
		keyReleaseEvent(&ev->key);
		break;
	}
	return false;
}

void Window::mousePressEvent(SDL_MouseButtonEvent* ev)
{
}

void Window::mouseReleaseEvent(SDL_MouseButtonEvent* ev)
{
}

void Window::mouseMoveEvent(SDL_MouseMotionEvent* ev)
{
}

void Window::mouseWheelEvent(SDL_MouseWheelEvent* ev)
{

}

void Window::keyPressEvent(SDL_KeyboardEvent* ev)
{
}

void Window::keyReleaseEvent(SDL_KeyboardEvent* ev)
{
}

void Window::paintEvent(SDL_Event* ev)
{
	
}

void Window::updateEvent(SDL_Event* ev)
{

}
