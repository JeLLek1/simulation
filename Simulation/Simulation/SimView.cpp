#include "pch.h"
#include "SimView.h"
#include "Simulation.h"
#include <iostream>

sf::Vector2f SimView::getCamPos()
{
	return camPos;
}

//Przy ka�dym od�wierzeniu metoda sprawdza czy pozycja myszy nie wskazuje na mo�liwo�� przesuni�cia mapy
void SimView::update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize, int map_width) {
	//temp przechowuje informacje na temat przesuni�cia
	sf::Vector2f temp;

	//Obliczanie pozycji do przesuni�cia w osi x
	if ((mousePos.x >= 0 && mousePos.x < SimView::PIXEL_TO_MOVE) || (mousePos.x > WindowSize.x - SimView::PIXEL_TO_MOVE && mousePos.x < WindowSize.x)) {
		if (mousePos.x < WindowSize.x / 2)
			temp.x = -(SimView::PIXEL_TO_MOVE - mousePos.x);
		else
			temp.x = SimView::PIXEL_TO_MOVE - WindowSize.x + mousePos.x;
	
	}
	else {
		temp.x = 0;
	}

	//Obliczanie pozycji do przesuni�cia w osi y
	if ((mousePos.y >= 0 && mousePos.y < SimView::PIXEL_TO_MOVE) || (mousePos.y > WindowSize.y - SimView::PIXEL_TO_MOVE && mousePos.y < WindowSize.y)){

		if (mousePos.y < WindowSize.y / 2)
			temp.y = -(SimView::PIXEL_TO_MOVE - mousePos.y);
		else
			temp.y = SimView::PIXEL_TO_MOVE - WindowSize.y + mousePos.y;
	}
	else {
		temp.y = 0;
	}

	//Je�eli za�o�enia co do przesuni�cia zgadzaj� si� z przekazanymi warto�ciami, przesuni�cie zostaje wykonane
	if (temp.x != 0 || temp.y != 0) {

		this->move(temp * (dt * SimView::SPEED));
		this->camPos = sf::Vector2f(Simulation::isoToCart(this->getCenter(), map_width));

	}
}

SimView::SimView()
{
	this->camPos = sf::Vector2f(50,50);
}


SimView::~SimView()
{
}
