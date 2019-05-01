#include "pch.h"
#include "BinaryFileMenager.h"

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
int BinaryFileMenager::binary_p_read(std::vector<Tile*>& titles, sf::Vector2u& mapSize)
{
	//Sprawdzanie czy tryb odczytu jest odpowiedni
	if (fmode == 2) {
		//Je�li uda�o si� otworzy� plik
		if (this->file.good())
		{
			//--Zczytywanie wielko�ci mapy--
			//Wska�nik na zmienn� wielko�ci unsigned int
			char* temp = new char[sizeof(unsigned int)];
			//Zczytywanie z pliku odpowiedniej ilo�ci bajt�w dla unsigned int
			this->file.read(temp, sizeof(Tile));
			mapSize.x = (unsigned int)(temp);
			this->file.read(temp, sizeof(Tile));
			mapSize.y = (unsigned int)(temp);
			delete temp;
			//--Koniec zczytywania wielko�ci mapy--

			//--Zczytywanie kolejnych kafelk�w mapy--
			//Wska�nik na zmienn� wielko�ci klasy tile
			temp = new char[sizeof(Tile)];
			//Dopuki jest jaki� element w pliku dodaj go do vektora przechowuj�cego kafelki
			while (!this->file.eof()) {
				this->file.read(temp, sizeof(Tile));

				Tile* tile = (Tile*)(temp);
				titles.push_back(tile);
			}
			delete temp;
			//--Koniec zczytywania kolejnych kafelk�w mapy--

			//Sprawdzenie, czy wielko�� mapy si� zgadza
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
		//Je�li uda�o si� otworzy� plik
		if (this->file.good()) {
			//zapisanie wielko�ci mapy
			this->file.write((char*)(&(mapSize.x)), sizeof(unsigned int));
			this->file.write((char*)(&(mapSize.y)), sizeof(unsigned int));
			//Zapisanie kolejnych kafelk�w mapy
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
