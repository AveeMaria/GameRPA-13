#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Button.hpp"

class Deathscreen : public GameObject {
private:
	bool visible = false;

	//x,y,w,h
	Button* respawn = new Button(200, 305, 412, 40);
	Button* titlescreen = new Button(200, 355, 412, 40);

	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/deathscreen.png");
public:
	Deathscreen(const char* texturesheet, float x, float y);
	Deathscreen() {};

	void SetVisible(bool v) { visible = v; }
	bool GetVisible() { return visible; }
	//a to sploh rabim?
	SDL_Rect GetDeathscreenRect() { return destRect; }

	int CheckButtonClick(float, float);

	void Update();
	void Render();
};