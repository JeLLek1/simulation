#include "pch.h"
#include "SimulationStateEditor.h"
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
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->window), sf::Vector2i(this->simulation->window->getSize()), this->map->mapSize.x);
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
		sf::Vector2i cart = sf::Vector2i(SimulationStateMain::isoToCart(mousePos, this->map->mapSize.x));
		if(cart.x>=0 && cart.x<this->map->mapSize.x && cart.y>=0 && cart.y<this->map->mapSize.y){
			if(this->typeOfBlock<5)
				this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = this->typeOfBlock;
			else
				this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = (this->typeOfBlock-4)*5;
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


	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin",1);

	this->map = new Map(50, 50);


	sf::Vector2f temp = SimulationStateMain::cartToIso(this->gameView.camPos, this->map->mapSize.x);
	this->gameView.setCenter(temp);

	delete fileMenager;
}

SimulationStateEditor::~SimulationStateEditor()
{
}
