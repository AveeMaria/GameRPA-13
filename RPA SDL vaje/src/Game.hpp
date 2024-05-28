#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool GetPaused() { return paused; }
	void render();
	void clean();

	void SpawnIcebergs();
	void SpawnGusarji();
	void SpawnAtoli();
	void SpawnKitolovci();

	void NextLevel();

	//bool GetHitboxes() { return showHitboxes; }
	//bool showHitboxes =false;
	
	static SDL_Renderer* renderer;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
private:
	char playername[20]="gapi";//idk ime igralca?
	//int score = 0;

	bool keyboardMovement = false;
	bool isRunning = false;
	bool paused = false;
	uint32_t cnt = 0;
	SDL_Window *window;
};