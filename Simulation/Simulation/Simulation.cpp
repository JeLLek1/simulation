#include<stack>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include "pch.h"
#include "Simulation.h"
#include "SimulationState.h"
#include "TextureManager.h"


/* Pobieranie tekstury t�a */

void Simulation::loadTextures()
{
	texmgr.loadTexture(TextureNames::BACKGROUND, "resouces/menuBackground.png");

	texmgr.loadTexture(TextureNames::GRASS, "resouces/grass.png");
	sprDivMgr.loadSprite(TextureNames::GRASS, texmgr.getRef(TextureNames::GRASS), sf::Vector2u(52, 26), 1);

	font->loadFromFile("resouces/font.ttf");
}

/*  Pobieranie wska�nika do danego stanu i uk�adanie go na stosie  */

void Simulation::pushState(SimulationState* state)
{
	this->states.push(state);

	return;
}

 /* Usuwanie topowego stanu ze stosu */

void Simulation::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

 /* Usuwanie poprzedniego stan ze stosu o ile istnieje i dodawanie nowego, czyli zmiana stanu */

void Simulation::changeState(SimulationState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

 /* Zwracanie wskaznika do stanu znajduj�cego si� na szczycie stosu */

SimulationState* Simulation::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

/* Obliczanie okresu trwania jednej klatki i wysy�anie go do wymagaj�cych r�nicy czasu metod
   Wywo�ywanie stanu na szczycie stosu, oraz wyswietlanie */

void Simulation::simulationLoop()
{

	sf::Clock clock;

	while (this->window->isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window->clear(sf::Color::Black);
		peekState()->draw(dt);
		this->window->display();
	}
}

Simulation::Simulation()
{
	this->font = new sf::Font();

	this->loadTextures();

	this->window = new SimWindow();
	this->window->setFramerateLimit(60);

	this->background.setTexture(*this->texmgr.getRef(TextureNames::BACKGROUND));
}


Simulation::~Simulation()
{
	while (!this->states.empty()) popState();
}
