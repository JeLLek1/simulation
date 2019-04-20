#ifndef SIMULATION_STATE_EDITOR_HPP
#define SIMULATION_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "SimulationState.h"


class SimulationStateEditor : public SimulationState
{
private:

	sf::View gameView;
	sf::View guiView;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();


	SimulationStateEditor(Simulation* simulation);
	~SimulationStateEditor();
};

#endif //SIMULATION_STATE_EDITOR_HPP