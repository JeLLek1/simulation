#pragma once
#include "StaticObject.h"
class StaticObjectResouces : public StaticObject
{
private:
	unsigned int version;
public:
	virtual void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep);
	virtual void update(const float dt);

	StaticObjectResouces(const ObjectType objectType, Map* map);
	~StaticObjectResouces();
};

