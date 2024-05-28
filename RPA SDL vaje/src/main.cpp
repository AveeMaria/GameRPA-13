#include "Game.hpp"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	srand(time(nullptr));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Sea Shepherd", 800, 600, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		//da stoppa game, sam sezmer preverja ce odpavziramo
		game->handleEvents();
		if (!game->GetPaused()) {
			game->update();
			game->render();
		}	

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
} 