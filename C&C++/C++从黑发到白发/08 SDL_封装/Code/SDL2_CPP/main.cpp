#include"Game.h"
int main(int argc, char* argv[])
{

	Game game;
	game.init("SDL2_Game", 640, 480, SDL_WINDOW_SHOWN);
	game.setFPS(1000/60.f);
	while (game.running())
	{
		game.frameBegin();

		game.handleEvents();
		game.update();
		game.render();
	
		game.frameEnd();
	}
	game.clean();
	return 0;
}

