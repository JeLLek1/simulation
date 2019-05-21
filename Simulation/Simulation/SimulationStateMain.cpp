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
	this->simulation->window->clear(sf::Color::Color(123, 152, 181));
	this->simulation->window->setView(this->gameView);
	this->map->draw(
		this->simulation->window, dt, 
		this->gameView.getCenter(),
		this->gameView.getSize(),
		this->simulation->sprDivMgr
	);

	this->population.front()->draw(&(this->gameView), this->simulation->window, this->map, this->simulation->sprDivMgr.getRef(TextureNames::MAN), dt);

	for (auto const& i : staticObjects)
	{
		i->draw(this->simulation->window, this->simulation->sprDivMgr.getRef(TextureNames::SOURCES), this->map->mapWidth(), this->simulation->sprDivMgr.returnAnimationStep());
	}

	return;
}

void SimulationStateMain::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->window), sf::Vector2i(this->simulation->window->getSize()), this->map->mapWidth());
	simulation->sprDivMgr.update(dt);


	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateMain::handleInput()
{
	sf::Event event;

	while (this->simulation->window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				this->simulation->window->close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->window->close();
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
	Man* man = new Man(sf::Vector2f(10, 10));
	this->population.push_front(man);

	this->simulation = simulation;
	
	std::vector<Tile*> tiles;
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 2);
	sf::Vector2u* mapSize = 0;
	if (fileMenager->binary_p_read(tiles, mapSize) != 0) {
		std::cout << "Brak pliku z mapa, lub plik z mapa jest uszkodzony. Skorzystaj z edytora map, aby go stworzyc";
		mapSize = new sf::Vector2u(0,0);
		this->map = new Map(mapSize);
		this->simulation->window->close();
	}
	else {
		this->map = new Map(mapSize, tiles);
		sf::Vector2f pos = sf::Vector2f(this->simulation->window->getSize());
		this->guiView.setSize(pos);
		this->gameView.setSize(pos);
		pos *= 0.5f;
		this->guiView.setCenter(pos);
		this->gameView.setCenter(pos);
		sf::Vector2f temp = Simulation::cartToIso(this->gameView.camPos, this->map->mapWidth());
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
}


SimulationStateMain::~SimulationStateMain()
{
}
