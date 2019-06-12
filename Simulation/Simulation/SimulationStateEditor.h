#pragma once
#include <SFML/Graphics.hpp>
#include "SimulationStateMain.h"
#include "SimView.h"
#include "Map.h"
#include "Simulation.h"
#include "StaticObjectResouces.h"
#include "StaticObjectFireplace.h"
class SimulationStateEditor : public SimulationState
{
private:
	//Wymiary mapy gdy brakuje pliku
	static const unsigned int
		MAP_WIDTH = 30,
		MAP_HEIGHT = 30;
	//Zmienna przechowuj¹ca typ bloku
	unsigned int typeOfBlock;

	SimView gameView;
	sf::View guiView;

	StaticObjectFireplace* fireplace;
	StaticObjectResouces* wareHouse;

	Map* map;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual bool handleInput();

	SimulationStateEditor(Simulation* simulation);

	~SimulationStateEditor();
};

