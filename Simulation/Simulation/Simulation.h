#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include<stack>
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "TextureManager.h"
#include "SpriteDividedMenager.h"
#include "SimWindow.h"

class SimulationState;

class Simulation
{
private:

	void loadTextures();


public:

	std::stack<SimulationState*> states;

	SimWindow *window;
	TextureManager texmgr;
	SpriteDividedMenager sprDivMgr;

	sf::Sprite background;
	sf::Font* font;

	void pushState(SimulationState* state);
	void popState();
	void changeState(SimulationState* state);
	SimulationState* peekState();

	void simulationLoop();


	Simulation();
	~Simulation();
};

#endif //SIMULATION_HPP