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

	sf::Vector2u getPosition();
	virtual void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep) = 0;
	virtual void update(const float dt) = 0;
	void setPos(sf::Vector2u pos, Map *map);
	StaticObject(const ObjectType objectType, Map *map);
	StaticObject(const ObjectType objectType, sf::Vector2u* pos);
};
