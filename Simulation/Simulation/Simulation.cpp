#include<stack>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include "pch.h"
#include "Simulation.h"
#include "SimulationState.h"
#include "TextureManager.h"


/* Pobieranie tekstury t³a */

void Simulation::loadTextures()
{
	texmgr.loadTexture(TextureNames::BACKGROUND, "resouces/menuBackground.png");

	texmgr.loadTexture(TextureNames::GROUND, "resouces/ground.png");
	sprDivMgr.loadSprite(TextureNames::GROUND, texmgr.getRef(TextureNames::GROUND), sf::Vector2u(52, 26), 50);

	texmgr.loadTexture(TextureNames::GROUND, "resouces/ground.png");
	sprDivMgr.loadSprite(TextureNames::GROUND, texmgr.getRef(TextureNames::GROUND), sf::Vector2u(52, 26), 50);

	texmgr.loadTexture(TextureNames::MAN, "resouces/man.png");
	sprDivMgr.loadSprite(TextureNames::MAN, texmgr.getRef(TextureNames::MAN), sf::Vector2u(52, 78), 24);

	font->loadFromFile("resouces/font.ttf");
}

/*  Pobieranie wskaŸnika do danego stanu i uk³adanie go na stosie  */

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

 /* Zwracanie wskaznika do stanu znajduj¹cego siê na szczycie stosu */

SimulationState* Simulation::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

/* Obliczanie okresu trwania jednej klatki i wysy³anie go do wymagaj¹cych ró¿nicy czasu metod
   Wywo³ywanie stanu na szczycie stosu, oraz wyswietlanie */

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

sf::Vector2f Simulation::cartToIso(sf::Vector2f cart, int map_size_x)
{
	return sf::Vector2f(
		(cart.x - cart.y) * Simulation::TILE_SIZE_Y + map_size_x * Simulation::TILE_SIZE_Y,
		(cart.x + cart.y) * Simulation::TILE_SIZE_Y * 0.5
	);
}

sf::Vector2f Simulation::isoToCart(sf::Vector2f iso, int map_size_x)
{
	return sf::Vector2f(
		iso.y / Simulation::TILE_SIZE_Y + iso.x / (2 * Simulation::TILE_SIZE_Y) - map_size_x * 0.5f + 0.5f,
		iso.y / Simulation::TILE_SIZE_Y - iso.x / (2 * Simulation::TILE_SIZE_Y) + map_size_x * 0.5f + 0.5f
	);
}

Simulation::~Simulation()
{
	while (!this->states.empty()) {
		this->popState();
	}
}
