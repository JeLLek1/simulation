#ifndef SIMULATION_STATE_HPP
#define SIMULATION_STATE_HPP

#include "Simulation.h"

class SimulationState
{

public:

	Simulation* simulation;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
	SimulationState();
	~SimulationState();
};

#endif //SIMULATION_STATE_HPP