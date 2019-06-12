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

//Rysowanie poszczególnych elemetnów 
void SimulationStateMain::draw(const float dt)
{
	this->simulation->getWindow()->clear(sf::Color::Color(123, 152, 181));
	//Widok mapy
	this->simulation->getWindow()->setView(this->gameView);
	this->map->draw(
		this->simulation->getWindow(), dt,
		this->gameView.getCenter(),
		this->gameView.getSize(),
		this->simulation->getSprDivMgr()
	);
	this->peopleManager->draw(&this->gameView, this->simulation->getWindow(), this->map, this->simulation->getSprDivMgr());
	//Widok gui
	this->simulation->getWindow()->setView(this->guiView);
	this->peopleManager->drawGUI(&this->guiView, this->simulation->getWindow(), this->simulation->getSprDivMgr(), this->simulation->getFont());
	if (!this->simulationRun) {
		sf::RectangleShape rectangle1(sf::Vector2f(static_cast<float>(this->guiView.getSize().x-50), 50));
		rectangle1.setFillColor(sf::Color(100, 150, 150));
		rectangle1.setPosition(sf::Vector2f(20, this->guiView.getSize().y/2 - rectangle1.getSize().y/2));
		this->simulation->getWindow()->draw(rectangle1);
		sf::Text text;
		sf::Vector2f textPos = (sf::Vector2f(50, this->guiView.getSize().y/2 - (text.getCharacterSize() + (30 - text.getCharacterSize())) / 2));
		text.setFont(*this->simulation->getFont());
		text.setFillColor(sf::Color::Green);
		text.setCharacterSize(20);
		text.setPosition(textPos);
		text.setString("Symulacja zakonczona sukcesem. Nacisnij dowolny przycisk klawiatury aby wrocic do menu...");
		this->simulation->getWindow()->draw(text);
	}
	return;
}

//Aktualizacja poszczególnych elementów w uzale¿nieniu od czasu
void SimulationStateMain::update(const float dt)
{
	if (this->simulationRun) {
		gameView.update(dt, sf::Mouse::getPosition(*this->simulation->getWindow()), sf::Vector2i(this->simulation->getWindow()->getSize()), this->map->mapWidth());
		simulation->getSprDivMgr()->update(dt);
		if (!this->peopleManager->update(dt, this->map)) {
			this->simulationRun = false;
		}
	}

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
				if (!this->simulationRun || event.key.code == sf::Keyboard::Escape)
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
	sf::Vector2u* warehousePos = NULL;
	sf::Vector2u* fireplacePos = NULL;
	//Czytanie z pliku binarnego. Je¿eli jest b³¹d to ka¿e przejœæ do edytora mapy
	int error = fileMenager->binary_p_read(tiles, mapSize, warehousePos, fireplacePos);
	if (error != 0) {
		std::cout << "Brak pliku z mapa, lub plik z mapa jest uszkodzony. Skorzystaj z edytora map, aby go stworzyc";
		mapSize = new sf::Vector2u(2,2);
		this->map = new Map(mapSize);
		this->simulation->getWindow()->close();
		warehousePos = new sf::Vector2u(0, 0);
		fireplacePos = new sf::Vector2u(0, 0);
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
	this->peopleManager = new PeopleMenager(this->map, warehousePos, fireplacePos);
	this->simulationRun = true;
	delete warehousePos;
	delete fireplacePos;
	delete mapSize;
	delete fileMenager;

}


SimulationStateMain::~SimulationStateMain()
{
	delete this->map;
	delete this->peopleManager;
}
