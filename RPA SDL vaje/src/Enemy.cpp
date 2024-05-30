#include "Enemy.hpp"

void Enemy::Update()
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

//narise krog okol enemyja (idk da vids range v F3 nacinu)
void Enemy::drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void Enemy::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes)
    {
        //narise enemyjev reach
        drawCircle(Game::renderer, xpos + srcRect.w/2, ypos + srcRect.h/2, 100);

        //narise hitbox
        SDL_RenderDrawRect(Game::renderer, &destRect);
    }
}

void Enemy::moveTowardsPlayer(float PlayerPosX, float PlayerPosY, Map* map) {
    float dx = PlayerPosX - xpos;
    float dy = PlayerPosY - ypos;

    //zracuna kot
    float angle = atan2(dy, dx);

    //zracuna distanco
    float distance = sqrt(dx * dx + dy * dy);

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    //da ne trippa zard floatov in ne premika enemyja ce je predalec od playerja
    if (distance <= 1 || (distance > triggerDistance && distance > triggerDistance + 50)) { return; }
    

    float tempX = xpos + speed * dxNormalized;
    float tempY = ypos + speed * dyNormalized;

    SDL_Rect enemyDestRect = {
        (int)tempX,
        (int)tempY,
        srcRect.w,
        srcRect.h
    };

    //preveri da negre enemy izven okna
    if (tempX >= 0 && tempX + srcRect.w <= 800 && tempY >= 0 && tempY + srcRect.h <= 600) {
        //preveri land collision
        if (!map->LandCollision(enemyDestRect)) {
            xpos = tempX;
            ypos = tempY;
        }
    }
}

Enemy::Enemy(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

Enemy::Enemy() {
    ID = rand()%900000+100000;
    xpos = (float)(rand() % 16 * 50);
    ypos = (float)(rand() % 12 * 50);
}

void Enemy::takeDamage(int dmg) {
    if (!immortalMode) {
        hp -= dmg;
    }
}

bool Enemy::collision(SDL_Rect x)
{
    return SDL_HasIntersection(&destRect, &x);
}
