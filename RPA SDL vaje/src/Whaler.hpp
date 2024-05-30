#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Utils.hpp"

class Whaler : public GameObject {
private:
	int ID;
	int hp = 100;

	int triggerDistance = 100;
	float speed = 0.5f;

	bool facingright = true;
	
	Direction currentDirection;

	bool visible = true;

	static int counter;

	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/whaler.png");
	bool immortalMode = false;
public:
	Whaler(const char* texturesheet, float x, float y);
	Whaler();

	bool alive() { return hp > 0; }

	int getTriggerDistance() { return triggerDistance; }

	void takeDamage(int);

	bool collision(SDL_Rect);

	void move(Map*);

	//bezi stran
	void moveAwayFromPlayer(float, float, Map*);

	SDL_Rect GetWhalerRect() { return destRect; }

	void drawCircle(SDL_Renderer*, int, int, int);

	void Update();
	void Render();

	void izpis();
};