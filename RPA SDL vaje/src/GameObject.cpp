#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "constants.hpp"

GameObject::GameObject(const char* texturesheet, float x, float y) 
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

//does nothing
GameObject::~GameObject() 
{
    SDL_DestroyTexture(objTexture);
}
float GameObject::distance(float X, float Y)
{
    float dx = X - xpos;
    float dy = Y - ypos;
    
    return sqrt(dx * dx + dy * dy);
    
}
/*
void GameObject::Update() 
{
    srcRect.h = 50;
    srcRect.w = 50;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = (int)xpos;
    destRect.y = (int)ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}*/

/*
void GameObject::Render() 
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes) 
    {
        SDL_RenderDrawRect(Game::renderer,&destRect);
    }    
}*/

/*
void GameObject::increaseX(float x)
{
    if (xpos <= WINDOW_WIDTH) {
        if (xpos + x > WINDOW_WIDTH - srcRect.w)
            xpos = (float) WINDOW_WIDTH - srcRect.w;
        else if (xpos + x < 0)
            xpos = 0;
        else xpos += x;
    }
}*/

/*
void GameObject::increaseY(float y) 
{
    if (ypos <= WINDOW_HEIGHT) {
        if (ypos + y > WINDOW_HEIGHT - srcRect.h)
            ypos = (float) WINDOW_HEIGHT - srcRect.h;
        else if (ypos + y < 0)
            ypos = 0;
        else ypos += y;
    }
}*/

void GameObject::setXY(float x,float y) {
    xpos = x; ypos = y;
}


