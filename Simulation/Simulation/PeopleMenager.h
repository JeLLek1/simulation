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
	void drawGUI(sf::View* guiView, sf::RenderWindow* window, SpriteDividedMenager* spriteMgr, sf::Font* font);
	void draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDividedMenager* spriteMgr);
	void update(float dt, Map* map);
	PeopleMenager(Map* map, StaticObjectFireplace *fireplace, StaticObjectResouces *warehouse);
	~PeopleMenager();
};

