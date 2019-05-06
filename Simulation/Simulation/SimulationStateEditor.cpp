#include "pch.h"
#include "SimulationStateEditor.h"
#include "Simulation.h"
#include "BinaryFileMenager.h"
#include <iostream>
#include <fstream>

void SimulationStateEditor::draw(const float dt)
{
	this->simulation->window->clear(sf::Color::Color(123, 152, 181));
	this->simulation->window->setView(this->gameView);
	this->map->draw(
		this->simulation->window, dt,
		this->gameView.getCenter(),
		this->gameView.getSize(),
		this->simulation->sprDivMgr
	);
	this->simulation->window->setView(this->guiView);

	return;
}

void SimulationStateEditor::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->window), sf::Vector2i(this->simulation->window->getSize()), this->map->mapHeight());
}

void SimulationStateEditor::handleInput()
{
	//Uwaga potem usun¹æ. Od tej chwili zaczyna siê edytor mapy
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
			if (event.key.code == sf::Keyboard::Escape) {
				this->simulation->window->close();
			}
			else if (event.key.code > 25 && event.key.code < 36) {
				this->typeOfBlock = event.key.code - 26;
			}
			else if (event.key.code > 84 && event.key.code < 89) {
				this->typeOfBlock = event.key.code - 75;
			}
		}
		default:
			break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f mousePos = this->simulation->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulation->window), this->gameView);
		sf::Vector2i cart = sf::Vector2i(Simulation::isoToCart(mousePos, this->map->mapWidth()));
		if(cart.x>=0 && cart.x<this->map->mapWidth() && cart.y>=0 && cart.y<this->map->mapHeight()){
			if(this->typeOfBlock<5)
				this->map->returnTile(cart.x, cart.y)->partNumber = this->typeOfBlock;
			else
				this->map->returnTile(cart.x, cart.y)->partNumber = (this->typeOfBlock-4)*5;
		}
	}
	return;
}

SimulationStateEditor::SimulationStateEditor(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window->getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

	std::vector<Tile*> tiles;
	sf::Vector2u *mapSize = 0;
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 2);
	
	
	if (fileMenager->binary_p_read(tiles, mapSize) != 0) {
		mapSize = new sf::Vector2u(
			SimulationStateEditor::MAP_WIDTH,
			SimulationStateEditor::MAP_HEIGHT);
		this->map = new Map(mapSize);
	}
	else {
		this->map = new Map(mapSize, tiles);
	}


	sf::Vector2f temp = Simulation::cartToIso(this->gameView.camPos, this->map->mapWidth());
	this->gameView.setCenter(temp);

	this->typeOfBlock = 0;

	delete mapSize;
	delete fileMenager;
}

SimulationStateEditor::~SimulationStateEditor()
{
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 1);
	sf::Vector2u* mapSize = new sf::Vector2u(this->map->mapWidth(), this->map->mapHeight());
	fileMenager->binary_write(this->map->getTileReference(), mapSize);
	delete mapSize;
	delete fileMenager;
}
