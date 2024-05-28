#include "Menu.hpp"
#include "Utils.hpp"

Menu::Menu(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}


void Menu::Render()
{
    if (visible)
    {
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);

        //idk narise se vse gumbe??? 
        SDL_RenderCopy(Game::renderer, buttonTextures[0], &srcRect, &buttons[0]);
        SDL_RenderCopy(Game::renderer, buttonTextures[1], &srcRect, &buttons[1]);
        SDL_RenderCopy(Game::renderer, buttonTextures[2], &srcRect, &buttons[2]);
    }
}

void Menu::Update()
{
    srcRect.h = 600;
    srcRect.w = 800;
    srcRect.x = 0;
    srcRect.y = 0;

    //destRect.x = (int)xpos + destRect.w / 2;
    //destRect.y = (int)ypos + destRect.h / 2;

    //idk nekak najleps zgleda ce je w/h 20
    destRect.x = 0;
    destRect.y = 0;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;






}

SDL_Rect Menu::GetNthRect(int n)
{
    return buttons[n];
}

//postavi Nti gumb na nek coord
void Menu::SetMenuButton(int n, float x, float y)
{
    buttons[n].x = x;
    buttons[n].y = y;
}

//preveri ce se miska nahaja v nekem rectanglu
bool Menu::isMouseInRect(SDL_Rect rect, float mouseX, float mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}


