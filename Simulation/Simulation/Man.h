#pragma once
#include <SFML/Graphics.hpp>
#include"pch.h"
#include "SpriteDividedMenager.h"
#include "SimView.h"
#include "Map.h"
#include "ManAi.h"
#include "Simulation.h"
#include <iostream>
enum class Task : char {
	NONE,
	GETWOOD,
	GETSTONE,
	BUILDFIREPLACE,
	RETURNRESOURCE
};
class Man
{
private:
	unsigned int hp;
	Task currentTask;
	sf::Vector2f currentPosition;
	sf::Vector2f destination;
	ManAi* manAi;
	bool going;

	const float COOLDOWN = 5.f;
	const float SPEED = 0.125;
	float actualWait;

	unsigned int direction();
	bool isCorrect(Map* map, SimView* view);
	
public:
	void draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite);
	sf::Vector2f getCurrentPosition();
	void update(float dt);
	bool setPath(ObjectType objectType, Map* map);
	Task returnTask();
	void setTask(Task task, Map *map);

	Man(sf::Vector2f currentPosition);
	Man();
	~Man();
};