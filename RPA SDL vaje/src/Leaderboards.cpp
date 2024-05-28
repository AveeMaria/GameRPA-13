#pragma once

#include "Game.hpp"

void ReadLeaderboards(const char* filename) {
	std::ifstream datai(filename);

	if (!datai.is_open()) {
		std::ofstream datao(filename);
		std::ifstream datai(filename);
	}

	if (datai.is_open()) {
		{
			std::string s;
			while (std::getline(datai, s)) {
				std::cout << s << "\n";
			}
		}
		datai.close();
	}
	else {
		std::cout << "file not open\n";
	}
}

int VrniVrstico(const char* filename, const char* iskanTXT) {
	std::ifstream datai(filename, std::ios::app);
	if (datai.is_open()) {
		int st_vrstice = 0;
		{
			std::string s;
			while (getline(datai, s)) {
				++st_vrstice;
				if (s == iskanTXT) {
					break;
				}
			}
		}
		return st_vrstice;
		datai.close();
	}
	else {
		std::cout << "file not open\n";
	}
	return 0;
}

void WriteSortedLeaderboards(const char* filename, std::string newString, int score) {
	std::ifstream currFile(filename, std::ios::app);
	std::ofstream tmpFile("tmp.txt");

	if (currFile.is_open() && tmpFile.is_open()) {
		std::string line;
		bool inserted = false;

		while (getline(currFile, line)) {
			//najde presledek da loh preberestevilo
			if (!inserted && score > std::stoi(line.substr(0, line.find(" ")))) {
				tmpFile << score << " " << newString << "\n";
				inserted = true;
			}

			tmpFile << line << "\n";
		}

		if (!inserted) {
			tmpFile << score << " " << newString << "\n";
		}

		currFile.close();
		tmpFile.close();

		remove(filename);
		rename("tmp.txt", filename);
	}
	else {
		std::cout << "File not open\n";
	}
}
