#pragma once

#include "Game.hpp"

struct Zapis {
	char name[16];
	int score;
	Zapis() {}
	Zapis(const char* pn, int s) { strcpy_s(name, pn); score = s; }
};

class Leaderboards {
private:
	const char* filename = "leaderboards.bin";
public:
	Leaderboards() { filename = "leaderboards.bin"; }

	//void VpisIgralec(Igralec& a);
	//Igralec MakeIgralec(const char* pname, int pscore);

	void IzpisDatoteke();

	void SortiranVpis(Zapis a);

	void DeleteRecords();//spuca file
};