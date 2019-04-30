#ifndef SIMULATION_STATE_START_HPP
#define SIMULATION_STATE_START_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "SimulationState.h"
#include "Button.h"

class SimulationStateStart : public SimulationState
{
private:
	
	sf::View view;
	std::list<Button*> buttons;

	void loadSimulation();

public:
	
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();


	SimulationStateStart(Simulation* simulation);
	~SimulationStateStart();
};

#endif //SIMULATION_STATE_START_HPP