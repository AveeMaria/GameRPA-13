#include "Deathscreen.hpp"

Deathscreen::Deathscreen(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    if (objTexture == NULL) {std::cout << "null texture\n";}
    xpos = x;
    ypos = y;
}

void Deathscreen::Render()
{
    if (visible)
    {
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
        respawn->Render();
        titlescreen->Render();
    }
}

//vrne stevilko ker button je kliknjen
int Deathscreen::CheckButtonClick(float x, float y)
{
    if (respawn->isMouseOver(x, y)) { return 1; }
    if (titlescreen->isMouseOver(x, y)) { return 2; }

    return -1;
}

void Deathscreen::Update()
{
    srcRect.h = 600;
    srcRect.w = 800;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = 0;
    destRect.y = 0;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;


    respawn->Update();
    titlescreen->Update();
}



