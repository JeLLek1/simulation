#include "pch.h"
#include "ManManager.h"

bool ManManager::isCorrect(SimView* view, sf::Vector2f position, Map* map)
{
	if (Simulation::cartToIso(position, map->mapHeight()).x >= (view->camPos.x - view->getSize().x / 2) &&
		Simulation::cartToIso(position, map->mapHeight()).x <= (view->camPos.x + view->getSize().x / 2) &&
		Simulation::cartToIso(position, map->mapWidth()).y <= (view->camPos.y + view->getSize().y / 2) &&
		Simulation::cartToIso(position, map->mapWidth()).y >= (view->camPos.y - view->getSize().y / 2))
		return true;
	else return false;
}

unsigned int ManManager::direction(sf::Vector2f position, sf::Vector2f destination)
{
	if (position.x < destination.x && position.y < destination.y) return 1; //prawy dol
	else if (position.x < destination.x && position.y > destination.y) return 2; //prawa gora
	else if (position.x > destination.x && position.y > destination.y) return 3; //lewa gora
	else if (position.x > destination.x && position.y < destination.y) return 2; //lewy dol
	else return 0;
}

ManManager::ManManager()
{
}

ManManager::~ManManager()
{
}
