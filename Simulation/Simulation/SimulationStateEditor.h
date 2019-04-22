#ifndef SIMULATION_STATE_EDITOR_HPP
#define SIMULATION_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "SimulationState.h"
#include "Map.h"
#include "SimView.h"


class SimulationStateEditor : public SimulationState
{
private:

	SimView gameView;
	sf::View guiView;

	Map* map;
	sf::Vector2f camPos;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();


	SimulationStateEditor(Simulation* simulation);
	~SimulationStateEditor();
};

#endif //SIMULATION_STATE_EDITOR_HPP