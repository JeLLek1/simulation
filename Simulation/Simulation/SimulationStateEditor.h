#pragma once
#include <SFML/Graphics.hpp>
#include "SimulationStateMain.h"
#include "SimView.h"
#include "Map.h"
#include "Simulation.h"
#include "StaticObjectResouces.h"
#include "StaticObjectFireplace.h"
class SimulationStateEditor : public SimulationState
{
private:
	static const unsigned int
		MAP_WIDTH = 30,
		MAP_HEIGHT = 30;
	unsigned int typeOfBlock;

	SimView gameView;

	StaticObjectFireplace* fireplace;
	StaticObjectResouces* wareHouse;

	Map* map;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	SimulationStateEditor(Simulation* simulation);

	~SimulationStateEditor();
};

