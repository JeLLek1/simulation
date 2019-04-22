#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class SimView : public sf::View
{
private:
	//Ile pixeli od krañców ekranu jest przeznaczonych na wykrywanie przesuniêcia
	const int pixelToMove=50;

	//Prêdkoœæ przesuniêcia
	const int speed = 20;
public:

	//Metoda odpowiedzialna za przesuwanie widoku
	void update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize);
	SimView();
	~SimView();
};

