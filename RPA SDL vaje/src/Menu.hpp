#pragma once

#include "Game.hpp"
#include "TextureManager.hpp"
//#include "GameObject.hpp"

class Menu{
private:
	//main rectangla za narsat ta menu
	SDL_Rect srcRect, destRect;

	bool visible = true;

	float xpos = 0, ypos = 0;

	//mamo tri gumbe al neki
	SDL_Rect buttons[3];

	//a je to legal??
	SDL_Texture* buttonTextures[3] = {
		//ne pozabt texturjeu
		TextureManager::LoadTexture("assets/button_1.png"),
		TextureManager::LoadTexture("assets/button_2.png"),
		TextureManager::LoadTexture("assets/button_3.png")
	};

	//ne pozabt textura bruh
	SDL_Texture* objTexture = TextureManager::LoadTexture("assets/Menu.png");
public:
	Menu(const char* texturesheet, float x, float y);
	Menu() {};

	void SetVisible(bool v) { visible = v; }
	bool GetVisible() { return visible; }
	
	//vrne celo okno kjer je menu narisan
	SDL_Rect GetMenuRect() { return destRect; }

	SDL_Rect GetNthRect(int);

	void SetMenuButton(int n,float x,float y);
	bool isMouseInRect(SDL_Rect rect, float mouseX, float mouseY);


	void Update();
	void Render();
};

