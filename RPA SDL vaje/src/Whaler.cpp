#include "Whaler.hpp"

void Whaler::Update()
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

//narise krog okol Whalerja (idk da vids range v F3 nacinu)
void Whaler::drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void Whaler::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes)
    {
        //narise Whalerjev reach
        drawCircle(Game::renderer, xpos + srcRect.w / 2, ypos + srcRect.h / 2, 100);

        //narise hitbox
        SDL_RenderDrawRect(Game::renderer, &destRect);
    }
}

//to je skopiran od PlayerMovementa
void Whaler::moveAwayFromPlayer(float PlayerPosX, float PlayerPosY, Map* map) {
    float dx = PlayerPosX - xpos;
    float dy = PlayerPosY - ypos;

    float angle = atan2(dy, dx);

    float distance = sqrt(dx * dx + dy * dy);

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    if (distance > 100.0 || distance <= 1 || (distance > triggerDistance && distance > triggerDistance + 50)) {
        return;
    }

    float tempX = xpos - speed * dxNormalized;
    float tempY = ypos - speed * dyNormalized;

    SDL_Rect WhalerDestRect = {
        (int)tempX,
        (int)tempY,
        srcRect.w,
        srcRect.h
    };

    if (tempX >= 0 && tempX + srcRect.w <= 800 && tempY >= 0 && tempY + srcRect.h <= 600) {
        if (!map->LandCollision(WhalerDestRect)) {
            xpos = tempX;
            ypos = tempY;
        }
    }
}

Whaler::Whaler(const char* texturesheet, float x, float y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

Whaler::Whaler() {
    ID = rand() % 900000 + 100000;
    xpos = (float)(rand() % 16 * 50);
    ypos = (float)(rand() % 12 * 50);
    Update();
}

void Whaler::takeDamage(int dmg) {
    if (!immortalMode) {
        hp -= dmg;
    }
}

bool Whaler::collision(SDL_Rect x)
{
    return SDL_HasIntersection(&destRect, &x);
}

void Whaler::izpis()
{
    std::cout << "ID: " << ID << " x: " << xpos << " y: " << ypos << "\n";
}

void Whaler::move(Map* map) {
    if (counter == 100) {
        counter = 0; //reseta kaunter
        currentDirection = static_cast<Direction>(std::rand() % 4);
    }

    switch (currentDirection) {
        SDL_Rect tempRect;
    case Direction::Up:
        if (ypos - 1 >= 0) {
            tempRect = { destRect.x, destRect.y - 1, destRect.w, destRect.h };
            if (!map->LandCollision(tempRect)) {
                ypos -= 1;
            }
        }
        break;
    case Direction::Down:
        if (ypos + 1 < 600) {
            tempRect = { destRect.x, destRect.y + 1, destRect.w, destRect.h };
            if (!map->LandCollision(tempRect)) {
                ypos += 1;
            }
        }
        break;
    case Direction::Left:
        if (xpos - 1 >= 0) {
            tempRect = { destRect.x - 1, destRect.y, destRect.w, destRect.h }; // Fixed
            if (!map->LandCollision(tempRect)) {
                xpos -= 1;
            }
        }
        break;
    case Direction::Right:
        if (xpos + 1 < 800) {
            tempRect = { destRect.x + 1, destRect.y, destRect.w, destRect.h }; // Fixed
            if (!map->LandCollision(tempRect)) {
                xpos += 1;
            }
        }
        break;
    default:
        std::cout << "Whaler cant move al neki\n";
        break;
    }
    ++counter;
}
