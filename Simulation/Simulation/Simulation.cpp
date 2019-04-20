#include<stack>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include "pch.h"
#include "Simulation.h"
#include "SimulationState.h"
#include "TextureManager.h"


void Simulation::loadTextures()
{
	texmgr.loadTexture("background", "background.png"); //Do zmiany!
}

void Simulation::pushState(SimulationState* state)
{
	this->states.push(state);

	return;
}

void Simulation::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Simulation::changeState(SimulationState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

SimulationState* Simulation::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Simulation::simulationLoop()
{

	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::Blue);
		peekState()->draw(dt);
		this->window.display();
	}
}


Simulation::Simulation()
{
	this->loadTextures();

	this->window.create(sf::VideoMode(800, 600), "Simple Simulation");
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texmgr.getRef("background"));
}


Simulation::~Simulation()
{
	while (!this->states.empty()) popState();
}
