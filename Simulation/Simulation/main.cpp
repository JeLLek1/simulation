#include "pch.h"
#include "SimulationStateStart.h"

int WinMain()
{
	Simulation *simulation = new Simulation();
	simulation->pushState(new SimulationStateStart(simulation));
	simulation->simulationLoop();
	delete simulation;
	return 0;
}