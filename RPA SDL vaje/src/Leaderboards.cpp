#include "Game.hpp"
#include "Leaderboards.hpp"
#include "Utils.hpp"

void Leaderboards::IzpisDatoteke() {
    std::ifstream datai(filename, std::ios::binary);
    if (datai.is_open()) {
        std::cout << "LEADERBOARDS:\n";
        Zapis x;
        //izpisemo vse iz fila
        while (datai.read((char*)&x, sizeof(x))) {
            std::cout << "player:" <<x.name << "\nscore:" << x.score << "\n";
        }
        datai.close();
    }
    else {
        std::cout << "file not open\n";
    }
}
/*
Zapis Leaderboard::MakeZapis(const char* pname,int pscore) {
    return Zapis(pname,pscore);
}*/

void Leaderboards::SortiranVpis(Zapis a) {
    std::ifstream datai(filename, std::ios::binary);
    std::ofstream datao("tmp.bin", std::ios::binary);

    //to je ce se ni fila zato da ga ustvari da ne joka
    if (datai.is_open() == false) {
        std::ofstream nardimofile(filename, std::ios::binary);
        datai.open(filename, std::ios::binary);
        nardimofile.close();
    }

    //prever da ni prazna in da je ze vpisu novga Zapisa
    bool neki = false;
    Zapis b;//tega preberemo

    if ((datai.is_open()) && (datao.is_open())) {
        //prebere celo dat
        while (datai.read((char*)&b, sizeof(b))) {
            //ce je vecji ga zapisemo prej
            if (a.score > b.score && neki == false) {
                datao.write((char*)&a, sizeof(a));
                neki = true;
            }
            //v vsakem primeru prepisemo b v tmp.bin
            datao.write((char*)&b, sizeof(b));
        }
        //ce je prazna dat se while ne izvede in zapise na prvo mesto
        if (neki == false) {
            datao.write((char*)&a, sizeof(a));
        }
        datai.close();
        datao.close();
    }

    //deletamo staro dat, preimenujemo tmp v ime stare datoteke
    remove(filename);
    rename("tmp.bin", filename);
}

void Leaderboards::DeleteRecords()
{
    //std::ofstream datao("leaderboards.bin", std::ios::binary);
    std::ofstream datao(filename, std::ios::binary);
    if (!datao.is_open()) { std::cout << "failed to clear file\n"; return; }
    datao.close();
}
