#include "pch.h"
#include "BinaryFileMenager.h"
#include "Tile.h"

//�adowanie pliku
BinaryFileMenager::BinaryFileMenager(std::string name, int mode)
{
	//Tryb odczytu pliku
	switch (mode)
	{
	case 1:
		//Usuwa poprzedni� tre�� i otwiera plik do zapisu
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
		//Je�li uda�o si� otworzy� plik
		if (this->file.good())
		{
			this->file.seekg(0, this->file.end);
			int length = this->file.tellg();
			this->file.seekg(0, this->file.beg);
			//Je�eli plik jest wystarczaj�co du�y i ma odpowiedni� ilo�� bajt�w
			if (length > static_cast<int>(3*sizeof(sf::Vector2u)) && (length - static_cast<int>(3*sizeof(sf::Vector2u)))%static_cast<int>(sizeof(Tile)) == 0) {
				//--Zczytywanie wielko�ci mapy--
				//Wska�nik na zmienn� wielko�ci unsigned int
				char* temp = new char[sizeof(sf::Vector2u)];
				//Zczytywanie z pliku odpowiedniej ilo�ci bajt�w dla unsigned int
				this->file.read(temp, sizeof(sf::Vector2u));
				mapSize = (sf::Vector2u*)(temp);
				//--Koniec zczytywania wielko�ci mapy--
				//--Zczytywanie fireplace i warehouse--
				temp = new char[sizeof(sf::Vector2u)];
				this->file.read(temp, sizeof(sf::Vector2u));
				warehousePos = (sf::Vector2u*)(temp);

				temp = new char[sizeof(sf::Vector2u)];
				this->file.read(temp, sizeof(sf::Vector2u));
				fireplacePos = (sf::Vector2u*)(temp);

				//--Koniec zczytywania fireplace i warehouse

				//--Zczytywanie kolejnych kafelk�w mapy--
				//Dopuki jest jaki� element w pliku dodaj go do vektora przechowuj�cego kafelki
				while (length > this->file.tellg()) {
					temp = new char[sizeof(Tile)];
					//Wska�nik na zmienn� wielko�ci klasy tile
					this->file.read(temp, sizeof(Tile));

					Tile* tile = (Tile*)(temp);
					tiles.push_back(tile);
				}
				//--Koniec zczytywania kolejnych kafelk�w mapy--
				//Sprawdzenie, czy wielko�� mapy si� zgadza
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
		//Je�li uda�o si� otworzy� plik
		if (this->file.good()) {
			//zapisanie wielko�ci mapy
			this->file.write((char*)(&(*mapSize)), sizeof(sf::Vector2u));
			this->file.write((char*)(&(*warehousePos)), sizeof(sf::Vector2u));
			this->file.write((char*)(&(*fireplacePos)), sizeof(sf::Vector2u));
			//Zapisanie kolejnych kafelk�w mapy
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
