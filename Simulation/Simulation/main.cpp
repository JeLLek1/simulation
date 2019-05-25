#include "pch.h"
#include "SimulationStateStart.h"
#include <iostream>

int main()
{
	Simulation *simulation = new Simulation();
	simulation->pushState(new SimulationStateStart(simulation));
	simulation->simulationLoop();
	std::cout << "XD";
	delete simulation;
	std::cout << "XD1";
	return 0;
}