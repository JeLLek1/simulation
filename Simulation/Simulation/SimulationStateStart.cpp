#include <SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationState.h"
#include "SimulationStateStart.h"
#include "SimulationStateEditor.h"

void SimulationStateStart::loadSimulation()
{
	this->simulation->pushState(new SimulationStateEditor(this->simulation));

	return;
}

void SimulationStateStart::draw(const float dt)
{
	this->simulation->window.setView(this->view);
	this->simulation->window.clear(sf::Color::Black);
	this->simulation->window.draw(this->simulation->background);

	return;
}

void SimulationStateStart::update(const float dt)
{
	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateStart::handleInput()
{
	sf::Event event;

	while (this->simulation->window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
			{
				simulation->window.close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->window.close();
				else if (event.key.code == sf::Keyboard::Space)
					this->loadSimulation();
				break;
			}
			default: 
				break;
		}
	}

	return;
}

SimulationStateStart::SimulationStateStart(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}


SimulationStateStart::~SimulationStateStart()
{
}
