#pragma once

#include "Game.hpp"

void ReadLeaderboards(const char* filename);

int VrniVrstico(const char* filename, const char* iskanTXT);

void WriteSortedLeaderboards(const char* filename, std::string newString, int score);

