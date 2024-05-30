#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Replay.hpp"

class Player:public GameObject
{
private:
	int hp = 100;
	int step = 2;
	int RenderDST = 250;

	int score = 0;

	float speed = 1.2f;
	
	bool immortalMode = false;

	bool sui = false;
	bool facingright = true;

	SDL_Texture* TargetLocation = TextureManager::LoadTexture("/assets/x.png");
public:
	Player(const char* texturesheet, float x, float y);
	Player() {}

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void ReplayMode(Replay*);

	void increaseX(float);
	void increaseY(float);

	void Update();
	void Render();

	void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);

	void SetHealth(int h) { hp = h; }

	//prever ce si crknu
	bool alive() {return hp > 0;}

	int GetPlayerStep() { return step; }

	int getRenderDistance() { return RenderDST; }

	//se ubije
	void KYS() { hp = 0; sui = true; }

	void Addscore(int s) { score += s; }
	int GetScore() { return score; }

	//da damage
	void takeDamage(int);

	void moveTowardsCoords(float, float, Map*);

	void ToggleImmortalMode() { immortalMode = !immortalMode; }

	bool getSui() { return sui; }

	//preveri collision
	bool collision(SDL_Rect);

	SDL_Rect GetPlayerRect() { return destRect; }
};
