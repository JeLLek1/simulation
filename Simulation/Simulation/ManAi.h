#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "ObjectType.h"

class ManAi
{
	std::list<sf::Vector2u> destination;

public:
	sf::Vector2u getNextStep(sf::Vector2u currenPos);
	bool dijkstraPath(ObjectType objectType, Map* map, sf::Vector2u start, sf::Vector2u end, bool seatchToEnd);
	void clearDestination();
	ManAi();
	~ManAi();
};

