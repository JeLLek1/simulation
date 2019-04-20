#include<SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationStateEditor.h"
#include "SimulationState.h"

void SimulationStateEditor::draw(const float dt)
{

	this->simulation->window.clear(sf::Color::Black);
	this->simulation->window.draw(this->simulation->background);

	return;
}

void SimulationStateEditor::update(const float dt)
{
	return;
}

void SimulationStateEditor::handleInput()
{
	sf::Event event;

	while (this->simulation->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				this->simulation->window.close();
				break;
			}
			case sf::Event::Resized:
			{
				gameView.setSize(event.size.width, event.size.height);
				guiView.setSize(event.size.width, event.size.height);
				this->simulation->background.setPosition(this->simulation->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
				this->simulation->background.setScale(float(event.size.width) / float(this->simulation->background.getTexture()->getSize().x), float(event.size.height) / float(this->simulation->background.getTexture()->getSize().y));
				break;
			}
			
			default:
				break;
		}
	}


	return;
}


SimulationStateEditor::SimulationStateEditor(Simulation* simulation)
{
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);
}


SimulationStateEditor::~SimulationStateEditor()
{
}
