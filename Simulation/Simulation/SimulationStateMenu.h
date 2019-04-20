#ifndef SIMULATION_STATE_MENU_HPP
#define SIMULATION_STATE_MENU_HPP

#include <SFML/Graphics.hpp>

#include "SimulationState.h"
#include "SimulationStateEditor.h"

class SimulationStateMenu : public SimulationState
{
private:

	void loadSimulation();

	sf::View view;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	SimulationStateMenu(Simulation* simulation);
	~SimulationStateMenu();
};

#endif