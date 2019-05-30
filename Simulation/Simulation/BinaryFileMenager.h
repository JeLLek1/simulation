#pragma once
#include <fstream>
#include <vector>
#include "Map.h"
#include "StaticObjectFireplace.h"
#include "StaticObjectResouces.h"

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
	int binary_p_read(std::vector<Tile*>& tiles, sf::Vector2u*& mapSize, sf::Vector2u*& warehousePos, sf::Vector2u*& fireplacePos);
	//Nadpisywanie pliku
	int binary_write(std::vector<Tile*>& tiles, sf::Vector2u* mapSize, sf::Vector2u* warehousePos, sf::Vector2u* fireplacePos);
	BinaryFileMenager(std::string name, int mode);
	~BinaryFileMenager();
};

