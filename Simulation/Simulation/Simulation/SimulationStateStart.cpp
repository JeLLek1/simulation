#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

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
	this->simulation->window->setView(this->view);
	this->simulation->window->clear(sf::Color::Black);
	this->simulation->window->draw(this->simulation->background);
	for (auto const& i : buttons) 
	{
		i->draw(simulation->window);
	}
	return;
}

void SimulationStateStart::update(const float dt)
{
	for (auto const& i : buttons)
	{
		i->update(dt, simulation);
	}
	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateStart::handleInput()
{
	sf::Event event;

	while (this->simulation->window->pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
			{
				simulation->window->close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->window->close();
				else if (event.key.code == sf::Keyboard::Space)
					this->loadSimulation();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if ((event.mouseButton.button==sf::Mouse::Left) && buttons.back()->coverage(sf::Mouse::getPosition(*this->simulation->window)))
					this->simulation->window->close();
				if ((event.mouseButton.button == sf::Mouse::Left) && buttons.front()->coverage(sf::Mouse::getPosition(*this->simulation->window)))
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
	sf::Vector2f pos = sf::Vector2f(this->simulation->window->getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	buttons.push_back(new Button("START", simulation->font, 40));
	buttons.push_back(new Button("EXIT", simulation->font, buttons.back(), 40));
}


SimulationStateStart::~SimulationStateStart()
{
}
