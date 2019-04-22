#include "pch.h"
#include "SimView.h"
#include <iostream>

//Przy ka¿dym odœwierzeniu metoda sprawdza czy pozycja myszy nie wskazuje na mo¿liwoœæ przesuniêcia mapy
void SimView::update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize) {
	//temp przechowuje informacje na temat przesuniêcia
	sf::Vector2f temp;

	//Obliczanie pozycji do przesuniêcia w osi x
	if ((mousePos.x > 0 && mousePos.x < this->pixelToMove) || (mousePos.x > WindowSize.x - this->pixelToMove && mousePos.x < WindowSize.x)) {
		if (mousePos.x < WindowSize.x / 2)
			temp.x = -(this->pixelToMove - mousePos.x);
		else
			temp.x = this->pixelToMove - WindowSize.x + mousePos.x;
	
	}
	else {
		temp.x = 0;
	}

	//Obliczanie pozycji do przesuniêcia w osi y
	if ((mousePos.y > 0 && mousePos.y < this->pixelToMove) || (mousePos.y > WindowSize.y - this->pixelToMove && mousePos.y < WindowSize.y)){

		if (mousePos.y < WindowSize.y / 2)
			temp.y = -(this->pixelToMove - mousePos.y);
		else
			temp.y = this->pixelToMove - WindowSize.y + mousePos.y;
	}
	else {
		temp.y = 0;
	}

	//Je¿eli za³o¿enia co do przesuniêcia zgadzaj¹ siê z przekazanymi wartoœciami, przesuniêcie zostaje wykonane
	if (temp.x != 0 || temp.y != 0) {

		this->move(temp * (dt * this->speed));
	}
}

SimView::SimView()
{
}


SimView::~SimView()
{
}
