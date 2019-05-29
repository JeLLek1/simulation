#pragma once
#include "Man.h"
#include "StaticObject.h"
#include "StaticObjectResouces.h"
#include "StaticObjectFireplace.h"
#include "ResouceType.h"
#include "map"

class PeopleMenager
{
private:
	std::list<Man*> population;
	std::list<StaticObject*> staticObjects;
	//std::map<StaticObject*, sf::Vector2f> objectTypePosition;
	std::map<Man*, sf::Vector2f> objectManPosition;
	std::map<ResouceType, int> ownedResouces;
public:
	void draw(SimView* simView, sf::View guiView, sf::RenderWindow* window, Map* map, SpriteDividedMenager* spriteMgr);
	void update(float dt);
	PeopleMenager(Map* map);
	~PeopleMenager();
};

