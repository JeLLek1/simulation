#pragma once
#include "StaticObject.h"
class StaticObjectResouces : public StaticObject
{
private:
	unsigned int version;
public:
	virtual void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep);

	StaticObjectResouces(const ObjectType objectType, Map* map);
	StaticObjectResouces(const ObjectType objectType, sf::Vector2u* pos);
	~StaticObjectResouces();
};

