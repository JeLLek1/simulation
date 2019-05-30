#include "pch.h"
#include "SimulationStateStart.h"
#include <iostream>

int main()
{
	Simulation *simulation = new Simulation();
	simulation->pushState(new SimulationStateStart(simulation));
	simulation->simulationLoop();
	delete simulation;
	return 0;
}