#include "Iceberg.hpp"

int rendom(int n, int x) {
    //srand(time(NULL));
    int a = (rand() % n + x);
    return a;
}

Iceberg::Iceberg()
{
    //srand(time(NULL));
    ID = rendom(900000, 100000);
    xpos = (float)rendom(16, 0) * 50;
    ypos = (float)rendom(12, 0) * 50;
    Update();//nujno da se DestRect updata
}

//podan x in y
Iceberg::Iceberg(float x, float y)
{
    ID = rand() % 900000 + 100000;
    xpos = x;
    ypos = y;
}

//idk
Iceberg::Iceberg(const char* texturesheet)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    ID = rand() % 900000 + 100000;
    xpos = (float)(rand() % 16) * 50;
    ypos = (float)(rand() % 12) * 50;
}

Iceberg::~Iceberg()
{
    SDL_DestroyTexture(objTexture);
}

void Iceberg::Update()
{
    srcRect.h = 50;
    srcRect.w = 50;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.y = 0;

    destRect.x = (int)xpos;
    destRect.y = (int)ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
   }

void Iceberg::izpis()
{
    std::cout << "ID: " << ID << " x: " << xpos << " y: " << ypos << "\n";
}

void Iceberg::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    if (showHitboxes)
    {
        SDL_RenderDrawRect(Game::renderer, &destRect);
    }
}

//skopiran movment od unga Whalerja
void Iceberg::move(Map* map) {
    if (counter == 100) {
        counter = 0;
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
            tempRect = { destRect.x - 1, destRect.y, destRect.w, destRect.h };
            if (!map->LandCollision(tempRect)) {
                xpos -= 1;
            }
        }
        break;
    case Direction::Right:
        if (xpos + 1 < 800) {
            tempRect = { destRect.x + 1, destRect.y, destRect.w, destRect.h };
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
