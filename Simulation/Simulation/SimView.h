#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class SimView : public sf::View
{
private:
	//Ile pixeli od kra�c�w ekranu jest przeznaczonych na wykrywanie przesuni�cia
	const int PIXEL_TO_MOVE=50;

	//Pr�dko�� przesuni�cia
	const int SPEED = 20;
public:
	//pozycja kamery kartezja�ska
	sf::Vector2f camPos;
	//Metoda odpowiedzialna za przesuwanie widoku
	void update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize, int map_width);
	SimView();
	~SimView();
};

