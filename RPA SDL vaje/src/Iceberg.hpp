#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Utils.hpp"
#include "Map.hpp"

class Iceberg:public GameObject {
private:
    int ID;

    SDL_Texture* objTexture = TextureManager::LoadTexture("assets/iceberg.png");
    SDL_Rect srcRect, destRect;

    static int counter;

    Direction currentDirection;
public:
    //random x,y
    Iceberg();
    //podan x,y
    Iceberg(float x, float y);
    //idk lol
    Iceberg(const char* texturesheet);
    ~Iceberg();    

    //returna svoj dest da prever collision
    SDL_Rect GetIcebergRect() {return destRect;}

    void moveIceberg(int& direction);

    void move(Map* map);

    void izpis();
    void Render();
    void Update();
    int ReturnID() { return ID; } //vrne ID
};