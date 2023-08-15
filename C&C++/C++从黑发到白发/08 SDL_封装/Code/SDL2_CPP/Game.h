#ifndef _GAME_H_
#define _GAME_H_
#include<SDL.h>
#include<SDL_image.h>
#include<string>
class Renderer;
class Window;
class Game
{
public:
	Game();
	bool init(const std::string& title, int w, int h, int flags);
	void clean();
	void update();
	void render();
	void handleEvents();
	bool running();
public:	//frame
	int fps = 1000 / 60;
	Uint32 frameStart = 0;
	int frameTime = 0;
	void setFPS(float fps);
	void frameBegin();
	void frameEnd();

	float currentFps = 0.f;
	int prevTime = 0;
public:
	static Renderer* renderer;
	static SDL_Event events;
private:
	Window* window;

	bool isRunning = false;
};

#endif // !_GAME_H_
