#pragma once
#include <SFML/Graphics.hpp>
#include "SimulationStateMain.h"
#include "SimView.h"
#include "Map.h"
#include "Simulation.h"
class SimulationStateEditor : public SimulationState
{
private:
	static const unsigned int
		MAP_WIDTH = 50,
		MAP_HEIGHT = 50;
	unsigned int typeOfBlock;

	SimView gameView;
	sf::View guiView;

	Map* map;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	SimulationStateEditor(Simulation* simulation);

	~SimulationStateEditor();
};

