#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <SFML/Graphics/Text.hpp>
#include "Simulation.h"

enum class ButtonEvents : char {
	SIMULATION_START,
	MAP_EDITOR,
	WINDOW_CLOSE,
	DO_NOTHING,
};

class Button
{
private:

	sf::Text text;
	sf::Vector2f size;
	const int DISTANCE = 80;
	const int MAX_SIZE = 50; 
	int choosenSize; //Rozmiar bazowy przycisku
	int currentSize; //Rozmiar obecny przycisku
	const int SPEED = 100; //Prêdkoœæ zmiany rozmiary przycisku
	ButtonEvents buttonEvent;

public:

	bool coverage(sf::Vector2i mousePosition);  //Sprawdzanie czy kursor myszy wskazuje na przycisk

	void update(const float dt, Simulation* simulation); //Zmiana wielkoœci przycisku w zale¿noœci od po³o¿enia kursora

	void draw(sf::RenderWindow* window);
	ButtonEvents getEvent();
	Button(const std::string& name, sf::Font* font, ButtonEvents buttonEvent, unsigned int fontSize);
	Button(const std::string& name, sf::Font* font, Button* button, ButtonEvents buttonEvent, unsigned int fontSize);
	~Button();
};

