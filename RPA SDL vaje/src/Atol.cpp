#include "Atol.hpp"

void Atol::Update()
{
    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = (int)xpos;
    destRect.y = (int)ypos;
    destRect.w = 50 + growth;
    destRect.h = 50 + growth;
}

void Atol::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes)
    {
        //narise hitbox
        SDL_RenderDrawRect(Game::renderer, &destRect);
    }
}

Atol::Atol(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

Atol::Atol() {
    ID = rand() % 900000 + 100000;
    xpos = (float)(rand() % 15 * 50);
    ypos = (float)(rand() % 11 * 50);
    Update();//importent
}

bool Atol::collision(SDL_Rect x)
{
    return SDL_HasIntersection(&destRect, &x);
}