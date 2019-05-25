#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class SimView : public sf::View
{
private:
	//Ile pixeli od krañców ekranu jest przeznaczonych na wykrywanie przesuniêcia
	const int PIXEL_TO_MOVE=50;

	//Prêdkoœæ przesuniêcia
	const int SPEED = 20;

	//pozycja kamery kartezjañska
	sf::Vector2f camPos;

public:
	
	sf::Vector2f getCamPos();
	//Metoda odpowiedzialna za przesuwanie widoku
	void update(const float dt, sf::Vector2i mousePos, sf::Vector2i WindowSize, int map_width);
	SimView();
	~SimView();
};

