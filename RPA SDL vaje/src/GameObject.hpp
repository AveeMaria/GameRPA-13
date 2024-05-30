#pragma once
#pragma once

#include "Game.hpp"
#include "TextureManager.hpp"
//#include "constants.hpp"

class GameObject 
{
protected:
	float xpos=0;
	float ypos=0;

	//int step = 50;

	int SCREENWIDTH = 800;
	int SCREENHEIGHT = 600;

	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;

	SDL_Texture* objTexture;

	//TODO: idk poprav to
	//SDL_Rect targetRect, targetDestRect;

	SDL_Rect srcRect, destRect;
	
public:
	static bool showHitboxes;
	GameObject(const char* texturesheet,float x,float y);
	GameObject() {}
	~GameObject();

	float distance(float, float);

	float getX() { return xpos; }
	float getY() { return ypos; }

	virtual void setXY(float,float);

	virtual void Update() = 0;
	virtual void Render() = 0;
};




