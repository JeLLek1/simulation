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

	this->simulation->getWindow()->setView(this->guiView);

	sf::Text text;
	sf::Vector2f textPos = (sf::Vector2f(20, 20));
	text.setFont(*this->simulation->getFont());
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(textPos);
	text.setString("Wersja bloku podloza:"+std::to_string(this->typeOfBlock));
	this->simulation->getWindow()->draw(text);
	textPos = (sf::Vector2f(20, (text.getCharacterSize() + 20)));
	text.setPosition(textPos);
	if(this->typeOfBlock == 1)
		text.setString("Blok interakcji: ognisko");
	else if(this->typeOfBlock == 2)
		text.setString("Blok interakcji: skladowisko");
	else
		text.setString("Blok interakcji: Brak");
	this->simulation->getWindow()->draw(text);
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
				if (this->typeOfBlock == 1 && cart.x >= 1 && cart.x < this->map->mapWidth()-1 && cart.y >= 1 && cart.y < this->map->mapHeight()-1 && !this->map->returnTile(cart)->returnCollision()){
					//Do sprawdzenia czy w okó³ ogniska jest pusto
					sf::Vector2u helper[8] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1), sf::Vector2u(1,1), sf::Vector2u(1,-1), sf::Vector2u(-1,1), sf::Vector2u(-1,-1) };
					bool test = true;
					for (int i = 0; i < 8; i++) {
						if (this->map->returnTile(cart + helper[i])->returnCollision()) {
						test = false;
						}
					}
					if(test)
						this->fireplace->setPos(cart, this->map);
				}
				else if (this->typeOfBlock == 2 && cart.x >= 0 && cart.x < this->map->mapWidth() && cart.y >= 0 && cart.y < this->map->mapHeight() && !this->map->returnTile(cart)->returnCollision()) {
					this->wareHouse->setPos(cart, this->map);

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
	this->guiView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
	this->guiView.setCenter(pos);

	std::vector<Tile*> tiles;
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 2);
	sf::Vector2u* mapSize = NULL;
	sf::Vector2u* warehousePos = NULL;
	sf::Vector2u* fireplacePos = NULL;
	int error = fileMenager->binary_p_read(tiles, mapSize, warehousePos, fireplacePos) != 0;
	
	if (error !=0) {
		mapSize = new sf::Vector2u(
			SimulationStateEditor::MAP_WIDTH,
			SimulationStateEditor::MAP_HEIGHT);
		this->map = new Map(mapSize);
		this->wareHouse = new StaticObjectResouces(ObjectType::WARECHOUSE, map);
		this->fireplace = new StaticObjectFireplace(ObjectType::FIREPLACE, map);
	}
	else {
		this->map = new Map(mapSize, tiles);
		this->wareHouse = new StaticObjectResouces(ObjectType::WARECHOUSE, warehousePos);
		this->fireplace = new StaticObjectFireplace(ObjectType::FIREPLACE, fireplacePos);
	}

	sf::Vector2f temp = Simulation::cartToIso(this->gameView.getCamPos(), this->map->mapWidth());
	this->gameView.setCenter(temp);

	this->typeOfBlock = 0;

	delete warehousePos;
	delete fireplacePos;
	delete mapSize;
	delete fileMenager;
}

SimulationStateEditor::~SimulationStateEditor()
{
	BinaryFileMenager* fileMenager = new BinaryFileMenager("resouces/map.bin", 1);
	sf::Vector2u* mapSize = new sf::Vector2u(this->map->mapWidth(), this->map->mapHeight());
	sf::Vector2u* warehousePos = new sf::Vector2u(this->wareHouse->getPosition());
	sf::Vector2u* fireplacePos = new sf::Vector2u(this->fireplace->getPosition());
	fileMenager->binary_write(this->map->getTileReference(), mapSize, warehousePos, fireplacePos);
	delete warehousePos;
	delete fireplacePos;
	delete mapSize;
	delete fileMenager;
	delete this->fireplace;
	delete this->wareHouse;
}
