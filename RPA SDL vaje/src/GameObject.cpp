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

void GameObject::setXY(float x,float y) {
    xpos = x; ypos = y;
}


