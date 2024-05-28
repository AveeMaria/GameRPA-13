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

    /*
    if (rand() % 2) {
        short a = 0;
        a=rand() % 3 - 1;
        if (xpos <= WINDOW_WIDTH) {
            if (xpos + 2*a > WINDOW_WIDTH - srcRect.w)
                xpos = (float) WINDOW_WIDTH - srcRect.w;
            else if (xpos + 2 *a < 0)
                xpos = 0;
            else xpos += 2 *a;
        }
    }
    if (rand() % 2) {
        short a = 0;
        a = rand() % 3 - 1;
        if (ypos <= WINDOW_HEIGHT) {
            if (ypos + 2 * a > WINDOW_HEIGHT - srcRect.h)
                ypos = (float) WINDOW_HEIGHT - srcRect.h;
            else if (ypos + 2 * a < 0)
                ypos = 0;
            else ypos += 2 * a;
        }
    }*/
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
/*
// to je treba fixnt
void Iceberg::moveIceberg(int& direction) {
    static int i = 0; 

    if (i >= 10) {
        direction = rand() % 4; // 0: up, 1: down, 2: left, 3: right
        i = 0; // Reset i to 0 after changing direction
    }

    switch (direction) {
    case 0:
        
        break;
    case 1:
        //enemyRect.y++;
        break;
    case 2:
        //enemyRect.x--;
        break;
    case 3:
        //enemyRect.x++;
        break;
    }

    i++; // Increment i by 1
}*/
void Iceberg::move(Map* map) {
    if (counter == 100) {
        counter = 0; // Reset the counter
        currentDirection = static_cast<Direction>(std::rand() % 4);
    }

    // Move according to the current direction
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
