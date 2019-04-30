#ifndef SIMULATION_STATE_EDITOR_HPP
#define SIMULATION_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "SimulationState.h"
#include "Map.h"
#include "SimView.h"


class SimulationStateEditor : public SimulationState
{
private:

	SimView gameView;
	sf::View guiView;

	Map* map;

	static const int
		TILE_SIZE_X = 52,
		TILE_SIZE_Y = 26;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	static sf::Vector2f cartToIso(sf::Vector2f cart, int map_size_x);
	static sf::Vector2f isoToCart(sf::Vector2f iso, int map_size_x);

	SimulationStateEditor(Simulation* simulation);
	~SimulationStateEditor();
};

#endif //SIMULATION_STATE_EDITOR_HPP