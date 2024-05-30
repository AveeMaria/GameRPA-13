#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

class Enemy: public GameObject{
private:
	//int step = 5;
	int ID;
	int hp = 100;

	int triggerDistance = 100;
	float speed = 0.5f;

	bool facingright = true;

	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/pirate.png");
	bool immortalMode = false;
	
public:
	Enemy(const char* texturesheet, float x, float y);
	Enemy();

	bool alive() { return hp > 0; }

	void takeDamage(int);

	bool collision(SDL_Rect);

	void moveTowardsPlayer(float, float, Map*);

	SDL_Rect GetEnemyRect() { return destRect; }

	void drawCircle(SDL_Renderer*, int, int, int);

	void Update();
	void Render();
};