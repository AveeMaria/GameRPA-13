#pragma once

#include "Game.hpp"
//#include "GameObject.hpp"
#include "Replay.hpp"
#include "Button.hpp"

class Replay
{
private:
	const char* filename = "replay.bin";
	bool replayOn = true;

	std::ofstream datao;
	std::ifstream datai;
	
	//SDL_Texture* TargetLocation = TextureManager::LoadTexture("/assets/x.png");
public:
	Replay(const char* texturesheet, float x, float y);
	Replay();
	~Replay();

	//zacne recordat playermovment
	void ReplaySave(SDL_Rect);

	//neha recordat playermovement
	void StopReplay();
	
	//vrne un rectangle k ga player uzame al neki?
	SDL_Rect GetReplayPos();

	//void Update();
	//void Render();
};






