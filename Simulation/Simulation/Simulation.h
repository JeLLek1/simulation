#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include<stack>
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include<iostream>
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

	std::stack<SimulationState*> states;

	SimWindow *window;

	SpriteDividedMenager* sprDivMgr;
	TextureManager* texmgr;
	sf::Sprite background;
	sf::Font* font;

public:

	SpriteDividedMenager* getSprDivMgr();
	sf::Font* getFont();
	sf::Sprite getBackground();

	SimWindow* getWindow();

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