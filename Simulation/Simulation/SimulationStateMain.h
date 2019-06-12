#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "SimulationState.h"
#include "Map.h"
#include "SimView.h"
#include "PeopleMenager.h"



class SimulationStateMain : public virtual SimulationState
{
protected:

	PeopleMenager* peopleManager;
	
	SimView gameView;
	sf::View guiView;

	Map* map;

	bool simulationRun;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual bool handleInput();

	SimulationStateMain(Simulation* simulation);
	~SimulationStateMain();
};
