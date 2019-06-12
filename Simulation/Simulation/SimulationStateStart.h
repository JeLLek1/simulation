#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "SimulationState.h"
#include "Button.h"

class SimulationStateStart : public virtual SimulationState
{
private:
	
	sf::View view;
	std::list<Button*> buttons;

	void loadSimulation();
	void loadEditor();

public:
	
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual bool handleInput();


	SimulationStateStart(Simulation* simulation);
	~SimulationStateStart();
};
