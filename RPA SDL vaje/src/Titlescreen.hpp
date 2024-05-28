#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

class Titlescreen : public GameObject {
private:
	bool visible = true;

	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/titlescreen.png");
public:
	Titlescreen(const char* texturesheet, float x, float y);
	Titlescreen() {};

	void SetVisible(bool v) { visible = v; }
	bool GetVisible() { return visible; }
	//a to sploh rabim?
	SDL_Rect GetTitlescreenRect() { return destRect; }

	void Update();
	void Render();
};