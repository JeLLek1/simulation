#include "pch.h"
#include "Simulation.h"
#include "SimulationStateStart.h"

int main()
{
	Simulation simulation;

	simulation.pushState(new SimulationStateStart(&simulation));
	simulation.simulationLoop();

	return 0;
}