#pragma once
#include <SFML/Graphics.hpp>
#include "SimulationStateMain.h"
#include "SimView.h"
#include "Map.h"
#include "Simulation.h"
class SimulationStateEditor : public SimulationStateMain
{
private:
	unsigned int typeOfBlock;
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	SimulationStateEditor(Simulation* simulation);

	virtual ~SimulationStateEditor();
};

