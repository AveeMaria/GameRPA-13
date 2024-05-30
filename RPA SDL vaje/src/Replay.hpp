#pragma once

#include "Game.hpp"
#include "Replay.hpp"
#include "Button.hpp"

class Replay
{
private:
	const char* filename = "replay.bin";
	bool replayOn = false;

	std::ofstream datao;
	std::ifstream datai;	
public:
	Replay();
	~Replay();

	//zacne recordat playermovment
	void ReplaySave(SDL_Rect);
	void ClearReplay();

	//neha recordat playermovement
	void ToggleReplay(bool ON) { replayOn = ON; }
	bool GetReplayOn() { return replayOn; }//sam za slucaj nvm ce rabm

	//vrne un rectangle k ga player uzame al neki?
	SDL_Rect GetReplayPos();
	int FileLen();
};






