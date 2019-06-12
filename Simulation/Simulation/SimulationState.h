#pragma once

#include "Simulation.h"

class SimulationState
{
protected:

	Simulation* simulation;

public:
	
	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual bool handleInput() = 0;

	virtual ~SimulationState();
};
