#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteDividedMenager.h"
#include "ObjectType.h"
#include "Map.h"

class StaticObject
{
protected:
	//Wersja spritea (dla kilku rodzajów spriteów jak drzewo, kamieñ)
	//Typ obiektu
	ObjectType objectType;
	//Pozycja na mapie
	sf::Vector2u posiotion;
public:

	virtual void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep) = 0;
	virtual void update(const float dt) = 0;
	StaticObject(const ObjectType objectType, Map *map);
};
