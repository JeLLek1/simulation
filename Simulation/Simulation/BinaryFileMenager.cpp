#include "pch.h"
#include "BinaryFileMenager.h"
#include "Tile.h"

//£adowanie pliku
BinaryFileMenager::BinaryFileMenager(std::string name, int mode)
{
	//Tryb odczytu pliku
	switch (mode)
	{
	case 1:
		//Usuwa poprzedni¹ treœæ i otwiera plik do zapisu
		this->file.open(name, std::ios::out | std::ios::trunc | std::ios::binary); //zapisywanie
		break;
	case 2:
		//Otwiera plik tylko do odczytu
		this->file.open(name, std::ios::in | std::ios::binary); //czytanie
		break;
	}
	this->fmode = mode;
	this->fname = name;
}

//Czytanie pliku binarnego
int BinaryFileMenager::binary_p_read(std::vector<Tile*>& tiles, sf::Vector2u*& mapSize, sf::Vector2u*& warehousePos, sf::Vector2u*& fireplacePos)
{
	//Sprawdzanie czy tryb odczytu jest odpowiedni
	if (fmode == 2) {
		//Jeœli uda³o siê otworzyæ plik
		if (this->file.good())
		{
			this->file.seekg(0, this->file.end);
			int length = this->file.tellg();
			this->file.seekg(0, this->file.beg);
			//Je¿eli plik jest wystarczaj¹co du¿y i ma odpowiedni¹ iloœæ bajtów
			if (length > static_cast<int>(3*sizeof(sf::Vector2u)) && (length - static_cast<int>(3*sizeof(sf::Vector2u)))%static_cast<int>(sizeof(Tile)) == 0) {
				//--Zczytywanie wielkoœci mapy--
				//WskaŸnik na zmienn¹ wielkoœci unsigned int
				char* temp = new char[sizeof(sf::Vector2u)];
				//Zczytywanie z pliku odpowiedniej iloœci bajtów dla unsigned int
				this->file.read(temp, sizeof(sf::Vector2u));
				mapSize = (sf::Vector2u*)(temp);
				//--Koniec zczytywania wielkoœci mapy--
				//--Zczytywanie fireplace i warehouse--
				temp = new char[sizeof(sf::Vector2u)];
				this->file.read(temp, sizeof(sf::Vector2u));
				warehousePos = (sf::Vector2u*)(temp);

				temp = new char[sizeof(sf::Vector2u)];
				this->file.read(temp, sizeof(sf::Vector2u));
				fireplacePos = (sf::Vector2u*)(temp);

				//--Koniec zczytywania fireplace i warehouse

				//--Zczytywanie kolejnych kafelków mapy--
				//Dopuki jest jakiœ element w pliku dodaj go do vektora przechowuj¹cego kafelki
				while (length > this->file.tellg()) {
					temp = new char[sizeof(Tile)];
					//WskaŸnik na zmienn¹ wielkoœci klasy tile
					this->file.read(temp, sizeof(Tile));

					Tile* tile = (Tile*)(temp);
					tiles.push_back(tile);
				}
				//--Koniec zczytywania kolejnych kafelków mapy--
				//Sprawdzenie, czy wielkoœæ mapy siê zgadza
				if (static_cast<unsigned int>(tiles.size()) != mapSize->x * mapSize->y) {
					return 3;
				}
				return 0;
			}
			return 4;
		}
		else {
			return 2;
		}
	}
	return 1;
}

int BinaryFileMenager::binary_write(std::vector<Tile*>& tiles, sf::Vector2u* mapSize, sf::Vector2u* warehousePos, sf::Vector2u* fireplacePos)
{
	//Sprawdzanie odpowiedniego trybu odczytu
	if (fmode == 1) {
		//Jeœli uda³o siê otworzyæ plik
		if (this->file.good()) {
			//zapisanie wielkoœci mapy
			this->file.write((char*)(&(*mapSize)), sizeof(sf::Vector2u));
			this->file.write((char*)(&(*warehousePos)), sizeof(sf::Vector2u));
			this->file.write((char*)(&(*fireplacePos)), sizeof(sf::Vector2u));
			//Zapisanie kolejnych kafelków mapy
			for (int i = 0; i < tiles.size(); i++) {
				this->file.write((char*)(&(*tiles[i])), sizeof(Tile));

			}
			return 0;
		}
		else {
			return 2;
		}
	}
	return 1;
}

BinaryFileMenager::~BinaryFileMenager()
{
	//zamykanie pliku
	this->file.close();
}
