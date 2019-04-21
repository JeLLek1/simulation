#include<SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationStateEditor.h"
#include "SimulationState.h"

void SimulationStateEditor::draw(const float dt)
{

	this->simulation->window->clear(sf::Color::Black);
	this->simulation->window->setView(gameView);
	std::cout << this->gameView.getCenter().x << " " << this->gameView.getCenter().y << std::endl;
	this->map->draw(this->simulation->window, dt, sf::Vector2i(static_cast<int>(this->camPos.x), static_cast<int>(this->camPos.y)), this->simulation->sprDivMgr);

	return;
}

void SimulationStateEditor::update(const float dt)
{
	return;
}

/* Pobieranie i obs³ugiwanie poleceñ */

void SimulationStateEditor::handleInput()
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
			
			default:
				break;
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

	this->map = new Map(100, 100);
	//Uwaga tutaj 50 potem zmienie na wartoœæ z jakiejœ klasy, po prostu chce sprawdziæ czy dzia³a jak coœ to jest y
	this->camPos = sf::Vector2f(50, 50);
	sf::Vector2f temp = sf::Vector2f((camPos.x - camPos.y) * 26 + this->map->mapSize.x * 26, (camPos.x + camPos.y) * 26 * 0.5);
	this->gameView.setCenter(temp);
}


SimulationStateEditor::~SimulationStateEditor()
{
}
