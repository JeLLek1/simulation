#include<SFML/Graphics.hpp>

#include "pch.h"
#include "SimulationStateEditor.h"
#include "SimulationState.h"

#include <iostream>

void SimulationStateEditor::draw(const float dt)
{

	this->simulation->window->clear(sf::Color::Color(123, 152, 181));
	this->simulation->window->setView(gameView);
	this->map->draw(
		this->simulation->window, dt, 
		gameView.getCenter(),
		gameView.getSize(),
		this->simulation->sprDivMgr
	);

	return;
}

void SimulationStateEditor::update(const float dt)
{
	gameView.update(dt, sf::Mouse::getPosition(*this->simulation->window), sf::Vector2i(this->simulation->window->getSize()), this->map->mapSize.x);
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
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->simulation->window->close();
				break;
			}


			//Uwaga potem usun¹æ. Od tej chwili zaczyna siê edytor mapy
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos = this->simulation->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulation->window), this->gameView);
					sf::Vector2i cart = sf::Vector2i(SimulationStateEditor::isoToCart(mousePos, this->map->mapSize.x));
					switch (this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber)
					{
					case 1:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 2;
						break;
					case 2:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 3;
						break;
					case 3:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 4;
						break;
					default:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 1;
						break;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					sf::Vector2f mousePos = this->simulation->window->mapPixelToCoords(sf::Mouse::getPosition(*this->simulation->window), this->gameView);
					sf::Vector2i cart = sf::Vector2i(SimulationStateEditor::isoToCart(mousePos, this->map->mapSize.x));
					switch (this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber)
					{
					case 5:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 10;
						break;
					case 10:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 15;
						break;
					case 15:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 20;
						break;
					case 20:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 25;
						break;
					case 25:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 30;
						break;
					case 30:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 35;
						break;
					case 35:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 40;
						break;
					case 40:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 45;
						break;
					default:
						this->map->titles[cart.x + cart.y * this->map->mapSize.x]->partNumber = 5;
						break;
					}
				}
				break;
			//Uwaga potem usun¹æ. Od tej chwili zaczyna siê edytor mapy



			default:
				break;
		}
	}


	return;
}


sf::Vector2f SimulationStateEditor::cartToIso(sf::Vector2f cart, int map_size_x)
{
	return sf::Vector2f(
		(cart.x - cart.y) * SimulationStateEditor::TILE_SIZE_Y + map_size_x * SimulationStateEditor::TILE_SIZE_Y,
		(cart.x + cart.y) * SimulationStateEditor::TILE_SIZE_Y * 0.5
	);
}

sf::Vector2f SimulationStateEditor::isoToCart(sf::Vector2f iso, int map_size_x)
{
	return sf::Vector2f(
		iso.y / SimulationStateEditor::TILE_SIZE_Y + iso.x / (2 * SimulationStateEditor::TILE_SIZE_Y) - map_size_x * 0.5f + 0.5f,
		iso.y / SimulationStateEditor::TILE_SIZE_Y - iso.x / (2 * SimulationStateEditor::TILE_SIZE_Y) + map_size_x * 0.5f + 0.5f
	);
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

	this->map = new Map(50, 50);
	sf::Vector2f temp = SimulationStateEditor::cartToIso(this->gameView.camPos, this->map->mapSize.x);
	this->gameView.setCenter(temp);
}


SimulationStateEditor::~SimulationStateEditor()
{
}
