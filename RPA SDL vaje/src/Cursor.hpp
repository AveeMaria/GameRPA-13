#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

class Cursor : public GameObject {
private:
	bool visible = true;

	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/x.png");
public:
	Cursor(const char* texturesheet, float x, float y);
	Cursor() {};

	//a to sploh rabim?
	SDL_Rect GetCursorRect() { return destRect; }

	void Update();
	void Render();
};