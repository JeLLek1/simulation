#ifndef SIMULATION_STATE_START_HPP
#define SIMULATION_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "SimulationState.h"

class SimulationStateStart : public SimulationState
{
private:
	
	sf::View view;

	void loadSimulation();

public:
	
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();


	SimulationStateStart(Simulation* simulation);
	~SimulationStateStart();
};

#endif //SIMULATION_STATE_START_HPP