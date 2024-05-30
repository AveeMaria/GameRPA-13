#include "Cursor.hpp"

Cursor::Cursor(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void Cursor::Render()
{
    if (visible)
    {
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    }
}

void Cursor::Update()
{
    srcRect.h = 20;
    srcRect.w = 20;
    srcRect.x = 0;
    srcRect.y = 0;    

    //idk nekak najleps zgleda ce je w/h 20
    destRect.x = (int)xpos + 12;
    destRect.y = (int)ypos + 12;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}





















