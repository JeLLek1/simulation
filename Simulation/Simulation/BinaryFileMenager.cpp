#include "pch.h"
#include "BinaryFileMenager.h"

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
int BinaryFileMenager::binary_p_read(std::vector<Tile*>& titles, sf::Vector2u& mapSize)
{
	//Sprawdzanie czy tryb odczytu jest odpowiedni
	if (fmode == 2) {
		//Jeœli uda³o siê otworzyæ plik
		if (this->file.good())
		{
			//--Zczytywanie wielkoœci mapy--
			//WskaŸnik na zmienn¹ wielkoœci unsigned int
			char* temp = new char[sizeof(unsigned int)];
			//Zczytywanie z pliku odpowiedniej iloœci bajtów dla unsigned int
			this->file.read(temp, sizeof(Tile));
			mapSize.x = (unsigned int)(temp);
			this->file.read(temp, sizeof(Tile));
			mapSize.y = (unsigned int)(temp);
			delete temp;
			//--Koniec zczytywania wielkoœci mapy--

			//--Zczytywanie kolejnych kafelków mapy--
			//WskaŸnik na zmienn¹ wielkoœci klasy tile
			temp = new char[sizeof(Tile)];
			//Dopuki jest jakiœ element w pliku dodaj go do vektora przechowuj¹cego kafelki
			while (!this->file.eof()) {
				this->file.read(temp, sizeof(Tile));

				Tile* tile = (Tile*)(temp);
				titles.push_back(tile);
			}
			delete temp;
			//--Koniec zczytywania kolejnych kafelków mapy--

			//Sprawdzenie, czy wielkoœæ mapy siê zgadza
			if (titles.size() != mapSize.x * mapSize.y) {
				return 3;
			}
			return 0;
		}
		else {
			return 2;
		}
	}
	return 1;
}

int BinaryFileMenager::binary_write(std::vector<Tile*>& titles, sf::Vector2u& mapSize)
{
	//Sprawdzanie odpowiedniego trybu odczytu
	if (fmode == 1) {
		//Jeœli uda³o siê otworzyæ plik
		if (this->file.good()) {
			//zapisanie wielkoœci mapy
			this->file.write((char*)(&(mapSize.x)), sizeof(unsigned int));
			this->file.write((char*)(&(mapSize.y)), sizeof(unsigned int));
			//Zapisanie kolejnych kafelków mapy
			for (int i = 0; i < titles.size(); i++) {
				this->file.write((char*)(&(titles[i])), sizeof(Tile));
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
