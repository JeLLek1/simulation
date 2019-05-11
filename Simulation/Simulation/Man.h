#pragma once
#include <SFML/Graphics.hpp>
#include"pch.h"
#include "SpriteDividedMenager.h"
#include "SimView.h"
#include "Map.h"
#include "ManManager.h"
#include "ManAi.h"
#include "Simulation.h"
#include <iostream>

class Man
{
private:
	TextureNames texname;
	unsigned int hp;
	std::string currentTask;
	sf::Vector2f currentPosition;
	sf::Vector2f destination;
	ManAi* manAi;

public:
	void draw(SimView* simView, sf::RenderWindow* window, Map* map, SpriteDivided* sprite, float dt, unsigned int mapWidth);
	void update(float dt);
	Man(sf::Vector2f currentPosition);
	Man();
	~Man();
};