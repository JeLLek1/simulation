#pragma once
#include <fstream>
#include <vector>
#include "Map.h"

class BinaryFileMenager
{
private:
	//Przechowywanie pliku
	std::fstream file;
	//Tryb odczytu
	int fmode;
	//Nazwa pliku
	std::string fname;
public:
	//Odczytywanie pliku
	int binary_p_read(std::vector<Tile*>& titles, sf::Vector2u& mapSize);
	//Nadpisywanie pliku
	int binary_write(std::vector<Tile*>& titles, sf::Vector2u& mapSize);
	BinaryFileMenager(std::string name, int mode);
	~BinaryFileMenager();
};

