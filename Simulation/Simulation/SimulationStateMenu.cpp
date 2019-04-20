#include<SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationStateMenu.h"
#include "SimulationStateEditor.h"

void SimulationStateMenu::loadSimulation()
{
	this->simulation->pushState(new SimulationStateEditor(this->simulation));

	return;
}

void SimulationStateMenu::draw(const float dt)
{
	this->simulation->window.setView(this->view);
	this->simulation->window.clear(sf::Color::Black);
	this->simulation->window.draw(this->simulation->background);

	return;
}

void SimulationStateMenu::update(const float dt)
{
	return;
}

void SimulationStateMenu::handleInput()
{
	sf::Event event;

	while (this->simulation->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			simulation->window.close();
			break;
		}

		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			this->simulation->background.setPosition(this->simulation->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			this->simulation->background.setScale(static_cast<float>(event.size.width) / static_cast<float>(this->simulation->background.getTexture()->getSize().x), static_cast<float>(event.size.height) / static_cast<float>(this->simulation->background.getTexture()->getSize().y));
			break;
		}

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				this->simulation->window.close();
			else if (event.key.code == sf::Mouse::Left&&1)                    //UZUPELNIC!!!!!!!
				this->loadSimulation();
			break;
		}
		default:
			break;
		}
	}

	return;
}

SimulationStateMenu::SimulationStateMenu(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}


SimulationStateMenu::~SimulationStateMenu()
{
}
