#pragma once
#include "StaticObject.h"

class StaticObjectFireplace : public StaticObject
{
public:
	virtual void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep);
	virtual void update(const float dt);

	StaticObjectFireplace(const ObjectType objectType, Map* map);
	StaticObjectFireplace(const ObjectType objectType, sf::Vector2u* pos);
	~StaticObjectFireplace();
};

