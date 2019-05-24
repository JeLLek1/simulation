#include "pch.h"
#include <vector>
#include <queue>

#include "ManAi.h"


sf::Vector2i ManAi::getNextStep()
{
	if (!this->destination.empty())
	{
		sf::Vector2i temp = this->destination.front();
		this->destination.pop_front();
		return temp;
	}
	else return sf::Vector2i(0, 0);
}

bool ManAi::dijkstraPath(ObjectType objectType, Map* map, sf::Vector2u start)
{
	std::vector<int> weight;
	weight.resize(map->mapWidth() * map->mapHeight(), -1);
	std::queue<sf::Vector2u> tileToCheck;
	weight[map->cordToTabPos(start)] = 0;
	tileToCheck.push(start);
	while (tileToCheck.size() > 0) {

	}
	return false;
}

void ManAi::clearDestination()
{
	this->destination.clear();
}

ManAi::ManAi()
{
	this->destination.push_front(sf::Vector2i(5, 49));
	this->destination.push_front(sf::Vector2i(30, 49));
	this->destination.push_front(sf::Vector2i(40, 4));
	this->destination.push_front(sf::Vector2i(30, 48));
	this->destination.push_front(sf::Vector2i(20, 28));
	this->destination.push_front(sf::Vector2i(10, 2));
	this->destination.push_front(sf::Vector2i(30, 48));
	this->destination.push_front(sf::Vector2i(50, 18));
	this->destination.push_front(sf::Vector2i(20, 48));
	this->destination.push_front(sf::Vector2i(49, 8));
}


ManAi::~ManAi()
{
}
