#include<SFML/Graphics.hpp>

#include "pch.h"
#include <time.h>
#include <cstdlib>
#include "SimulationStateMain.h"
#include "SimulationState.h"
#include "BinaryFileMenager.h"
#include "StaticObjectResouces.h"
#include "StaticObjectFireplace.h"
#include <iostream>

void SimulationStateMain::draw(const float dt)
{
	this->simulation->getWindow()->clear(sf::Color::Color(123, 152, 181));
	this->simulation->getWindow()->setView(this->gameView);
	this->map->draw(
		this->simulation->getWindow(), dt,
		this->gameView.getCenter(),
		this->gameView.getSize(),
		this->simulation->getSprDivMgr()
	);

	this->population.front()->draw(&(this->gameView), this->simulation->getWindow(), this->map, this->simulation->getSprDivMgr()->getRef(TextureNames::MAN), dt);

	for (auto const& i : staticObjects)
	{
		i->draw(this->simulation->getWindow(), this->simulation->getSprDivMgr()->getRef(TextureNames::SOURCES), this->map->mapWidth(), this->simulation->getSprDivMgr()->returnAnimationStep());
	}

	return;
}

void SimulationStateMain::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->getWindow()), sf::Vector2i(this->simulation->getWindow()->getSize()), this->map->mapWidth());
	simulation->getSprDivMgr()->update(dt);


	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateMain::handleInput()
{
	sf::Event event;

	while (this->simulation->getWindow()->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				this->simulation->getWindow()->close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->getWindow()->close();
				break;
			}
			default:
				break;
		}
	}


	return;
}

SimulationStateMain::SimulationStateMain(Simulation* simulation)
{

	this->simulation = simulation;
	
	std::vector<Tile*> tiles;
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 2);
	sf::Vector2u* mapSize = 0;
	if (fileMenager->binary_p_read(tiles, mapSize) != 0) {
		std::cout << "Brak pliku z mapa, lub plik z mapa jest uszkodzony. Skorzystaj z edytora map, aby go stworzyc";
		mapSize = new sf::Vector2u(0,0);
		this->map = new Map(mapSize);
		this->simulation->getWindow()->close();
	}
	else {
		this->map = new Map(mapSize, tiles);
		sf::Vector2f pos = sf::Vector2f(this->simulation->getWindow()->getSize());
		this->guiView.setSize(pos);
		this->gameView.setSize(pos);
		pos *= 0.5f;
		this->guiView.setCenter(pos);
		sf::Vector2f temp = Simulation::cartToIso(this->gameView.getCamPos(), this->map->mapWidth());
		this->gameView.setCenter(temp);

	}
	delete mapSize;
	delete fileMenager;




	for (int i = 0; i < 10; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::WOOD, this->map);
		this->staticObjects.push_front(object);
	}
	for (int i = 0; i < 10; i++) {
		StaticObject* object = new StaticObjectResouces(ObjectType::STONE, this->map);
		this->staticObjects.push_front(object);
	}
	for (int i = 0; i < 10; i++) {
		StaticObject* object = new StaticObjectFireplace(ObjectType::FIREPLACE, this->map);
		this->staticObjects.push_front(object);
	}


	Man* man = new Man(sf::Vector2f(10, 10));
	man->setPath(ObjectType::WOOD, this->map);
	this->population.push_front(man);
}


SimulationStateMain::~SimulationStateMain()
{
}
