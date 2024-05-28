#include "Replay.hpp"
//#include "Map.hpp"

Replay::Replay() {
    //datao.open(filename, std::ios::binary);
    datai.open(filename, std::ios::binary);
}

Replay::~Replay()
{
    if (datai.is_open()) {
        datai.close();
    }
    if (datao.is_open()) {
        datao.close();
    }
}

Replay::Replay(const char* texturesheet, float x, float y)
{
    
}

//vpise koordinato za playerja zdj
void Replay::ReplaySave(SDL_Rect a)
{
    datao.open(filename, std::ios::binary|std::ios::ate);

    if (!datao.is_open()) { std::cout << "output file not open\n"; return; }

    datao.write((char*)&a, sizeof a);

    datao.close();
}

//vrne usak saved player spot kje si biu
SDL_Rect Replay::GetReplayPos()
{
    SDL_Rect pos{0,0,0,0};

    if (!datai.is_open()) { std::cout << "input file not open\n"; return pos; }
    datai.read((char*)&pos, sizeof(pos));

    return pos;
}



//tega najbrs nerabm
void Replay::StopReplay()
{

}