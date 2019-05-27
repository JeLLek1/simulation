#pragma once
#include <SFML/Graphics.hpp>
#include"pch.h"
#include "SpriteDividedMenager.h"
#include "SimView.h"
#include "Map.h"
#include "ManAi.h"
#include "Simulation.h"
#include <iostream>

class Man
{
private:
	unsigned int hp;
	std::string currentTask;
	sf::Vector2f currentPosition;
	sf::Vector2f destination;
	ManAi* manAi;

	unsigned int direction();
	bool isCorrect(Map* map, SimView* view);
	
public:
	void draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite, float dt);
	void update(float dt);
	bool setPath(ObjectType objectType, Map* map);
	Man(sf::Vector2f currentPosition);
	Man();
	~Man();
};