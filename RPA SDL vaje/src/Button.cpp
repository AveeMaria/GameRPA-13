#include "Button.hpp"

bool Button::isMouseOver(float mouseX, float mouseY) {
    return mouseX >= destRect.x && mouseX <= (destRect.x + destRect.w) && mouseY >= destRect.y && mouseY <= (destRect.y + destRect.h);
}

Button::Button(int x, int y, int width, int height) {
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
}

void Button::Render()
{
    if (showHitboxes) {SDL_RenderDrawRect(Game::renderer, &destRect);}    
}

void Button::Update()
{
    //nc se ne zgodi kr je fiksn button
}

