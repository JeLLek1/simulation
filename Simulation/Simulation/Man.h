#pragma once
#include <SFML/Graphics.hpp>
#include"pch.h"
#include "SpriteDividedMenager.h"
#include "SimView.h"
#include "Map.h"
#include "ManAi.h"
#include "Simulation.h"
#include "ResouceType.h"


enum class Task : char {
	NONE,
	GETWOOD,
	GETSTONE,
	GETFOOD,
	BUILDFIREPLACE,
	RETURNRESOURCE
};


class Man
{
private:
	Task currentTask;
	sf::Vector2f currentPosition;
	sf::Vector2f destination;
	ManAi* manAi;
	bool going;
	ResouceType pocket;
	unsigned int last;


	const float COOLDOWN = 1.f;
	const float SPEED = 1;
	float actualWait;

	unsigned int direction();
	
public:

	ResouceType getPocket();
	void draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite);
	sf::Vector2f getCurrentPosition();
	Task update(float dt, Map* map);
	bool setPath(ObjectType objectType, Map* map, sf::Vector2u end = sf::Vector2u(0, 0));
	Task returnTask();
	void setTask(Task task, Map *map);

	Man(sf::Vector2f currentPosition);
	Man();
	~Man();
};