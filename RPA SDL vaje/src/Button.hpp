#pragma once

#include "Game.hpp"

class Button {
public:
    //default constructor
    Button(int x, int y, int width, int height);
    Button() {}

    //prevermo ce je mouse cez sdlrect
    bool isMouseOver(float mouseX, float mouseY);

    // Getter for the button's SDL_Rect
    SDL_Rect getRect() const { return destRect; }

    void Update();
    void Render();
private:
    bool showHitboxes = false;
    SDL_Rect destRect;
};