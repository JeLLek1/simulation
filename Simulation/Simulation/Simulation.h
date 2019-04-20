#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include<stack>
#include<SFML/Graphics.hpp>
#include "TextureManager.h"

class SimulationState;

class Simulation
{
private:

	void loadTextures();


public:

	std::stack<SimulationState*> states;

	sf::RenderWindow window;
	TextureManager texmgr;
	sf::Sprite background;

	void pushState(SimulationState* state);
	void popState();
	void changeState(SimulationState* state);
	SimulationState* peekState();

	void simulationLoop();


	Simulation();
	~Simulation();
};

#endif //SIMULATION_HPP