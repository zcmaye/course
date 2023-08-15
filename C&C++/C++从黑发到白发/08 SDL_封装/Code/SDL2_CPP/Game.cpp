#include "Game.h"
#include "Renderer.h"
#include "Window.h"
#include "Controller.h"
Controller controller;
Renderer* Game::renderer;
SDL_Event Game::events;
Game::Game()
{

}

bool Game::init(const std::string& title, int w, int h, int flags)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
	{
		SDL_Log("game init!\n");
		//创建窗口
		window = Window::createWindow(title ,w, h, SDL_WINDOW_SHOWN);
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
		isRunning = true;
	}
	else
	{
		SDL_Log("SDL Init failed!\n");
		isRunning = false;
	}
	return isRunning;
}

void Game::clean()
{
	delete renderer;
	delete window;
	SDL_Quit();
}

void Game::update()
{
	//在这里添加你的数据更新代码
}

void Game::render()
{
	renderer->setDrawColor(255, 255, 255, 255);
	renderer->clear();
	//在这里添加你的渲染代码
	controller.draw();
	renderer->present();
}

void Game::handleEvents()
{
	if (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
		{
			isRunning = false;
		}
		controller.event(&events);
	}
}

bool Game::running()
{
	return isRunning;
}

void Game::setFPS(float fps)
{
	this->fps = fps;
}

void Game::frameBegin()
{
	frameStart = SDL_GetTicks();
}

void Game::frameEnd()
{
	frameTime = SDL_GetTicks() - frameStart;
	if (fps - frameTime > 0)
	{
		SDL_Delay(fps - frameTime);
	}
}
