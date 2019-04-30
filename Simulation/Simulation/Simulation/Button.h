#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <SFML/Graphics/Text.hpp>
#include "Simulation.h"


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

public:

	bool coverage(sf::Vector2i mousePosition);  //Sprawdzanie czy kursor myszy wskazuje na przycisk

	void update(const float dt, Simulation* simulation); //Zmiana wielkoœci przycisku w zale¿noœci od po³o¿enia kursora

	void draw(sf::RenderWindow* window);
	Button(const std::string& name, sf::Font* font, unsigned int fontSize);
	Button(const std::string& name, sf::Font* font, Button* button, unsigned int fontSize);
	~Button();
};

#endif // !BUTTON_HPP
