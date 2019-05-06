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

	static const int
		TILE_SIZE_X = 52,
		TILE_SIZE_Y = 26;
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

	static sf::Vector2f cartToIso(sf::Vector2f cart, int map_size_x);
	static sf::Vector2f isoToCart(sf::Vector2f iso, int map_size_x);


	Simulation();
	~Simulation();
};

#endif //SIMULATION_HPP