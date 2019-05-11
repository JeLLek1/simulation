#pragma once
#include <list>
#include <SFML/Graphics.hpp>


class ManAi
{
	std::list<sf::Vector2i> destination;

public:
	sf::Vector2i getNextStep();
	ManAi();
	~ManAi();
};

