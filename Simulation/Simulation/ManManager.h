#pragma once
#include "pch.h"
#include "SpriteDividedMenager.h"
#include "SimView.h"
#include "SimulationStateEditor.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <string>

class ManManager
{

public:
	bool isCorrect(SimView* view, sf::Vector2f position, Map* map);
	unsigned int direction(sf::Vector2f position, sf::Vector2f destination);
	ManManager();
	~ManManager();
};