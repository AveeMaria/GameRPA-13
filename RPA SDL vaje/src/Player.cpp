#include "Player.hpp"
#include "Map.hpp"
#include "Replay.hpp"

Player::Player(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

//To NE bo delal >:(
//cel replay zaigra
void Player::ReplayMode(Replay* r,Map* m) {
    //k je konc replaya returna 0 0 0 0 rectangle
    int i = 0;
    int len = r->FileLen();

    while ((!(destRect.w == 0 || destRect.h == 0)) && (i < len)) {
        ++i;
        SDL_RenderClear(Game::renderer);//riskiy bisky stuff
        destRect = r->GetReplayPos();
        SDL_Delay(4);

        xpos = destRect.x;
        ypos = destRect.y;
        
        
        m->DrawMap();
        Render();
        Update();
        SDL_RenderPresent(Game::renderer);//to ceu screen updejta
    }

    destRect.w = 50;
    destRect.h = 50;
    r->ClearReplay();
}



void Player::increaseX(float x)
{
    if (xpos <= WINDOW_WIDTH) {
        if (xpos + x > WINDOW_WIDTH - srcRect.w)
            xpos = (float)WINDOW_WIDTH - srcRect.w;
        else if (xpos + x < 0)
            xpos = 0;
        else xpos += x;
    }
}

void Player::increaseY(float y)
{
    if (ypos <= WINDOW_HEIGHT) {
        if (ypos + y > WINDOW_HEIGHT - srcRect.h)
            ypos = (float) WINDOW_HEIGHT - srcRect.h;
        else if (ypos + y < 0)
            ypos = 0;
        else ypos += y;
    }
}

//narise krog okol Whalerja (idk da vids range v F3 nacinu)
void Player::drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int i = 0; i < 360; ++i) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//rdec circle
        double angle = i * M_PI / 180;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//reseta barvo
}

void Player::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes)
    {
        drawCircle(Game::renderer, xpos + srcRect.w / 2, ypos + srcRect.h / 2, RenderDST);
        SDL_RenderDrawRect(Game::renderer, &destRect);
    }
}

void Player::Update()
{
    srcRect.h = 50;
    srcRect.w = 50;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = (int)xpos;
    destRect.y = (int)ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void Player::moveLeft() 
{
    if(xpos - step < 0)
            xpos = 0;
    else xpos -= step;
}

void Player::moveRight()
{
    if (xpos <= WINDOW_WIDTH) {
        if (xpos + step > WINDOW_WIDTH - srcRect.w)
            xpos = (float)WINDOW_WIDTH - srcRect.w;
        else xpos += step;
    }
}

void Player::moveUp()
{ 
    if (ypos <= WINDOW_HEIGHT) {
        if (ypos - step < 0)
            ypos = 0;
        else ypos -= step;
    }
}

void Player::moveDown()
{
    if (ypos <= WINDOW_HEIGHT) {
        if (ypos + step > WINDOW_HEIGHT - srcRect.h)
            ypos = (float)WINDOW_HEIGHT - srcRect.h;
        else ypos += step;
    }
}

bool Player::collision(SDL_Rect x) 
{
    return SDL_HasIntersection(&destRect, &x);
}

void Player::takeDamage(int dmg) {
    if (!immortalMode) {
        hp -= dmg;
    }
}

void Player::moveTowardsCoords(float PlayerPosX, float PlayerPosY, Map* map) {
    float dx = PlayerPosX - xpos;
    float dy = PlayerPosY - ypos;

    //zracuna kot
    float angle = atan2(dy, dx);

    //zracuna distanco
    float distance = sqrt(dx * dx + dy * dy);

    //da ne trippa zarad floatov
    if (distance <= 1) { return; }
    //std::cout << "distance: "<< distance << "\n";

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    float tempX = xpos + speed * dxNormalized;
    float tempY = ypos + speed * dyNormalized;

    SDL_Rect playerDestRect = {
        (int)tempX,
        (int)tempY,
        srcRect.w,
        srcRect.h
    };

    //preveri da negremo izven okna
    if (tempX >= 0 && tempX + srcRect.w <= 800 && tempY >= 0 && tempY + srcRect.h <= 600) {
        //preveri land collision
        if (!map->LandCollision(playerDestRect)) {
            xpos = tempX;
            ypos = tempY;
        }
    }
}
