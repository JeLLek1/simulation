#include<SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationStateMain.h"
#include "SimulationState.h"

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

	return;
}

void SimulationStateMain::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->window), sf::Vector2i(this->simulation->window->getSize()), this->map->mapSize.x);
	return;
}

/* Pobieranie i obsługiwanie poleceń */

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


sf::Vector2f SimulationStateMain::cartToIso(sf::Vector2f cart, int map_size_x)
{
	return sf::Vector2f(
		(cart.x - cart.y) * SimulationStateMain::TILE_SIZE_Y + map_size_x * SimulationStateMain::TILE_SIZE_Y,
		(cart.x + cart.y) * SimulationStateMain::TILE_SIZE_Y * 0.5
	);
}

sf::Vector2f SimulationStateMain::isoToCart(sf::Vector2f iso, int map_size_x)
{
	return sf::Vector2f(
		iso.y / SimulationStateMain::TILE_SIZE_Y + iso.x / (2 * SimulationStateMain::TILE_SIZE_Y) - map_size_x * 0.5f + 0.5f,
		iso.y / SimulationStateMain::TILE_SIZE_Y - iso.x / (2 * SimulationStateMain::TILE_SIZE_Y) + map_size_x * 0.5f + 0.5f
	);
}

SimulationStateMain::SimulationStateMain()
{
}

SimulationStateMain::SimulationStateMain(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window->getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

	this->map = new Map(50, 50);
	sf::Vector2f temp = SimulationStateMain::cartToIso(this->gameView.camPos, this->map->mapSize.x);
	this->gameView.setCenter(temp);
}


SimulationStateMain::~SimulationStateMain()
{
}
