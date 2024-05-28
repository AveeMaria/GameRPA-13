#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

class Atol : public GameObject {
private:
	int ID;
	int growth = 0;
	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/atol.png");

public:
	Atol(const char* texturesheet, float x, float y);
	Atol();

	bool collision(SDL_Rect);

	//proba zrastat 1% chance ma
	void TryToGrow() { if (rand() % 100 == 0) { ++growth; } }

	SDL_Rect GetAtolRect() { return destRect; }

	void Update();
	void Render();
};