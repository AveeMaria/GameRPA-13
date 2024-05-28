#pragma once

#include "Game.hpp"
#include "Utils.hpp"

class Map {
private:
	SDL_Rect src, dest;
	
	const char* textureFilepaths[9] = {
		//za antarktiko
		"assets/antarctic_sand.png",
		"assets/antarctic_grass.png",
		"assets/antarctic_water.png"
		//za severno morje
		"assets/northern_sand.png",
		"assets/northern_grass.png",
		"assets/northern_water.png"
		//za juznokitajsko morje
		"assets/sand.png",
		"assets/grass.png",
		"assets/water.png"
	};

	int currLvl = 1;

	SDL_Texture* water;
	SDL_Texture* sand;
	SDL_Texture* grass;
	SDL_Texture* corrupted;

	int tilesize = 25;
	int m = 24; int n = 32;

	//int map[15][20] za tilesize = 40;
	//int map[24][32] za tilesize = 25;

public:
	Map();
	~Map();

	//void LevelReloadTextures(int n);

	//da zamenjamo lvl?
	void LoadMapLVLselect(int n);

	void LoadMap(int [24][32]);
	void DrawMap();

	//iskreno
	int MaxIcebergs(float);
	
	//vrne na kermu levlu smo zdle
	int GetcurrLvl() { return currLvl; }
	
	bool LandCollision(SDL_Rect, Direction);

	bool LandCollision(SDL_Rect);
	//vector superiority???
	int map[24][32];
};