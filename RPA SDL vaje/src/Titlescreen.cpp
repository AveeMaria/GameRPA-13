#include "Titlescreen.hpp"

Titlescreen::Titlescreen(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}


void Titlescreen::Render()
{
    if (visible)
    {
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    }
}

void Titlescreen::Update()
{
    srcRect.h = 600;
    srcRect.w = 800;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = 0;
    destRect.y = 0;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}



