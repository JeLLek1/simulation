#ifndef SIMULATION_STATE_EDITOR_HPP
#define SIMULATION_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "SimulationState.h"
#include "Map.h"
#include "SimView.h"
#include "Man.h"



class SimulationStateMain : public virtual SimulationState
{
protected:

	std::list<Man*> population;

	SimView gameView;
	sf::View guiView;

	Map* map;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	SimulationStateMain(Simulation* simulation);
	~SimulationStateMain();
};

#endif //SIMULATION_STATE_EDITOR_HPP