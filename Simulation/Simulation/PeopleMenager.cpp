#include "pch.h"
#include "PeopleMenager.h"


void PeopleMenager::draw(SimView* simView, sf::View guiView, sf::RenderWindow* window, Map* map, SpriteDividedMenager* spriteMgr)
{
	this->population.front()->draw((simView), window, map, spriteMgr->getRef(TextureNames::MAN));

	for (auto const& i : staticObjects)
	{
		i->draw(window, spriteMgr->getRef(TextureNames::SOURCES), map->mapWidth(), spriteMgr->returnAnimationStep());
	}
}

void PeopleMenager::update(float dt)
{
	for (auto const& i : population)
	{
		i->update(dt);
	}
	for (auto const& i : staticObjects)
	{
		i->update(dt);
	}
}

PeopleMenager::PeopleMenager(Map* map)
{

	for (int i = 0; i < 1; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::WOOD, map);
		this->staticObjects.push_front(object);
	}
	for (int i = 0; i < 10; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::STONE, map);
		this->staticObjects.push_front(object);
	}
	for (int i = 0; i < 10; i++) {
		StaticObject* object = new StaticObjectFireplace(ObjectType::FIREPLACE, map);
		this->staticObjects.push_front(object);
	}

	this->ownedResouces.insert(std::pair<ObjectType, int>(ObjectType::STONE, 0));
	this->ownedResouces.insert(std::pair<ObjectType, int>(ObjectType::WOOD, 0));
	this->ownedResouces.insert(std::pair<ObjectType, int>(ObjectType::STRAWBERRY, 0));
	
	for (auto const& i : staticObjects)
	{
		//this->objectTypePosition.insert(std::pair<StaticObject*, sf::Vector2f>(i, i->getPosition()));
	}

	Man* man = new Man(sf::Vector2f(5, 5));
	this->population.push_front(man);
	man->setTask(Task::GETWOOD, map);
	
}


PeopleMenager::~PeopleMenager()
{
}
