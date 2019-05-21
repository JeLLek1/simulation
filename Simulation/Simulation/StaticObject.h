#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteDividedMenager.h"
enum class ObjectType : char {
	NONE,
	WOOD,
	STONE,
	STRAWBERRY,
	FIREPLACE,
	WARECHOUSE
};

class StaticObject
{
private:
	sf::Vector2u posiotion;
	unsigned char partNumber;

public:

	void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, float dt);
	virtual void update(const float dt) = 0;
};

