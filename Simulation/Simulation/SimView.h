#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class SimView : public sf::View
{
private:
	//Ile pixeli od kra�c�w ekranu jest przeznaczonych na wykrywanie przesuni�cia
	const int pixelToMove=50;

	//Pr�dko�� przesuni�cia
	const int speed = 20;
public:

	//Metoda odpowiedzialna za przesuwanie widoku
	void update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize);
	SimView();
	~SimView();
};

