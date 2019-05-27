#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "ObjectType.h"

class ManAi
{
	std::list<sf::Vector2i> destination;

public:
	sf::Vector2i getNextStep(sf::Vector2i currenPos);
	bool dijkstraPath(ObjectType objectType, Map* map, sf::Vector2u start);
	void clearDestination();
	ManAi();
	~ManAi();
};

