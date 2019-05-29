#include "pch.h"
#include "SimulationStateEditor.h"
#include "Simulation.h"
#include "BinaryFileMenager.h"
#include <cmath>
#include <iostream>
#include <fstream>

void SimulationStateEditor::draw(const float dt)
{
	this->simulation->getWindow()->clear(sf::Color::Color(123, 152, 181));
	this->simulation->getWindow()->setView(this->gameView);
	this->map->draw(
		this->simulation->getWindow(), dt,
		this->gameView.getCenter(),
		this->gameView.getSize(),
		this->simulation->getSprDivMgr()
	);
	this->wareHouse->draw(this->simulation->getWindow(), this->simulation->getSprDivMgr()->getRef(TextureNames::SOURCES), this->map->mapWidth(), this->simulation->getSprDivMgr()->returnAnimationStep());
	this->fireplace->draw(this->simulation->getWindow(), this->simulation->getSprDivMgr()->getRef(TextureNames::SOURCES), this->map->mapWidth(), this->simulation->getSprDivMgr()->returnAnimationStep());

	return;
}

void SimulationStateEditor::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->getWindow()), sf::Vector2i(this->simulation->getWindow()->getSize()), this->map->mapHeight());
	simulation->getSprDivMgr()->update(dt);
}

void SimulationStateEditor::handleInput()
{
	//Uwaga potem usun¹æ. Od tej chwili zaczyna siê edytor mapy
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
			if (event.key.code == sf::Keyboard::Escape) {
				this->simulation->getWindow()->close();
			}
			else if (event.key.code > 25 && event.key.code < 36) {
				this->typeOfBlock = event.key.code - 26;
			}
			else if (event.key.code > 84 && event.key.code < 89) {
				this->typeOfBlock = event.key.code - 75;
			}
		}
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right) {
				sf::Vector2f mousePos = this->simulation->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->simulation->getWindow()), this->gameView);
				sf::Vector2u cart = sf::Vector2u(std::round(Simulation::isoToCart(mousePos, this->map->mapWidth()).x), std::round(Simulation::isoToCart(mousePos, this->map->mapWidth()).y));

				if (!this->map->returnTile(cart)->returnCollision() && cart.x >= 0 && cart.x < this->map->mapWidth() && cart.y >= 0 && cart.y < this->map->mapHeight()){
					if (this->typeOfBlock == 1) {
						this->fireplace->setPos(cart, this->map);
					}
					else {
						this->wareHouse->setPos(cart, this->map);
					}
				}
			}
		break;
		default:
			break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f mousePos = this->simulation->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->simulation->getWindow()), this->gameView);
		sf::Vector2u cart = sf::Vector2u(std::round(Simulation::isoToCart(mousePos, this->map->mapWidth()).x), std::round(Simulation::isoToCart(mousePos, this->map->mapWidth()).y));
		if(((cart.x != wareHouse->getPosition().x && cart.y != wareHouse->getPosition().y) || (cart.x != fireplace->getPosition().x && cart.y != fireplace->getPosition().y))
			&& cart.x>=0 && cart.x<this->map->mapWidth() && cart.y>=0 && cart.y<this->map->mapHeight()){
			if(this->typeOfBlock<5)
				this->map->returnTile(cart)->setPart(this->typeOfBlock);
			else
				this->map->returnTile(cart)->setPart((this->typeOfBlock-4)*5);
		}
	}
	return;
}

SimulationStateEditor::SimulationStateEditor(Simulation* simulation)
{
	this->fireplace = NULL;
	this->wareHouse = NULL;
	this->simulation = simulation;
	sf::Vector2f pos = sf::Vector2f(this->simulation->getWindow()->getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);

	std::vector<Tile*> tiles;
	sf::Vector2u *mapSize = 0;
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 2);
	
	int error = fileMenager->binary_p_read(tiles, mapSize, this->fireplace, this->wareHouse) != 0;
	
	if (error !=0) {
		mapSize = new sf::Vector2u(
			SimulationStateEditor::MAP_WIDTH,
			SimulationStateEditor::MAP_HEIGHT);
		this->map = new Map(mapSize);
		if (error == 3) {
			delete this->fireplace;
			delete this->wareHouse;
		}
		this->fireplace = new StaticObjectFireplace(ObjectType::FIREPLACE, map);
		this->wareHouse = new StaticObjectResouces(ObjectType::WARECHOUSE, map);
	}
	else {
		this->map = new Map(mapSize, tiles);
	}


	sf::Vector2f temp = Simulation::cartToIso(this->gameView.getCamPos(), this->map->mapWidth());
	this->gameView.setCenter(temp);

	this->typeOfBlock = 0;

	delete mapSize;
	delete fileMenager;
}

SimulationStateEditor::~SimulationStateEditor()
{
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 1);
	sf::Vector2u* mapSize = new sf::Vector2u(this->map->mapWidth(), this->map->mapHeight());
	fileMenager->binary_write(this->map->getTileReference(), mapSize, this->fireplace, this->wareHouse);
	delete mapSize;
	delete fileMenager;
}
