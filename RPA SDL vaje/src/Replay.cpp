#include "Replay.hpp"

Replay::Replay() {
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

//vpise koordinato za playerja zdj
void Replay::ReplaySave(SDL_Rect a)
{
    datao.open(filename, std::ios::binary|std::ios::app);

    if (!datao.is_open()) { std::cout << "output file not open\n"; return; }

    datao.write((char*)&a, sizeof a);

    datao.close();
}

void Replay::ClearReplay() 
{
    datao.open(filename, std::ios::binary);

    if (!datao.is_open()) { std::cout << "failed to clear file\n"; return; }

    datao.close();
}

//vrne usak saved player spot kje si biu
SDL_Rect Replay::GetReplayPos() 
{
    SDL_Rect pos{ 0,0,0,0 };
    if (!datai.is_open()) { std::cout << "input file not open\n"; return SDL_Rect{ 0,0,-1,-1 }; }
    datai.read((char*)&pos, sizeof(pos));

    //faking end of file zkj to obstaja
    if (datai.eof()) {
        replayOn = false;
        return SDL_Rect{ 0, 0, 0, 0 }; //konc datoteke
    }
    
    return pos;
}

//vrne lenght fila
int Replay::FileLen() {
    int i = 0;
    SDL_Rect a{ 0,0,0,0 };
    std::ifstream datainput(filename, std::ios::binary);

    if (!datainput.is_open()) { std::cout << "input file not open\n"; return -1; }

    while (datainput.read((char*)&a, sizeof a)) {
        ++i;
    }
    
    datainput.close();
    return i;
}